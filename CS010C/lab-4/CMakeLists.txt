cmake_minimum_required(VERSION 3.14)
project(my_list_tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests test_lab_4.cpp)

target_link_libraries(run_tests gtest gtest_main)

enable_testing()