#include <catch2/catch_test_macros.hpp>
#include "PriorityQueue.hpp"

#include "Key.hpp"
#include "Node.hpp"
#include <iostream>

using namespace Pathfinding::Datastructures;

TEST_CASE( "Created priorityQeueu should be empty", "[constructor]" ) {
    PriorityQueue queue;
    REQUIRE(queue.size() == 0);
}


TEST_CASE( "Adding elements to the queue should increase the size", "[size]" ) 
{
    Node * n1 = new Node();
    Node * n2 = new Node();
    Node * n3 = new Node();

    n1->location = GraphLocation(1,2);
    n2->location = GraphLocation(3,5);
    n3->location = GraphLocation(7,9);

    PriorityQueue queue;

    queue.insert(n1, Key(23,42));
    queue.insert(n2, Key(21,52));
    queue.insert(n3, Key(4,2));

    REQUIRE(queue.size() == 3);

    delete n1;
    delete n2;
    delete n3;
}

TEST_CASE( "topKey should return the smallest key", "[topKey]" ) 
{
    PriorityQueue queue;

    Node * n1 = new Node();
    Node * n2 = new Node();
    Node * n3 = new Node();
    Node * n4 = new Node();

    n1->location = GraphLocation(1,2);
    n2->location = GraphLocation(3,5);
    n3->location = GraphLocation(7,9);
    n4->location = GraphLocation(43,1);

    Key k1(23,42);
    Key k2(21,52);
    Key k3(4,2);
    Key k4(4,1);

    queue.insert(n1, k1);
    queue.insert(n2, k2);
    queue.insert(n3, k3);
    queue.insert(n4, k4);

    REQUIRE(queue.top().first == k4);

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}

TEST_CASE( "testing contains function", "[contains]" ) 
{
    PriorityQueue queue;

    Node * n1 = new Node();
    Node * n2 = new Node();
    Node * n3 = new Node();
    Node * n4 = new Node();

    n1->location = GraphLocation(1,2);
    n2->location = GraphLocation(3,5);
    n3->location = GraphLocation(7,9);
    n4->location = GraphLocation(43,1);

    Key k1(23,42);
    Key k2(21,52);
    Key k3(4,2);
    Key k4(4,1);

    queue.insert(n1, k1);
    queue.insert(n2, k2);

    REQUIRE(queue.contains(n1));
    REQUIRE(queue.contains(n2));
    REQUIRE(!queue.contains(n3));
    REQUIRE(!queue.contains(n4));

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}

TEST_CASE( "pop should return the node with the smallest key and delete in from the queue", "[pop]" ) 
{
    PriorityQueue queue;

    Node * n1 = new Node();
    Node * n2 = new Node();
    Node * n3 = new Node();
    Node * n4 = new Node();

    n1->location = GraphLocation(1,2);
    n2->location = GraphLocation(3,5);
    n3->location = GraphLocation(7,9);
    n4->location = GraphLocation(43,1);

    Key k1(23,42);
    Key k2(21,52);
    Key k3(4,2);
    Key k4(4,1);

    queue.insert(n1, k1);
    queue.insert(n2, k2);
    queue.insert(n3, k3);
    queue.insert(n4, k4);

    REQUIRE(queue.size() == 4);
    REQUIRE(queue.popD() == n4);
    REQUIRE(queue.size() == 3);
    REQUIRE(!queue.contains(n4));

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}