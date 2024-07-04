
# What is this?
A special library intended to be loaded from libnb.so to patch native bridges in memory.

# Installation
1. Obtain a compiled libnbpatcher.so and libnb.so (see [here](https://github.com/qwerty12356-wart/test_nb_c)) (see Build)
2. Copy libnb.so and libnbpatcher.so to system/lib (for 32 bit) and system/lib64 (for 64 bit)

# Build
1. export or edit ANDROID_NDK_HOME in CMakeLists.txt to point to a folder containing the extracted Android NDK
2. ``cmake . -B build``
3. ``cd build``, ``make`` or ``ninja``
4. The compiled library should be located in build/src
   
Available build options:

COMPILE_ARCH: Available option x86 (for compiling 32 bit) and x86_64 (default, for compiling with 64 bit)

LOG_DEBUG

Example build option: cmake -B build -DCOMPILE_ARCH=x86_64


