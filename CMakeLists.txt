cmake_minimum_required(VERSION 3.14)

project(romdup2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Xml)

add_executable(romdup2
  main.cpp
  game.cpp
  games.cpp
  romdup.cpp
  romdup.h
)
target_link_libraries(romdup2 Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(romdup2 Qt${QT_VERSION_MAJOR}::Xml)

install(TARGETS romdup2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
