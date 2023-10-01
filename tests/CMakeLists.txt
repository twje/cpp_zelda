add_executable(ZeldaTests 
    Example.cpp    
    PlayerStatusTest.cpp)

target_link_libraries(ZeldaTests PUBLIC 
    gtest_main
    ZeldaLibrary
)

add_test(
    NAME ZeldaTests
    COMMAND ZeldaTests
)