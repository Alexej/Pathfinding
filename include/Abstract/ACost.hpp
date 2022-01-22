#ifndef D9429164_9A34_4D48_8AD0_E1256EA919D9
#define D9429164_9A34_4D48_8AD0_E1256EA919D9

namespace Pathfinding::Abstract
{
    class ACost
    {
        public:
            virtual int32_t calculate(const Node * from, const Node * to) = 0;
            virtual ~ACost() = default;
    }
}

#endif /* D9429164_9A34_4D48_8AD0_E1256EA919D9 */
