
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)


set(SOURCES_TESTS
    ../src/Algorithms/DStarLite.cpp
    ../src/Algorithms/AStar.cpp
    ../src/Algorithms/DiagonalHeuristic.cpp
    ../src/Algorithms/DefaultCostFunction.cpp
    ../src/Algorithms/DFSMazeGenerator.cpp
    ../src/Events/EventManager.cpp
    ../src/Datastructures/LatticeGraph.cpp
    ../src/Datastructures/Node.cpp
    ../src/Datastructures/PathfinderCache.cpp
    ../src/Datastructures/LatticeGraphWrapper.cpp
    ../src/Datastructures/PriorityQueue.cpp
    ../src/Core/Application.cpp
    ../src/Core/ApplicationState.cpp
    ../src/Core/GraphOperations.cpp
    ../src/Core/ApplicationBuilder.cpp
    ../src/Rendering/DrawableNode.cpp
    ../src/Rendering/DrawablePath.cpp
    ../src/Rendering/NodeStateColors.cpp
    ../src/Core/GraphDimension.cpp
    ../src/Helpers/RootPath.cpp
    ../src/Helpers/GuiHelpers.cpp
    ../src/Helpers/SFMLHelpers.cpp
    ../src/Helpers/RenderingHelpers.cpp
    ../src/Helpers/ILatticeGraphHelpers.cpp
    ../src/Helpers/FontLoader.cpp
    ../src/Helpers/AlgorithmFunctionHelpers.cpp
    ../src/Gui/Menu.cpp

    PathLangParser.cpp
    TestLocation.cpp
    TestDStarLite.cpp
    TestDefaultCost.cpp
    TestVector2.cpp
    TestLatticeGraph.cpp
    TestNode.cpp
    TestPriorityQueue.cpp
    TestKey.cpp
    )

add_executable(tests ${SOURCES_TESTS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE ImGui-SFML::ImGui-SFML)

if(WIN32)
  if(BUILD_SHARED_LIBS)
    add_custom_command(TARGET tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
              $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
              $<TARGET_FILE:sfml-graphics>
              $<TARGET_FILE:sfml-window>
              $<TARGET_FILE:sfml-system>
              $<TARGET_FILE_DIR:tests>)
  endif()
endif()