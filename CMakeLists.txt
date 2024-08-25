cmake_minimum_required(VERSION 3.10)
project(Snayke)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.6.1 COMPONENTS graphics audio network system window REQUIRED)

# Collect all source files
file(GLOB_RECURSE SOURCE_FILES 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Collect all header files
file(GLOB_RECURSE HEADER_FILES 
    "${CMAKE_SOURCE_DIR}/src/include/*.hpp"
)

# Create a static library with all your source files
add_library(${PROJECT_NAME}_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Set include directories for the library
target_include_directories(${PROJECT_NAME}_lib PUBLIC 
    "${CMAKE_SOURCE_DIR}/src/include"
)

# Create the executable
add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/src/main.cpp")

# Link the executable with the library
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        ${PROJECT_NAME}_lib
        sfml-graphics sfml-audio sfml-network sfml-system sfml-window
)

# Set icon for Windows
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
    set(APP_ICON_RESOURCE "${CMAKE_SOURCE_DIR}/lib/images/icon.png")
    target_sources(${PROJECT_NAME} PRIVATE ${APP_ICON_RESOURCE})
endif()

# Copy resource folders
file(COPY 
    "${CMAKE_SOURCE_DIR}/lib/fonts"
    "${CMAKE_SOURCE_DIR}/lib/images"
    "${CMAKE_SOURCE_DIR}/lib/sounds"
    DESTINATION "${CMAKE_BINARY_DIR}/resources"
)

# Copy SFML DLLs to build directory (only for Windows)
if(WIN32)
    file(COPY 
        "C:/msys64/mingw64/bin/libsfml-graphics-2.dll"
        "C:/msys64/mingw64/bin/libsfml-audio-2.dll"
        "C:/msys64/mingw64/bin/libsfml-network-2.dll"
        "C:/msys64/mingw64/bin/libsfml-system-2.dll"
        "C:/msys64/mingw64/bin/libsfml-window-2.dll"
        DESTINATION ${CMAKE_BINARY_DIR}
    )
endif()

# Add definitions for resource paths
target_compile_definitions(${PROJECT_NAME} PRIVATE
    FONTS_DIR="${CMAKE_BINARY_DIR}/resources/fonts"
    IMAGES_DIR="${CMAKE_BINARY_DIR}/resources/images"
    SOUNDS_DIR="${CMAKE_BINARY_DIR}/resources/sounds"
)