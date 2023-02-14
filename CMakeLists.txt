cmake_minimum_required(VERSION 3.16)
project(miniRT LANGUAGES C)

OPTION (BUILD_SHARED_LIBS OFF)
set(CMAKE_BINARY_DIR "./build")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_subdirectory(ft ${CMAKE_BINARY_DIR}/ft)
add_subdirectory(ftprintf ${CMAKE_BINARY_DIR}/ftprintf)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


if  (APPLE)
    include_directories(
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/ft/include
            ${PROJECT_SOURCE_DIR}/ftprintf/include
            ${PROJECT_SOURCE_DIR}/lib/mlx/macOS
            ${PROJECT_SOURCE_DIR}/src
            )
    file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/ft/include/*.h"
        "${PROJECT_SOURCE_DIR}/ftprintf/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/mlx/macOS/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )
    add_executable(miniRT ${all_SRCS})
    add_dependencies(miniRT minilibx ft ftprintf)
    target_link_directories(miniRT PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/ft ${CMAKE_BINARY_DIR}/ftprintf ${PROJECT_SOURCE_DIR}/lib/mlx/macOS)
    target_link_libraries(miniRT PRIVATE ft ftprintf mlx ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
    set_target_properties(miniRT PROPERTIES LINK_FLAGS "-framework OpenGL -framework AppKit")
    add_custom_target(
       minilibx
       COMMAND make --silent
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/macOS
    )

    add_custom_target(
       fclean
       COMMAND make clean --silent
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/macOS
    )
    add_definitions(-DMACOS)
else()
    include_directories(
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/ft/include
            ${PROJECT_SOURCE_DIR}/ftprintf/include
            ${PROJECT_SOURCE_DIR}/lib/mlx/linux
            ${PROJECT_SOURCE_DIR}/src
            )
    file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/ft/include/*.h"
        "${PROJECT_SOURCE_DIR}/ftprintf/include/*.h"
        "${PROJECT_SOURCE_DIR}/lib/mlx/linux/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )
    add_executable(miniRT ${all_SRCS})
    add_dependencies(miniRT minilibx ft ftprintf)
    target_link_directories(miniRT PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/ft ${CMAKE_BINARY_DIR}/ftprintf ${PROJECT_SOURCE_DIR}/lib/mlx/linux)
    target_link_libraries(miniRT PRIVATE ft ftprintf mlx ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
    set_target_properties(miniRT PROPERTIES LINK_FLAGS "-lm -lX11 -lXext -lpthread")
    add_custom_target(
       minilibx
       COMMAND make --silent
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/linux
    )
    add_custom_target(
       fclean
       COMMAND make clean --silent
       WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/mlx/linux
    )
    add_definitions(-DLINUX)
endif()

