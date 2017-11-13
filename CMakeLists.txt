cmake_minimum_required(VERSION 2.8)
project(course01)

add_definitions("-g")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)

add_executable(qobject qobject.cc)
qt5_use_modules(qobject Widgets)

add_executable(implicit_sharing implicit_sharing.cc)
qt5_use_modules(implicit_sharing Widgets)

add_executable(qvariant qvariant.cc)
qt5_use_modules(qvariant Widgets)
