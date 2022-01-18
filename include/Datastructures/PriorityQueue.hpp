#ifndef BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787
#define BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787

#include <queue>
#include <vector>
#include <list>
#include <utility>
#include "Node.hpp"
#include "Key.hpp"

namespace Pathfinding::Datastructures
{
    using queue_element = std::pair<Key, Node*>;

    template <typename T>
    class Comperator
    {
    public:
        auto operator()(const T &lhs, const T &rhs)
        {
            return lhs.first > rhs.first;
        }
    };

    class PriorityQueue final : public std::priority_queue<queue_element, std::vector<queue_element>, Comperator<queue_element>>
    {
    public:
        auto begin() { return this->c.begin(); }
        auto end() { return this->c.end(); }
        const auto begin() const { return this->c.begin(); }
        const auto end() const { return this->c.end(); }

        void remove(Node * node)
        {
            auto it = std::find_if(this->c.begin(), this->c.end(), [&node](const queue_element &element)
                                   { return element.second == node; });
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        void insert(Node * node, Key key)
        {
            this->push(std::make_pair(key, node));
        }

        Key topKey()
        {
            return this->top().first;
        }

        Node * popD()
        {
            auto topNode = this->top();
            pop();
            return topNode.second;
        }

        bool contains(const Node * node)
        {
            return std::find_if(this->c.begin(), this->c.end(), [&node](const queue_element & input)
            {
                return *input.second == *node;
            }
            ) != this->c.end();
        }

    private:
        using std::priority_queue<queue_element, std::vector<queue_element>, Comperator<queue_element>>::pop;
    };
}

#endif /* BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787 */
