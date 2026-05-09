cmake_minimum_required(VERSION 4.2)

add_executable(test1 test1.c)

target_link_libraries(test1 PRIVATE jsmn-iterator)
target_include_directories(test1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_test(NAME test1 COMMAND test1)

set_target_properties(test1 PROPERTIES
  C_STANDARD 99
  C_STANDARD_REQUIRED ON
)
