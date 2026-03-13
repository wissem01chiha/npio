cmake_minimum_required(VERSION 3.24)

if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW) # Enable MSVC_RUNTIME_LIBRARY setting
endif()
if(POLICY CMP0092)
  cmake_policy(SET CMP0092 NEW) # disable /W3 warning, if possible
endif()

project(
  npio
  VERSION 0.1.0
  DESCRIPTION "NUMPY NPY/NPZ File I/O Library"
  HOMEPAGE_URL "https://github.com/wissem01chiha/npio"
  LANGUAGES C 
)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(CMakePackageConfigHelpers)
include(CMakeDependentOption)
include(CheckCCompilerFlag)
include(GNUInstallDirs)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

set (CTEST_OUTPUT_ON_FAILURE TRUE)
set(BUILD_TESTING ON)

option(NPIO_BUILD_SHARED "Build shared library" OFF)

cmake_dependent_option(NPIO_BUILD_TESTS
  "Build the unit tests when BUILD_TESTING is enabled and we are the root project" ON
  "BUILD_TESTING;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)

option(ASAN "Enable AddressSanitizer" OFF)

if(ASAN)
  if(CMAKE_C_COMPILER_ID MATCHES "AppleClang|GNU|Clang")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
  endif()
endif()

set(npio_sources 
  src/npio.c
)

include(cmake/external/zlib.cmake)

if(NPIO_BUILD_SHARED)
 add_library(npio SHARED ${npio_sources})
 set_target_properties(npio PROPERTIES OUTPUT_NAME "npio")
 target_link_libraries(npio PUBLIC ZLIB::ZLIB)
endif()

add_library(npio_a STATIC ${npio_sources})
set_target_properties(npio_a PROPERTIES OUTPUT_NAME "npio")
if(ZLIB_FOUND)
  target_link_libraries(npio_a PUBLIC ZLIB::ZLIB)
else()
  target_link_libraries(npio_a PUBLIC ZLIB::ZLIBSTATIC)
endif()

if(NPIO_BUILD_TESTS)

  set(npio_test_sources 
    test/test_npio_strerror.c
    test/test_npy_array_create.c
    test/test_npy_load.c
    test/test_npy_save.c
    test/test_npz_load.c
  )

  include(CTest)
  enable_testing()
  include(cmake/external/unity.cmake)

  foreach(npio_test_source IN LISTS npio_test_sources)

    get_filename_component(npio_test_bin ${npio_test_source} NAME_WE)
    add_executable(${npio_test_bin} ${npio_test_source})
    target_include_directories(${npio_test_bin} PRIVATE 
      ${UNITY_INCLUDE_DIRS} 
      ${CMAKE_SOURCE_DIR}/src
    )
    add_test (NAME ${npio_test_bin} 
      COMMAND ${npio_test_bin}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    if(NPIO_BUILD_SHARED)
      target_link_libraries(${npio_test_bin} PRIVATE unity npio)
      add_dependencies(${npio_test_bin} npio)
    else()
      target_link_libraries(${npio_test_bin} PRIVATE unity npio_a)
      add_dependencies(${npio_test_bin} npio_a)
    endif()

  endforeach()
endif()

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  @ONLY
)

install(DIRECTORY src/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING PATTERN "*.*h"
)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)

if(NPIO_BUILD_SHARED)
  install(TARGETS npio  EXPORT npioTargets)
else()
  install(TARGETS npio_a  EXPORT npioTargets)
endif()

write_basic_package_version_file("npio-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/npio-config.cmake.in"
  "${PROJECT_BINARY_DIR}/npio-config.cmake"
  @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/npio-config-version.cmake"
  "${PROJECT_BINARY_DIR}/npio-config.cmake"
  DESTINATION share/cmake/mio)

set(CPACK_PACKAGE_VENDOR "wissem")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "NUMPY NPY/NPZ File I/O Library")
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/wissem01chiha/npio")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)

