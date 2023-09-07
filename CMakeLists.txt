cmake_minimum_required(VERSION 3.16)

project(FormalTask)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(include)

add_executable(main formal_lang.cpp)
target_link_libraries(main PUBLIC AlgorithmCYK)

add_subdirectory(tests)



