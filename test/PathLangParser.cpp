#include "PathLangParser.hpp"
#include <exception>
#include <iostream>
#include "Vec2.hpp"
#include "ApplicationState.hpp"


namespace Pathfinding::Test
{
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Core::AlgorithmState;
    namespace
    {
        CommandsKeyWords mapStringToCommandKeyWord(std::string commandString)
        {
            CommandsKeyWords CommandsKeyWordsReturn;
            if(commandString == std::string("BLOCK"))
            {
                CommandsKeyWordsReturn = CommandsKeyWords::BLOCK;
            }
            else if(commandString == std::string("STEP"))
            {
                CommandsKeyWordsReturn = CommandsKeyWords::STEP;
            }
            else
            {
                throw std::exception("Unknown command keyword");
            }
            return CommandsKeyWordsReturn;
        }


        AlgorithmState convertStringToState(std::string stateStr)
        {
            AlgorithmState state;
            if(stateStr == std::string("NO_PATH"))
            {
                state = AlgorithmState::NO_PATH;
            }
            else if(stateStr == std::string("DONE"))
            {
                state = AlgorithmState::FOUND_PATH;
            }
            else
            {
                throw std::exception("State unknown!");
            }
            return state;
        }
    }


    PathLangParser::PathLangParser(std::string pathToScenarios)
    {
        input.open(pathToScenarios);
        if(!input.is_open())
        {
            throw std::exception("Wrong .pathlang path");
        }
        parse();
    }

    void PathLangParser::readLines()
    {
        std::vector<std::string> buffer;

        auto flushBuffer = [&]()
        {
            if(!buffer.empty())
            {
                if(buffer.size() < 5)
                {
                    throw std::exception("wrong scenarion layout!");
                }
                sectionsAsStrings.push_back(buffer);
                buffer.clear();
            }
        };

        for(std::string line; getline(input, line );)
        {
            if(std::regex_match(line, commentRegex) || std::regex_match(line, emptyLineRegex))
            {
                continue;
            }
            if(std::regex_match(line, scenarioRegex))
            {
                flushBuffer();
            }
            buffer.push_back(line);
        }
        flushBuffer();
    }

    void PathLangParser::parseFooter(Scenario & scenario, const std::vector<std::string> & sectionStrings)
    {
        std::smatch baseMatch;
        if(std::regex_match(sectionStrings.back(), baseMatch, resultRegex))
        {
            scenario.result = convertStringToState(baseMatch[2].str());
        }
        else
        {
            throw std::exception("{RESULT [Algorithm State] ;} not found");
        }
    }

    void PathLangParser::parseHeader(Scenario & scenario, const std::vector<std::string> & sectionStrings)
    {
        std::smatch baseMatch;
        if(std::regex_match(sectionStrings[0], baseMatch, scenarioRegex))
        {
            scenario.name = baseMatch[2].str();
        }
        else
        {
            throw std::exception("{SCENRAIO [name] ;} not found");
        }

        if(std::regex_match(sectionStrings[1], baseMatch, sizeRegex))
        {
            scenario.size = Vec2i(std::stoi(baseMatch[3].str()), std::stoi(baseMatch[4].str()));
        }
        else
        {
            throw std::exception("{SIZE VEC2([num]:[num]) ;} not found");
        }

        if(std::regex_match(sectionStrings[2], baseMatch, startRegex))
        {
            scenario.start = Vec2i(std::stoi(baseMatch[3].str()), std::stoi(baseMatch[4].str()));
        }
        else
        {
            throw std::exception("{START VEC2([num]:[num]) ;} not found");
        }

        if(std::regex_match(sectionStrings[3], baseMatch, goalRegex))
        {
            scenario.goal = Vec2i(std::stoi(baseMatch[3].str()), std::stoi(baseMatch[4].str()));
        }
        else
        {
            throw std::exception("{GOAL VEC2([num]:[num]) ;} not found");
        }
    }

    void PathLangParser::parseCommands(Scenario & scenario, const std::vector<std::string> & sectionStrings)
    {
        std::smatch baseMatch;
        for(std::size_t i = 4; i < sectionStrings.size() - 1; ++i)
        {
            if(std::regex_match(sectionStrings[i], baseMatch, commandRegex))
            {
                auto vec2iPos = Vec2i(std::stoi(baseMatch[3].str()), std::stoi(baseMatch[4].str()));
                auto command = mapStringToCommandKeyWord(baseMatch[1].str());
                scenario.commands.push_back({command, vec2iPos});
            }
            else
            {
                throw std::exception("{COMMAND VEC2([num]:[num]) ;} not found");
            }
        }
    }

    void PathLangParser::parseLines()
    {
        for(const auto & sectionStrings : sectionsAsStrings)
        {
            Scenario scenario;
            parseHeader(scenario, sectionStrings);
            parseFooter(scenario, sectionStrings);
            parseCommands(scenario, sectionStrings);
            scenarios.push_back(scenario);
        }
    }

    void PathLangParser::parse()
    {
        readLines();
        parseLines();
    }
}