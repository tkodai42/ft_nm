#include <stdio.h>
#include <elf.h>

char get_symbol_type(unsigned char st_info, unsigned char st_other, unsigned short st_shndx) {
    switch (st_info & 0xf) {
        case STT_NOTYPE:
            switch (st_shndx) {
                case SHN_UNDEF: return "U";  // Undefined
                case SHN_ABS:   return "A";  // Absolute
                case SHN_COMMON:return "C";  // Common
                default:        return "?";
            }
            break;
        case STT_OBJECT:
            switch (st_shndx) {
                case SHN_UNDEF: return "U";  // Undefined
                case SHN_ABS:   return "A";  // Absolute
                case SHN_COMMON:return "C";  // Common
                default:
                    if ((st_other & 0x7) == STV_HIDDEN) {
                        return "i";  // Indirect
                    } else {
                        return "D";  // Data
                    }
            }
            break;
        case STT_FUNC:
            switch (st_shndx) {
                case SHN_UNDEF: return "U";  // Undefined
                case SHN_ABS:   return "A";  // Absolute
                case SHN_COMMON:return "C";  // Common
                default:
                    if ((st_other & 0x7) == STV_HIDDEN) {
                        return "t";  // Indirect
                    } else {
                        return "T";  // Text
                    }
            }
            break;
        case STT_SECTION:
            return "S";  // Section symbol
            break;
        case STT_FILE:
            return "f";  // File symbol
            break;
        case STT_COMMON:
            return "C";  // Common data
            break;
        case STT_TLS:
            switch (st_shndx) {
                case SHN_UNDEF: return "U";  // Undefined
                case SHN_ABS:   return "A";  // Absolute
                case SHN_COMMON:return "C";  // Common
                default:
                    if ((st_other & 0x7) == STV_HIDDEN) {
                        return "v";  // Indirect
                    } else {
                        return "T";  // TLS
                    }
            }
            break;
        case STT_RELC:
            return "r";  // Relocation with addend
            break;
        case STT_SRELC:
            return "R";  // Signed relocation with addend
            break;
        case STT_GNU_IFUNC:
            return "i";  // GNU indirect function
            break;
        default:
            return "?";
            break;
    }
}


