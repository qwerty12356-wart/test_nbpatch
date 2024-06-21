#include "main.h"
#include "patch_tools.h"



void Patch_Permissive_Mmap_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT 
        res = PatchHex_32(nbbase, 0x27e467, 0x0fbaf002, 0x909090f8);
    #else //default to 64 bit
        res = PatchHex_32(nbbase, 0x2efd51, 0x48b8fbff, 0x48b8ffff);

    #endif
    if (res){
        debug_print("Patch_Permissive_Mmap failed.");
    }

}

void Patch_Permissive_Mprotect_Houdini13_39190(){
    int res =0;
    #ifdef IS32BIT
        //These stupid hexes took fucking AGES to find because ghidra ENTIRELY miss a very important function.
        res = PatchHex_8(nbbase, 0x2829c0, 0xfb, 0xff);
    #else
        res = PatchHex_32(nbbase, 0x2f3778, 0x0fbaf102, 0x909090f8);
    #endif
    if (res){
        debug_print("Patch_Permissive_Mprotect failed.");
    }
}