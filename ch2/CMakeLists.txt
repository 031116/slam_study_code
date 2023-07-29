cmake_minimum_required( VERSION 2.8 )

project( main )


add_executable( main /home/psj/Desktop/slam_study/ch2/src/main.cpp)
add_library(helloslam SHARED /home/psj/Desktop/slam_study/ch2/src/helloslam.cpp)
target_link_libraries( main helloslam)

#set( CMAKE_BUILD_TYPE "Debug")