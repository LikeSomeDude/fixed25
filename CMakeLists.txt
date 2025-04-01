cmake_minimum_required(VERSION 3.9)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test for Fixed
enable_testing()

add_executable(
  fixedtests
  fixedtests.cpp
  fixed.h 
  fixed.cpp)
target_link_libraries(
  fixedtests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(fixedtests)

# Add main programm
add_executable(
  mainprogram
  mainprogram.cpp
  fixed.h
  fixed.cpp)
