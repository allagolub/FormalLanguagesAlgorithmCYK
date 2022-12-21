include_directories(../include)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
        SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" ${PROJECT_SOURCE_DIR}/cmake)

SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")

include(CodeCoverage)

enable_testing()
add_executable(testing main.cpp test.cpp test.h)
target_link_libraries(testing AlgorithmCYK GTest::gtest_main gcov Threads::Threads)

include(GoogleTest)
gtest_discover_tests(testing)
setup_target_for_coverage(coverage ${PROJECT_SOURCE_DIR}/bin/testing coverage)