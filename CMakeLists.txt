CMAKE_MINIMUM_REQUIRED(VERSION 3.12...3.27)
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(NPIO VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF)

set(NPIO_TEST_SOURCES
  test/example.cpp
)

set(NPIO_EXAMPLE_SOURCES
  example/example.cpp
)

option(ENABLE_STATIC "Build static library" ON)
option(ENABLE_TESTS "Build tests" ON)
option(ENABLE_EXAMPLES "Build examples" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(cmake/external/zlib.cmake)

if(ENABLE_STATIC)
  add_library(npio-static STATIC "npio.cpp")
  set_target_properties(npio-static PROPERTIES OUTPUT_NAME "npio")
  target_link_libraries(npio-static PUBLIC ZLIB::ZLIBSTATIC)
else()
  # build shared library
  add_library(npio SHARED "npio.cpp")
  set_target_properties(npio PROPERTIES OUTPUT_NAME "npio")
  target_link_libraries(npio PUBLIC ZLIB::ZLIB)
endif()

if(ENABLE_TESTS)
  enable_testing()
  include(cmake/external/googletest.cmake)
  foreach(TEST_SOURCE_FILE IN LISTS NPIO_TEST_SOURCES)
    get_filename_component(TEST_EXECUTABLE_NAME ${TEST_SOURCE_FILE} NAME_WE)
    add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILE})
    target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE 
      ${GTEST_INCLUDE_DIRS} 
      ${CMAKE_SOURCE_DIR}
    )
    add_test (NAME ${TEST_EXECUTABLE_NAME} COMMAND ${TEST_EXECUTABLE_NAME})
    if(ENABLE_STATIC)
      target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE GTest::gtest_main npio-static)
      add_dependencies(${TEST_EXECUTABLE_NAME} npio-static)
    else()
      target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE GTest::gtest_main npio)
      add_dependencies(${TEST_EXECUTABLE_NAME} npio)
    endif()
    include(GoogleTest)
    gtest_discover_tests(${TEST_EXECUTABLE_NAME})
  endforeach()
endif()

if(ENABLE_EXAMPLES)

endif()

install(FILES "npio.h" DESTINATION include)
if(ENABLE_STATIC)
  install(TARGETS "npio-static" ARCHIVE DESTINATION lib)
else()
  install(TARGETS "npio" LIBRARY DESTINATION lib 
  PERMISSIONS OWNER_READ OWNER_WRITE 
  OWNER_EXECUTE GROUP_READ 
  GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  )
endif()


