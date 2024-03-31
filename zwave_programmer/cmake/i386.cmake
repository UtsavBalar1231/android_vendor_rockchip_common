# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
# Target system Processor
set(CMAKE_SYSTEM_PROCESSOR "i386")

# which compilers to use for C and C++
SET(CMAKE_C_FLAGS             "-m32" CACHE STRING "C compiler flags"   FORCE)
SET(CMAKE_CXX_FLAGS           "-m32" CACHE STRING "C++ compiler flags" FORCE)

