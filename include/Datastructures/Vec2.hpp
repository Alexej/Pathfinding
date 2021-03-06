#ifndef C71A173D_A9A7_4ABC_B640_D4C5497B6103
#define C71A173D_A9A7_4ABC_B640_D4C5497B6103

#include <compare>
#include <cstdint>

namespace Pathfinding::Datastructures
{
    /**
     * @brief
     * !didn't want to use sf::Vector<T> from sfml because my code uses first coordinate to store the height,
     * !x for height would be misleading.
     * @tparam T
     */
    template <typename T>
    struct Vec2
    {
        Vec2() = default;

        Vec2(T height_, T width_) : height(height_), width(width_) {}

        auto operator<=>(const Vec2<T> &) const = default;

        Vec2 &operator+=(const Vec2 &rhs)
        {
            this->height += rhs.height;
            this->width += rhs.width;
            return *this;
        }

        T height = 0;
        T width = 0;
    };

    template <typename T>
    Vec2<T> operator-(const Vec2<T> &lhs, const Vec2<T> &rhs)
    {
        return {lhs.height - rhs.height, lhs.width - rhs.width};
    }

    template <typename T>
    Vec2<T> operator+(Vec2<T> lhs, const Vec2<T> rhs)
    {
        return lhs += rhs;
    }

    template <typename T>
    Vec2<T> operator*(Vec2<T> lhs, int32_t rhs)
    {
        return {lhs.height * rhs, lhs.width * rhs};
    }


    using Vec2i = Vec2<int32_t>;
}

#endif /* C71A173D_A9A7_4ABC_B640_D4C5497B6103 */
