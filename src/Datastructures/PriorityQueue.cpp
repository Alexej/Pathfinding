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
            auto it = std::find(c.begin(), c.end(), node);
            c.erase(it);
            std::make_heap(c.begin(), c.end(), comp);
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
            if (empty())
            {
                return Key();
            }
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
            return std::find(c.begin(), c.end(), node) != c.end();
        }
}