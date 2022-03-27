#ifndef ADAA4FC9_A07E_4621_ADAA_C53D5AF42592
#define ADAA4FC9_A07E_4621_ADAA_C53D5AF42592

#include "AException.hpp"

namespace Pathfinding::Exceptions
{
    class WrongNodeNumberForDimensionException final : public Pathfinding::Abstract::AException
    {
        public:
            WrongNodeNumberForDimensionException(const char* msg)
            : AException(msg) {}
    };
}

#endif /* ADAA4FC9_A07E_4621_ADAA_C53D5AF42592 */
