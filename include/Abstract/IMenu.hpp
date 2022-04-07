#ifndef F1BFB729_3722_4367_B4BB_1866BE040231
#define F1BFB729_3722_4367_B4BB_1866BE040231

#include <functional>

namespace Pathfinding::Gui { struct MenuCallBacks; }
namespace sf { class RenderWindow; }
namespace sf { class Time; }
namespace sf { class Event; }

namespace Pathfinding::Abstract
{
    class IMenu
    {
        public: 
            virtual void show() = 0;
            
            virtual void addCallbacks(Pathfinding::Gui::MenuCallBacks callBacks) = 0;
            
            virtual void showGraph(std::vector<int32_t> values, std::string name) const = 0;

            virtual void update(sf::RenderWindow & window, sf::Time deltaClock) = 0;

            virtual void processEvent(const sf::Event & event) = 0;

            virtual void shutDown() = 0;

            virtual void init(sf::RenderWindow & window) = 0;

            virtual void render(sf::RenderWindow & window) = 0;

            virtual ~IMenu() = default;
    };
}

#endif /* F1BFB729_3722_4367_B4BB_1866BE040231 */
