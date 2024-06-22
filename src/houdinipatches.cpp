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

void Patch_Performance_Mprotect_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x282b64, 0xe8a784ec, 0x90909090);
        res = res | PatchHex_8(nbbase, 0x282b68, 0xff, 0x90);
    #else
        res = PatchHex_32(nbbase, 0x2f3903, 0xe8588fed, 0x90909090);
        res = res | PatchHex_8(nbbase,0x2f3907 , 0xff, 0x90);
    #endif
    if (res){
        debug_print("Patch_Performace_Mprotect failed.");
    }
}

void Patch_Performance_Mprotect_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x271b56, 0xe8e59cec, 0x90909090);
        res |= PatchHex_8(nbbase, 0x271b5a, 0xff, 0x90);
    #else
        res = PatchHex_32(nbbase, 0x2f7660, 0xe8bb2aee, 0x90909090);
        res |= PatchHex_8(nbbase, 0x2f7664, 0xff, 0x90);
    #endif
    if (res){
        debug_print("Patch_Performance_Mprotect failed.");
    }
}

void Patch_Permissive_Mprotect_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_8(nbbase, 0x2719b3, 0xfb, 0xff);
    #else
       res = PatchHex_32(nbbase, 0x2f74e6, 0x0fbaf102, 0x909090f8);
    #endif
    if (res){
        debug_print("Patch_Permissive_Mprotect failed.");
    }
}

void Patch_Permissive_Mmap_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x26d3a7, 0x0fbaf002, 0x909090f8);
    #else
        res = PatchHex_32(nbbase, 0x2f3ae1, 0x48b8fbff, 0x48b8ffff);
    #endif
    if (res){
        debug_print("Patch_Permissive_Mmap failed.");
    }
}