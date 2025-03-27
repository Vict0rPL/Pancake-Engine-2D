# Pancake Engine 2D

**This is a project for PSK PGK classes.**

## Part I. Setup

### In order to run Pancake Engine, please follow the steps below:

1. **Clone the repository.**

2. **Initialize and update submodules:**  
   Run the following command in the root of the repository to initialize and update the submodules (imgui and SDL):
```bash
   git submodule update --init --recursive
```
3. **Create the ImGui CMakeLists.txt file:**  
   In the Libraries/imgui/ folder, create a file named CMakeLists.txt with the following content:
```cmake
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

add_library(ImGui STATIC 
  imgui.cpp
  imgui_draw.cpp
  imgui_widgets.cpp
  imgui_demo.cpp
  imgui_tables.cpp  
  backends/imgui_impl_sdl3.cpp
  backends/imgui_impl_sdlrenderer3.cpp
)

# Make sure ImGui can see its own headers and the backends directory
target_include_directories(ImGui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
    # Add SDL's include path
    ${CMAKE_SOURCE_DIR}/Libraries/SDL/include
)

# Create an alias target for convenience
add_library(ImGui::ImGui ALIAS ImGui)
```
4. **Build the project:**  
   Open the project in Visual Studio (which will automatically create an out/ folder) or manually build the `CMakeLists.txt` file located in the root folder of the project.
5. **Copy SDL3.dll:** 
   In the created `out/` folder, copy the SDL3.dll file from `out/build/x64-debug/Libraries/SDL` to `out/build/x64-debug/Editor` if its not there try buiding project and run `Editor.exe` once. (in the final version thiss will be ommited after we add post-build script to CMake)
6. **Run the Editor:**  
   Execute `Editor.exe`.

## Part II. Tasks and Deadlines

### Kamien Milowy 30.03.2025
- Obsługa klawiatury i myszy: OK

- Obsługa współrzędnych (Point2D): OK

- Rysowanie prymitywów

### Obrona projektu 27.04.2025
- Wypełnianie prymitywów kolorem

- Przekształcenia geometryczne

- Hierarchia klas

- Obsługa bitmap

- Animowanie bitmap

- Demo technologiczne (do obrony)

- Sprawozdanie i dokumentacja