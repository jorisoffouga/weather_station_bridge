cmake_minimum_required (VERSION 2.6)

project (weather_station_bridge)

include(FindPkgConfig)

pkg_check_modules(SYSTEMD libsystemd>=211 REQUIRED)

# cpp requirements
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# check results and add flag
if(COMPILER_SUPPORTS_CXX11)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(
    GLOB_RECURSE
    weather_SOURCES
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${weather_SOURCES})

target_link_libraries(${PROJECT_NAME} periphery pthread systemd)
