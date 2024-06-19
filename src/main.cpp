#include "asm-generic/mman-common.h"
#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <sys/mman.h>

#define debug_print(mesg) __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", mesg)

struct NativeBridgeRuntimeCallbacks {
  const char* (*getMethodShorty)(JNIEnv* env, jmethodID mid);
  uint32_t (*getNativeMethodCount)(JNIEnv* env, jclass clazz);
  uint32_t (*getNativeMethods)(JNIEnv* env, jclass clazz, JNINativeMethod* methods,
                               uint32_t method_count);
};

//this is only part of the full Callbacks definition but should be good enough
struct NativeBridgeCallbacks {
  uint32_t version;
  bool (*initialize)(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* private_dir,
                     const char* instruction_set);
};

void Patch_Permissive_Mprotect_Houdini13_39190();

void Patch_Permissive_Mmap_Houdini13_39190();


typedef bool (*initfn)(const NativeBridgeRuntimeCallbacks*, const char*, const char*);
typedef void (*patchfn)();

static const patchfn Patch_Permissive_Mprotect[]{
    Patch_Permissive_Mprotect_Houdini13_39190
};
static const patchfn Patch_Permissive_Mmap[]{
    Patch_Permissive_Mmap_Houdini13_39190
};


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


