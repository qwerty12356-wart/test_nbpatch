#include "main.h"
#include "logging.h"
#include <cerrno>
#include <cstring>
#include <sys/mman.h>
#include <string.h>




typedef bool (*initfn)(const NativeBridgeRuntimeCallbacks*, const char*, const char*);

initfn org_init = nullptr;

unsigned short g_nbindex = HOUDINI13_39190_INDEX;


extern "C"
bool onDemandPatch(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* privatedir, const char* insrt_set){
    
    
    if(mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ)!=-1){
        
    
        const char* found = strstr(privatedir, "com.nexon.bluearchive");
        if (found){
            Patch_Performance_Mprotect(g_nbindex);
        }
        mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);
        found = strstr(privatedir, "com.roblox.client");
        if (found){
            Patch_Hook_Unk_Function_Houdini11_38765();
        }
    }
    else {
        error_print("Failed to gain access to libhoudini, mprotect error code : %i", errno);
    }
    return 0;
}



bool patch_substation(){
    
   // uint8_t cucumber = *(uint8_t*)nbbase;
    
    if (mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ) == -1){
        error_print("Failed to gain access to libhoudini, mprotect error code : %i", errno);
        goto end;
    }
    Patch_Permissive_Mprotect(g_nbindex);
    Patch_Permissive_Mmap(g_nbindex);
    Patch_Linker_namespace(g_nbindex);
    Patch_Permissive_Mprotect2(g_nbindex);
    Patch_Permissive_PkeyMprotect2(g_nbindex);
    mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);
    end:
    return 0;
}


#define LIBRARY_ADDRESS_BY_HANDLE(dlhandle) ((NULL == dlhandle) ? NULL : (void*)*(size_t const*)(dlhandle))

//Prevent name mangling
extern "C"
int patch_main(void* ext_nbbase,unsigned short nbindex){
    if (ext_nbbase != 0){
        debug_print("Begin patching with %ld with patches %u", (long)ext_nbbase, nbindex);
        nbbase = ext_nbbase;
         g_nbindex = nbindex;
        nbsize = GetSizeFromIndex(g_nbindex);
        patch_substation();
        return 0;
    }
    error_print("nbbase is passed in as 0. Also nbindex is %u", nbindex);
    return 1;
}


