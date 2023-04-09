#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

#define BUFFER_SIZE 1024

typedef struct {
    Elf64_Sym* symbol_table;
    char* string_table;
    int num_symbols;
} SymbolTable;

char get_symbol_type(Elf64_Sym symbol) {
    switch (symbol.st_info & 0xf) {
        case STT_NOTYPE:
            return ' ';
        case STT_OBJECT:
            return (symbol.st_shndx == SHN_COMMON) ? 'C' : ((symbol.st_shndx == SHN_ABS) ? 'A' : (symbol.st_shndx == SHN_UNDEF) ? 'U' : 'D');
        case STT_FUNC:
            return (symbol.st_shndx == SHN_UNDEF) ? 'U' : 'T';
        case STT_SECTION:
            return ' ';
        case STT_FILE:
            return ' ';
        case STT_COMMON:
            return 'C';
        case STT_TLS:
            return ' ';
        case STT_GNU_IFUNC:
            return 'i';
        default:
            return '?';
    }
}

void print_symbol_table(SymbolTable* table) {
    for (int i = 0; i < table->num_symbols; i++) {
        char type = get_symbol_type(table->symbol_table[i]);
        printf("%016lx %c %s\n", table->symbol_table[i].st_value, type, &table->string_table[table->symbol_table[i].st_name]);
    }
}

SymbolTable* read_symbol_table(int fd, Elf64_Ehdr header) {
    SymbolTable* table = malloc(sizeof(SymbolTable));

    // get section headers
    Elf64_Shdr section_headers[header.e_shnum];
    lseek(fd, header.e_shoff, SEEK_SET);
    read(fd, section_headers, sizeof(section_headers));

    // find symbol table and string table
    Elf64_Shdr symbol_table_header;
    Elf64_Shdr string_table_header;
    for (int i = 0; i < header.e_shnum; i++) {
        if (section_headers[i].sh_type == SHT_SYMTAB) {
            symbol_table_header = section_headers[i];
            string_table_header = section_headers[section_headers[i].sh_link];
            break;
        }
    }

    // read symbol table
    table->num_symbols = symbol_table_header.sh_size / sizeof(Elf64_Sym);
    table->symbol_table = malloc(table->num_symbols * sizeof(Elf64_Sym));
    lseek(fd, symbol_table_header.sh_offset, SEEK_SET);
    read(fd, table->symbol_table, symbol_table_header.sh_size);

    // read string table
    table->string_table = malloc(string_table_header.sh_size);
    lseek(fd, string_table_header.sh_offset, SEEK_SET);
    read(fd, table->string_table, string_table_header.sh_size);

    return table;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    Elf64_Ehdr header;
    read(fd, &header, sizeof(header));

    if (memcmp(header.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "%s is not an ELF file\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    SymbolTable* table = read_symbol_table(fd, header);
    print_symbol_table(table);

    free(table->symbol_table);
    free(table->string_table);
    free(table);

    close(fd);

    return EXIT_SUCCESS;
}

