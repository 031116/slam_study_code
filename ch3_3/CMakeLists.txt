cmake_minimum_required( VERSION 2.8 )

project( coordinateTransform )

set( CMAKE_BUILD_TYPE "Release")
# set( CMAKE_CXX_FLAGS ".03")

add_executable( main /home/psj/Desktop/slam_study/ch3_3/src/coordinateTransform.cpp)


# add_executable( main /home/psj/Desktop/slam_study/ch2/src/main.cpp)
# add_library(helloslam SHARED /home/psj/Desktop/slam_study/ch2/src/helloslam.cpp)
# target_link_libraries( main helloslam)

include_directories("/usr/include/eigen3")

#set( CMAKE_BUILD_TYPE "Debug")