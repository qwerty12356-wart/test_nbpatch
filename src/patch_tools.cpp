#include "patch_tools.h"
#include <cstdint>
#include <cerrno>
#include <android/log.h>
#include "main.h"
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#if INTPTR_MAX == INT32_MAX
    #define IS_32
#else
    #define IS_64
#endif

int is_readable(void* p){
    int dummypipe[2];
    if( pipe(dummypipe) == -1)
    {
        error_print("Pipe Error: %i", errno);
        return 0;
    }
    
    int writeable = write(dummypipe[1], p, 1);
    if (writeable == -1){
        return 0;
    }
    close(dummypipe[0]);
    close(dummypipe[1]);
    return 1;
}

//Please don't jinx this up, compiler
int PatchHex_32(void* baseaddress, uint64_t offset, uint32_t original_hex, uint32_t new_hex){

        #ifdef IS_32
        uint32_t* addrtocheck = (uint32_t*)baseaddress + (uint32_t)offset;
        #else
        uint32_t* addrtocheck = (uint32_t*)baseaddress + offset;
        
        #endif
        if ((addrtocheck - (uint32_t*)nbbase) > nbsize){
            error_print("Patching out of range!");
            return 1;
        }
        
        if (!is_readable(addrtocheck)){
            error_print("Address is not readable!");
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
    #ifdef IS_32
        uint8_t* addrtocheck = (uint8_t*)baseaddress + (uint8_t)offset;
        #else
        uint8_t* addrtocheck = (uint8_t*)baseaddress + offset;
        #endif
        if ((addrtocheck - (uint8_t*)nbbase) > nbsize){
            error_print("Patching out of range!");
            return 1;
        }
        if (!is_readable(addrtocheck)){
            error_print("Address is not readable!");
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