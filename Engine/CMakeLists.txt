# Engine/CMakeLists.txt
# Build configuration for the core engine library

# Create a library target for the engine
add_library(Engine STATIC
    src/Engine.cpp
    src/Scene.cpp
    src/GameObject.cpp
    src/Game.cpp
    src/PrimitiveRenderer.cpp
    src/Point2D.cpp
    src/Square.cpp
    src/Circle.cpp
    src/Ellipse.cpp
    src/Polygon.cpp
    src/Line.cpp  # Upewnij się, że ten plik jest tutaj
    "include/PrimitiveRenderer.h" "include/Point2D.h" "include/Square.h" "include/Circle.h" "include/Ellipse.h" "include/Polygon.h" "include/Line.h"
 "include/TransformableObject.h" "include/Transform.h")


# Include directories for Engine
target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Libraries/SDL/include
)


target_link_libraries(Engine 
    PRIVATE
    SDL3::SDL3
    nlohmann_json::nlohmann_json
)