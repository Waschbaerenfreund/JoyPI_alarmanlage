cmake_minimum_required(VERSION 3.13.0)

get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project(${ProjectId} VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB all_Source_Files *.cpp *.c)
add_executable(${PROJECT_NAME} ${all_Source_Files})

# Find and link necessary libraries
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_library(FMT_LIBRARIES NAMES fmt)
find_library(SPI_LIBRARIES NAMES spidev)

target_link_libraries(${ProjectId} ${WIRINGPI_LIBRARIES} ${FMT_LIBRARIES} ${SPI_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)