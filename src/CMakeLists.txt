cmake_minimum_required(VERSION 3.16)
project(ezOutletTray)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# ✅ Enable AUTOMOC
set(CMAKE_AUTOMOC ON)

add_executable(ezOutletTray
    main.cpp
    traycontroller.cpp
    traycontroller.h
)

target_link_libraries(ezOutletTray
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)
