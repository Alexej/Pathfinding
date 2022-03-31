#ifndef BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4
#define BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4

#include <stack>
#include <string>
#include <concepts>
#include "Node.hpp"


namespace Pathfinding::Helpers
{
    template<typename ElementType, typename Function>
    void iterateOver2DVector(std::vector<std::vector<ElementType>> & vec, 
                             Function function)
    {

        for(auto & row : vec)
        {
            for(auto & element : row)
            {
                function(element);
            }
        }
    }

    template<typename ElementType, typename Function>
    void iterateOver2DVector(const std::vector<std::vector<ElementType>> & vec, 
                             Function function)
    {
        for(auto & row : vec)
        {
            for(auto & element : row)
            {
                function(element);
            }
        }
    }

    template<typename PointerType>
    bool isNullptr(PointerType pointer)
    {
        static_assert(std::is_pointer<PointerType>::value, "Pointer required."); 
        return pointer == nullptr; 
    }

    template <std::integral IntegerType>
    bool isEven(IntegerType number)
    {
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

    template<typename ElementType>
    inline std::vector<ElementType> flushVector(std::vector<ElementType> & nodesExpanded)
    {
        auto tmpNodesExpanded = nodesExpanded;
        nodesExpanded.clear();
        return tmpNodesExpanded;
    }
}

#endif /* BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4 */
