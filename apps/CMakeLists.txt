add_executable(demo demo.cpp)
target_include_directories(demo PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(demo PUBLIC smald)
