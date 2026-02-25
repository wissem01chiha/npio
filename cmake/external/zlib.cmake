find_package(ZLIB QUIET)
if(ZLIB_FOUND)
    message(STATUS "zlib found: ${ZLIB_INCLUDE_DIRS}")
else()
    message(STATUS "zlib not found. Downloading and building from source...")
    include(FetchContent)
    FetchContent_Declare(
        zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG master    
    )
    set(ZLIB_BUILD_SHARED OFF)
    set(ZLIB_BUILD_TESTING OFF)
    FetchContent_MakeAvailable(zlib)

    include_directories(SYSTEM ${zlib_SOURCE_DIR})
    message(STATUS "zlib has been fetched and is available at ${zlib_SOURCE_DIR}")
endif()
