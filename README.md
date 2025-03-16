# Pancake Engine 2D
##--------------- imgui cmake list
cmake_minimum_required(VERSION 3.10)
project(ImGui)

set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    backends/imgui_impl_sdl3.cpp
    backends/imgui_impl_sdlrenderer3.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})

# Make sure ImGui can see its own headers and the backends directory
target_include_directories(ImGui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
    # Add SDL's include path if you don’t rely on a global include
    # For example, if SDL is in Libraries/SDL/include:
    ${CMAKE_SOURCE_DIR}/Libraries/SDL/include
)

# Link to SDL3 if your SDL library target is named "SDL3"
target_link_libraries(ImGui PUBLIC SDL3::SDL3)

# Optionally create an alias target for convenience
add_library(ImGui::ImGui ALIAS ImGui)



##-------------------