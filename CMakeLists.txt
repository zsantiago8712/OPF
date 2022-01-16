cmake_minimum_required(VERSION 3.19)

set(CMAKE_C_STANDARD 11)
project(CBLAS)
set(SRC src)


add_executable(${PROJECT_NAME} main.c)

add_subdirectory(${SRC}/)

target_include_directories(${PROJECT_NAME} PUBLIC ${SRC})

target_link_directories(${PROJECT_NAME} PRIVATE ${SRC})

target_link_libraries(${PROJECT_NAME} includes)
