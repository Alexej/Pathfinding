#include "GraphDimension.hpp"
#include <cmath>
#include "WrongNodeNumberForDImensionException.hpp"

#include <iostream>

namespace Pathfinding::Core
{
    using Pathfinding::Exceptions::WrongNodeNumberForDimensionException;

    GraphDimension::GraphDimension(int32_t sideLength, std::initializer_list<int32_t> numberOfNodesInRow_)
        : numberOfNodesInRow(numberOfNodesInRow_)
    {
        for (auto numOfNodes : numberOfNodesInRow)
        {
            if (sideLength % numOfNodes != 0)
            {
                throw WrongNodeNumberForDimensionException("Wrong dimensions entered",
                                                           "GraphDimension.cpp",
                                                           14,
                                                           "GraphDimension::GraphDimension(int32_t sideLength, std::initializer_list<int32_t> numberOfNodesInRow_)");
            }
            int32_t numberOfNodes = static_cast<int32_t>(std::pow(numOfNodes, 2));
            numberOfNodesInt.push_back(numberOfNodes);
            numberOfNodesString.push_back(std::to_string(numberOfNodes));
            nodeSideLengths.push_back(sideLength / numOfNodes);
            setCurrentNumberOfNodesIndex(0);
        }
    }

    GraphDimension::GraphDimension()
        : GraphDimension(800, {10}) {}

    int32_t GraphDimension::currentNumberOfNodesIndex() const
    {
        return currentNumberOfNodesIndex_;
    }

    int32_t GraphDimension::currentNumberOfNodes() const
    {
        return numberOfNodesInt[currentNumberOfNodesIndex_];
    }

    int32_t GraphDimension::currentNodeSideLength() const
    {
        return nodeSideLengths[currentNumberOfNodesIndex_];
    }

    int32_t GraphDimension::currentNumberOfNodesInRow() const
    {
        return numberOfNodesInRow[currentNumberOfNodesIndex_];
    }

    bool GraphDimension::canShowNodeInfo() const
    {
        return currentNodeSideLength() >= 80;
    }

    void GraphDimension::setCurrentNumberOfNodesIndex(int32_t index)
    {
        currentNumberOfNodesIndex_ = index;
    }

    int32_t GraphDimension::width() const
    {
        return currentNumberOfNodesInRow();
    }

    int32_t GraphDimension::height() const
    {
        return currentNumberOfNodesInRow();
    }

    const std::vector<std::string> &GraphDimension::getNumberOfNodesInRowString() const
    {
        return numberOfNodesString;
    }
}