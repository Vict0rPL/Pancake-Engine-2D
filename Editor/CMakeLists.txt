 add_executable(Editor
     src/EditorUI.cpp
     src/main.cpp
     # add other Editor source files
     # tinyfiledialogs implementation
     ${CMAKE_SOURCE_DIR}/thirdparty/tinyfiledialogs/tinyfiledialogs.c
 )

 target_include_directories(Editor PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}/include          # Editor-specific headers
     ${CMAKE_SOURCE_DIR}/Engine/include           # Engine headers
     ${CMAKE_SOURCE_DIR}/Libraries/SDL/include    # SDL3 headers (SDL.h)
     ${CMAKE_SOURCE_DIR}/Libraries/imgui          # ImGui headers
     ${CMAKE_SOURCE_DIR}/thirdparty/tinyfiledialogs  # <— so we can #include "tinyfiledialogs.h"
 )

 target_link_libraries(Editor
     Engine         # Link your Engine library target
     ImGui::ImGui   # Link Dear ImGui
     nlohmann_json::nlohmann_json
 )
