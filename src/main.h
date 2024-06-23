#pragma once

#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <sys/mman.h>


#if INTPTR_MAX == INT32_MAX
    #define IS32BIT
#else
    #define IS64BIT
#endif




//#define debug_print(mesg) __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", mesg)
#define debug_print(...) __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", __VA_ARGS__)
enum{
    HOUDINI13_39190_INDEX = 0,
    NDK_TRANS13_R125_15853_INDEX = 1,
    HOUDINI12_38818_INDEX = 2
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



static unsigned int GetSizeFromIndex(unsigned short index){
    switch (index){
    case HOUDINI13_39190_INDEX:
    {
        return 7 * 1024 * 1024;
    }
    case NDK_TRANS13_R125_15853_INDEX:
    {
        return 3 * 1024 * 1024;
    }
    case HOUDINI12_38818_INDEX:
    {
        return 7 * 1024 * 1024;
    }
    default:{
        return 4 * 1024 * 1024;
    }
    }
}

inline void* nbbase = nullptr;

//Details NB specific patches down here.
void Patch_Permissive_Mprotect_Houdini13_39190();
void Patch_Permissive_Mprotect_Houdini12_38818();
void Patch_Permissive_Mmap_Houdini13_39190();
void Patch_Permissive_Mmap_Houdini12_38818();

void Patch_Performance_Mprotect_Houdini13_39190();
void Patch_Performance_Mprotect_Houdini12_38818();

void Patch_Permissive_MProtect_NDK_Translation_R125_15853();

void Patch_Permissive_Mmap_NDK_Translation_R125_15853();

void Patch_Linker_namespace_Houdini13_39190();
void Patch_Linker_namespace_Houdini12_38818();



//General NB patches:
inline void Patch_Linker_namespace(unsigned short index){
    switch(index){
        case HOUDINI13_39190_INDEX:
        {
            Patch_Linker_namespace_Houdini13_39190();
            break;
        }
        case HOUDINI12_38818_INDEX:
        {
            Patch_Linker_namespace_Houdini12_38818();
            break;
        }
    }
}


inline void Patch_Permissive_Mprotect(unsigned short index){
    switch(index){
        case HOUDINI13_39190_INDEX:
        {
            Patch_Permissive_Mprotect_Houdini13_39190();
            Patch_Performance_Mprotect_Houdini13_39190();
            break;
        }
        case NDK_TRANS13_R125_15853_INDEX:
        {
            Patch_Permissive_MProtect_NDK_Translation_R125_15853();
            break;
        }
        case HOUDINI12_38818_INDEX:
        {
            Patch_Permissive_Mprotect_Houdini12_38818();
            Patch_Performance_Mprotect_Houdini12_38818();
            break;
        }
    }
}

inline void Patch_Permissive_Mmap(unsigned short index){
    switch(index){
        case HOUDINI13_39190_INDEX:
        {
            Patch_Permissive_Mmap_Houdini13_39190();
            break;
        }
        case NDK_TRANS13_R125_15853_INDEX:
        {
            Patch_Permissive_Mmap_NDK_Translation_R125_15853();
            break;
        }
        case HOUDINI12_38818_INDEX:
        {
            Patch_Permissive_Mmap_Houdini12_38818();
            break;
        }
    }
}