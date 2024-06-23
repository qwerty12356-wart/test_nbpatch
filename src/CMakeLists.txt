message("Source Loaded")

add_library(nbpatcher SHARED main.cpp main.h houdinipatches.cpp patch_tools.h ndk_transpatches.cpp patch_tools.cpp)
target_link_libraries(nbpatcher log)