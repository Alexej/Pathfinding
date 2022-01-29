#ifndef C71A173D_A9A7_4ABC_B640_D4C5497B6103
#define C71A173D_A9A7_4ABC_B640_D4C5497B6103


#include <compare>
#include <stdint.h>

namespace Pathfinding::Datastructures
{
    /**
     * @brief 
     * !didn't want to use sf::Vector<T> from sfml because my code uses the first coordinate to store the height,
     * !x for height would be misleading.
     * @tparam T 
     */
    template<typename T>
    struct Vector2
    {
        Vector2() = default;
        Vector2(T height_, T width_) : height(height_), width(width_) {}
        T height = 0;
        T width = 0;
        auto operator<=>(const Vector2<T> &) const = default;
    };
    using Vector2i = Vector2<int64_t>;
}

#endif /* C71A173D_A9A7_4ABC_B640_D4C5497B6103 */
