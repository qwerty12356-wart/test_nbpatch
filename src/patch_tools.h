#pragma once
#include <android/log.h>
#include <cstdint>
#include <dlfcn.h>



//Return 0 on success, return 1 on failure.
//4 HEX ie FF FF FF FF
int PatchHex_32(void* baseaddress,uint64_t offset, uint32_t original_hex, uint32_t new_hex);

//2 HEX ie FF FF
inline int PatchHex_16(void* baseaddress, int offset, uint16_t original_hex, uint16_t new_hex){
    uint16_t* addrtocheck = (uint16_t*)baseaddress + offset;
    if (*addrtocheck == original_hex){
        *addrtocheck = new_hex;
        return 0;
    }
    return 1;
}

//1 HEX ie: FF
inline int PatchHex_8(void* baseaddress, int offset, uint8_t original_hex, uint8_t new_hex){
    uint8_t* addrtocheck = (uint8_t*)baseaddress + offset;
    if (*addrtocheck == original_hex){
        *addrtocheck = new_hex;
        return 0;
    }
    if (*addrtocheck == new_hex){
        __android_log_print(ANDROID_LOG_ERROR, "libnbpatcher", "Hex matches but failed to apply patch");
    }
    return 1;
}