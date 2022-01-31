#ifndef BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787
#define BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787

#include <queue>
#include <vector>
#include <list>
#include <functional>
#include <utility>
#include "Node.hpp"
#include "Key.hpp"


namespace Pathfinding::Datastructures
{
    using queueElement = std::pair<Key, Node*>;
    class PriorityQueue final : public std::priority_queue<queueElement, 
                                       std::vector<queueElement>, 
                                       std::greater<queueElement>>
    {
    public:
        auto begin() { return this->c.begin(); }
        auto end() { return this->c.end(); }
        auto begin() const { return this->c.cbegin(); }
        auto end() const { return this->c.cend(); }

        void remove(Node * node)
        {
            auto it = std::find_if(this->c.begin(), this->c.end(), [&node](const queueElement &element)
                                   { return element.second == node; });
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        void insert(Node * node, Key key)
        {
            this->push(std::make_pair(key, node));
        }

        void reset()
        {
            c.clear();
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
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
            return std::find_if(this->c.begin(), this->c.end(), [&node](const queueElement & input)
            {
                return *input.second == *node;
            }
            ) != this->c.end();
        }

    private:
        using std::priority_queue<queueElement, std::vector<queueElement>, std::greater<queueElement>>::pop;
    };
}

#endif /* BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787 */
