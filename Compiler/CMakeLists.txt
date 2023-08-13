cmake_minimum_required(VERSION 3.10)
project(CompilerProject)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# include catch2 through its cmake integration
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1
)

FetchContent_MakeAvailable(Catch2)

## source files as a library
file(GLOB LIB_SOURCES "src/**/*.cpp")
add_library(compilerLib ${LIB_SOURCES})

# Add main executable 
file(GLOB SOURCES "src/main.cpp")
add_executable(compiler ${SOURCES})
target_link_libraries(compiler PRIVATE compilerLib)

# Add tests executable
file(GLOB TEST_SOURCES "test/**/*.cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE compilerLib Catch2::Catch2)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
