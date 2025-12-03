if (CMAKE_SYSTEM_NAME AND NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(FATAL_ERROR "Toolchain 'clang-cl.cmake' is only available on Windows.")
endif()

# Visual Studio ignores the compiler set and just uses 'cl',
# unless the 'ClangCL' toolset is specified
if(CMAKE_GENERATOR MATCHES "Visual Studio" AND
   NOT CMAKE_GENERATOR_TOOLSET MATCHES "ClangCL")
  message(FATAL_ERROR
    "'toolchains/clang-cl.cmake' is incompatible with a 'Visual Studio' generator,"
    " unless the '-T ClangCL' toolset is specified."
  )
endif()

set(CMAKE_CXX_COMPILER clang-cl)

set(CMAKE_CXX_STANDARD          23 )
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS        OFF)

# Workaround to Catch2 requiring 'target_compile_features(Catch2 PUBLIC cxx_std_14)'
# We add every sensible standard that might be required.
foreach(ver IN ITEMS 11 14 17 20 23)
  set(feat "cxx_std_${ver}")
  if(NOT feat IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    list(APPEND CMAKE_CXX_COMPILE_FEATURES "${feat}")
  endif()
endforeach()

option(CMAKE_COMPILE_WARNING_AS_ERROR "Treat compiler warnings as errors" ON)
