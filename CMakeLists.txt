CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.27)
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(NPIO VERSION 0.1.0 LANGUAGES C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(BUILD_SHARED_LIBS OFF)
set (CTEST_OUTPUT_ON_FAILURE TRUE)
option(ENABLE_STATIC "build static library" ON)
option(ENABLE_TESTS "build tests" ON)

set(NPIO_TEST_SOURCES
  test/test_npio_strerror.c
  test/test_npy_init.c
  test/test_npy_save.c
  test/test_npz_load.c
)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(cmake/external/zlib.cmake)

if(ENABLE_STATIC)
  add_library(npio-static STATIC "src/npio.c")
  set_target_properties(npio-static PROPERTIES OUTPUT_NAME "npio")
  if(ZLIB_FOUND)
    target_link_libraries(npio-static PUBLIC ZLIB::ZLIB)
  else()
    target_link_libraries(npio-static PUBLIC ZLIB::ZLIBSTATIC)
  endif()
else()
  add_library(npio SHARED "src/npio.c")
  set_target_properties(npio PROPERTIES OUTPUT_NAME "npio")
  target_link_libraries(npio PUBLIC ZLIB::ZLIB)
endif()

if(ENABLE_TESTS)
  enable_testing()
  include(cmake/external/unity.cmake)
  foreach(TEST_SOURCE_FILE IN LISTS NPIO_TEST_SOURCES)
    get_filename_component(TEST_EXECUTABLE_NAME ${TEST_SOURCE_FILE} NAME_WE)
    add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILE})
    target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE 
      ${UNITY_INCLUDE_DIRS} 
      ${CMAKE_SOURCE_DIR}/src
    )
    add_test (NAME ${TEST_EXECUTABLE_NAME} COMMAND ${TEST_EXECUTABLE_NAME})
    if(ENABLE_STATIC)
      target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE unity npio-static)
      add_dependencies(${TEST_EXECUTABLE_NAME} npio-static)
    else()
      target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE unity npio)
      add_dependencies(${TEST_EXECUTABLE_NAME} npio)
    endif()
  endforeach()
endif()

install(FILES "src/npio.h" DESTINATION include)
if(ENABLE_STATIC)
  install(TARGETS "npio-static" ARCHIVE DESTINATION lib)
else()
  install(TARGETS "npio" LIBRARY DESTINATION lib 
  PERMISSIONS OWNER_READ OWNER_WRITE 
  OWNER_EXECUTE GROUP_READ 
  GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  )
endif()


