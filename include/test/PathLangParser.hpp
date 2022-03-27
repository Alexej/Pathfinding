#ifndef F233EE77_7F12_4D3C_8E55_45F0BCF188B2
#define F233EE77_7F12_4D3C_8E55_45F0BCF188B2

#include <string>
#include <vector>
#include <fstream>
#include <regex>

#include "Scenario.hpp"
#include "Vec2.hpp"

namespace Pathfinding::Test
{
    class PathLangParser
    {
        private:
            using PDVec2i = Pathfinding::Datastructures::Vec2i;
        public:
            explicit PathLangParser(std::string pathToScenarios);
            
            auto begin() const { return scenarios.cbegin(); }
            
            auto end() const { return scenarios.cend(); }
            
        private:
            void parse();
            
            void readLines();
            
            void parseLines();
            
            void parseFooter(Scenario & scenario, const std::vector<std::string> & sectionStrings);
            
            void parseHeader(Scenario & scenario, const std::vector<std::string> & sectionStrings);
            
            void parseCommands(Scenario & scenario, const std::vector<std::string> & sectionStrings);
        
        private:
            PDVec2i parseStartLocation(const std::string & line) const;

            PDVec2i parseGoalLocation(const std::string & line) const;

            std::string parseScenarioName(const std::string & line) const;

            PDVec2i parseSize(const std::string & line) const;

            bool codeLine(const std::string & line) const;
            
        public:
            std::vector<Scenario> scenarios;
            std::ifstream input;
            std::vector<std::vector<std::string>> sectionsAsStrings;
            const std::regex commentRegex{"^( *#.*)"};
            const std::regex scenarioRegex{"^(SCENARIO) ([a-zA-Z0-9]+) +;$"};
            const std::regex sizeRegex{"^(SIZE) +(VEC2\\(([0-9]):([0-9])\\)) +;$"};
            const std::regex resultRegex{"^(RESULT) +(FOUND_PATH|NO_PATH) +;$"};
            const std::regex commandRegex{"^(STEP|BLOCK|CLEAR) +(VEC2\\(([0-9]):([0-9])\\)) +;$"};
            const std::regex startRegex{"^(START) +(VEC2\\(([0-9]):([0-9])\\)) +;$"};
            const std::regex goalRegex{"^(GOAL) +(VEC2\\(([0-9]):([0-9])\\)) +;$"};
            const std::regex emptyLineRegex{" *"};
    };
}

#endif /* F233EE77_7F12_4D3C_8E55_45F0BCF188B2 */
