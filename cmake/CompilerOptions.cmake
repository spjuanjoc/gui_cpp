#
# File: CompilerOptions.cmake
#
# Date:   2021-05-31
# Author: spjuanjoc
#
# Based upon: https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
#
# Function that sets the compiler options for the given target
# This function must be called after add_library()/add_executable() instructions.
#
# See the warnings documentation:
#   MSVC  https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warnings-by-compiler-version?view=msvc-170
#   clang https://clang.llvm.org/docs/UsersManual.html
#   gcc   https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
#
# Usage:
#   set_compiler_options(${TARGET_NAME})
#

function(set_compiler_options TARGET_NAME)

  set(MSVC_OPTIONS
    /W4
    /permissive-
    /w14242
    /w14254
    /w14263
    /w14265
    /w14287
    /we4289
    /w14296
    /w14311
    /w14545
    /w14546
    /w14547
    /w14549
    /w14555
    /w14619
    /w14640
    /w14826
    /w14905
    /w14906
    /w14928
  )

  set(COMMON_OPTIONS
    -Wall
    -Wextra
    -pedantic

    -Wcast-align
    -Wconversion
    -Wdelete-incomplete
    -Wdelete-non-virtual-dtor
    -Wdouble-promotion
    -Wnon-virtual-dtor
    -Wnull-dereference
    -Wold-style-cast
    -Woverloaded-virtual
    -Wshadow
    -Wsign-conversion
    -Wunused
    -Wvarargs
  )

  set(CLANG_OPTIONS
    ${COMMON_OPTIONS}
    -Weverything
    -Wdangling-initializer-list
#    -Wdocumentation
    -Wdynamic-class-memaccess
    -Winvalid-noreturn
    -Wunsequenced
    -Wuser-defined-literals
    -Wvexing-parse

    -Wno-class-varargs
    -Wno-c99-extensions
    -Wno-c++98-compat   # in everything
    -Wno-documentation  # in everything
    -Wno-undefined-var-template
  )

  set(GCC_OPTIONS
    ${COMMON_OPTIONS}
    -Wcast-qual
    -Wctor-dtor-privacy
    -Wdeprecated
    -Wdeprecated-declarations
    -Wduplicated-branches
    -Wduplicated-cond
    -Wfloat-equal
    -Winvalid-offsetof
    -Wlogical-op
    -Wpacked
    -Wpointer-arith
    -Wredundant-decls
    -Wundef
#    -Wunused-macros # Not enabled due to an {fmt} issue https://github.com/fmtlib/fmt/pull/2651
    -Wuseless-cast

    -Wno-class-memaccess
    -Wno-long-long
  )


  ## Warnings as errors
  if (ENABLE_WERROR)
    set(MSVC_OPTIONS  ${MSVC_OPTIONS}   /WX)
    set(CLANG_OPTIONS ${CLANG_OPTIONS}  -Werror)
    set(GCC_OPTIONS   ${GCC_OPTIONS}    -Werror -pedantic-errors)
  endif ()


  ## Set the options for each compiler.
  if(MSVC)
    set(COMPILER_OPTIONS ${MSVC_OPTIONS})
  elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(COMPILER_OPTIONS ${CLANG_OPTIONS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_OPTIONS ${GCC_OPTIONS})
    if(ENABLE_COVERAGE)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage" PARENT_SCOPE) # PARENT_SCOPE required since this is called from a function
      message(STATUS "coverage enabled: ${CMAKE_CXX_FLAGS}")
    endif()
  else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  target_compile_options(${TARGET_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${COMPILER_OPTIONS}>) # for header-only use INTERFACE
  target_compile_features(${TARGET_NAME} PUBLIC cxx_std_23)

  message (STATUS "Target name:     ${TARGET_NAME}")
  message (STATUS "Target options:  ${COMPILER_OPTIONS}")
  message (STATUS "Compiler:        ${CMAKE_CXX_COMPILER}")
  message (STATUS "Compiler ID:     ${CMAKE_CXX_COMPILER_ID}")
  message (STATUS "Platform:        ${CMAKE_SYSTEM_NAME}")

endfunction()
