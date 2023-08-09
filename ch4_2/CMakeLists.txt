cmake_minimum_required( VERSION 2.8 )
add_definitions( -std=c++11 )

project( trajectoryError )


set( CMAKE_BUILD_TYPE "Release")
# set( CMAKE_CXX_FLAGS ".03")

add_executable( main /home/psj/Desktop/slam_study/ch4_2/src/trajectoryError.cpp)


include_directories("/usr/include/eigen3")


find_package(Sophus REQUIRED)
find_package(Pangolin REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

target_link_libraries( main ${Sophus_LIBRARIES} fmt)
target_link_libraries( main ${Pangolin_LIBRARIES})

#set( CMAKE_BUILD_TYPE "Debug")