#ifndef FE79F168_93E8_4752_89DD_3BBE25381541
#define FE79F168_93E8_4752_89DD_3BBE25381541

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Abstract
{
    class IDStarLiteFunction
    {
        protected:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            virtual double calculate(const PDNode *from, const PDNode *to) = 0;
            virtual ~IDStarLiteFunction() = default;
    };
}

#endif /* FE79F168_93E8_4752_89DD_3BBE25381541 */
