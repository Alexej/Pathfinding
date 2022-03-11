#ifndef AD6126EE_B0B8_41A7_B97D_118F9BD06A92
#define AD6126EE_B0B8_41A7_B97D_118F9BD06A92

#include <exception>

namespace Pathfinding::Abstract
{
    class AException : public std::exception
    {
    public:
        AException(const char *msg) : std::exception(msg) {}
        
        virtual ~AException() = default;
    };
}

#endif /* AD6126EE_B0B8_41A7_B97D_118F9BD06A92 */
