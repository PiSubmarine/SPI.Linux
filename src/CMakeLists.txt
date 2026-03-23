message("${_build_cmake_local}")
include("${_build_cmake_local}")

if(NOT UNIX)
    message(FATAL_ERROR "PiSubmarine.SPI.Linux can only be built for Linux target.")
endif ()

add_library(PiSubmarine.SPI.Linux PiSubmarine/SPI/Linux/Driver.cpp)
target_include_directories(PiSubmarine.SPI.Linux PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../public")
PiSubmarineInitTarget(PiSubmarine.SPI.Linux)

PiSubmarineAddDependency("https://github.com/PiSubmarine/SPI.Api" "")
target_link_libraries(PiSubmarine.SPI.Linux PUBLIC PiSubmarine.SPI.Api)