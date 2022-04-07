set(SOURCES_PATHFINDING
Algorithms/DStarLite.cpp
Algorithms/AStar.cpp
Algorithms/DiagonalHeuristic.cpp
Algorithms/DefaultCostFunction.cpp
Algorithms/DFSMazeGenerator.cpp
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
Rendering/DrawableNode.cpp
Rendering/DrawablePath.cpp
Rendering/NodeStateColors.cpp
Rendering/GradientChanger.cpp
Core/GraphDimension.cpp
Helpers/RootPath.cpp
Helpers/GuiHelpers.cpp
Helpers/SFMLHelpers.cpp
Helpers/RenderingHelpers.cpp
Helpers/ILatticeGraphHelpers.cpp
Helpers/FontLoader.cpp
Helpers/AlgorithmFunctionHelpers.cpp
Gui/Menu.cpp
main.cpp
)

set(GCC_PATHFINDING_FLAGS "/WX")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_PATHFINDING_FLAGS}")

add_executable(pathfinding_b ${SOURCES_PATHFINDING})
target_link_libraries(pathfinding_b PRIVATE ImGui-SFML::ImGui-SFML)

if(WIN32)
  if(BUILD_SHARED_LIBS)
    add_custom_command(TARGET pathfinding_b POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
              $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
              $<TARGET_FILE:sfml-graphics>
              $<TARGET_FILE:sfml-window>
              $<TARGET_FILE:sfml-system>
              $<TARGET_FILE_DIR:pathfinding_b>)
  endif()
endif()