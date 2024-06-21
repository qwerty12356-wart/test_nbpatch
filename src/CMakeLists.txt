message("Source Loaded")

add_library(nbpatch SHARED main.cpp main.h houdinipatches.cpp patch_tools.h ndk_transpatches.cpp)
target_link_libraries(nbpatch log)