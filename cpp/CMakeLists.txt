cmake_minimum_required(VERSION 2.8)

project(Mitsuba-Tests)

find_package(OpenCV REQUIRED)

set(${PROJECT_NAME}_CPP imageProcessing.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_CPP})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
