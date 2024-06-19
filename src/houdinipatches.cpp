#include "main.h"
#include "patch_tools.h"



void Patch_Permissive_Mmap_Houdini13_39190(){
    #ifdef IS32BIT 

    #else //default to 64 bit

    #endif

}

void Patch_Permissive_Mprotect_Houdini13_39190(){
    #ifdef IS32BIT

    #else

    #endif
}