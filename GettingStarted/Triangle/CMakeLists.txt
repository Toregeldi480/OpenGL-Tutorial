cmake_minimum_required(VERSION 3.10)
project(Triangle LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

# Find dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Add main executable
add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLFW3_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
)
