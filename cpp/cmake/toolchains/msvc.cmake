if (CMAKE_SYSTEM_NAME AND NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(FATAL_ERROR "Toolchain 'msvc.cmake' is only available on Windows.")
endif()

set(CMAKE_CXX_COMPILER cl)

set(CMAKE_CXX_STANDARD          23 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS        OFF)

# By default, MSVC’s predefined macro '__cplusplus' does not report the correct
# C++ standard version (it just returns 199711L, which corresponds to C++98).
# Why, you may ask? Some stones are better left unturned.
add_compile_options(/Zc:__cplusplus)

option(CMAKE_COMPILE_WARNING_AS_ERROR "Treat compiler warnings as errors" ON)
