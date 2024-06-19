#include "main.h"




typedef bool (*initfn)(const NativeBridgeRuntimeCallbacks*, const char*, const char*);


enum{
    HOUDINI13_39190_INDEX = 0,
    NDK_TRANS13_INDEX = 1
};

initfn org_init = nullptr;
void* nbbase = nullptr;
int nbsize = 6291456; //Arbitrary Number
unsigned short g_nbindex = HOUDINI13_39190_INDEX;





bool x_init(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* privatedir, const char* insrt_set){
    //privatedir SHOULD contain the app ID or whatever, use it to identify
    
    mprotect(nbbase, nbsize, PROT_EXEC | PROT_WRITE | PROT_READ);


    mprotect(nbbase, nbsize, PROT_EXEC | PROT_READ);
    int initreturn = org_init(runtime_cbs, privatedir, insrt_set);
    return initreturn;
}


int patch_main(void* nblibaddr, int size,unsigned short nbindex){
    Dl_info dlinfo{};
    dladdr("NativeBridgeItf" ,&dlinfo);
    if (dlinfo.dli_saddr){
        NativeBridgeCallbacks* ncbs = reinterpret_cast<NativeBridgeCallbacks*>(dlinfo.dli_saddr);
        if (ncbs->initialize){
            org_init = ncbs->initialize;
            ncbs->initialize = (initfn)x_init;
            nbbase = nblibaddr;
            nbsize = size;
            g_nbindex = nbindex;
            return 0;
        }
    }
    return 1;
}


