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




