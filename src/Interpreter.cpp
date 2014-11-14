#include "Interpreter.h"
#include<iostream>
Interpreter::Interpreter()
{

}

Interpreter::~Interpreter()
{
    //dtor
}

void Interpreter::imterpretuj()
{
    InterpMorf *nazwa;
    nazwa=morfeusz_analyse("Mam tak samo jak ty");
    std::cout<<nazwa->forma<<"  "<<nazwa->haslo;
}
