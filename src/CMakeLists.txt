
set(SOURCES_PATHFINDING
  Algorithms/DStarLite.cpp
  Algorithms/DiagonalHeuristic.cpp
  Algorithms/DefaultCostFunction.cpp
  Events/EventManager.cpp
  Datastructures/LatticeGraph.cpp
  Datastructures/Node.cpp
  Datastructures/LatticeGraphWrapper.cpp
  Core/Application.cpp
  Core/ApplicationState.cpp
  Core/Renderer.cpp
  Core/GraphDimension.cpp
  Core/AlgorithmStepSpeed.cpp
  Helpers/RootPath.cpp
  Helpers/GuiHelpers.cpp
  Helpers/SFMLHelpers.cpp
  Helpers/GraphOperations.cpp
  Helpers/ALatGrWrHelpers.cpp
  Helpers/ApplicationBuilder.cpp
  Helpers/AlgorithmFunctionHelpers.cpp
  ../test/PathLangParser.cpp
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