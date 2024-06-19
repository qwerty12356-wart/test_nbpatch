#pragma once

#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <sys/mman.h>

#define debug_print(mesg) __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", mesg)

enum{
    HOUDINI13_39190_INDEX = 0,
    NDK_TRANS13_INDEX = 1
};

typedef void (*patchfn)();

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


static void* nbbase = nullptr;

//Details NB specific patches down here.
void Patch_Permissive_Mprotect_Houdini13_39190();

void Patch_Permissive_Mmap_Houdini13_39190();


//General NB patches:
inline void Patch_Permissive_Mprotect(unsigned short index){
    switch(index){
        case HOUDINI13_39190_INDEX:
        {
            Patch_Permissive_Mprotect_Houdini13_39190();
            break;
        }
    }
}

inline void Patch_Permissive_Mmap(unsigned short index){

}