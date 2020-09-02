cmake_minimum_required(VERSION 3.15)
project(SimpleATMController)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(SimpleATMController
        logic/bridge.h
        logic/transaction.cc
        logic/accessor.cc
        controller.cc
        )
add_executable(SimpleATMController_TEST
        logic/bridge.h
        logic/transaction.cc
        logic/accessor.cc
        test.cc
        )
target_link_libraries(SimpleATMController_TEST ${GTEST_LIBRARIES} pthread)