#include "Mario/KontrolerInterpretera.h"
#include "morfeusz.h"
namespace Mario {

KontrolerInterpretera::KontrolerInterpretera()
:
    interpreter(Interpreter::getInstance())
{

}

KontrolerInterpretera & KontrolerInterpretera::getInstance()
{
    static KontrolerInterpretera instance;
    return instance;
}

std::string KontrolerInterpretera::interpretuj(std::string in)
{
    std::string odp = interpreter.interpretuj(in);
    return odp;
}

} // namespace Mario

