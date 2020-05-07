cmake_minimum_required(VERSION 3.15)
project(Task4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(SQLiteCpp)

add_executable(Task4 main.cpp src/FilmLibrary.cpp include/FilmLibrary.h src/Film.cpp src/Date.cpp include/Date.h  src/Connector.cpp include/Connector.h include/View.h src/View.cpp include/View.h)

target_link_libraries(Task4 SQLiteCpp)