cmake_minimum_required(VERSION 3.16)
project(miniRT LANGUAGES C)

OPTION (BUILD_SHARED_LIBS OFF)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(lib/ft ${CMAKE_BINARY_DIR}/ft)
add_subdirectory(lib/ftprintf ${CMAKE_BINARY_DIR}/ftprintf)

find_package(OpenGL REQUIRED)
message(STATUS "OpenGL included at ${OPENGL_INCLUDE_DIRS}")
find_package(GLUT REQUIRED)
message(STATUS "GLUT included at ${GLUT_INCLUDE_DIRS}")
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


if  (APPLE)
    include_directories(
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/lib/ft/include
            ${PROJECT_SOURCE_DIR}/lib/ftprintf/include
            ${PROJECT_SOURCE_DIR}/lib/mlx/macOS
            ${PROJECT_SOURCE_DIR}/src
            )
    file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/ft/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/ftprintf/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/mlx/macOS/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )
    add_executable(miniRT ${all_SRCS})
    add_dependencies(miniRT minilibx ft ftprintf)
    target_link_directories(miniRT PRIVATE ${CMAKE_BINARY_DIR}/ft ${CMAKE_BINARY_DIR}/ftprintf ${PROJECT_SOURCE_DIR}/lib/mlx/macOS)
    target_link_libraries(miniRT PRIVATE ft ftprintf mlx ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
    set_target_properties(miniRT PROPERTIES LINK_FLAGS "-framework OpenGL -framework AppKit")
    add_custom_target(
       minilibx
       COMMAND make --silent
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/macOS
    )
    add_custom_target(
        fclean
        COMMAND make clean ${CMAKE_BINARY_DIR}
        COMMAND make clean --silent
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/macOS
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/CMakeCache.txt
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/CMakeFiles/
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/Makefile
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/cmake_install.cmake
    )
    add_definitions(-DMACOS)
else()
    include_directories(
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/lib/ft/include
            ${PROJECT_SOURCE_DIR}/lib/ftprintf/include
            ${PROJECT_SOURCE_DIR}/lib/mlx/linux
            ${PROJECT_SOURCE_DIR}/src
            )
    file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/ft/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/ftprintf/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/mlx/linux/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )
    add_executable(miniRT ${all_SRCS})
    add_dependencies(miniRT minilibx ft)
    target_link_directories(miniRT PRIVATE ${CMAKE_BINARY_DIR}/ftprintf ${CMAKE_BINARY_DIR}/ft ${PROJECT_SOURCE_DIR}/lib/mlx/linux)
    target_link_libraries(miniRT PRIVATE ft ftprintf mlx m X11 Xext pthread  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
    add_custom_target(
       minilibx
       COMMAND make --silent
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/linux
    )
    add_custom_target(
        fclean
        COMMAND make clean ${CMAKE_BINARY_DIR}
        COMMAND make clean --silent
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/linux
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/CMakeCache.txt
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/CMakeFiles/
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/Makefile
        COMMAND rm -rf ${PROJECT_SOURCE_DIR}/cmake_install.cmake
    )
    add_definitions(-DLINUX)
endif()

