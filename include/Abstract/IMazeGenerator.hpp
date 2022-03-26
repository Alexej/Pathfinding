#ifndef C95A42FC_29F8_4146_B735_0A6D34E13BA2
#define C95A42FC_29F8_4146_B735_0A6D34E13BA2

namespace Pathfinding::Core { class RandomIntegers; }

namespace Pathfinding::Abstract
{
    class ILatticeGraph;
    class IMazeGenrator
    {
        private:
            using RCRandomIntegers = Pathfinding::Core::RandomIntegers;
        public:
            virtual void generate(ILatticeGraph & latGraph, RCRandomIntegers & ri) = 0;
    };
}

#endif /* C95A42FC_29F8_4146_B735_0A6D34E13BA2 */
