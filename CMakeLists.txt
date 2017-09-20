cmake_minimum_required(VERSION 3.8.2)
project(Ripl)

#SET(GCC_COMPILE_FLAGS "-g")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
#SET(GCC_LIN_FLAGS "")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")

# Ripl
file(GLOB_RECURSE RIPL "src/*.c")
# Example
file(GLOB_RECURSE EXAMPLE "example/*.c")

add_executable(Ripl ${RIPL} ${EXAMPLE})
target_link_libraries(Ripl LINK_PUBLIC jack m)
