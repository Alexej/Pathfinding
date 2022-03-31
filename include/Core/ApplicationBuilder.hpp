#ifndef FB23F09D_BB6A_4446_8683_4BBE6E4646E5
#define FB23F09D_BB6A_4446_8683_4BBE6E4646E5

#include <memory>
#include <initializer_list>
#include <memory>

#include "GraphDimension.hpp"

namespace Pathfinding::Core {class Application;}
namespace Pathfinding::Abstract {class IApplication;}
namespace Pathfinding::Abstract {class IFontLoader;}

namespace Pathfinding::Core
{
    class FontLoader;
    class ApplicationBuilder
    {
    public:
        ApplicationBuilder();

        void setDimension(std::initializer_list<int32_t> numberOfNodesInRow);

        void setCosts(int32_t diagonalCost, int32_t straightCost);

        void setFontLoader(std::shared_ptr<Pathfinding::Abstract::IFontLoader> fontLoaderSPtr);

        std::unique_ptr<Pathfinding::Abstract::IApplication> make();

    private:
        void instantiateObjects();

        void initializeObjects();

        void createEventManagerBindings();

        void setMenuCallBacks();

        void initDStarLite();

        void initAStar();

        void lastPreparations();

    private:
        std::unique_ptr<Pathfinding::Core::Application> applicationUPtr = nullptr;
        std::shared_ptr<Pathfinding::Abstract::IFontLoader> fontLoaderSPtr;
        Pathfinding::Core::GraphDimension dimension;
        int32_t diagonalCost;
        int32_t straightCost;
    };
}

#endif /* FB23F09D_BB6A_4446_8683_4BBE6E4646E5 */
