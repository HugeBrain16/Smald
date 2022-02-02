include_directories("${PROJECT_SOURCE_DIR}/include")

file(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/test_conf.conf"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/"
)

add_definitions(
    -DTEST_CONF_FILEPATH="${CMAKE_CURRENT_BINARY_DIR}/test_conf.conf"
)

add_executable(test_trim test_trim.cpp)
add_executable(test_parse_args test_parse_args.cpp)
add_executable(test_command test_command.cpp)
add_executable(test_conf test_conf.cpp)
target_link_libraries(test_trim PUBLIC smald)
target_link_libraries(test_parse_args PUBLIC smald)
target_link_libraries(test_command PUBLIC smald)
target_link_libraries(test_conf PUBLIC smald)

add_test(TestTrim "${CMAKE_CURRENT_BINARY_DIR}/test_trim")
add_test(TestParseArgs "${CMAKE_CURRENT_BINARY_DIR}/test_parse_args")
add_test(TestCommand "${CMAKE_CURRENT_BINARY_DIR}/test_command")
add_test(TestConf "${CMAKE_CURRENT_BINARY_DIR}/test_conf")
