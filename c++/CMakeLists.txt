cmake_minimum_required(VERSION 3.10)
project(RemotePull VERSION 1.0 LANGUAGES CXX)

# Qt5 Instellingen
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON) # Belangrijk voor Qt Signals/Slots
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Bronbestanden
set(SOURCES
    main.cpp
    mainwindow.cpp
    rsynccore.cpp
    argumenthandler.cpp
    progressdialog.cpp
    mainwindow.h
    rsynccore.h
    argumenthandler.h
    progressdialog.h
)

add_executable(RemotePull ${SOURCES})

# Linken aan Qt5
target_link_libraries(RemotePull Qt5::Widgets)
