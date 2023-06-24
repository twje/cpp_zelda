cmake_minimum_required(VERSION 3.21)

project(Zelda C CXX)

enable_testing()

add_subdirectory(vendor/googletest)

set(Headers
    ""
)

set(Source
    src/Main.cpp
)

add_library(Zelda STATIC ${Source} ${Headers})

# refactor into CMakeLists.txt

add_executable(ZeldaTests tests/Example.cpp)

target_link_libraries(ZeldaTests PUBLIC 
    gtest_main
    Zelda
)

add_test(
    NAME ZeldaTests
    COMMAND ZeldaTests
)