cmake_minimum_required(VERSION 3.21)

project(Zelda C CXX)

include(Functions.cmake)
include(FetchContent)

enable_testing()

# Add nlohmann sub-module
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_ImplicitConversions OFF CACHE INTERNAL "")
add_subdirectory("vendor/nlohmann")

# Add googletest sub-module
add_subdirectory(vendor/googletest)

# Add SFML sub-module
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git)
FetchContent_MakeAvailable(SFML)

# Configure project
set(ZeldaIncludes
    ${SFML_SOURCE_DIR}/include
    vendor/nlohmann/include
    src
)

add_library(ZeldaLibrary STATIC
    src/Core/OstreamOverloads.h
    src/Constants.h
    src/Core/Debug.h
    src/Core/Debug.cpp    
    src/Core/SpriteGroup.h
    src/Core/SpriteGroup.cpp
    src/Core/Sprite.h
    src/Core/Sprite.cpp
    src/Core/Rect.h
    src/Support.h
    src/Support.cpp
    src/Game.h
    src/Game.cpp
    src/Settings.h
    src/Level.h
    src/Level.cpp
    src/LevelView.h
    src/LevelView.cpp
    src/Player.h
    src/Player.cpp
    src/Tile.h
    src/Tile.cpp    
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

set_debug_build_target(ZeldaLibrary)

add_executable(Zelda 
    bootstrap/Main.cpp
)

target_link_libraries(Zelda PRIVATE ZeldaLibrary)

add_subdirectory(tests)