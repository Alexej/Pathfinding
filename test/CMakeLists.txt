
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
    ../src/Datastructures/LatticeGraph.cpp
    ../src/Datastructures/Node.cpp
    ../src/Datastructures/PathfinderCache.cpp
    ../src/Datastructures/LatticeGraphWrapper.cpp
    ../src/Datastructures/PriorityQueue.cpp
    ../src/Core/ApplicationState.cpp
    ../src/Core/GraphDimension.cpp
    ../src/Helpers/RootPath.cpp
    ../src/Helpers/ILatticeGraphHelpers.cpp
    ../src/Helpers/AlgorithmFunctionHelpers.cpp

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