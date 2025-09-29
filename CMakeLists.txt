cmake_minimum_required(VERSION 3.10)
project(SnakeGame C)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

# Include directories
include_directories(
    "C:/Users/Drakendgarp/Downloads/Neverland/include"
    "C:/msys64/mingw64/include"
)

# Library directories
link_directories(
    "C:/Users/Drakendgarp/Downloads/Neverland/SDL3-3.2.22/x86_64-w64-mingw32/lib"
    "C:/msys64/mingw64/lib"
)

# Source files
file(GLOB SRC "*.c")

# Executable
add_executable(main ${SRC})

# Link libraries
target_link_libraries(main SDL3)

# Optional: Windows GUI flag (-mwindows)
if(MINGW)
    set_target_properties(main PROPERTIES LINK_FLAGS "-mwindows")
endif()
