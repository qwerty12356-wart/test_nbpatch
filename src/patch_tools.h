#pragma once
#include <android/log.h>
#include <cstdint>



//Return 0 on success, return 1 on failure.
//4 HEX ie FF FF FF FF
int PatchHex_32(void* baseaddress,int offset, uint32_t original_hex, uint32_t new_hex);

//2 HEX ie FF FF
int PatchHex_16(void* baseaddress, int offset, uint16_t original_hex, uint32_t new_hex);

//1 HEX ie: FF
int PatchHex_8(void* baseaddress, int offset, uint8_t original_hex, uint8_t new_hex);