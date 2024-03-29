if(NOT STD_COMPAT_USE_SYSTEM_GTEST)
  configure_file(GTestCMakeLists.txt.in googletest-download/CMakeLists.txt)

  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
  )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()

  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
  )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
    ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
    EXCLUDE_FROM_ALL)
  include(GoogleTest)
endif()

function(add_gtest)
  get_filename_component(test_name ${ARGV0} NAME_WE)
  add_executable(${test_name} ${ARGV})
  if(STD_COMPAT_USE_SYSTEM_GTEST)
    find_package(GTest REQUIRED)
    target_link_libraries(${test_name} PRIVATE GTest::gtest_main GTest::gtest GTest::gmock)
  else()
    target_link_libraries(${test_name} PRIVATE gtest_main gtest gmock)
  endif()
  gtest_discover_tests(${test_name})
endfunction()

add_gtest(test_stdcompat.cc)

# vim: ft=cmake :
