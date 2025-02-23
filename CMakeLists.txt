cmake_minimum_required(VERSION 3.10...3.21)
project(task-GUI)

# Use vcpkg for dependencies
set(CMAKE_TOOLCHAIN_FILE "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/dev/vcpkg/installed/x64-mingw-dynamic")
# Include source directory
include_directories(src)

# Define the executable
add_executable(task-GUI src/main.cpp src/task_manager.cpp)

# Find and link nlohmann_json
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(task-GUI PRIVATE nlohmann_json::nlohmann_json)
