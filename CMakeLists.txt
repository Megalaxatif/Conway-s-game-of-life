cmake_minimum_required(VERSION 3.27)

set(EXEC_NAME "Prog")

project(formation-SDL)


add_executable(${EXEC_NAME} src/main.cpp src/texture.cpp)

target_include_directories(${EXEC_NAME} PUBLIC include src/header)

target_link_directories(${EXEC_NAME} PRIVATE lib)

target_link_libraries(${EXEC_NAME} SDL2.dll.a SDL2main SDL2.a)
