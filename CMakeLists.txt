cmake_minimum_required(VERSION 3.0)
project(Tetris)

add_compile_options(-Wall -Wextra -Werror -pedantic -std=c++20 -g)

# Set the SFML library path
set(SFML_DIR "/path/to/sfml/lib/cmake/SFML")

# Find the SFML components
find_package(SFML 2.5 COMPONENTS graphics window system audio network REQUIRED)

# Add the source files
set(SOURCES
    src/main.cc)

# Create the executable and link SFML libraries
add_executable(Tetris ${SOURCES})
target_link_libraries(Tetris sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
