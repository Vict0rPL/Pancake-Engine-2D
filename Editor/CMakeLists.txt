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

add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/Libraries/SDL/SDL3.dll
            $<TARGET_FILE_DIR:Editor>/SDL3.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/Libraries/SDL_image/SDL3_image.dll
            $<TARGET_FILE_DIR:Editor>/SDL3_image.dll
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:Editor>/Engine/assets
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/Engine/assets/pacman.png
            $<TARGET_FILE_DIR:Editor>/Engine/assets/pacman.png
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/Engine/assets/pancake.bmp
            $<TARGET_FILE_DIR:Editor>/Engine/assets/pancake.bmp
    COMMENT "Copying DLLs and assets to output directory"
)

