#include "PriorityQueue.hpp"

#include "Node.hpp"
#include "Key.hpp"

namespace Pathfinding::Datastructures
{
    bool DStarLiteQueueComperator::operator()(const Node *lhs, const Node *rhs)
    {
        return lhs->key > rhs->key;
    }

    void PriorityQueue::remove(const Node *node)
    {
        auto it = std::ranges::find(c, node);
        c.erase(it);
        std::ranges::make_heap(c, std::ranges::greater{}, &Node::key);
    }

    void PriorityQueue::insert(Node *node)
    {
        push(node);
    }

    void PriorityQueue::reset()
    {
        c.clear();
    }

    Key PriorityQueue::topKey() const
    {
        if (empty()) { return Key(); }
        return top()->key;
    }

    Node *PriorityQueue::pop()
    {
        auto topNode = top();
        base::pop();
        return topNode;
    }

    bool PriorityQueue::contains(const Node *node) const
    {
        return std::ranges::find(c, node) != c.end();
    }
}