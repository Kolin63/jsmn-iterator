cmake_minimum_required(VERSION 4.2)

add_executable(example1 example1.c)

target_link_libraries(example1 PRIVATE jsmn-iterator)
target_include_directories(example1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(example1 PROPERTIES
  C_STANDARD 99
  C_STANDARD_REQUIRED ON
)
