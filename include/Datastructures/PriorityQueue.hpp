#ifndef BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787
#define BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787

#include <queue>
#include <vector>
#include <list>
#include <functional>
#include "Node.hpp"
#include "Key.hpp"

namespace Pathfinding::Datastructures
{
    class DStarLiteQueueComperator
    {
    public:
        bool operator()(const Node *lhs, const Node *rhs)
        {
            return lhs->key > rhs->key;
        }
    };

    class PriorityQueue final : public std::priority_queue<Node *, std::vector<Node *>, DStarLiteQueueComperator>
    {
    public:
        void remove(const Node *node)
        {
            auto it = std::find(c.begin(), c.end(), node);
            c.erase(it);
            std::make_heap(c.begin(), c.end(), comp);
        }

        void insert(Node *node)
        {
            push(node);
        }

        void reset()
        {
            c.clear();
        }

        Key topKey() const
        {
            if (empty())
            {
                return Key();
            }
            return top()->key;
        }

        Node *pop()
        {
            auto topNode = top();
            base::pop();
            return topNode;
        }

        bool contains(const Node *node) const
        {
            return std::find(c.begin(), c.end(), node) != c.end();
        }

    private:
        using base = std::priority_queue<Node *, std::vector<Node *>, DStarLiteQueueComperator>;
    };
}

#endif /* BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787 */
