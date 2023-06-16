## template for a CMake C++ Library
cmake_minimum_required(VERSION 3.14)
project(std_compat VERSION "0.0.19" LANGUAGES CXX)

#correct was to set a default build type
# https://blog.kitware.com/cmake-and-the-default-build-type/
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type was set. Setting build type to ${default_build_type}.")
  set(CMAKE_BUILD_TYPE ${default_build_type} CACHE 
    STRING "Choose the type to build" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

include(CTest)
include(GNUInstallDirs)
include(CheckCXXCompilerFlag)

if(NOT USE_SANITIZER)
  set(USE_SANITIZER "" CACHE STRING "use a build sanitizer" FORCE)
endif()
set_property(CACHE USE_SANITIZER PROPERTY STRINGS "" "Address" "Thread" "Undefined" "Leak" "Memory")
if (USE_SANITIZER STREQUAL "Address")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
elseif (USE_SANITIZER STREQUAL "Thread")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=thread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
elseif (USE_SANITIZER STREQUAL "Undefined")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
elseif (USE_SANITIZER STREQUAL "Leak")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=leak")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
elseif (USE_SANITIZER STREQUAL "Memory")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=memory")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
endif()

#compiler flags and standard conformance checks
check_cxx_compiler_flag("-fno-omit-frame-pointer" HAVE_NO_OMIT_FRAME_POINTER)
set(NO_OMIT_FRAME_POINTER_FLAG "")
if(HAVE_NO_OMIT_FRAME_POINTER)
  set(NO_OMIT_FRAME_POINTER_FLAG "-fno-omit-frame-pointer")
endif()

option(STDCOMPAT_CXX_UNSTABLE "allow the extension versions of the compiler" OFF)
set(default_cxx_standard 17)
if(NOT STDCOMPAT_CXX_VERSION)
  set(STDCOMPAT_CXX_VERSION ${default_cxx_standard} CACHE 
    STRING "Which version of the cxx standard to expect" FORCE)
endif()
set_property(CACHE STDCOMPAT_CXX_VERSION PROPERTY STRINGS 11 14 17 20)

message("using c++${STDCOMPAT_CXX_VERSION} with unstable=${STDCOMPAT_CXX_UNSTABLE}")

#check for c++17 features
function(check_cpp_standard api)
  string(TOUPPER "${api}" HEADER_SUFFIX)
  try_compile(
    COMPILED
    ${CMAKE_BINARY_DIR}
    SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/checks/${api}.cc" 
    CXX_STANDARD ${STDCOMPAT_CXX_VERSION}
    CXX_STANDARD_REQUIRED ${STDCOMPAT_CXX_UNSTABLE}
  )
  message(STATUS "Checking for ${api}: ${COMPILED}")
  set(STDCOMPAT_HAS_${HEADER_SUFFIX} ${COMPILED} PARENT_SCOPE)
endfunction()

check_cpp_standard(lerp)
check_cpp_standard(transform_reduce)
check_cpp_standard(exclusive_scan)
check_cpp_standard(exchange)
check_cpp_standard(rbeginend)
check_cpp_standard(optional)
check_cpp_standard(variant)
check_cpp_standard(make_unique)
check_cpp_standard(conjunction)
check_cpp_standard(multiplies)
check_cpp_standard(midpoint)
check_cpp_standard(nth_element)
check_cpp_standard(span)
check_cpp_standard(void_t)
check_cpp_standard(negation)
check_cpp_standard(clamp)
check_cpp_standard(string_view)
check_cpp_standard(is_null_pointer)
check_cpp_standard(four_arg_equals)
check_cpp_standard(endian)
check_cpp_standard(shared_mutex)
check_cpp_standard(mutex)
check_cpp_standard(cbeginend)
check_cpp_standard(byteswap)

if(NOT (STDCOMPAT_HAS_OPTIONAL AND STDCOMPAT_HAS_VARIANT AND STDCOMPAT_HAS_STRING_VIEW AND STDCOMPAT_HAS_SHARED_MUTEX))
    set(STDCOMPAT_BOOST_REQUIRED TRUE)
else()
    set(STDCOMPAT_BOOST_REQUIRED FALSE)
endif()
message(WARNING "STDCOMPAT_BOOST_REQUIRED=${STDCOMPAT_BOOST_REQUIRED}")


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "build std_compat as a shared library" ON)

add_library(std_compat
  ./src/std_compat.cc
  ./src/variant.cc
  ./src/optional.cc
  ./src/span.cc
  ./include/algorithm.h
  ./include/numeric.h
  ./include/std_compat.h
  ./include/functional.h
  ./include/variant.h
  ./include/memory.h
  ./include/type_traits.h
  ./include/span.h
  ./include/iterator.h
  ./include/utility.h
  ./include/optional.h
  ./include/cstddef.h
  ./include/language.h
  ./include/string_view.h
  ./include/cmath.h
  )
