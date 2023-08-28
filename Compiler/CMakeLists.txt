cmake_minimum_required(VERSION 3.10)
project(CompilerProject)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_CLANG_TIDY "")

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
        message("Coverage build")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

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
target_include_directories(compilerLib PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(compilerLib PROPERTIES CMAKE_CXX_CLANG_TIDY
        "clang-tidy;-checks=*;-header-filter='${CMAKE_SOURCE_DIR}/include/*'")

# Add main executable 
file(GLOB SOURCES "src/main.cpp")
add_executable(compiler ${SOURCES})
target_link_libraries(compiler PRIVATE compilerLib)
target_include_directories(compiler PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(compilerLib PROPERTIES CMAKE_CXX_CLANG_TIDY
        "clang-tidy;-checks=*;-header-filter='${CMAKE_SOURCE_DIR}/include/*'")

# Add tests executable
file(GLOB TEST_SOURCES "test/**/*.cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE compilerLib Catch2::Catch2)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
