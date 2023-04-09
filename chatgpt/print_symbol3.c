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


char symbol_type(Elf64_Sym sym) {
    switch (ELF64_ST_TYPE(sym.st_info)) {
        case STT_NOTYPE:
            return 'U';
        case STT_OBJECT:
            return (sym.st_shndx == SHN_COMMON) ? 'C' : 'D';
        case STT_FUNC:
            return (sym.st_shndx == SHN_UNDEF) ? 'U' : 'T';
        case STT_SECTION:
            return 'S';
        case STT_FILE:
            return 'N';
        default:
            return '?';
    }
}

char symbol_binding(Elf64_Sym sym) {
    switch (ELF64_ST_BIND(sym.st_info)) {
        case STB_LOCAL:
            return 'l';
        case STB_GLOBAL:
            return 'g';
        case STB_WEAK:
            return (sym.st_shndx == SHN_UNDEF) ? 'u' : 'w';
        default:
            return '?';
    }
}

char symbol_visibility(Elf64_Sym sym) {
    switch (ELF64_ST_VISIBILITY(sym.st_other)) {
        case STV_DEFAULT:
            return ' ';
        case STV_INTERNAL:
            return 'i';
        case STV_HIDDEN:
            return 'h';
        case STV_PROTECTED:
            return 'p';
        default:
            return '?';
    }
}

char symbol_2(char type, char binding, char visibility) {
    switch (type) {
        case 'U':
        case 'C':
        case 'D':
        case 'T':
        case 'S':
        case 'N':
        case '?':
            break;
        default:
            return '?';
    }
    switch (binding) {
        case 'l':
        case 'g':
        case 'u':
        case 'w':
        case '?':
            break;
        default:
            return '?';
    }
    switch (visibility) {
        case ' ':
        case 'i':
        case 'h':
        case 'p':
            break;
        default:
            return '?';
    }
    return type | binding | visibility;
}

char	get_symbol_type(Elf64_Sym symbol)
{
	char type, binding, visibility;

	type = symbol_type(symbol);
	binding = symbol_binding(symbol);
	visibility = symbol_visibility(symbol);

	return symbol_2(type, binding, visibility);

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

