#include "patch_tools.h"
#include <cstdint>
#include <cerrno>
#include <android/log.h>
#include "main.h"
#include <unistd.h>
#if INTPTR_MAX == INT32_MAX
    #define IS_32
#else
    #define IS_64
#endif


//Please don't jinx this up, compiler
int PatchHex_32(void* baseaddress, uint64_t offset, uint32_t original_hex, uint32_t new_hex){

    /*
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
            __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", "PatchHex_32 sucessfully");
            return 0;
        }
        if (*addrtocheck == new_hex){
            __android_log_print(ANDROID_LOG_ERROR, "libnbpatcher", "Hex match but hex patches is not applied!");
        }
        __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", "Failed to patch hex %u at %ld (original_hex: %u, new_hex: %u)", *addrtocheck, workaroundvar, original_hex, new_hex);


    #endif
    */
        mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
        if (errno){
            error_print("Failed to gain access (gaslighted): %i", errno);
            return 1;
        }
        #ifdef IS_32
        uint32_t* addrtocheck = (uint32_t*)baseaddress + (uint32_t)offset;
        #else
        uint32_t* addrtocheck = (uint32_t*)baseaddress + offset;
        
        #endif
        if ((addrtocheck - (uint32_t*)nbbase) > nbsize){
            error_print("Patching out of range!");
            return 1;
        }
        


        if (*addrtocheck != original_hex){
            error_print("Hex %u mismatch at %lld (new hex is %u, original_hex is %u)", *addrtocheck, (unsigned long long)addrtocheck, new_hex, original_hex);
            return 1;
        }
        if (*addrtocheck == new_hex){
            error_print("Already patched!");
            return 1;
        }
        if (*addrtocheck == original_hex){
            *addrtocheck = new_hex;
            info_print("PatchHex_32 Patched successfully");
            return 0;
        }
        error_print("How did we get here");
    return 1;
}

int PatchHex_8(void* baseaddress, int offset, uint8_t original_hex, uint8_t new_hex){
    mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
        if (errno){
            error_print("Failed to gain access (gaslighted): %i", errno);
            return 1;
        }
    #ifdef IS_32
        uint8_t* addrtocheck = (uint8_t*)baseaddress + (uint8_t)offset;
        #else
        uint8_t* addrtocheck = (uint8_t*)baseaddress + offset;
        #endif
        if ((addrtocheck - (uint8_t*)nbbase) > nbsize){
            error_print("Patching out of range!");
            return 1;
        }
        if (*addrtocheck != original_hex){
            error_print("Hex %u mismatch at %lld (new hex is %u, original_hex is %u)", *addrtocheck, (unsigned long long)addrtocheck, new_hex, original_hex);
            return 1;
        }
        if (*addrtocheck == new_hex){
            error_print("Already patched!");
            return 1;
        }
        if (*addrtocheck == original_hex){
            *addrtocheck = new_hex;
            info_print("PatchHex_32 Patched successfully");
            return 0;
        }
        error_print("How did we get here");
    return 1;
}