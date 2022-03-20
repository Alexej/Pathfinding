
set(SOURCES_PATHFINDING
  Algorithms/DStarLite.cpp
  Algorithms/AStar.cpp
  Algorithms/DiagonalHeuristic.cpp
  Algorithms/DefaultCostFunction.cpp
  Events/EventManager.cpp
  Datastructures/LatticeGraph.cpp
  Datastructures/Node.cpp
  Datastructures/PathfinderCache.cpp
  Datastructures/LatticeGraphWrapper.cpp
  Datastructures/PriorityQueue.cpp
  Core/Application.cpp
  Core/ApplicationState.cpp
  Core/GraphOperations.cpp
  Core/ApplicationBuilder.cpp
  Rendering/Renderer.cpp
  Rendering/DrawableNode.cpp
  Rendering/DrawablePath.cpp
  Core/GraphDimension.cpp
  Helpers/RootPath.cpp
  Helpers/GuiHelpers.cpp
  Helpers/SFMLHelpers.cpp
  Helpers/RenderingHelpers.cpp
  Helpers/LatticeGraphHelpers.cpp
  Helpers/FontLoader.cpp
  Helpers/AlgorithmFunctionHelpers.cpp
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