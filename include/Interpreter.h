#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "morfeusz.h"
#include "Game.h"
#include "Console.h"

class Interpreter
{
    public:
        Interpreter(TaskManager * tm, Console * console);
    void interpretuj();


        virtual ~Interpreter();
    protected:
    private:
        TaskManager * taskManager;
        Console * console;
};

#endif // INTERPRETER_H
