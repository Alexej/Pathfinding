#ifndef ADAA4FC9_A07E_4621_ADAA_C53D5AF42592
#define ADAA4FC9_A07E_4621_ADAA_C53D5AF42592

#include "AException.hpp"

namespace Pathfinding::Exceptions
{
    class WrongNodeNumberForDimensionException final : public Pathfinding::Abstract::AException
    {
        public:
        WrongNodeNumberForDImensionException(const char* msg, const char* file_, int line_, const char* func_, const char* info_ = "")
        : AException(msg, file_, line_, func_, info_) {}
    };
}

#endif /* ADAA4FC9_A07E_4621_ADAA_C53D5AF42592 */
