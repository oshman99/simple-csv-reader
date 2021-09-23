cmake_minimum_required(VERSION 3.2)

project (csvreader)
set(CMAKE_CXX_STANDARD 17)

#sources
set(READER_SRC
    src/main.cpp
    src/csvMapClass.h
    src/csvMapClass.cpp
    )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/*.csv
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#executalbe
add_executable(csvreader ${READER_SRC})
include_directories(src/)
