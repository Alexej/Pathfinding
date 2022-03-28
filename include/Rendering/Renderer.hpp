#ifndef EE121C46_77A1_42C0_82FD_AA5B2F176C40
#define EE121C46_77A1_42C0_82FD_AA5B2F176C40

#include <SFML/Graphics/RenderWindow.hpp>
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
namespace sf { class RenderWindow; }

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

    class DrawablePath;
    class Renderer final : public Pathfinding::Abstract::IRenderer
    {
    private:
        using PDNode = Pathfinding::Datastructures::Node;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PCGraphDimension = Pathfinding::Core::GraphDimension;
        using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        using PAIFontLoader = Pathfinding::Abstract::IFontLoader;
        using SFRenderWindow = sf::RenderWindow;
    public:
        Renderer() = default;
        
        Renderer(PCApplicationState *appStateSPtr, std::shared_ptr<PAIFontLoader> fontLoaderSPtr);
        
        void render(sf::RenderWindow & window, const std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr) override;
        
        void render(SFRenderWindow & window, const DrawablePath & path) override;
                
        void reset() override;
        
        void resize() override;
        

    private:
        void init();
                
        void updateColorDiff();
        
        void updateColors();

    private:
        PCApplicationState *appStateSPtr = nullptr;
        PCGraphDimension *dimensionPtr = nullptr;
        std::shared_ptr<PAIFontLoader> fontLoaderSPtr;

        sf::Color startNodeGradient;
        sf::Color blockedNodeGradient;
        Gradients gradients;

        DrawableNode drawableNode;
        DrawablePath drawablePath;

        int32_t currentNodeSideLength = 10;
        const int32_t baseNodeSideLength = 10;
    };
}

#endif /* EE121C46_77A1_42C0_82FD_AA5B2F176C40 */