target_compile_features(std_compat PUBLIC cxx_std_${STDCOMPAT_CXX_VERSION})
target_include_directories(std_compat 
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/std_compat>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  )
target_compile_options(std_compat PRIVATE 
  $<$<CONFIG:Debug>: -Wall -Wextra -Wpedantic>
  $<$<CONFIG:RelWithDebInfo>: ${NO_OMIT_FRAME_POINTER_FLAG}>
  )
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/std_compat_version.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/std_compat/std_compat_version.h
  )

if(NOT (STDCOMPAT_HAS_VARIANT OR STDCOMPAT_HAS_OPTIONAL))
  find_package(Boost COMPONENTS REQUIRED)
  target_link_libraries(std_compat PUBLIC Boost::boost)
  set(STDCOMPAT_BOOST_CPPFLAGS "-I${Boost_INCLUDE_DIRS}")
  set(STDCOMPAT_BOOST_LDFLAGS "")
else()
  set(STDCOMPAT_BOOST_CPPFLAGS "")
  set(STDCOMPAT_BOOST_LDFLAGS "")
endif()

if(NOT STDCOMPAT_HAS_SHARED_MUTEX)
  find_package(Boost COMPONENTS thread REQUIRED)
  find_package(Threads REQUIRED)
  target_link_libraries(std_compat PUBLIC Boost::thread)
  set(STDCOMPAT_BOOST_CPPFLAGS "${STDCOMPAT_BOOST_CPPFLAGS} -I${Boost_INCLUDE_DIRS}")
  get_target_property(thread_lib Threads::Threads INTERFACE_LINK_LIBRARIES)
  if("${thread_lib}" STREQUAL "thread_lib-NOTFOUND")
    set(STDCOMPAT_BOOST_LDFLAGS "")
  else()
    set(STDCOMPAT_BOOST_LDFLAGS "${thread_lib}")
  endif()
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/std_compat.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/std_compat.pc
  @ONLY
  )
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/std_compat_cxx.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/std_compat_cxx.pc
  @ONLY
  )



include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/std_compatConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/std_compat/std_compatConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_PREFIX}/share/std_compat/"
  )
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/std_compat/std_compatConfigVersion.cmake"
  VERSION ${std_compat_VERISON}
  COMPATIBILITY SameMinorVersion
  )
export(TARGETS std_compat NAMESPACE std_compat:: FILE std_compatTargets.cmake)
install(TARGETS std_compat EXPORT std_compatTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
install(EXPORT std_compatTargets NAMESPACE std_compat:: DESTINATION share/std_compat/cmake)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/std_compat/std_compatConfigVersion.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/std_compat/std_compatConfig.cmake"
  DESTINATION share/std_compat/cmake
  )
install(DIRECTORY include/ DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/std_compat)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/std_compat/std_compat_version.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/std_compat)
install(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/std_compat.pc 
  ${CMAKE_CURRENT_BINARY_DIR}/std_compat_cxx.pc 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pkgconfig)

option(STD_COMPAT_USE_SYSTEM_GTEST "use the system gtest dependency" OFF)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

option(USE_CLANG_TIDY "include clang-tidy warnings in the build log" OFF)
if(USE_CLANG_TIDY)
  find_program(CLANG_TIDY clang-tidy)
  set_target_properties(std_compat PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY}")
  set_target_properties(std_compat PROPERTIES C_CLANG_TIDY "${CLANG_TIDY}")
endif()

option(USE_INCLUDE_WHAT_YOU_USE "include include-what-you-use warnings in the build log" OFF)
if(USE_INCLUDE_WHAT_YOU_USE)
  find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
  set_target_properties(std_compat PROPERTIES CXX_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
  set_target_properties(std_compat PROPERTIES C_INCLUDE_WHAT_YOU_USE "${INCLUDE_WHAT_YOU_USE}")
endif()

option(BUILD_DOCS "build the documentation" OFF)
if(BUILD_DOCS)
  find_package(Doxygen REQUIRED dot)
  set(DOXYGEN_MAN_LINKS YES)
  set(DOXYGEN_GENERATE_MAN YES)
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_EXTRACT_LOCAL_METHODS YES)
  set(DOXYGEN_EXTRACT_STATIC YES)
  set(DOXYGEN_MACRO_EXPANSION YES)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
  doxygen_add_docs(
    docs
    ${PROJECT_SOURCE_DIR}/README.md
    ${PROJECT_SOURCE_DIR}/include
    COMMENT "Generate Documenation"
  )
endif()
# vim: ft=cmake :
