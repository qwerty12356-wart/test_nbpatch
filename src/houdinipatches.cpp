#include "main.h"
#include "patch_tools.h"



void Patch_Permissive_Mmap_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT 
        res = PatchHex_32(nbbase, 0x27e467, 0x0fbaf002, 0x909090f8);
    #else //default to 64 bit
        res = PatchHex_8(nbbase, 0x2efd53, 0xfb, 0xff);

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
        res = PatchHex_32(nbbase, 0x2f3778, 0x02F1BA0F, 0xF8909090);
    #endif
    if (res){
        debug_print("Patch_Permissive_Mprotect failed.");
    }
}

void Patch_Performance_Mprotect_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x282b64, 0xEC84A7E8, 0x90909090);
        res = res | PatchHex_8(nbbase, 0x282b68, 0xff, 0x90);
    #else
        res = PatchHex_32(nbbase, 0x2f3903, 0xED8F58E8, 0x90909090);
        res = res | PatchHex_8(nbbase,0x2f3907 , 0xff, 0x90);
    #endif
    if (res){
        debug_print("Patch_Performace_Mprotect failed.");
    }
}

void Patch_Performance_Mprotect_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x271b56, 0xEC9CE5E8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x271b5a, 0xff, 0x90);
    #else
        res = PatchHex_32(nbbase, 0x2f7660, 0xEE2ABBE8, 0x90909090);
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
       res = PatchHex_32(nbbase, 0x2f74e6, 0x02F1BA0F, 0xF8909090);
    #endif
    if (res){
        debug_print("Patch_Permissive_Mprotect failed.");
    }
}

void Patch_Permissive_Mmap_Houdini12_38818(){
    int res = 0;
    #ifdef IS32BIT
        res = PatchHex_32(nbbase, 0x26d3a7, 0x02F0BA0F, 0xF8909090);
    #else
        res = PatchHex_32(nbbase, 0x2f3ae1, 0xFFFFB848, 0xFFFFB848);
        
    #endif
    if (res){
        debug_print("Patch_Permissive_Mmap failed.");
    }
}

void Patch_Linker_namespace_Houdini13_39190(){
    int res = 0;
    #ifdef IS32BIT
        //No 32 bit because im too lazy
    #else
        res = PatchHex_32(nbbase, 0x460b78, 0xFFBB93E8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x460b7c, 0xff, 0x90);
    #endif
    if (res){
        debug_print("Patch_Linker_namespace failed.");
    }
}

void Patch_Linker_namespace_Houdini12_38818(){
    int res = 0;
     #ifdef IS32BIT

    #else
        res = PatchHex_32(nbbase, 0x335e1a, 0x0042D1E8, 0x90909090);
        res |= PatchHex_8(nbbase, 0x335e1e, 0x00, 0x90);
    #endif
    if (res){
        debug_print("Patch_Linker_namespace failed.");
    }
}