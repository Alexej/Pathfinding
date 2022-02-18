#ifndef C876092C_11D4_473D_9649_488CA26108A9
#define C876092C_11D4_473D_9649_488CA26108A9

#include <initializer_list>
#include <cstdint>
#include <string>
#include <vector>

namespace Pathfinding::Core
{
    class AlgorithmStepSpeed
    {
    public:
        AlgorithmStepSpeed(std::initializer_list<int32_t> list);
        AlgorithmStepSpeed();
        const std::vector<std::string> &getStepSpeedVecString() const;
        int32_t getCurrentStepSpeedIndex() const;
        int32_t getCurrentStepSpeed() const;
        void setCurrentAlgorithmStepSpeedIndex(int32_t index);

    private:
        std::vector<std::string> stepSpeedVecString;
        std::vector<int32_t> stepSpeedVecInt;
        int32_t currentStepSpeedIndex;
    };
}

#endif /* C876092C_11D4_473D_9649_488CA26108A9 */
