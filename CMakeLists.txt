cmake_minimum_required(VERSION 4.2)

project(jsmn-iterator)

enable_testing()
add_subdirectory(tests)
add_subdirectory(examples)

add_library(${PROJECT_NAME} src/jsmn-iterator.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
