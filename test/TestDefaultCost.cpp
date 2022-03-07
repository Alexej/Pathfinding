#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <vector>

#include "AlgorithmFunctionHelpers.hpp"
#include "DefaultCostFunction.hpp"
#include "Node.hpp"
#include "Vec2.hpp"


using namespace Pathfinding::Algorithms;
using namespace Pathfinding::Datastructures;
using namespace Pathfinding::Helpers;


TEST_CASE( "Default cost Function should be ready to use after object creation" ) {
    int32_t diagonalMovementCost = static_cast<int32_t>(std::sqrt(2) * 10);
    int32_t straightMovementCost = 10 * 1;

    DefaultCostFunction defCostFunc = DefaultCostFunction(diagonalMovementCost, straightMovementCost);

    std::vector<Node *> nodes;

    for(int32_t h = 0; h < 3; ++h)
    {
        for(int32_t w = 0; w < 3; ++w)
        {
            nodes.push_back(new Node(h,w));
        }
    }

    for(auto node : nodes)
    {
        if(node->location != nodes[4]->location)
        {
            if(twoNodesDiagonal(nodes[4], node))
            {
                REQUIRE(defCostFunc.calculate(nodes[4], node) == diagonalMovementCost);
            }
            else
            {
                REQUIRE(defCostFunc.calculate(nodes[4], node) == straightMovementCost);
            }
        }
    }


    for(auto node : nodes)
    {
        delete node;
    }
}


TEST_CASE("Blocked node should have of infinity") {
    int32_t diagonalMovementCost = static_cast<int32_t>(std::sqrt(2) * 10);
    int32_t straightMovementCost = 10 * 1;

    DefaultCostFunction defCostFunc = DefaultCostFunction(diagonalMovementCost, straightMovementCost);

    Node * n1 = new Node();
    Node * n2 = new Node();
    n2->state = NodeState::Blocked;

    REQUIRE(defCostFunc.calculate(n1,n2) == std::numeric_limits<double>::infinity());
    REQUIRE(defCostFunc.calculate(n2,n1) == std::numeric_limits<double>::infinity());

    delete n1;
    delete n2;
}
