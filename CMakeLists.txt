cmake_minimum_required(VERSION 2.8)
project(crashtest)

if (EXISTS "$ENV{WORKSPACE}/sysconfig/cmake/physycom_config.cmake")
   message(STATUS "Enabling physycom settings")
   include("$ENV{WORKSPACE}/sysconfig/cmake/physycom_config.cmake")
else()
   message(STATUS "Unable to find physycom settings file")
endif()

set (CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(crashtest
  ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(crashtest
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)
