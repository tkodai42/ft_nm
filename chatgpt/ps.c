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
	Elf64_Sym *sym = &symbol;
//char symbol_type(Elf64_Sym* sym) {
    char type = '?';
    switch (ELF64_ST_TYPE(sym->st_info)) {
        case STT_NOTYPE:
            type = 'N';
            break;
        case STT_OBJECT:
            type = 'O';
            break;
        case STT_FUNC:
            type = 'T';
            break;
        case STT_SECTION:
            type = 'S';
            break;
        case STT_FILE:
            type = 'F';
            break;
        case STT_COMMON:
            type = 'C';
            break;
        case STT_TLS:
            type = 'V';
            break;
/*        case STT_RELC:
        case STT_REL:
            if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) {
                type = 'r';
            } else {
                type = 'R';
            }
            break;
        case STT_SHNDX:
            type = 'X';
            break;
        case STT_LOOS:
        case STT_HIOS:
            type = 'o';
            break;
        case STT_GNU_IFUNC:
            type = 'i';
            break;*/
        default:
            type = '?';
            break;
    }

    // Set visibility
    switch (ELF64_ST_VISIBILITY(sym->st_other)) {
        case STV_DEFAULT:
            break;
        case STV_INTERNAL:
            type = toupper(type);
            break;
        case STV_HIDDEN:
            type = 'h';
            break;
        case STV_PROTECTED:
            type = 't';
            break;
        default:
            break;
    }

    // Set special types
    if (sym->st_shndx == SHN_ABS) {
        type = 'A';
    } else if (sym->st_shndx == SHN_COMMON) {
        type = 'C';
    } else if (sym->st_shndx == SHN_UNDEF) {
        type = 'U';
    } else if (sym->st_shndx == SHN_ABS + 1) {
        type = 'a';
    } else if (sym->st_shndx == SHN_COMMON + 1) {
        type = 'c';
    } else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT) {
            type = 'V';
        } else if (ELF64_ST_TYPE(sym->st_info) == STT_FUNC) {
            type = 'W';
        }
    }

    return type;
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

