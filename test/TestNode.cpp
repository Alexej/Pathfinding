#include <catch2/catch_test_macros.hpp>
#include "Node.hpp"

using namespace Pathfinding::Datastructures;


TEST_CASE( "Nodes with same location should be equal 1", "[constructor]" ) {
    Node n1;
    Node n2; 

    n1.location.height = 2;
    n1.location.width = 3;

    n2.location.height = 2;
    n2.location.width = 3;

    REQUIRE(n1 == n2);
}


TEST_CASE( "Nodes with same location should not be equal", "[constructor]" ) {
    Node n1;
    Node n2; 

    n1.location.height = 2;
    n1.location.width = 3;

    n2.location.height = 2;
    n2.location.width = 5;

    REQUIRE(n1 != n2);
}
