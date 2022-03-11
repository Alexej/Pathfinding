#include "LatticeGraph.hpp"

#include "DStarLiteHelpers.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Helpers::DStarLiteHelpers;

    namespace
    {
        void initNode(Node &node, int32_t h, int32_t w)
        {
            node.location = Vec2i(h, w);
            node.g = std::numeric_limits<double>::infinity();
            node.rhs = std::numeric_limits<double>::infinity();
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

    bool LatticeGraph::inBounds(int32_t height_, int32_t width_) const
    {
        int32_t widthI = static_cast<int32_t>(width());
        int32_t heightI = static_cast<int32_t>(height());
        return 0 <= height_ && height_ < heightI && 0 <= width_ && width_ < widthI;
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