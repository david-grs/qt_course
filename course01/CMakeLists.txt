cmake_minimum_required(VERSION 2.8)
project(course01)

add_definitions(" -DQT_DEBUG -DQT_CORE_LIB ")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
add_executable(qobject qobject.cc)

qt5_use_modules(qobject Widgets)
