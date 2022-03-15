#ifndef BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787
#define BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787

#include <queue>
#include <vector>
#include <list>
#include <functional>


namespace Pathfinding::Datastructures
{
    struct Node;
    struct Key;
    class DStarLiteQueueComperator
    {
    public:
        bool operator()(const Node *lhs, const Node *rhs);

    };

    class PriorityQueue final : public std::priority_queue<Node *, std::vector<Node *>, DStarLiteQueueComperator>
    {
    public:
        void remove(const Node *node);

        void insert(Node *node);

        void reset();

        Key topKey() const;

        Node *pop();

        bool contains(const Node *node) const;

    private:
        using base = std::priority_queue<Node *, std::vector<Node *>, DStarLiteQueueComperator>;
    };
}

#endif /* BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787 */
