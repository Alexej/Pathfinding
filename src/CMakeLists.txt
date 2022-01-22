
set(SOURCES_PATHFINDING
  Datastructures/LatticeGraph.cpp
  Helpers/GraphOperations.cpp
  Algorithms/DStarLite.cpp
  Events/EventManager.cpp
  Datastructures/Node.cpp
  Datastructures/Key.cpp
  Core/Application.cpp
  Core/ApplicationState.cpp
  Core/Renderer.cpp
  Core/GraphDimension.cpp
  Gui/Menu.cpp
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