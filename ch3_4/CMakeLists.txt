cmake_minimum_required( VERSION 2.8 )

project( plotTrajectory )

set( CMAKE_BUILD_TYPE "Release")
# set( CMAKE_CXX_FLAGS ".03")

add_executable( main /home/psj/Desktop/slam_study/ch3_4/src/plotTrajectory.cpp)


# add_executable( main /home/psj/Desktop/slam_study/ch2/src/main.cpp)
# add_library(helloslam SHARED /home/psj/Desktop/slam_study/ch2/src/helloslam.cpp)

include_directories("/usr/include/eigen3")


find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
target_link_libraries(main ${Pangolin_LIBRARIES})

#set( CMAKE_BUILD_TYPE "Debug")