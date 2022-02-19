#ifndef FD0247C3_67EB_48FC_909F_6614B9CC4CBC
#define FD0247C3_67EB_48FC_909F_6614B9CC4CBC

#include "Node.hpp"
#include <vector>
#include <ILatticeGraph.hpp>

namespace Pathfinding::Datastructures
{
    class LatticeGraph final : public Pathfinding::Abstract::ILatticeGraph
    {

    public:
        LatticeGraph() = default;
        LatticeGraph(int32_t height, int32_t width);
        explicit LatticeGraph(Vec2i dimension);
        void resize(int32_t height, int32_t width) override;
        std::vector<Node> & operator[](std::size_t height)  override { return graph[height]; }
        const std::vector<Node> & operator[](std::size_t height) const override { return graph[height]; }
        bool inBounds(int32_t height, int32_t width) const override;
        std::size_t width() const override { return graph[0].size(); }
        std::size_t height() const override { return graph.size(); }
    private:
        template <typename Type>
        using Vector2D = std::vector<std::vector<Type>>;

    private:
        Vector2D<Node> graph;
    };
}

#endif /* FD0247C3_67EB_48FC_909F_6614B9CC4CBC */
