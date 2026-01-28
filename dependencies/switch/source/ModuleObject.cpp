// huge props to Thog for oss-rtld, couldn't do this without you
#include "ModuleObject.hpp"

unsigned long __rtld_elf_hash(const char *name) {
    unsigned long h = 0;
    unsigned long g;

    while (*name) {
        h = (h << 4) + *name++;
        if ((g = h & 0xf0000000)) h ^= g >> 24;
        h &= ~g;
    }
    return h;
}


int __rtld_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++; s2++;
    }
    return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}

namespace rtld {

Elf64_Sym* ModuleObject::GetSymbolByName(const char* name) {
    unsigned long name_hash = __rtld_elf_hash(name);

    for (uint32_t i = this->hash_bucket[name_hash % this->hash_nbucket_value]; i; i = this->hash_chain[i]) {
        bool is_common = this->dynsym[i].st_shndx ? this->dynsym[i].st_shndx == SHN_COMMON : true;
        if (!is_common &&  __rtld_strcmp(name, this->dynstr + this->dynsym[i].st_name) == 0)
            return &this->dynsym[i];
    }

    return nullptr;
}

}