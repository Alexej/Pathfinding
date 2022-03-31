#include "LatticeGraph.hpp"
#include "InformedSearchAlgorithmHelpers.hpp"
#include "CppHelpers.hpp"

namespace Pathfinding::Datastructures
{
    using Pathfinding::Helpers::infinity;
    using Pathfinding::Helpers::iterateOver2DVector;

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

    const Node * LatticeGraph::node(Vec2i location) const
    {
        return &graph[location.height][location.width];
    }

    bool LatticeGraph::inBounds(Vec2i dimension) const
    {
        int32_t widthI = static_cast<int32_t>(width());
        int32_t heightI = static_cast<int32_t>(height());
        return 0 <= dimension.height && dimension.height < heightI && 0 <= dimension.width && dimension.width < widthI;
    }

    void LatticeGraph::reset()
    {
        iterateOver2DVector(graph, [](Node & node) { node.reset(); });
    }

    void LatticeGraph::update()
    {
        iterateOver2DVector(graph, [](Node & node) { node.update(); });
    }

    void LatticeGraph::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        iterateOver2DVector(graph, [&] (const Node & node) { target.draw(node); });
    }

    void LatticeGraph::resize(int32_t height, int32_t width)
    {
        graph.clear();
        for (int32_t h = 0; h < height; ++h)
        {
            std::vector<Node> row;
            for (int32_t w = 0; w < width; ++w)
            {
                row.push_back(Node(h,w));
            }
            graph.push_back(row);
        }
    }

}