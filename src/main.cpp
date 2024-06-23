#include "main.h"
#include <android/log.h>
#include <dlfcn.h>




typedef bool (*initfn)(const NativeBridgeRuntimeCallbacks*, const char*, const char*);

initfn org_init = nullptr;
unsigned int nbsize = GetSizeFromIndex(0);
unsigned short g_nbindex = HOUDINI13_39190_INDEX;





bool x_init(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* privatedir, const char* insrt_set){
    //privatedir SHOULD contain the app ID or whatever, use it to identify
    __android_log_print(ANDROID_LOG_INFO, "libnbpatcher", "Begin Hex patching native bridge");
    mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
    Patch_Permissive_Mprotect(g_nbindex);
    Patch_Permissive_Mmap(g_nbindex);



    mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);
    int initreturn = org_init(runtime_cbs, privatedir, insrt_set);
    return initreturn;
}
#define LIBRARY_ADDRESS_BY_HANDLE(dlhandle) ((NULL == dlhandle) ? NULL : (void*)*(size_t const*)(dlhandle))

bool init_guard = false;
//Prevent name mangling
extern "C"
int patch_main(void* ext_nbbase,unsigned short nbindex){
    if (!init_guard){
        init_guard = true;
    __android_log_print(ANDROID_LOG_INFO, "libnbpatcher", "Patching initialize");
    void* nbhandle = dlopen("libhoudini.so", RTLD_LOCAL);
    NativeBridgeCallbacks* nbcallbacks = (NativeBridgeCallbacks*)dlsym(nbhandle, "NativeBridgeItf");
    if (ext_nbbase){
       nbbase = ext_nbbase;
       nbsize = GetSizeFromIndex(nbindex);
       g_nbindex = nbindex;
        if (nbcallbacks->initialize){
            org_init = nbcallbacks->initialize;
            mprotect(nbcallbacks, 128, PROT_EXEC | PROT_WRITE | PROT_READ);
            nbcallbacks->initialize = (initfn)x_init;
            mprotect(nbcallbacks, 128, PROT_EXEC | PROT_READ);
            __android_log_print(ANDROID_LOG_INFO, "libnbpatcher", "Patched initialize");
            return 0;
        }
    }
    }
    return 1;
}


