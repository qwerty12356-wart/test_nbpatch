message("Source Loaded")

add_library(nbpatch SHARED main.cpp main.h houdinipatches.cpp patch_tools.h)
target_include_directories(nbpatch PRIVATE "${ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include")