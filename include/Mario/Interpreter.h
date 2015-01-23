#ifndef MARIO_INTERPRETER_H
#define MARIO_INTERPRETER_H

#include <vector>
#include <string.h>
#include <string>
#include "Helper.h"
#include "morfeusz.h"

namespace Mario {

class Interpreter
{
    public:
        static Interpreter & getInstance();
    protected:
    private:
        Interpreter();
    public:
        std::vector<std::string> morfeusz(std::string in);
};

} // namespace Mario

#endif // MARIO_INTERPRETER_H
