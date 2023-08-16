# cmake needs this line
cmake_minimum_required(VERSION 3.10)
 
# Define project name
project(mutex_project)
 
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
set(BOOST_ROOT "/home/slam007/Dev/someip_demo/boost_1_72_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS
    thread
)
message(STATUS "Boost Version:" ${Boost_INCLUDE_DIR})
if(Boost_FOUND)
  MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
  MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
  MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
else()
  MESSAGE( WARNING "Not found Boost")
endif()
if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()
 
include_directories(${Boost_INCLUDE_DIRS})
# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} boost-demo.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})