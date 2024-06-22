#include "main.h"




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


int patch_main(void* nblibaddr,unsigned short nbindex){
    Dl_info dlinfo{};
    dladdr("NativeBridgeItf" ,&dlinfo);
    if (dlinfo.dli_saddr){
        NativeBridgeCallbacks* ncbs = reinterpret_cast<NativeBridgeCallbacks*>(dlinfo.dli_saddr);
        if (ncbs->initialize){
            org_init = ncbs->initialize;
            
            nbbase = nblibaddr;
            nbsize = GetSizeFromIndex(nbindex);
            g_nbindex = nbindex;

            
            mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);
            ncbs->initialize = (initfn)x_init;
            mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);

            return 0;
        }
    }
    return 1;
}


