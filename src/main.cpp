#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>

#define debug_print(mesg) __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", mesg)

struct NativeBridgeRuntimeCallbacks {
  // Get shorty of a Java method. The shorty is supposed to be persistent in memory.
  //
  // Parameters:
  //   env [IN] pointer to JNIenv.
  //   mid [IN] Java methodID.
  // Returns:
  //   short descriptor for method.
  const char* (*getMethodShorty)(JNIEnv* env, jmethodID mid);
  // Get number of native methods for specified class.
  //
  // Parameters:
  //   env [IN] pointer to JNIenv.
  //   clazz [IN] Java class object.
  // Returns:
  //   number of native methods.
  uint32_t (*getNativeMethodCount)(JNIEnv* env, jclass clazz);
  // Get at most 'method_count' native methods for specified class 'clazz'. Results are outputed
  // via 'methods' [OUT]. The signature pointer in JNINativeMethod is reused as the method shorty.
  //
  // Parameters:
  //   env [IN] pointer to JNIenv.
  //   clazz [IN] Java class object.
  //   methods [OUT] array of method with the name, shorty, and fnPtr.
  //   method_count [IN] max number of elements in methods.
  // Returns:
  //   number of method it actually wrote to methods.
  uint32_t (*getNativeMethods)(JNIEnv* env, jclass clazz, JNINativeMethod* methods,
                               uint32_t method_count);
};

//this is only part of the full Callbacks definition but should be good enough
struct NativeBridgeCallbacks {
  // Version number of the interface.
  uint32_t version;
  // Initialize native bridge. Native bridge's internal implementation must ensure MT safety and
  // that the native bridge is initialized only once. Thus it is OK to call this interface for an
  // already initialized native bridge.
  //
  // Parameters:
  //   runtime_cbs [IN] the pointer to NativeBridgeRuntimeCallbacks.
  // Returns:
  //   true if initialization was successful.
  bool (*initialize)(const NativeBridgeRuntimeCallbacks* runtime_cbs, const char* private_dir,
                     const char* instruction_set);
};

typedef bool (*initfn)(const NativeBridgeRuntimeCallbacks*, const char*, const char*);
initfn org_init = nullptr;
void* nbbase = nullptr;

bool x_init(const NativeBridgeCallbacks* runtime_cbs, const char* privatedir, const char* insrt_set){
    
}


int patch_main(void* nblibaddr){
    Dl_info dlinfo{};
    dladdr("NativeBridgeItf" ,&dlinfo);
    if (dlinfo.dli_saddr){
        NativeBridgeCallbacks* ncbs = reinterpret_cast<NativeBridgeCallbacks*>(dlinfo.dli_saddr);
        if (ncbs->initialize){
            org_init = ncbs->initialize;
            ncbs->initialize = (initfn)x_init;
            nbbase = nblibaddr;
            return 0;
        }
    }
    return 1;
}


