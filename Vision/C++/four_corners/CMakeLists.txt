cmake_minimum_required(VERSION 2.8)
project( FourCorners )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( four_corners four_corners.cpp )
target_link_libraries( four_corners ${OpenCV_LIBS} )