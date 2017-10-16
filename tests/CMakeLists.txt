cmake_minimum_required(VERSION 3.2.2)

project(clrinverttests)

find_package(Threads REQUIRED)

include_directories(./ ../inc)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_HOME_DIRECTORY}/src/*.cpp")
list(REMOVE_ITEM SOURCES ${CMAKE_HOME_DIRECTORY}/src/main.cpp)

add_executable(clrinverttests ${SOURCES})

target_link_libraries(clrinverttests
                          gmock
												  gmock_main
												  ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME clrinverttests COMMAND $<TARGET_FILE:clrinverttests>)

