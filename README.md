
# What is this?
A special library intended to be loaded from libnb.so to patch native bridges in memory.

# Installation
Work in progress. Not intended for public use. Figure it out yourself.

# Build
1. export or edit ANDROID_NDK_HOME in CMakeLists.txt to point to a folder containing the extracted Android NDK
2. ``cmake . -B build``
3. ``cd build``, ``make`` or ``ninja``
4. The compiled library should be located in build/src


