#include "patch_tools.h"
#include <cstdint>
#include <android/log.h>
#if INTPTR_MAX == INT32_MAX
    #define IS_32
#else
    #define IS_64
#endif


//Please don't jinx this up, compiler
int PatchHex_32(void* baseaddress, uint64_t offset, uint32_t original_hex, uint32_t new_hex){


    #ifdef IS_32
    uint32_t* addrtocheck = (uint32_t*)((char*)baseaddress + offset); //yup, a hack to fix a dumb compiler bug
    if (*addrtocheck == original_hex){
        *addrtocheck = new_hex;
        return 0;
    }
    #else
        uint64_t workaroundvar = (uint64_t)baseaddress + offset;
        uint32_t* addrtocheck = (uint32_t*)workaroundvar; //Lol
        if (*addrtocheck == original_hex){
            *addrtocheck = new_hex;
            return 0;
        }
        if (*addrtocheck == new_hex){
            __android_log_print(ANDROID_LOG_ERROR, "libnbpatcher", "Hex match but hex patches is not applied!");
        }
        __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", "Failed to patch hex %u at %ld (original_hex: %u, new_hex: %u)", *addrtocheck, workaroundvar, original_hex, new_hex);


    #endif
    return 1;
}