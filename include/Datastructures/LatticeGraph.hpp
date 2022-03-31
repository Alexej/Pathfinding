#ifndef FD0247C3_67EB_48FC_909F_6614B9CC4CBC
#define FD0247C3_67EB_48FC_909F_6614B9CC4CBC

#include <vector>

#include "Node.hpp"
#include "ILatticeGraph.hpp"
#include "Vec2.hpp"

namespace Pathfinding::Datastructures
{
    class LatticeGraph final : public Pathfinding::Abstract::ILatticeGraph
    {

    public:
        LatticeGraph() = default;

        LatticeGraph(int32_t height, int32_t width);

        explicit LatticeGraph(Vec2i dimension);

        void resize(int32_t height, int32_t width) override;

        void reset() override;

        Node *node(Vec2i location) override;

        const Node * node(Vec2i location) const override;

        bool inBounds(Vec2i location) const override;

        std::size_t width() const override { return graph[0].size(); }

        std::size_t height() const override { return graph.size(); }

        void update() override;  

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        template <typename Type>
        using Vector2D = std::vector<std::vector<Type>>;

    private:
        Vector2D<Node> graph;
    };
}

#endif /* FD0247C3_67EB_48FC_909F_6614B9CC4CBC */
