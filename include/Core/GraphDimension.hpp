#ifndef A260E5D5_D418_4CAF_9276_2D09AF3140A7
#define A260E5D5_D418_4CAF_9276_2D09AF3140A7

#include <vector>
#include <string>

namespace Pathfinding::Core
{
    class GraphDimension
    {
        public:
            GraphDimension();
            GraphDimension(int32_t sideLength, std::initializer_list<int32_t> numberOfNodesInRow);
            void setCurrentNumberOfNodesIndex(int32_t index);
            int32_t currentNumberOfNodesIndex() const;
            int32_t currentNumberOfNodes() const;
            int32_t currentNodeSideLength() const;
            int32_t currentNumberOfNodesInRow() const;
            const std::vector<std::string> & getNumberOfNodesInRowString() const;
            bool canShowNodeInfo() const;
            int32_t width() const;
            int32_t height() const;
        private:
            std::vector<int32_t> nodeSideLengths;
            std::vector<int32_t> numberOfNodesInRow;
            std::vector<int32_t> numberOfNodesInt;
            std::vector<std::string> numberOfNodesString;
            int32_t currentNumberOfNodesIndex_;
    };
}

#endif /* A260E5D5_D418_4CAF_9276_2D09AF3140A7 */
