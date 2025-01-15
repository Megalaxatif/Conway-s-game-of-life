cmake_minimum_required(VERSION 3.27)

set(EXEC_NAME "Prog")

project(formation-SDL)

file(GLOB IMGUI_FILES "src/imgui/*.cpp")
file(GLOB SRC_FILES "src/*.cpp")

add_executable(${EXEC_NAME} ${SRC_FILES} ${IMGUI_FILES})

target_include_directories(${EXEC_NAME} PUBLIC include src/header src/imgui)

target_link_directories(${EXEC_NAME} PRIVATE lib)

target_link_libraries(${EXEC_NAME} SDL2.dll.a SDL2main SDL2.a)
