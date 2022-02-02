cmake_minimum_required(VERSION 3.1)

project("Smald"
    VERSION "0.3.0"
    DESCRIPTION "A quality of life library, i guess"
    LANGUAGES CXX
)

enable_testing()

add_subdirectory("${PROJECT_SOURCE_DIR}/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/apps")
add_subdirectory("${PROJECT_SOURCE_DIR}/tests")
