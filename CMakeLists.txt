cmake_minimum_required(VERSION 2.8)
project(MainProject)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(HEADER_FILES
include/GerenteBD.h
include/GerenteLogin.h
include/Reserva.h
include/SistemaLinf.h
include/Usuario.h)

add_library(mylib src/GerenteBD.cpp
src/GerenteLogin.cpp
src/Reserva.cpp
src/SistemaLinf.cpp
src/Usuario.cpp )


############ outras ideias

SOURCES

cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( include )
set( SOURCES
src/Usuario.cpp
src/Reserva.cpp
src/GerenteBD.cpp
src/GerenteLogin.cpp
src/SistemaLinf.cpp)

add_executable( DisplayImage Main.cpp ${SOURCES} )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )

# fonte
# http://docs.opencv.org/3.2.0/db/df5/tutorial_linux_gcc_cmake.html
# https://cmake.org/cmake-tutorial/
# http://docs.ros.org/kinetic/api/catkin/html/howto/format2/building_libraries.html
# https://developer.android.com/studio/projects/add-native-code.html?hl=pt-br
