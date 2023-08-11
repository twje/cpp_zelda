cmake_minimum_required(VERSION 3.21)

project(Zelda C CXX)

include(Functions.cmake)
include(FetchContent)

enable_testing()

# Add yaml-cpp
set(YAML_CPP_BUILD_TESTS OFF)
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)

# Add googletest dependency
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

# Add SFML dependency
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG master
)
FetchContent_MakeAvailable(SFML)

# Configure project
set(ZeldaIncludes
    ${SFML_SOURCE_DIR}/include
    ${yaml-cpp_SOURCE_DIR}/include
    src
)

add_library(ZeldaLibrary STATIC
    src/Core/ResourceManager/ResourceManager.h
    src/Core/ResourceManager/ResourceManager.inl
    src/Core/ResourceManager/ResourceManagerUtils.h
    src/Core/ResourceManager/ResourceManagerUtils.cpp   
    src/Core/ResourceManager/ResourceManager.cpp
    src/Core/ResourceManager/TextureManager.h
    src/Core/ResourceManager/GUIStyleManager.h
    src/Core/ResourceManager/FontManager.h
    src/Core/Base.h
    src/Core/OstreamOverloads.h    
    src/Core/Debug.h
    src/Core/Debug.cpp    
    src/Core/Group.h
    src/Core/Group.cpp
    src/Core/Sprite.h
    src/Core/Sprite.cpp    
    src/Core/Animation.h
    src/Core/Animation.cpp
    src/Core/AnimationSequence.h
    src/Core/AnimationSequence.cpp
    src/Core/Toggles.h
    src/Core/Toggles.cpp
    src/Core/RectUtils.h
    src/Core/RectUtils.cpp
    src/Core/Layer.h
    src/Core/LayerStack.h
    src/Core/LayerStack.cpp
    src/Core/Application.h
    src/Core/Application.cpp
    src/Core/GameObject.h
    src/Core/GameObject.cpp
    src/Core/GuiStyle.h
    src/Core/GuiStyle.cpp
    src/Core/InflatableTextBox.h
    src/Core/InflatableTextBox.cpp
    src/Core/TextureOverlay.h
    src/Core/TextureOverlay.cpp
    src/Bar.h
    src/Bar.cpp
    src/Weapon.h
    src/Weapon.cpp
    src/Support.h
    src/Support.cpp
    src/Game.h
    src/Game.cpp    
    src/UI.h
    src/UI.cpp
    src/Settings.h
    src/Settings.cpp
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
    yaml-cpp
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