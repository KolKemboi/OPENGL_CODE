cmake_minimum_required(VERSION 3.10)
project(vulkan)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

include_directories(${Vulkan_INCLUDE_DIRS})

add_executable(vulkan src/main.cpp src/engine.cpp)

target_link_libraries(vulkan glfw Vulkan::Vulkan)
