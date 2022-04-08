#ifndef FE79F168_93E8_4752_89DD_3BBE25381541
#define FE79F168_93E8_4752_89DD_3BBE25381541

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Abstract
{
    class IInformedSearchAlgorithmFunctions
    {
        public:
            virtual double calculate(const Pathfinding::Datastructures::Node *from, 
                                     const Pathfinding::Datastructures::Node *to) = 0;
            
            virtual ~IInformedSearchAlgorithmFunctions() = default;
            
    };
}

#endif /* FE79F168_93E8_4752_89DD_3BBE25381541 */
