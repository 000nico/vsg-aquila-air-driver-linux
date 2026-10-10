cmake_minimum_required(VERSION 3.10)
project(vsg_aquila_air_driver C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
list(APPEND SOURCES ${SRC_SOURCES})

file(GLOB IMGUI_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/imgui/*.cpp"
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(HIDAPI REQUIRED IMPORTED_TARGET hidapi-hidraw)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)
find_package(OpenGL REQUIRED)

add_executable(aquila-air-driver ${SOURCES} ${IMGUI_SOURCES})

target_include_directories(aquila-air-driver PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/imgui"
)

target_link_libraries(aquila-air-driver PRIVATE
    PkgConfig::HIDAPI
    PkgConfig::GLFW
    OpenGL::GL
    ${CMAKE_DL_LIBS}
)
