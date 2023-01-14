# http://google.github.io/googletest/quickstart-cmake.html

cmake_minimum_required(VERSION 3.14)
project(traffic_light VERSION 0.1)

# GoogleTest requires >= C++14
# jthread requires >= C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
#FetchContent_Declare(
#  googletest
#  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# build TrafficLightTest.cpp
enable_testing()

add_executable(
  TrafficLightTest
  tests/TrafficLightTest.cpp
  Controller.cpp
  Controller.hpp
  include.h
  TrafficLight.cpp
  TrafficLight.hpp
  Types.cpp
  Types.hpp
  VehicleTrafficLight.cpp
  VehicleTrafficLight.hpp
)
target_link_libraries(
  TrafficLightTest
  GTest::gtest_main
)
add_compile_definitions(TEST=1)
add_compile_definitions(DEBUG=0)

include(GoogleTest)
gtest_discover_tests(TrafficLightTest)
