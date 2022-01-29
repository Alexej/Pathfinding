#include <catch2/catch_test_macros.hpp>
#include "LatticeGraph.hpp"

using namespace Pathfinding::Datastructures;

TEST_CASE( "Created graph should have apropriate dimensions", "[constructor]" ) {
    LatticeGraph graph(20,30);
    REQUIRE(graph.width() == 30);
    REQUIRE(graph.height() == 20);
}

TEST_CASE( "Every node should have apropriate location", "[constructor]" ) {
    LatticeGraph graph(20,30);
    for(int64_t h = 0; h < graph.height(); ++h)
    {
        for(int64_t w = 0; w <graph. width(); ++w)
        {
            REQUIRE(graph[h][w].location == Vector2i(h,w));
        }
    }
}