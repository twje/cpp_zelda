# Define a CMake function to set the DEBUG_BUILD macro based on the generator type
function(set_debug_build_target target_name)
    # Check if the build configuration is Debug and define the macro accordingly
    list(FIND CMAKE_CONFIGURATION_TYPES "Debug" isDebugConfig)
    if(isDebugConfig GREATER -1)
        # For multi-configuration generators (e.g., Visual Studio, Xcode)
        target_compile_definitions(${target_name} PRIVATE $<$<CONFIG:Debug>:DEBUG_BUILD>)
    else()
        # For single-configuration generators (e.g., Make, Ninja)
        target_compile_definitions(${target_name} PRIVATE DEBUG_BUILD)
    endif()
endfunction()