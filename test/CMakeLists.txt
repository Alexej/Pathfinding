
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)


set(SOURCES_TESTS
    ../src/Datastructures/Node.cpp
    ../src/Datastructures/LatticeGraph.cpp
    ../src/Datastructures/Key.cpp

    TestLocation.cpp
    TestVector2.cpp
    TestLatticeGraph.cpp
    TestPriorityQueue.cpp
    )

add_executable(tests ${SOURCES_TESTS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)