cmake_minimum_required(VERSION 3.22)


if(NOT DEFINED COMPILE_ARCH)
    set(COMPILE_ARCH x86_64)
endif()

include(FetchContent)

FetchContent_Declare(
    cmakescript
    GIT_REPOSITORY https://github.com/StableCoder/cmake-scripts.git
    GIT_TAG 45f72fdc2d715030c6cb61e3d5977811ea45abda
)

FetchContent_MakeAvailable(cmakescript)

set(CMAKE_BUILD_TYPE Release)

set(ANDROID_NDK_HOME ~/Downloads/android-ndk-r26d)
if (DEFINED ENV{ANDROID_NDK_HOME})
    set(ANDROID_NDK_HOME $ENV{ANDROID_NDK_HOME})
endif()



include(${cmakescript_SOURCE_DIR}/c++-standards.cmake)

cxx_20()
set(CMAKE_ANDROID_NDK ${ANDROID_NDK_HOME})
set(ANDROID_PLATFORM 30) #Android 11 SDK ver



set(ANDROID_ABI ${COMPILE_ARCH})
set(ANDROID_STL c++_static)
set(ANDROID_CPP_FEATURES,"no-rtti no-exceptions")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_TOOLCHAIN_FILE ${ANDROID_NDK_HOME}/build/cmake/android.toolchain.cmake)


project(libnbpatcher)
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 30)
set(CMAKE_ANDROID_ARCH_ABI ${COMPILE_ARCH})
set(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION clang)
set(CMAKE_ANDROID_STL_TYPE c++_static)


#message("${CMAKE_ANDROID_NDK_VERSION}")
#include_directories(${ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
