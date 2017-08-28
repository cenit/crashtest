cmake_minimum_required(VERSION 2.8)
project(crashtest)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(MSVC)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS}) 

find_package(OpenCV 3 REQUIRED HINTS /usr/local/opt/opencv3)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(crashtest
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(crashtest 
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES} 
)

