cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

project(${ProjectId} VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB all_Source_Files *.cpp)
add_executable(${PROJECT_NAME} ${all_Source_Files})

find_package(fmt REQUIRED)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(${ProjectId} ${WIRINGPI_LIBRARIES} fmt::fmt)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)