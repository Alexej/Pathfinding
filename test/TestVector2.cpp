#include <catch2/catch_test_macros.hpp>
#include "Vector2.hpp"

using namespace Pathfinding::Datastructures;

TEST_CASE( "Vector created with default constructor should be init to zeros", "[constructor]" ) {
    Vec2i v1;
    REQUIRE(v1.height == 0);
    REQUIRE(v1.width == 0);
}

TEST_CASE( "Vector should have apr. dim. when creating with values", "[constructor]" ) {
    Vec2i v1(2,5);
    REQUIRE(v1.height == 2);
    REQUIRE(v1.width == 5);
}

TEST_CASE( "Two vectors with the same dimension should be equal", "[Spaceship]" ) {
    Vec2i v1(2,5);
    Vec2i v2(2,5);
    REQUIRE(v1 == v2);
}

TEST_CASE( "Two vectors with diff. dimension should be not equal", "[Spaceship]" ) {
    Vec2i v1(2,5);
    Vec2i v2(2,56);
    REQUIRE(v1 != v2);
}

TEST_CASE( "Testing lexographical comparison less 1", "[Spaceship]" ) {
    Vec2i v1(2,5);
    Vec2i v2(2,56);
    REQUIRE(v1 < v2);
}

TEST_CASE( "Testing lexographical comparison less 2", "[Spaceship]" ) {
    Vec2i v1(3,4);
    Vec2i v2(4,5);
    REQUIRE(v1 < v2);
}

TEST_CASE( "Testing lexographical comparison greater 1", "[Spaceship]" ) {
    Vec2i v1(4,5);
    Vec2i v2(3,5);
    REQUIRE(v1 > v2);
}

TEST_CASE( "Testing lexographical comparison greater 2", "[Spaceship]" ) {
    Vec2i v1(4,6);
    Vec2i v2(4,5);
    REQUIRE(v1 > v2);
}