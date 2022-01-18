#include "LatticeGraph.hpp"

namespace Pathfinding::Datastructures
{
    LatticeGraph::LatticeGraph(int32_t height, int32_t width)
    {
        resize(height, width);
    }

    bool LatticeGraph::inBounds(GraphLocation location) const
    {
        int32_t widthI = static_cast<int32_t>(width());
        int32_t heightI = static_cast<int32_t>(height());
        return 0 <= location.height && location.height < heightI && 0 <= location.width && location.width < widthI;
    }

    void LatticeGraph::resetEndpoints()
    {
        int32_t heightI = static_cast<int32_t>(height());
        int32_t widthI = static_cast<int32_t>(width());
        goalLocation_ = GraphLocation(heightI - 1, widthI - 1);
        startLocation_ = GraphLocation(0, 0);
        node(goalLocation_).state = NodeState::Goal;
        node(startLocation_).state = NodeState::Start;
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
                graph[h][w].location = GraphLocation(h, w);
            }
        }
        resetEndpoints();
    }

    GraphLocation LatticeGraph::startLocation() const
    {
        return startLocation_;
    }

    GraphLocation LatticeGraph::goalLocation() const
    {
        return goalLocation_;
    }

    void LatticeGraph::setGoal(GraphLocation location)
    {
        if (node(location).state == NodeState::Free)
        {
            node(goalLocation_).state = NodeState::Free;
            goalLocation_ = location;
            node(goalLocation_).state = NodeState::Goal;
        }
    }

    void LatticeGraph::setStart(GraphLocation location)
    {
        if (node(location).state == NodeState::Free)
        {
            node(startLocation_).state = NodeState::Free;
            startLocation_ = location;
            node(startLocation_).state = NodeState::Start;
        }
    }

    void LatticeGraph::blockNode(GraphLocation location)
    {
        if (node(location).state == NodeState::Free)
        {
            node(location).state = NodeState::Blocked;
        }
    }

    void LatticeGraph::clearNode(GraphLocation location)
    {
        if (node(location).state == NodeState::Blocked)
        {
            node(location).state = NodeState::Free;
        }
    }
}