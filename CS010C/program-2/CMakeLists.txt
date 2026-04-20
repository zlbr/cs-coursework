cmake_minimum_required(VERSION 3.14)
project(my_project_tests)

# 1. Download GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: prevents overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 2. Add your executable
add_executable(run_tests 
    test_main.cpp 
    # add other source files here
)

# 3. Link to GoogleTest
# gtest_main provides a default main() function so you don't have to write one
target_link_libraries(run_tests GTest::gtest_main)

# 4. Enable CTest discovery
include(GoogleTest)
gtest_discover_tests(run_tests)