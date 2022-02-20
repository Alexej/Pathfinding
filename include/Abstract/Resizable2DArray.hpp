#ifndef D611F9DF_C7A3_421B_9CEE_5C3831BD9E8A
#define D611F9DF_C7A3_421B_9CEE_5C3831BD9E8A

#include <cstddef>
#include <cstdint>
#include "Vec2.hpp"

namespace Pathfinding::Abstract
{
    class Resizable2DArray
    {
        private:
            using PDVec2i = Pathfinding::Datastructures::Vec2i;
        public:
            virtual void resize(int32_t height, int32_t width) = 0;
            virtual std::size_t width() const = 0;
            virtual std::size_t height() const = 0;
            virtual ~Resizable2DArray() = default;
    };
}

#endif /* D611F9DF_C7A3_421B_9CEE_5C3831BD9E8A */
