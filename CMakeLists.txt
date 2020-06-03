cmake_minimum_required(VERSION 3.12)

project(App)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport)

file(GLOB HEADERS /*.hpp)
file(GLOB SOURCES library/*.cpp)

add_library(library ${HEADERS} ${SOURCES})
target_include_directories(library PUBLIC ./library/)

set_target_properties(library PROPERTIES CXX_STANDARD 17)

add_executable(app
               application/mainwindow.cpp
               application/main.cpp
)

target_link_libraries(app library)
target_link_libraries(app Qt5::Widgets Qt5::PrintSupport)

set_target_properties(app PROPERTIES CXX_STANDARD 17)

include_directories(3rdparty)
add_subdirectory(3rdparty/gtest)

add_executable(simple_test tests/main.cpp tests/simple_test.cpp)
target_link_libraries(simple_test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT} pthread)

enable_testing()
add_test(NAME simple_test COMMAND simple_test)
