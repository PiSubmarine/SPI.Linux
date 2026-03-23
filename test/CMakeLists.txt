cmake_minimum_required(VERSION 3.20)

include(FetchContent)

project(PiSubmarine.SPI.Linux.Test LANGUAGES CXX)

set(PiSubmarine.SPI.Linux.Test.Sources
        "PiSubmarine/SPI/Linux/DriverTest.cpp")

enable_testing()

# spdlog
find_package(spdlog)
find_package(GTest)

add_executable(PiSubmarine.SPI.Linux.Test ${PiSubmarine.SPI.Linux.Test.Sources})
PiSubmarineInitTarget(PiSubmarine.SPI.Linux.Test)

target_link_libraries(PiSubmarine.SPI.Linux.Test PRIVATE PiSubmarine.SPI.Linux)
target_link_libraries(PiSubmarine.SPI.Linux.Test PRIVATE spdlog::spdlog)
target_link_libraries(PiSubmarine.SPI.Linux.Test PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(PiSubmarine.SPI.Linux.Test)