#ifndef AIML_H
#define AIML_H

#include<map>
#include <sstream>
#include <iostream>
#include<fstream>
#include <vector>
#define DEBUG false




using namespace std;

struct category
{
    string pattern1;
    string template1;

};

class destination
{
public:
    int x,y;
    string nazwa;
    bool error=false;

    const string toString()
    {

        ostringstream ss,ssq;
        ss << x;
        string xs = ss.str();

        ssq << y;
        string ys = ssq.str();

        if(nazwa=="nie znaleziono objektu"||nazwa=="dane nie moga byc uznane za poprawne"||nazwa=="dane sa nie poprawne ale nie wiem dla czego moze za duzo?"||nazwa=="za malo wspozednych")
            return nazwa;

        else
            return nazwa+" "+xs+" "+ys;
    }

};

class kierunek
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
        string znajdowanie(string a);
        string weToZrob(string komedna);
        vector<string> explode(const string& str, const char delimiter);
        int string_to_int(string a);
    protected:
    private:
        inline std::string trim(std::string& str);
        string JakiPoziom(string tekst);
        string PomiedzyTagami(string tekst,string poziom);
        string pobierzxml();
        vector<category> wstawxml();
        string implode(vector<string> & elements, char delimiter);
        vector < string > CzesciowaKomenda(vector < string > dana);
        string CzesciowaKomendajaka(vector < string > dana);
        bool czyliczba(int i);
        void wypisz(vector < string > tablica);
        bool in_array(const string &needle, const vector< string > &haystack);


};

#endif // AIML_H
