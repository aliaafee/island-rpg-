cmake_minimum_required(VERSION 3.1.0)
project(island-rpg)
set (CMAKE_CXX_STANDARD 20)

include_directories("include")

add_subdirectory("src")

add_executable(island-rpg "src/main.cpp")
target_link_libraries(island-rpg island-lib -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window)

include(CTest)
file(GLOB test_sources "tests/*.cpp")
foreach(test_source ${test_sources})
    string(REPLACE ".cpp" "" test_target ${test_source})
    get_filename_component(test_target ${test_source} NAME_WE)
    message(STATUS "Found Test: ${test_target}")
    add_executable(${test_target} ${test_source})
    target_link_libraries(${test_target} island-lib -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window)
    add_test(NAME ${test_target} COMMAND ${test_target})
endforeach()