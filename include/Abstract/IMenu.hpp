#ifndef F1BFB729_3722_4367_B4BB_1866BE040231
#define F1BFB729_3722_4367_B4BB_1866BE040231

#include <functional>

namespace Pathfinding::Gui { struct MenuCallBacks; }

namespace Pathfinding::Abstract
{
    class IMenu
    {
        public: 
            virtual void show() = 0;
            
            virtual void addCallbacks(Pathfinding::Gui::MenuCallBacks callBacks) = 0;
            
            virtual void showGraph(std::vector<int32_t> values, std::string name) = 0;
            
            virtual ~IMenu() = default;
    };
}

#endif /* F1BFB729_3722_4367_B4BB_1866BE040231 */
