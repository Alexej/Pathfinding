#ifndef BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4
#define BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4

#include <stack>
#include <string>
#include "Node.hpp"

namespace Pathfinding::Helpers
{
    template <typename IntegerType>
    bool isEven(IntegerType number)
    {
        static_assert(std::is_integral<IntegerType>::value, "Integral required.");
        return number % 2 == 0;
    }

    template <typename ElementType>
    ElementType pop(std::stack<ElementType> &stack)
    {
        auto lastTop = stack.top();
        stack.pop();
        return lastTop;
    }

    template <typename ElementType>
    bool inVector(std::vector<ElementType> vec, ElementType element)
    {
        return std::find(vec.begin(), vec.end(), element) != vec.end();
    }
    
    inline std::string getSubstrBeforeChar(std::string string, char character)
    {
        return string.substr(0, string.find(character, 0));
    }

    inline std::vector<Pathfinding::Datastructures::Node *>
    flushVector(std::vector<Pathfinding::Datastructures::Node *> &nodesExpanded)
    {
        auto tmpNodesExpanded = nodesExpanded;
        nodesExpanded.clear();
        return tmpNodesExpanded;
    }
}

#endif /* BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4 */
