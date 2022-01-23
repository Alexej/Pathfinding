#ifndef FD0247C3_67EB_48FC_909F_6614B9CC4CBC
#define FD0247C3_67EB_48FC_909F_6614B9CC4CBC

#include <vector>
#include "Node.hpp"
#include <unordered_map>

namespace Pathfinding::Datastructures
{

    template <typename Type>
    using Vector2D = std::vector<std::vector<Type>>;
    
    class LatticeGraph
    {
    public:
        LatticeGraph() = default;
        LatticeGraph(int32_t height, int32_t width);
        explicit LatticeGraph(GraphLocation dimension);

        std::size_t width() const { return graph[0].size(); }
        std::size_t height() const { return graph.size(); }

        bool inBounds(GraphLocation location) const;

        const Node * startNode() const;
        const Node * goalNode() const;
        
        std::vector<Node> &operator[](std::size_t height) { return graph[height]; }
        const std::vector<Node> &operator[](std::size_t height) const { return graph[height]; }

        Node * node(GraphLocation location) { return &graph[location.height][location.width]; }
        const Node * node(GraphLocation location) const { return &graph[location.height][location.width]; }

        Node * startNode();
        Node * goalNode();

        void setGoal(GraphLocation location);
        void setStart(GraphLocation location);
        void blockNode(GraphLocation location);
        void clearNode(GraphLocation location);

        void resetEndpoints();
        void resize(int32_t height, int32_t width);

    private:
        Vector2D<Node> graph;
        Node * goalNodePtr;
        Node * startNodePtr;
    };
}

#endif /* FD0247C3_67EB_48FC_909F_6614B9CC4CBC */
