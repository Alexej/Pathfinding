#ifndef A6775541_7B0D_48D7_98C3_0BC29F68F709
#define A6775541_7B0D_48D7_98C3_0BC29F68F709

namespace Pathfinding::Core::Abstract
{
    class AState
    {
        public:
            AState();
            virtual void init() = 0;
            virtual void handleEvent() = 0;
            virtual void update() = 0;

            virtual ~AState() = default;
        protected:

    };
}

#endif /* A6775541_7B0D_48D7_98C3_0BC29F68F709 */
