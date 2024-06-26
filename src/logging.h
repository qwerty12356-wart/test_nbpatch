#include <android/log.h>

#ifdef LOG_DEBUG
#define debug_print(...) __android_log_print(ANDROID_LOG_DEBUG, "libnbpatcher", __VA_ARGS__)
#else
#define debug_print(...)
#endif
#define error_print(...) __android_log_print(ANDROID_LOG_ERROR, "libnbpatcher", __VA_ARGS__)
#define info_print(...) __android_log_print(ANDROID_LOG_INFO, "libnbpatcher", __VA_ARGS__)