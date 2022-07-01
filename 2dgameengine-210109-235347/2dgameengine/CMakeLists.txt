cmake_minimum_required(VERSION 3.10)
project(2dgameengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(gameengine ${SRC_FILES})

target_compile_options(gameengine PRIVATE -Wall)
target_compile_options(gameengine PRIVATE -Wfatal-errors)

target_include_directories(gameengine
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
	${CMAKE_CURRENT_SOURCE_DIR}/src/Game
	${CMAKE_CURRENT_SOURCE_DIR}/src/Logger
	${CMAKE_CURRENT_SOURCE_DIR}/src/ECS
	${CMAKE_CURRENT_SOURCE_DIR}/src/AssetManager
)

target_link_libraries(gameengine
    SDL2 SDL2_image SDL2_ttf SDL2_mixer
    lua dl
)