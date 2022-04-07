#ifndef BB1F1402_93A5_498F_AB28_5E164076558D
#define BB1F1402_93A5_498F_AB28_5E164076558D

#include <ranges>
#include "Node.hpp"
#include "ILatticeGraph.hpp"

namespace Pathfinding::Datastructures
{
    struct Edge
    {
        Node * from;
        double weight;
        Node * to;
    };

    bool operator==(const Edge & lhs, const Edge & rhs)
    {
        return (lhs.from == rhs.from && lhs.to == rhs.to) || (lhs.from == rhs.to && lhs.to == rhs.from);
    }

    class CostFunction
    {
        public:
            void init(Pathfinding::Abstract::ILatticeGraph & graph)
            {

            }

            bool contains(const Edge & edge) const
            {
                return std::ranges::find(edges, edge) != edges.end();
            }

            void updateAllEdgesFromNode(const Node * node, double weight)
            {
            }


            void updateEdge(const Node * from, const Node * to, double weight)
            {
                
            }

            void add(Edge edge)
            {
                if(!contains(edge))
                {
                    edges.push_back(edge);
                }
            }
        private:
            std::vector<Edge> edges;
    };
}

#endif /* BB1F1402_93A5_498F_AB28_5E164076558D */

