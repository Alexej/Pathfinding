#ifndef EE121C46_77A1_42C0_82FD_AA5B2F176C40
#define EE121C46_77A1_42C0_82FD_AA5B2F176C40

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

#include "IRenderer.hpp"

namespace Pathfinding::Datastructures { class LatticeGraph; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Datastructures { enum class NodeState; }
namespace Pathfinding::Abstract { class ALatGraphWr; }
namespace Pathfinding::Abstract { class IApplicationState; }
namespace Pathfinding::Abstract { class IFontLoader; }
namespace Pathfinding::Core { class GraphDimension; }
namespace Pathfinding::Core { struct ApplicationState; }

namespace Pathfinding::Rendering
{
    class Renderer final : public Pathfinding::Abstract::IRenderer
    {
    private:
        using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDNodeState = Pathfinding::Datastructures::NodeState;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PCGraphDimension = Pathfinding::Core::GraphDimension;
        using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        using PAIFontLoader = Pathfinding::Abstract::IFontLoader;

    public:
        Renderer() = default;
        
        Renderer(sf::RenderWindow *window, PCApplicationState *appStateSPtr, std::shared_ptr<PAIFontLoader> fontLoaderSPtr);
        
        void render(const std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr) override;
        
        void renderPath(const std::vector<PDNode *> &path, sf::Color color) override;
        
        void update() override;
        
        void reset() override;
        
        void resize() override;
        

    private:
        void init();
                
        void renderNode(const PDNode &node, sf::Vector2f coords);
        
        void renderNodeInfo(const PDNode &node, sf::Vector2f coords);
        
        void renderPathLineEndPoints(const std::vector<PDNode *> &path, sf::Vector2f pointPositionOffset, sf::Color color);
        
        void renderPathLines(const std::vector<PDNode *> &path, sf::Vector2f pointPositionOffset);
        
        sf::Color stateColor(PDNodeState state);
        
        void updateColor();
        
        void setPathColor(sf::Color color);
        

    private:
        sf::RectangleShape nodeRect;
        sf::Text text;
        sf::Font font;
        sf::CircleShape nodePoint;
        sf::RectangleShape diagonalLine;
        sf::RectangleShape straightLine;
        sf::RectangleShape factorRect;
        sf::Color goalNodeDiff = sf::Color::Black;
        sf::RenderWindow *windowPtr = nullptr;
        PCApplicationState *appStateSPtr = nullptr;
        PCGraphDimension *dimensionPtr = nullptr;
        sf::Color visitedNodeDiff = sf::Color::Black;
        sf::Color goalColor;
        sf::Color visitedColor;
        bool colorUp = false;
        std::shared_ptr<PAIFontLoader> fontLoaderSPtr;
    };
}

#endif /* EE121C46_77A1_42C0_82FD_AA5B2F176C40 */
