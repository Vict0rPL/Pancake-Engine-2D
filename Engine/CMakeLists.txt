# Engine/CMakeLists.txt
# Build configuration for the core engine library

# Create a library target for the engine
add_library(Engine STATIC
    src/Engine.cpp
    src/Scene.cpp
    src/GameObject.cpp
    # Add other source files as needed
 "src/PrimitiveRenderer.cpp" "include/PrimitiveRenderer.h" "include/Point2D.h" "src/Point2D.cpp")

# Include directories for Engine
target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Libraries/SDL/include
)


target_link_libraries(Engine 
    PRIVATE
    SDL3::SDL3     # Link SDL3
)