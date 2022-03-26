#ifndef F1BFB729_3722_4367_B4BB_1866BE040231
#define F1BFB729_3722_4367_B4BB_1866BE040231

#include <functional>

namespace Pathfinding::Abstract
{
    class IMenu
    {
        private:
            using fPtrVI = std::function<void(int32_t)>;
            using fPtrVV = std::function<void(void)>;
        public: 
            virtual void show() = 0;
            
            virtual void addNumberOfNodesChangedCallBack(fPtrVI callBack) = 0;
            
            virtual void addStepCallBack(fPtrVV callBack) = 0;
            
            virtual void addStartCallBack(fPtrVV callBack) = 0;
            
            virtual void addResetCallBack(fPtrVV callBack) = 0;
            
            virtual void addRandomGraphCallBack(fPtrVV callBack) = 0;

            virtual void addMazeGraphCallBack(fPtrVV callBack) = 0;

            virtual void addMouseWheelEventChangedCallBack(fPtrVI callBack) = 0;
            
            virtual bool initialized() const = 0;
            
            virtual void showGraph(std::vector<int32_t> values, std::string name) = 0;
            
            virtual ~IMenu() = default;
            
    };
}

#endif /* F1BFB729_3722_4367_B4BB_1866BE040231 */
