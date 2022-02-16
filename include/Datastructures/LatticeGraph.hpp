#ifndef FD0247C3_67EB_48FC_909F_6614B9CC4CBC
#define FD0247C3_67EB_48FC_909F_6614B9CC4CBC

#include "Node.hpp"
#include <vector>

namespace Pathfinding::Datastructures
{

    class LatticeGraph
    {

    public:
        LatticeGraph() = default;
        LatticeGraph(int32_t height, int32_t width);
        explicit LatticeGraph(Vec2i dimension);

        std::size_t width() const { return graph[0].size(); }
        std::size_t height() const { return graph.size(); }

        bool inBounds(Vec2i location) const;

        std::vector<Node> &operator[](std::size_t height) { return graph[height]; }
        const std::vector<Node> &operator[](std::size_t height) const { return graph[height]; }

        /*
        Move this to another class
        */
        //////////////////////////////////
        Node *node(Vec2i location) { return &graph[location.height][location.width]; }
        const Node *node(Vec2i location) const { return &graph[location.height][location.width]; }

        const Node *startNode() const;
        const Node *goalNode() const;

        Node *startNode();
        Node *goalNode();

        void setGoal(Vec2i location);
        void setStart(Vec2i location);
        void blockNode(Vec2i location);
        void clearNode(Vec2i location);

        void resetEndpoints();
        void resize(int32_t height, int32_t width);
        ///////////////////////////////////////////////////
    private:
        template <typename Type>
        using Vector2D = std::vector<std::vector<Type>>;

    private:
        Vector2D<Node> graph;
        Node *goalNodePtr;
        Node *startNodePtr;
    };

    void initRandomGraph(LatticeGraph &graph);
    std::vector<Node*> neighbors(LatticeGraph & graph, Node * node);

}

#endif /* FD0247C3_67EB_48FC_909F_6614B9CC4CBC */
