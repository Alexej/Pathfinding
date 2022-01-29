#include "GraphDimension.hpp"


namespace Pathfinding::Core
{
    void GraphDimension::setCurrentNumberOfNodes(NumberOfNodes numOfNodes)
    {
        currentNumberOfNodes_ = numOfNodes;
    }

    int64_t GraphDimension::currentNumberOfNodesIndex() const
    {
        return static_cast<int64_t>(currentNumberOfNodes_);
    }

    NumberOfNodes GraphDimension::currentNumberOfNodes() const
    {
        return currentNumberOfNodes_;
    }

    int64_t GraphDimension::currentNodeSideLength() const
    {
        return NODE_SIDE_LENGTH[static_cast<int64_t>(currentNumberOfNodes_)];
    }

    int64_t GraphDimension::currentNumberOfNodesInRow() const
    {
        return NUMBER_OF_NODES_IN_ROW[static_cast<int64_t>(currentNumberOfNodes_)];
    }

    bool GraphDimension::canShowNodeInfo() const
    {
        return currentNumberOfNodes_ == NUMBER_OF_NODES_FOR_RENDER_INFO;
    }

    void GraphDimension::setCurrentNumberOfNodesIndex(int64_t index)
    {
        currentNumberOfNodes_ = static_cast<NumberOfNodes>(index);
    }

    int64_t GraphDimension::width() const
    {
        return currentNumberOfNodesInRow();
    }
    
    int64_t GraphDimension::height() const
    {
        return currentNumberOfNodesInRow();
    }
}