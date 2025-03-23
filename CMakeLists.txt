# CMakeList.txt : CMake project for Pancake Engine 2D, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Pancake Engine 2D")
# Add third-party libraries
#Load SDL First
add_subdirectory(Libraries/SDL)
add_subdirectory(Libraries/imgui)

# Add subdirectories
add_subdirectory(Engine)
add_subdirectory(Editor)


add_custom_target(run
    COMMAND Editor
    DEPENDS Editor
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Editor PROPERTY CXX_STANDARD 20)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
