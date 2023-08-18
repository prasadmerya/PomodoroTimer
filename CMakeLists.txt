cmake_minimum_required(VERSION 3.10)

# set the project name
project(POMODOROtimer)

# Add source files here
set(SOURCES pomodoro.c)

add_executable( ${CMAKE_PROJECT_NAME} ${SOURCES} )

# Link any required libraries
target_link_libraries(${CMAKE_PROJECT_NAME} pthread) # Link the pthread library
