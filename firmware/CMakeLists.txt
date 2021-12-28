cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(ngage-display-converter C CXX ASM)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(-Wall -Wextra)

include_directories(
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/assets)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/libdvi)

add_executable(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/src/main.c
  ${CMAKE_SOURCE_DIR}/src/ngage.c)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

target_link_libraries(${PROJECT_NAME}
  pico_stdlib
  pico_multicore
  pico_util
  libdvi)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})
