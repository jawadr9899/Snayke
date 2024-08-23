cmake_minimum_required(VERSION 3.10)
project(Snake-For-Class)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.6.1 COMPONENTS graphics audio network system window REQUIRED)
if(WIN32)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()
add_executable(${PROJECT_NAME} main.cpp)

# Link SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network sfml-system sfml-window)

# Copy resource folders
file(COPY ${CMAKE_SOURCE_DIR}/lib DESTINATION ${CMAKE_BINARY_DIR})