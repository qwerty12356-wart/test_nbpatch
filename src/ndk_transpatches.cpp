#include "main.h"
#include "patch_tools.h"


void Patch_Permissive_MProtect_NDK_Translation_R125_15853(){
    int res = 0;
    #ifdef IS32BIT
         res = PatchHex_8(nbbase, 0x1fdb95, 0xfa, 0xff);
    #else
         res = PatchHex_8(nbbase, 0x212ec0, 0xfa, 0xff);
    #endif
    if (res){
        debug_print("Patch_Permissive_Mprotect failed.");
    }
}


void Patch_Permissive_Mmap_NDK_Translation_R125_15853(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_8(nbbase, 0x10DA49, 0xfa, 0xff);
    #else
        res = PatchHex_8(nbbase, 0x212DC8, 0xfa, 0xff);
    #endif
    if (res){
        debug_print("Patch_Permissive_Mmap failed");
    }
}