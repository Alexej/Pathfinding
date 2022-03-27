#ifndef A1F9932C_22C0_4CE7_A428_E5CFF0AF1EC6
#define A1F9932C_22C0_4CE7_A428_E5CFF0AF1EC6

#include "AException.hpp"

namespace Pathfinding::Exceptions
{
    class CouldNotFindPathToFontException final : public Pathfinding::Abstract::AException
    {
        public:
            CouldNotFindPathToFontException(const char* msg)
            : AException(msg) {}
    };
}

#endif /* A1F9932C_22C0_4CE7_A428_E5CFF0AF1EC6 */
