#ifndef F1BFB729_3722_4367_B4BB_1866BE040231
#define F1BFB729_3722_4367_B4BB_1866BE040231

#include <functional>

namespace Pathfinding::Abstract
{
    class IMenu
    {
        public: 
            virtual void show() = 0;
            
            virtual void addNumberOfNodesChangedCallBack(std::function<void(int32_t)> callBack) = 0;
            
            virtual void addStepCallBack(std::function<void(void)> callBack) = 0;
            
            virtual void addStartCallBack(std::function<void(void)> callBack) = 0;
            
            virtual void addResetCallBack(std::function<void(void)> callBack) = 0;
            
            virtual void addRandomGraphCallBack(std::function<void(void)> callBack) = 0;

            virtual void addMazeGraphCallBack(std::function<void(void)> callBack) = 0;

            virtual void addMouseWheelEventChangedCallBack(std::function<void(int32_t)> callBack) = 0;
            
            virtual bool initialized() const = 0;
            
            virtual void showGraph(std::vector<int32_t> values, std::string name) = 0;
            
            virtual ~IMenu() = default;
            
    };
}

#endif /* F1BFB729_3722_4367_B4BB_1866BE040231 */
