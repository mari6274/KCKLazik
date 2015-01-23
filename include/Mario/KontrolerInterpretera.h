#ifndef MARIO_KONTROLERINTERPRETERA_H
#define MARIO_KONTROLERINTERPRETERA_H

#include "Mario/Interpreter.h"
#include "SFML/System.hpp"
#include "Aiml.h"
#include <vector>

namespace Mario {

class KontrolerInterpretera
{
    public:
        static KontrolerInterpretera & getInstance();
        std::string rob();
    protected:
    private:
        KontrolerInterpretera();
        Interpreter & interpreter;
};

} // namespace Mario

#endif // MARIO_KONTROLERINTERPRETERA_H
