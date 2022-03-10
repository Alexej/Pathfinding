#ifndef AD6126EE_B0B8_41A7_B97D_118F9BD06A92
#define AD6126EE_B0B8_41A7_B97D_118F9BD06A92

#include <exception>


//https://peterforgacs.github.io/2017/06/25/Custom-C-Exceptions-For-Beginners/
namespace Pathfinding::Abstract
{
    class AException : public std::exception
    {
        const char *file;
        int line;
        const char *func;
        const char *info;

    public:
        AException(const char *msg, 
                    const char *file_, 
                    int line_, const char *func_, 
                    const char *info_ = "") 
        : std::exception(msg),
        file(file_),
        line(line_),
        func(func_),
        info(info_)
        {}

        const char *getFile() const { return file; }
        
        int getLine() const { return line; }
        
        const char *getFunc() const { return func; }
        
        const char *getInfo() const { return info; }
        
        virtual ~AException() = default;
    };
}

#endif /* AD6126EE_B0B8_41A7_B97D_118F9BD06A92 */
