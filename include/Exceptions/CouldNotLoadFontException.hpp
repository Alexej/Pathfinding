#ifndef A3A6229C_A42C_4EA3_885F_0A92AE26A501
#define A3A6229C_A42C_4EA3_885F_0A92AE26A501

#include "AException.hpp"

namespace Pathfinding::Exceptions
{
    class CouldNotLoadFontException final : public Pathfinding::Abstract::AException
    {
        public:
            CouldNotLoadFontException(const char *msg)
                : AException(msg) {}
    };
}

#endif /* A3A6229C_A42C_4EA3_885F_0A92AE26A501 */
