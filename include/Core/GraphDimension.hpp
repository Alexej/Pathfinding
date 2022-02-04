#ifndef A260E5D5_D418_4CAF_9276_2D09AF3140A7
#define A260E5D5_D418_4CAF_9276_2D09AF3140A7

#include <array>
namespace Pathfinding::Core
{
    // For Imgui ComboBox
    constexpr const char *NUMBER_OF_NODES_CHAR[] = {"100", "400", "625", "1600"};
    enum class NumberOfNodes
    {
        N_100,
        N_400,
        N_625,
        N_1600
    };
    class GraphDimension
    {
    public:
        void setCurrentNumberOfNodes(NumberOfNodes numOfNodes);
        void setCurrentNumberOfNodesIndex(int32_t index);
        int32_t currentNumberOfNodesIndex() const;
        NumberOfNodes currentNumberOfNodes() const;
        int32_t currentNodeSideLength() const;
        int32_t currentNumberOfNodesInRow() const;
        bool canShowNodeInfo() const;
        int32_t width() const;
        int32_t height() const;

    private:
        using arr4i = std::array<int32_t, 4>;

    private:
        NumberOfNodes currentNumberOfNodes_ = NumberOfNodes::N_100;
        arr4i NUMBER_OF_NODES{100, 400, 625, 1600};
        arr4i NODE_SIDE_LENGTH{80, 40, 32, 20};
        arr4i NUMBER_OF_NODES_IN_ROW{10, 20, 25, 40};
        const NumberOfNodes NUMBER_OF_NODES_FOR_RENDER_INFO = NumberOfNodes::N_100;
    };
}

#endif /* A260E5D5_D418_4CAF_9276_2D09AF3140A7 */
