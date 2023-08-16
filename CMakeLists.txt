cmake_minimum_required (VERSION 3.10)
project(vsomeip-demo)
set (CMAKE_CXX_FLAGS "-g -std=c++0x")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
find_package (vsomeip3  REQUIRED)
set(BOOST_ROOT "/home/slam007/Dev/someip_demo/boost_1_72_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
find_package(Boost 1.72 COMPONENTS system thread log REQUIRED )
include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(service-example service-example.cpp)
add_executable(client-example client-example.cpp)
target_link_libraries(service-example vsomeip3 ${Boost_LIBRARIES})
target_link_libraries(client-example vsomeip3 ${Boost_LIBRARIES})