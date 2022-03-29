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
    Node * n1 = new Node({1,1});
    Node * n2 = new Node({2,2});
    Node * n3 = new Node({3,3});

    n1->location = Vec2i(1,2);
    n2->location = Vec2i(3,5);
    n3->location = Vec2i(7,9);

    n1->key = Key(23,42);
    n2->key = Key(21,52);
    n3->key = Key(4,2);

    PriorityQueue queue;

    queue.insert(n1);
    queue.insert(n2);
    queue.insert(n3);

    REQUIRE(queue.size() == 3);

    delete n1;
    delete n2;
    delete n3;
}

TEST_CASE( "topKey should return the smallest key", "[topKey]" ) 
{
    PriorityQueue queue;

    Node * n1 = new Node({1,1});
    Node * n2 = new Node({2,2});
    Node * n3 = new Node({3,3});
    Node * n4 = new Node({4,4});

    n1->location = Vec2i(1,2);
    n2->location = Vec2i(3,5);
    n3->location = Vec2i(7,9);
    n4->location = Vec2i(43,1);

    Key k1 =  Key(23,42);  
    Key k2 =  Key(21,52);
    Key k3 =  Key(4,2);
    Key k4 =  Key(4,1);

    n1->key = k1;
    n2->key = k2;
    n3->key = k3;
    n4->key = k4;

    queue.insert(n1);
    queue.insert(n2);
    queue.insert(n3);
    queue.insert(n4);

    REQUIRE(queue.topKey() == k4);

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}

TEST_CASE( "testing contains function", "[contains]" ) 
{
    PriorityQueue queue;

    Node * n1 = new Node({1,1});
    Node * n2 = new Node({2,2});
    Node * n3 = new Node({3,3});
    Node * n4 = new Node({4,4});

    n1->location = Vec2i(1,2);
    n2->location = Vec2i(3,5);
    n3->location = Vec2i(7,9);
    n4->location = Vec2i(43,1);

    Key k1(23,42);
    Key k2(21,52);
    Key k3(4,2);
    Key k4(4,1);

    n1->key = k1;
    n2->key = k2;

    queue.insert(n1);
    queue.insert(n2);

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

    Node * n1 = new Node({1,1});
    Node * n2 = new Node({2,2});
    Node * n3 = new Node({3,3});
    Node * n4 = new Node({4,4});

    n1->location = Vec2i(1,2);
    n2->location = Vec2i(3,5);
    n3->location = Vec2i(7,9);
    n4->location = Vec2i(43,1);

    Key k1(23,42);
    Key k2(21,52);
    Key k3(4,2);
    Key k4(4,1);

    n1->key = k1;
    n2->key = k2;
    n3->key = k3;
    n4->key = k4;


    queue.insert(n1);
    queue.insert(n2);
    queue.insert(n3);
    queue.insert(n4);

    REQUIRE(queue.size() == 4);
    REQUIRE(queue.pop() == n4);
    REQUIRE(queue.size() == 3);
    REQUIRE(!queue.contains(n4));

    delete n1;
    delete n2;
    delete n3;
    delete n4;
}


TEST_CASE( "empty priority queue should return [inf;inf] when topKey is called", "[pop]" ) 
{
    PriorityQueue queue;
    auto topKey = queue.topKey();
    auto inf = std::numeric_limits<double>::infinity();
    REQUIRE(topKey == Key(inf,inf));
}
