#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <vector>

#include "ApplicationState.hpp"
#include "ALatticeGraphWrapper.hpp"
#include "ILatticeGraph.hpp"
#include "IDStarLite.hpp"

#include "LatticeGraph.hpp"
#include "LatticeGraphWrapper.hpp"
#include "DStarLite.hpp"

#include "DefaultCostFunction.hpp"
#include "DiagonalHeuristic.hpp"

#include "RootPath.hpp"
#include "PathLangParser.hpp"

using namespace Pathfinding::Abstract;
using namespace Pathfinding::Algorithms;
using namespace Pathfinding::Datastructures;
using namespace Pathfinding::Helpers;
using namespace Pathfinding::Core;
using namespace Pathfinding::Helpers;
using namespace Pathfinding::Test;

class DStarLiteTester
{
    public:
        DStarLiteTester()
        {
            std::unique_ptr<ILatticeGraph> latticeGraph = std::make_unique<LatticeGraph>(heightStart,widthStart);
            latGraphWrapSPtr = std::make_shared<LatticeGraphWrapper>(std::move(latticeGraph));
            dStarLiteUPtr = std::make_unique<DStarLite>(latGraphWrapSPtr);

            dStarLiteUPtr->addDoneCallBack(std::bind(&DStarLiteTester::pathFound, this));
            dStarLiteUPtr->addNoPathCallBack(std::bind(&DStarLiteTester::noPath, this));

            int32_t diagonalCost = static_cast<int32_t>(std::sqrt(2) * 10);
            int32_t straightCost = 10 * 1;

            dStarLiteUPtr->setHeuristic(std::make_unique<DiagonalHeuristic>(diagonalCost, straightCost));
            dStarLiteUPtr->setCostFunction(std::make_unique<DefaultCostFunction>(diagonalCost, straightCost));
        }

        State getState() const
        {
            return state;    
        }

        std::shared_ptr<ALatticeGraphWrapper> getLatGraphWrapperSPtr()
        {
            return latGraphWrapSPtr;
        }

        bool done() const
        {
            return state != State::NO_PATH || state != State::DONE;
        }

        void reset(int32_t height, int32_t width)
        {
            dStarLiteUPtr->reset();
            latGraphWrapSPtr->resize(height,width);
        }

        void initialRun()
        {
            dStarLiteUPtr->initialRun();
        }

        void initialize()
        {
            dStarLiteUPtr->initialize();
        }

        void changedNode(Node * node)
        {
            dStarLiteUPtr->addChangedNode(node);
        }

        void step()
        {
            dStarLiteUPtr->moveStart();
        }

    private:
        void pathFound()
        {
            state = State::DONE;
        }

        void noPath()
        {
            state = State::NO_PATH;
        }

    private:
        int32_t heightStart = 5;
        int32_t widthStart = 5;
        std::shared_ptr<ALatticeGraphWrapper> latGraphWrapSPtr = nullptr;
        std::unique_ptr<IDStarLite> dStarLiteUPtr = nullptr;
        State state = State::READY;
};


TEST_CASE( "Testing scenarios" ) {
    DStarLiteTester mockObject;
    try
    {
        std::string pathToScenarios = getRootPath() + "\\test\\scenarios.pathlang";
        for(const auto & scenario : PathLangParser(pathToScenarios))
        {
            mockObject.reset(scenario.size.height, scenario.size.width); 
            mockObject.getLatGraphWrapperSPtr()->setGoal(scenario.goal);
            mockObject.getLatGraphWrapperSPtr()->setStart(scenario.start);
            mockObject.initialize();
            mockObject.initialRun();
            for(const auto & command : scenario.commands)
            {
                auto start = mockObject.getLatGraphWrapperSPtr()->startNode();
                switch(command.first)
                {
                    case CommandsKeyWords::BLOCK:
                        {
                        auto node = mockObject.getLatGraphWrapperSPtr()->node(command.second);
                        node->state = NodeState::Blocked;
                        mockObject.changedNode(mockObject.getLatGraphWrapperSPtr()->node(command.second));
                        }
                        break;
                    case CommandsKeyWords::ERASE:
                        {
                        auto node = mockObject.getLatGraphWrapperSPtr()->node(command.second);
                        node->state = NodeState::Free;
                        mockObject.changedNode(mockObject.getLatGraphWrapperSPtr()->node(command.second));
                        }
                        break;
                    case CommandsKeyWords::STEP:
                        mockObject.step();
                        REQUIRE(mockObject.getLatGraphWrapperSPtr()->startNode()->location == command.second);
                        break;
                }
            }
            REQUIRE(mockObject.getState() == scenario.result);
        }
    }
    catch(std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
}
