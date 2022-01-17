
set(SOURCES_PATHFINDING
    Datastructures/Key.cpp
    Core/Application.cpp
    Core/Renderer.cpp
    Helpers/LatticeGraphOperations.cpp
    main.cpp
)

add_executable(pathfinding_b ${SOURCES_PATHFINDING})
target_link_libraries(pathfinding_b PRIVATE ImGui-SFML::ImGui-SFML)

if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET pathfinding_b POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:pathfinding_b>)
  endif()
endif()