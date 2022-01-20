#include "GraphDimension.hpp"


namespace Pathfinding::Core
{
    void GraphDimension::setCurrentNumberOfNodes(NumberOfNodes numOfNodes)
    {
        currentNumberOfNodes_ = numOfNodes;
    }

    int32_t GraphDimension::currentNumberOfNodesI() const
    {
        return NUMBER_OF_NODES[static_cast<int32_t>(currentNumberOfNodes_)];
    }

    NumberOfNodes GraphDimension::currentNumberOfNodes() const
    {
        return currentNumberOfNodes_;
    }

    int32_t GraphDimension::currentNodeSideLength() const
    {
        return NODE_SIDE_LENGTH[static_cast<int32_t>(currentNumberOfNodes_)];
    }

    int32_t GraphDimension::currentNumberOfNodesInRow() const
    {
        return NUMBER_OF_NODES_IN_ROW[static_cast<int32_t>(currentNumberOfNodes_)];
    }

    bool GraphDimension::canRenderInfo() const
    {
        return currentNumberOfNodes_ == NUMBER_OF_NODES_FOR_RENDER_INFO;
    }
}