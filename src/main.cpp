#include "main.h"
#include <dlfcn.h>




typedef bool (*initfn)(const NativeBridgeRuntimeCallbacks*, const char*, const char*);

initfn org_init = nullptr;
unsigned int nbsize = GetSizeFromIndex(0);
unsigned short g_nbindex = HOUDINI13_39190_INDEX;





bool x_init(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* privatedir, const char* insrt_set){
    //privatedir SHOULD contain the app ID or whatever, use it to identify
    mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
    Patch_Permissive_Mprotect(g_nbindex);
    Patch_Permissive_Mmap(g_nbindex);



    mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);
    int initreturn = org_init(runtime_cbs, privatedir, insrt_set);
    return initreturn;
}
#define LIBRARY_ADDRESS_BY_HANDLE(dlhandle) ((NULL == dlhandle) ? NULL : (void*)*(size_t const*)(dlhandle))

int patch_main(void* nbhandle,unsigned short nbindex){
    NativeBridgeCallbacks* nbcallbacks = (NativeBridgeCallbacks*)dlsym(nbhandle, "NativeBridgeItf");
    if (LIBRARY_ADDRESS_BY_HANDLE(nbhandle)){
       nbbase = LIBRARY_ADDRESS_BY_HANDLE(nbhandle);
       nbsize = GetSizeFromIndex(nbindex);
       g_nbindex = nbindex;
        if (nbcallbacks->initialize){
            org_init = nbcallbacks->initialize;
            mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
            nbcallbacks->initialize = (initfn)x_init;
            mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);

            return 0;
        }
    }
    return 1;
}


