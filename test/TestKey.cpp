#include <catch2/catch_test_macros.hpp>
#include <limits>
#include "Key.hpp"

using namespace Pathfinding::Datastructures;

TEST_CASE( "key created with default constructor should be init to zeros", "[constructor]" ) {
    Key key1;
    REQUIRE(key1.k1 == std::numeric_limits<double>::infinity());
    REQUIRE(key1.k2 == std::numeric_limits<double>::infinity());
}

TEST_CASE( "key should hake apr. dim. when creating with kalues", "[constructor]" ) {
    Key key1(2,5);
    REQUIRE(key1.k1 == 2);
    REQUIRE(key1.k2 == 5);
}

TEST_CASE( "Two keys with the same dimension should be equal", "[Spaceship]" ) {
    Key key1(2,5);
    Key key2(2,5);
    REQUIRE(key1 == key2);
}

TEST_CASE( "Two keys with diff. dimension should be not equal", "[Spaceship]" ) {
    Key key1(2,5);
    Key key2(2,56);
    REQUIRE(key1 != key2);
}

TEST_CASE( "Testing lexographical comparison less 1 key", "[Spaceship]" ) {
    Key key1(2,5);
    Key key2(2,56);
    REQUIRE(key1 < key2);
}

TEST_CASE( "Testing lexographical comparison less 2 key", "[Spaceship]" ) {
    Key key1(3,4);
    Key key2(4,5);
    REQUIRE(key1 < key2);
}

TEST_CASE( "Testing lexographical comparison greater 1 key", "[Spaceship]" ) {
    Key key1(4,5);
    Key key2(3,5);
    REQUIRE(key1 > key2);
}

TEST_CASE( "Testing lexographical comparison greater 2 key", "[Spaceship]" ) {
    Key key1(4,6);
    Key key2(4,5);
    REQUIRE(key1 > key2);
}