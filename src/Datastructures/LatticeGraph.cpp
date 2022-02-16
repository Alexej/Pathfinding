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

    bool LatticeGraph::inBounds(Vec2i location) const
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

    void LatticeGraph::setGoal(Vec2i location)
    {
        if (node(location)->state == NodeState::Free)
        {
            goalNodePtr->state = NodeState::Free;
            goalNodePtr = node(location);
            goalNodePtr->state = NodeState::Goal;
        }
    }

    void LatticeGraph::setStart(Vec2i location)
    {
        if (node(location)->state != NodeState::Goal && node(location)->state != NodeState::Blocked)
        {
            startNodePtr->state = NodeState::Free;
            startNodePtr = node(location);
            startNodePtr->state = NodeState::Start;
        }
    }

    void LatticeGraph::blockNode(Vec2i location)
    {
        if (node(location)->state != NodeState::Start && node(location)->state != NodeState::Goal)
        {
            node(location)->state = NodeState::Blocked;
        }
    }

    void LatticeGraph::clearNode(Vec2i location)
    {
        if (node(location)->state == NodeState::Blocked)
        {
            if(node(location)->visitedOnce)
            {
                node(location)->state = NodeState::Visited;
            }
            else
            {
                node(location)->state = NodeState::Free;
            }
        }
    }

    void initRandomGraph(LatticeGraph &graph)
    {
        for (int32_t h = 0; h < graph.height(); ++h)
        {
            for (int32_t w = 0; w < graph.width(); ++w)
            {
                if (graph[h][w].state == NodeState::Free && rand() % 3 == 0)
                {
                    graph[h][w].state = NodeState::Blocked;
                }
            }
        }
    }

    std::vector<Node*> neighbors(LatticeGraph & graph, Node * node)
    {
        std::vector<Node *> nbors;
        int32_t hFrom = node->location.height - 1;
        int32_t hTo = node->location.height + 1;
        int32_t wFrom = node->location.width - 1;
        int32_t wTo = node->location.width + 1;

        for (int32_t h = hFrom; h <= hTo; ++h)
        {
            for (int32_t w = wFrom; w <= wTo; ++w)
            {
                Vec2i location(h, w);
                if (graph.inBounds(location) && node->location != location && !DStarLiteHelpers::blocked(graph.node(location)))
                {
                    nbors.push_back(graph.node(location));
                }
            }
        }
        return nbors;
    }
}