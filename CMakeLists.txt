cmake_minimum_required(VERSION 3.21)

project(Zelda C CXX)

enable_testing()

# Add nlohmann sub-module
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_ImplicitConversions OFF CACHE INTERNAL "")
add_subdirectory("vendor/nlohmann")

# Add googletest sub-module
add_subdirectory(vendor/googletest)

# Add SFML sub-module
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
add_subdirectory(vendor/SFML)

# Configure project
set(ZeldaIncludes
    vendor/SFML/include
    vendor/nlohmann/include
    src
)

add_library(ZeldaLibrary STATIC     
    src/Debug.h
    src/Debug.cpp    
    src/Game.h
    src/Game.cpp
    src/Settings.h
    src/Level.h
    src/Level.cpp
    src/SpriteGroup.h
    src/SpriteGroup.cpp
    src/Sprite.h
    src/Sprite.cpp
    src/Player.h
    src/Player.cpp
    src/Tile.h
    src/Tile.cpp
    src/Rect.h
    src/Rect.cpp
)

target_link_libraries(ZeldaLibrary PUBLIC
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    sfml-network
    nlohmann_json::nlohmann_json
)

target_include_directories(ZeldaLibrary PUBLIC
    ${ZeldaIncludes}
)

add_executable(Zelda 
    bootstrap/Main.cpp
)

target_link_libraries(Zelda PRIVATE ZeldaLibrary)

add_subdirectory(tests)