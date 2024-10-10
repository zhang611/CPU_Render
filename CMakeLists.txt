cmake_minimum_required(VERSION 3.10)
project(Tinyrenderer)
set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()

# set(OpenCV_DIR "D:/Computer Science/Library/opencv/build/x64/mybuild")
set(OpenCV_DIR "D:/Computer Science/Library/opencv/build/x64/vc15/lib")

find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "version:${OpenCV_VERSION}")
message(STATUS "libraries:${OpenCV_LIBS}")
message(STATUS "include path:${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})

# don't need .h file
add_executable(${PROJECT_NAME} main.cpp gl.cpp geometry.cpp model.cpp tgaimage.cpp )
# target_link_libraries(${PROJECT_NAME} PRIVATE tga_lib model_lib)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS})