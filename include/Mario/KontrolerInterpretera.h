#ifndef MARIO_KONTROLERINTERPRETERA_H
#define MARIO_KONTROLERINTERPRETERA_H

#include "Mario/Interpreter.h"
#include "SFML/System.hpp"
#include "Aiml.h"
#include <vector>
#include "Console.h"
#include "TaskManager.h"
#include "Helper.h"

namespace Mario {

class KontrolerInterpretera
{
    public:
        KontrolerInterpretera(Console * console, TaskManager * tm);
        void interpretuj();
    protected:
    private:
        Interpreter & interpreter;
        Console * console;
        TaskManager * tm;

        void wykonajKomende(std::string komenda);
};

} // namespace Mario

#endif // MARIO_KONTROLERINTERPRETERA_H
