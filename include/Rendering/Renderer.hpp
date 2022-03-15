#ifndef EE121C46_77A1_42C0_82FD_AA5B2F176C40
#define EE121C46_77A1_42C0_82FD_AA5B2F176C40

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

#include "RenderingHelpers.hpp"
#include "IRenderer.hpp"
#include "DrawableNode.hpp"
#include "DrawablePath.hpp"

namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Core { struct ApplicationState; }
namespace Pathfinding::Core { class GraphDimension; }
namespace Pathfinding::Abstract { class ALatGraphWr; }
namespace Pathfinding::Abstract { class IFontLoader; }
namespace Pathfinding::Helpers { class ColorGradient; }

namespace Pathfinding::Rendering
{
    struct Gradients
    {
        private:
            using PHColorGradient = Pathfinding::Helpers::ColorGradient;
        public:
            PHColorGradient gradientBlockedRed;
            PHColorGradient gradientBlockedBlue;
            PHColorGradient gradientGoalRed;
            PHColorGradient gradientGoalGreen;
    };

    class Renderer final : public Pathfinding::Abstract::IRenderer
    {
    private:
        using PDNode = Pathfinding::Datastructures::Node;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PCGraphDimension = Pathfinding::Core::GraphDimension;
        using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        using PAIFontLoader = Pathfinding::Abstract::IFontLoader;
    public:
        Renderer() = default;
        
        Renderer(sf::RenderWindow *window, PCApplicationState *appStateSPtr, std::shared_ptr<PAIFontLoader> fontLoaderSPtr);
        
        void render(const std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr) override;
        
        void renderPath(const std::vector<PDNode *> &path, sf::Color color) override;
                
        void reset() override;
        
        void resize() override;
        

    private:
        void init();
                
        void updateColorDiff();
        
        void updateColors();

    private:
        sf::RenderWindow *windowPtr = nullptr;
        PCApplicationState *appStateSPtr = nullptr;
        PCGraphDimension *dimensionPtr = nullptr;
        std::shared_ptr<PAIFontLoader> fontLoaderSPtr;

        sf::Color startNodeGradient;
        sf::Color blockedNodeGradient;
        Gradients gradients;

        DrawableNode drawableNode;
        DrawablePath drawablePath;
    };
}

#endif /* EE121C46_77A1_42C0_82FD_AA5B2F176C40 */
