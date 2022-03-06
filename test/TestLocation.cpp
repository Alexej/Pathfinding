#include <catch2/catch_test_macros.hpp>
#include "Vec2.hpp"

using namespace Pathfinding::Datastructures;


TEST_CASE( "by default node location is {0,0}", "[constructor]" ) {
    Vec2i nl;
    REQUIRE(nl.width == 0);
    REQUIRE(nl.height == 0);
}

TEST_CASE( "Position can be passed to constructor", "[constructor]" ) {
    Vec2i nl(2,3);
    REQUIRE(nl.height == 2);
    REQUIRE(nl.width == 3);
}

TEST_CASE( "two objects with the same location should be equal", "[constructor]" ) {
    Vec2i n1(2,3);
    Vec2i n2(2,3);
    REQUIRE(n1 == n2);
}