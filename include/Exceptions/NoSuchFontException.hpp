#ifndef D2F7BD00_6D6D_4D59_ACBF_C07A756FA8F5
#define D2F7BD00_6D6D_4D59_ACBF_C07A756FA8F5

#include "AException.hpp"

namespace Pathfinding::Exceptions
{
    class NoSuchFontException final : public Pathfinding::Abstract::AException
    {
    public:
        NoSuchFontException(const char *msg)
            : AException(msg) {}
    };
}

#endif /* D2F7BD00_6D6D_4D59_ACBF_C07A756FA8F5 */
