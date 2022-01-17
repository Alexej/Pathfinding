#ifndef FD0247C3_67EB_48FC_909F_6614B9CC4CBC
#define FD0247C3_67EB_48FC_909F_6614B9CC4CBC

#include <vector>
#include "Node.hpp"

template<typename Type>
using Vector2D = std::vector<std::vector<Type>>;

namespace Pathfinding::Datastructures
{
    class LatticeGraph
    {
        public:
            LatticeGraph(int32_t height, int32_t width)
            {
                graph.resize(height, std::vector<Node>(width));
                for(int32_t h = 0; h < height; ++h)
                {
                    std::vector<Node> row;
                    for(int32_t w = 0; w < width; ++w)
                    {
                        graph[h][w].location = GraphLocation(h,w);
                    }
                }
            }

            std::vector<Node> & operator[](std::size_t height) {return graph[height];}
            const std::vector<Node> & operator[](std::size_t height) const {return graph[height];}
            Node & node(GraphLocation location) {return graph[location.height][location.width];}
            const Node & node(GraphLocation location) const {return graph[location.height][location.width];}
            
            std::size_t width() const {return graph[0].size();}
            std::size_t height() const {return graph.size();}

            bool inBounds(GraphLocation location) const
            {
                int32_t widthI = static_cast<int32_t>(width());
                int32_t heightI = static_cast<int32_t>(height());
                return 0 <= location.height && location.height < heightI && 0 <= location.width && location.width < widthI;
            }

        private:
            Vector2D<Node> graph;
    };
    
    std::vector<Node> & successors(LatticeGraph & graph, Node node);
}

#endif /* FD0247C3_67EB_48FC_909F_6614B9CC4CBC */
