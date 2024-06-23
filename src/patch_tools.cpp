#include "patch_tools.h"
#include <cstdint>
#if INTPTR_MAX == INT32_MAX
    #define IS_32
#else
    #define IS_64
#endif


//Please don't jinx this up, compiler
int PatchHex_32(void* baseaddress, long offset, uint32_t original_hex, uint32_t new_hex){


    #ifdef IS_32
    uint32_t* addrtocheck = (uint32_t*)((char*)baseaddress + offset); //yup, a hack to fix a dumb compiler bug
    if (*addrtocheck == original_hex){
        *addrtocheck = new_hex;
        return 0;
    }
    #else
        uint32_t* addrtocheck = (uint32_t*)(char*)baseaddress + (uint64_t)offset; //Lol
        if (*addrtocheck == original_hex){
            *addrtocheck = new_hex;
            return 0;
        }

    #endif
    return 1;
}