#include "main.h"
#include <android/log.h>
#include <cerrno>
#include <cstring>
#include <dlfcn.h>
#include <sys/mman.h>




typedef bool (*initfn)(const NativeBridgeRuntimeCallbacks*, const char*, const char*);

initfn org_init = nullptr;

unsigned short g_nbindex = HOUDINI13_39190_INDEX;



/*
bool x_init(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* privatedir, const char* insrt_set){
    //privatedir SHOULD contain the app ID or whatever, use it to identify
    __android_log_print(ANDROID_LOG_INFO, "libnbpatcher", "Begin Hex patching native bridge %ld", (long)nbbase);
    mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
    Patch_Permissive_Mprotect(g_nbindex);
    Patch_Permissive_Mmap(g_nbindex);
    Patch_Linker_namespace(g_nbindex);
    const char* found = strstr(privatedir, "com.nexon.bluearchive");
    if (found != 0){
        Patch_Performance_Mprotect(g_nbindex);
    }

    
    int initreturn = org_init(runtime_cbs, privatedir, insrt_set);
    return initreturn;
}
*/
extern "C"
bool onDemandPatch(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* privatedir, const char* insrt_set){
    //mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
    //const char* found = strstr(privatedir, "com.nexon.bluearchive");
    //if (found != 0){
     //   Patch_Performance_Mprotect(g_nbindex);
    //}
    //mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);
    return 0;
}

bool patch_substation(){
    
   // uint8_t cucumber = *(uint8_t*)nbbase;
    if (mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ) != 0){
        error_print("Failed to gain access to libhoudini, mprotect error code : %i", errno);
        goto end;
    }
    Patch_Permissive_Mprotect(g_nbindex);
    Patch_Permissive_Mmap(g_nbindex);
    Patch_Linker_namespace(g_nbindex);
    mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);
    end:
    return 0;
}


#define LIBRARY_ADDRESS_BY_HANDLE(dlhandle) ((NULL == dlhandle) ? NULL : (void*)*(size_t const*)(dlhandle))

//Prevent name mangling
extern "C"
int patch_main(void* ext_nbbase,unsigned short nbindex){

    /*
    __android_log_print(ANDROID_LOG_INFO, "libnbpatcher", "Patching initialize");
    void* nbhandle = dlopen("libhoudini.so", RTLD_LOCAL);
    NativeBridgeCallbacks* nbcallbacks = (NativeBridgeCallbacks*)dlsym(nbhandle, "NativeBridgeItf");
    
    if (ext_nbbase){
       nbbase = ext_nbbase;
       nbsize = GetSizeFromIndex(nbindex);
       g_nbindex = nbindex;
        if (nbcallbacks->initialize && nbcallbacks->initialize != x_init){
            org_init = nbcallbacks->initialize;
            mprotect(nbcallbacks, 128, PROT_EXEC | PROT_WRITE | PROT_READ);
            nbcallbacks->initialize = (initfn)x_init;
            mprotect(nbcallbacks, 128, PROT_EXEC | PROT_READ);
            __android_log_print(ANDROID_LOG_INFO, "libnbpatcher", "Patched initialize");
            return 0;
        }
    }
    */
    if (ext_nbbase != 0){
        __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", "Begin patching with %ld with patches %u", (long)ext_nbbase, nbindex);
        nbbase = ext_nbbase;
         g_nbindex = nbindex;
        nbsize = GetSizeFromIndex(g_nbindex);
        patch_substation();
        return 0;
    }
    error_print("nbbase is passed in as 0. Also nbindex is %u", nbindex);
    return 1;
}


