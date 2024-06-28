#include "patch_tools.h"
#include <cstdint>
#include <cerrno>
#include <android/log.h>
#include "logging.h"
#include <string.h>
#include <unistd.h>
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

int PatchHex_8(void* baseaddress, int offset, uint8_t original_hex, uint8_t new_hex){
    uint8_t* addrtocheck = (uint8_t*)baseaddress + offset;
    if (!is_readable(addrtocheck)){
        return 1;
    }
    uint8_t memtocheck = 0;
    memcpy(&memtocheck, addrtocheck, sizeof(uint8_t));
    if (memtocheck == original_hex){
        memcpy(addrtocheck, &new_hex, sizeof(uint8_t));
        return 0;
    }
    return 1;
}

int PatchHex_32(void *baseaddress, int offset, uint32_t original_hex, uint32_t new_hex){
    uint8_t* addrtocheck = (uint8_t*)baseaddress + offset;
    if (!is_readable(addrtocheck)){
        return 1;
    }
    uint32_t memtocheck = 0;
    memcpy(&memtocheck, addrtocheck, sizeof(uint32_t));
    if (memtocheck == original_hex){
        memcpy(addrtocheck, &new_hex, sizeof(uint32_t));
        return 0;
    }
    return 1;
}

/*
int PatchHex_32(void* baseaddress, uint64_t offset, uint32_t original_hex, uint32_t new_hex){
    #ifdef ISTESTING
        return PatchHex_32_mcp(baseaddress,offset,original_hex,new_hex);
    #else
    uint8_t* u8orghex = (uint8_t*)&original_hex;
    uint8_t* u8newhex = (uint8_t*)&new_hex;
    int ret_val = 0;
    ret_val |= PatchHex_8(baseaddress, offset, u8orghex[0], u8newhex[0] );
    ret_val |= PatchHex_8(baseaddress, offset + 1, u8orghex[1], u8newhex[1]);
    ret_val |= PatchHex_8(baseaddress, offset + 2, u8orghex[2], u8newhex[2]);
    ret_val |= PatchHex_8(baseaddress, offset + 3, u8orghex[3], u8newhex[3]);
    return ret_val;
    #endif
}

int PatchHex_8(void* baseaddress, int offset, uint8_t original_hex, uint8_t new_hex){
    #ifdef ISTESTING
        return PatchHex_8_mcp(baseaddress, offset, original_hex, new_hex);
    #else
    #ifdef IS_32
        uint8_t* addrtocheck = (uint8_t*)baseaddress + (uint8_t)offset;
        #else
        uint8_t* addrtocheck = (uint8_t*)baseaddress + offset;
        #endif
        if (!is_readable(addrtocheck)){
            error_print("Address is not readable!");
            return 1;
        }

        if (*addrtocheck != original_hex){
            error_print("Hex %u mismatch at %lld (new hex is %u, original_hex is %u)", *addrtocheck, (unsigned long long)addrtocheck, new_hex, original_hex);
            return 1;
        }
        if (*addrtocheck == new_hex){
            info_print("Already patched!");
            return 0;
        }
        if (*addrtocheck == original_hex){
            *addrtocheck = new_hex;
            info_print("PatchHex_32 Patched successfully");
            return 0;
        }
        error_print("How did we get here");
    return 1;
    #endif
}

*/