#include <elf.h>

char symbol_type(Elf64_Sym* sym) {
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
        case STT_RELC:
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
            break;
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

