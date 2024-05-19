cmake_minimum_required(VERSION 3.22)
project(InternetCafe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(InternetCafe src/main.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
        cafe_test
        test/test.cpp
)

target_link_libraries(
        cafe_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cafe_test)
