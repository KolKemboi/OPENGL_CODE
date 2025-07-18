
cmake_minimum_required(VERSION 3.10)
set(PROJ_NAME OpenGLProject)

project(${PROJ_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extLibs/imgui)
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(IMGUI_SOURCES
  ${IMGUI_DIR}/imgui.cpp
  ${IMGUI_DIR}/imgui_demo.cpp
  ${IMGUI_DIR}/imgui_draw.cpp
  ${IMGUI_DIR}/imgui_impl_glfw.cpp
  ${IMGUI_DIR}/imgui_impl_opengl3.cpp
  ${IMGUI_DIR}/imgui_tables.cpp
  ${IMGUI_DIR}/imgui_widgets.cpp
) 

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

add_executable(${PROJ_NAME}
  src/App.cpp 
  src/toolbox/engine.cpp 
  src/toolbox/model.cpp 
  src/toolbox/shader.cpp 
  src/toolbox/camera.cpp 
  src/glad.c
)

target_include_directories(${PROJ_NAME} PUBLIC ${GLAD_DIR})

# Include directories
include_directories(include)

# Add the executable and link the libraries

target_link_libraries(${PROJ_NAME} 
  imgui
  glfw 
  GL
)
