cmake_minimum_required(VERSION 3.10)

project(IndustrialVision)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

add_executable(vision_node
    src/main.cpp
    src/converter.cpp
    src/imageCapturer.cpp
    src/histCalculator.cpp
)

target_link_libraries(vision_node 
    ${OpenCV_LIBS}
    ${JSONCPP_LIBRARIES}
)
