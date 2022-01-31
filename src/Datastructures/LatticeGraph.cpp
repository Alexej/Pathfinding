#include "LatticeGraph.hpp"

namespace Pathfinding::Datastructures
{
    namespace 
    {
        void initNode(Node & node, int32_t h, int32_t w)
        {
            node.location = Vector2i(h, w);
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

    LatticeGraph::LatticeGraph(Vector2i dimension)
    {
        resize(dimension.height, dimension.width);
    }

    bool LatticeGraph::inBounds(Vector2i location) const
    {
        int32_t widthI = static_cast<int32_t>(width());
        int32_t heightI = static_cast<int32_t>(height());
        return 0 <= location.height && location.height < heightI && 0 <= location.width && location.width < widthI;
    }

    void LatticeGraph::resetEndpoints()
    {
        int32_t heightI = static_cast<int32_t>(height());
        int32_t widthI = static_cast<int32_t>(width());
        goalNodePtr = &graph[heightI - 1][widthI - 1];
        startNodePtr = &graph[0][0];
        goalNodePtr->state = NodeState::Goal;
        startNodePtr->state = NodeState::Start;
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
        resetEndpoints();
    }

    const Node *LatticeGraph::startNode() const
    {
        return startNodePtr;
    }

    const Node *LatticeGraph::goalNode() const
    {
        return goalNodePtr;
    }

    Node *LatticeGraph::startNode()
    {
        return startNodePtr;
    }

    Node *LatticeGraph::goalNode()
    {
        return goalNodePtr;
    }

    void LatticeGraph::setGoal(Vector2i location)
    {
        if (node(location)->state == NodeState::Free)
        {
            goalNodePtr->state = NodeState::Free;
            goalNodePtr = &graph[location.height][location.width];
            goalNodePtr->state = NodeState::Goal;
        }
    }

    void LatticeGraph::setStart(Vector2i location)
    {
        if (node(location)->state == NodeState::Free)
        {
            startNodePtr->state = NodeState::Free;
            startNodePtr = &graph[location.height][location.width];
            startNodePtr->state = NodeState::Start;
        }
    }

    void LatticeGraph::blockNode(Vector2i location)
    {
        if (node(location)->state == NodeState::Free)
        {
            node(location)->state = NodeState::Blocked;
        }
    }

    void LatticeGraph::clearNode(Vector2i location)
    {
        if (node(location)->state == NodeState::Blocked)
        {
            node(location)->state = NodeState::Free;
        }
    }
}