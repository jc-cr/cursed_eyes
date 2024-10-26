cmake_minimum_required(VERSION 3.10)
project(cursed_eyes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set("CMAKE_CXX_FLAGS" "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -Wno-unused-parameter -O3")

# Find required packages
find_package(Curses REQUIRED)

# Create list of source files
set(SOURCES 
    src/main.cc
    src/eye.cc
)

# Add executable
add_executable(cursor_eyes ${SOURCES})

# Add include directory
target_include_directories(cursor_eyes 
    PRIVATE 
        ${CURSES_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(cursor_eyes PRIVATE ${CURSES_LIBRARIES})