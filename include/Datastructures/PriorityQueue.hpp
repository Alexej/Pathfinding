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
    class NodeComperator
    {
    public:
        bool operator() (const Node * lhs, const Node * rhs)
        {
            return lhs->key > rhs->key;
        }
    };

    class PriorityQueue final : public std::priority_queue<Node *, std::vector<Node *>, NodeComperator>
    {
    public:
        void remove(Node *node)
        {
            auto it = std::find_if(this->c.begin(), this->c.end(), 
            
                [&node](const Node * element)
                { 
                    return *element == *node; 
                });

            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        void insert(Node *node)
        {
            this->push(node);
        }

        void reset()
        {
            c.clear();
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        Key topKey() const
        {
            if (this->empty())
            {
                return Key();
            }
            return this->top()->key;
        }

        Node *popD()
        {
            auto topNode = this->top();
            pop();
            return topNode;
        }

        bool contains(const Node *node)
        {
            return std::find_if(this->c.begin(), this->c.end(), 
            [&node](const Node* input)
            { 
                return *input == *node; 
            }) != this->c.end();
        }

    private:
        using std::priority_queue<Node *, std::vector<Node *>, NodeComperator>::pop;
    };
}

#endif /* BCC940D8_CEDF_4B76_8CE4_D8C9A4D1A787 */
