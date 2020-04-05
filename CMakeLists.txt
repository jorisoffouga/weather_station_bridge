cmake_minimum_required (VERSION 2.6)

project (weather-station-bridge)

include(FindPkgConfig)

pkg_check_modules(SYSTEMD libsystemd>=211 REQUIRED)
pkg_check_modules(CPERIPHERY libperiphery REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(
    GLOB
    weather_SOURCES
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${weather_SOURCES})

target_link_libraries(${PROJECT_NAME} ${CPERIPHERY_LIBRARIES} pthread ${SYSTEMD_LIBRARIES})
