#include "AlgorithmStepSpeed.hpp"

namespace Pathfinding::Core
{
    AlgorithmStepSpeed::AlgorithmStepSpeed(std::initializer_list<int32_t> list)
    : stepSpeedVecInt(list)
    {
        for(auto stepSpeed : stepSpeedVecInt)
        {
            stepSpeedVecString.push_back(std::to_string(stepSpeed));
        }
        currentStepSpeedIndex = 0;
    }

    AlgorithmStepSpeed::AlgorithmStepSpeed()
    : AlgorithmStepSpeed({1000})
    {}
    
    
    const std::vector<std::string> & AlgorithmStepSpeed::getStepSpeedVecString() const
    {
        return stepSpeedVecString;
    }
    
    int32_t AlgorithmStepSpeed::getCurrentStepSpeedIndex() const
    {
        return currentStepSpeedIndex;
    }

    int32_t AlgorithmStepSpeed::getCurrentStepSpeed() const
    {
        return stepSpeedVecInt[currentStepSpeedIndex];
    }
    
    void AlgorithmStepSpeed::setCurrentAlgorithmStepSpeedIndex(int32_t index)
    {
        currentStepSpeedIndex = index;
    }
}