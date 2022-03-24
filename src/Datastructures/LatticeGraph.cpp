#include "LatticeGraph.hpp"
#include "InformedSearchAlgorithmHelpers.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Helpers::infinity;

    namespace
    {
        void initNode(Node &node, int32_t h, int32_t w)
        {
            node.location = Vec2i(h, w);
            node.g = infinity();
            node.rhs = infinity();
            node.key = Key();
            node.state = NodeState::Free;
        }
    }

    LatticeGraph::LatticeGraph(int32_t height, int32_t width)
    {
        resize(height, width);
    }

    LatticeGraph::LatticeGraph(Vec2i dimension)
    {
        resize(dimension.height, dimension.width);
    }

    Node *LatticeGraph::node(Vec2i location)
    {
        return &graph[location.height][location.width];
    }

    const Node *LatticeGraph::node(Vec2i location) const
    {
        return &graph[location.height][location.width];
    }

    bool LatticeGraph::inBounds(Vec2i dimension) const
    {
        int32_t widthI = static_cast<int32_t>(width());
        int32_t heightI = static_cast<int32_t>(height());
        return 0 <= dimension.height && dimension.height < heightI && 0 <= dimension.width && dimension.width < widthI;
    }

    void LatticeGraph::resize(int32_t height, int32_t width)
    {
        graph.clear();
        graph.resize(height, std::vector<Node>(width));
        for (int32_t h = 0; h < height; ++h)
        {
            std::vector<Node> row;
            for (int32_t w = 0; w < width; ++w)
            {
                initNode(graph[h][w], h, w);
            }
        }
    }
}