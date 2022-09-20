
# add google test for ut
if (DEFINED ENV{USE_GTEST_URL})
    set(GTEST_SOURCE_URL "$ENV{USE_GTEST_URL}")
else ()
    # default using 1.12.1, for legacy compilers using 1.10
    set(GTEST_SOURCE_URL "https://github.com/google/googletest/archive/release-1.12.1.tar.gz")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(GTEST_SOURCE_URL "https://github.com/google/googletest/archive/release-1.10.0.tar.gz")
    endif()
endif ()

FetchContent_Declare(
    googletest
    URL ${GTEST_SOURCE_URL}
)

find_package(GTest)

if (${GTest_FOUND})
    message(STATUS "Using gtest from system")
    include_directories(${GTEST_INCLUDE_DIRS})
else ()
    message(STATUS "Using gtest from source")
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif()

    set(GTEST_LIBRARIES gtest)
    set(GMOCK_LIBRARIES gmock)
    set(GTEST_MAIN_LIBRARIES gtest_main)
endif ()



set(ut_files
    ut/test_bfprt.cpp
)

add_executable(testing-ut ${ut_files})
target_include_directories(testing-ut PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(testing-ut PRIVATE ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
gtest_discover_tests(testing-ut)

