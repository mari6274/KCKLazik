#ifndef AIML_H
#define AIML_H

#include<map>
#include <sstream>
#include <iostream>
#include<fstream>
#include <vector>
#define DEBUG false
#include "Game.h"
#include "TaskManager.h"
#include "Console.h"




using namespace std;

struct Category
{
    string pattern1;
    string template1;

};

class Destination
{
public:
    int x,y;
    string nazwa;
    bool error=false;

    Destination()
    {

    };
    Destination(Object* o)
    {
        this->nazwa = o->getName();
        this->x = o->getPosition().x;
        this->y = o->getPosition().y;
    };

    const string toString()
    {

        ostringstream ss,ssq;
        ss << x;
        string xs = ss.str();

        ssq << y;
        string ys = ssq.str();

        if(nazwa=="nie znaleziono objektu"||nazwa=="dane nie moga byc uznane za poprawne"||nazwa=="dane sa nie poprawne ale nie wiem dla czego moze za duzo?"||nazwa=="za mało współżędnych")
            return nazwa;

        else
            return nazwa+" "+xs+" "+ys;
    }

};

class Kierunek
{
public:
    int odleglosc;
    string sprojnik;
    string kierunek;
    string error="";
    const string toString()
    {
        if(error=="")
        {
            ostringstream ss;
            ss << odleglosc;
            string odlegloscs = ss.str();
            return odlegloscs +" "+sprojnik+" "+kierunek;
        }
        else
        {
            return error;
        }
    }
};

class Aiml
{
    public:
        Aiml(Console * c, TaskManager * t);
        string znajdowanie(string a);
        string weToZrob(string komedna);
        vector<string> explode(const string& str, const char delimiter);
        int string_to_int(string a);

        vector<string> start(string komenda);
    protected:
    private:
        Console * console;
        TaskManager * taskManager;

        inline std::string trim(std::string& str);
        string JakiPoziom(string tekst);
        string PomiedzyTagami(string tekst,string poziom);
        string pobierzxml();
        vector<Category> wstawxml();
        string implode(vector<string> & elements, char delimiter);
        vector < string > CzesciowaKomenda(vector < string > dana);
        string CzesciowaKomendajaka(vector < string > dana);
        bool czyliczba(int i);
        void wypisz(vector < string > tablica);
        bool in_array(const string &needle, const vector< string > &haystack);


};

#endif // AIML_H
