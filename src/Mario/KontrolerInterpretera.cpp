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

std::string KontrolerInterpretera::rob()
{
    std::vector<std::string> vect = interpreter.morfeusz("idź do domu");
    for (std::string x : vect)
    {
        if (x == "iść") return "super!";
    }
    return "błąd";
}

} // namespace Mario

