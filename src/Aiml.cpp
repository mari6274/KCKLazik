#include "Aiml.h"

Aiml::Aiml(Console* c, TaskManager* t)
{
    this->console = c;
    this->taskManager = t;
}

inline std::string Aiml::trim(std::string& str)
{
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
    return str;
}

vector<string> Aiml::explode(const string& str, const char delimiter)
{
    vector<string> elements;
    stringstream stream(str);
    string item;
    while (getline(stream, item, delimiter))
        if (item!="")
            elements.push_back(item);

    return elements;
}


string Aiml::JakiPoziom(string tekst)
{
    string    poziom="";
    if (tekst[0]=='<')
    {
        tekst.erase(0,1);
        while (tekst[0]!='>')
        {
            poziom=poziom+tekst[0];
            tekst.erase(0,1);
        }
    }
    return poziom;
}


string Aiml::PomiedzyTagami(string tekst,string poziom)
{
    string slowo="";
    if(tekst.find("<"+poziom+">")==0 )
    {
        tekst.erase(0,poziom.size()+2);
        for(int i=0; i<tekst.find(poziom)-2; i++)
        {
            slowo=slowo+tekst[i];
        }
        tekst.erase(tekst.find(poziom)-2,poziom.size()+3);
    }
    return slowo;


}
string Aiml::pobierzxml()
{
    fstream plik;
    string tekst="";


    plik.open( "aiml2.xml", ios::in );
    if( plik.good() )
    {
        string napis;
        getline( plik, napis );

        while( !plik.eof() )
        {
            getline( plik, napis );
            if(DEBUG)       cout<<napis<<endl;
            trim(napis);

            tekst=tekst+napis;

        }

        plik.close();
    }
    else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    // cout<<JakiPoziom(tekst);


    return tekst;
}




vector<category> Aiml::wstawxml()
{

    string tekst=pobierzxml();
    //  cout<<tekst<<endl;
    vector<category> kategorie;
    category kategoria;

    string kat="";
    int dlugosc=0;
    for(int i=0; i<100; i++)
    {
        if(tekst.size()==0)break;

        // cout<<PomiedzyTagami(tekst,"category")<<endl<<endl;

        if(JakiPoziom(tekst)=="aiml")
            tekst=PomiedzyTagami(tekst,JakiPoziom(tekst));
        if (JakiPoziom(tekst)=="category")
        {
            kat=tekst;
            tekst=PomiedzyTagami(tekst,JakiPoziom(tekst));
//           cout<<endl<<tekst<<endl;
            dlugosc=(tekst.size()+JakiPoziom("category").size()*2+5+16);//niewiem czemu +16 ale musi tak byc

        }

        if( JakiPoziom(tekst)=="pattern")
        {

            kategoria.pattern1=PomiedzyTagami(tekst,"pattern");
            tekst.erase(0,PomiedzyTagami(tekst,"pattern").size()+JakiPoziom(tekst).size()*2+5); //usuwa caly tag pattern



        }
        if( JakiPoziom(tekst)=="template")
        {

            kategoria.template1=PomiedzyTagami(tekst,"template");
            tekst.erase(0,PomiedzyTagami(tekst,"template").size()+JakiPoziom(tekst).size()*2+5);

//cout<<endl<<"usuwam"<<dlugosc<<kat;
            kat.erase(0,dlugosc);


            //          cout<<endl<<endl<<"usunienty"<<kat<<endl<<endl;
            tekst=kat;
            // kategorie.push_back(kategoria);
        }
        kategorie.push_back(kategoria);
    }

    return kategorie;
}
string Aiml::znajdowanie(string a)
{
    // cout<<" \n\n                     "<<a<<"\n\n\n";
    vector<category> kategorie;

    map<string, string> znajdz;
    kategorie=wstawxml();

    for(int i=0; i<kategorie.size(); i++)
    {
        if(DEBUG)   cout<<kategorie.at(i).pattern1<<endl;
        if(DEBUG)   cout<<kategorie.at(i).template1<<endl<<endl;
        if(JakiPoziom(kategorie.at(i).template1)=="srai")  znajdz[kategorie.at(i).pattern1] =znajdz[ PomiedzyTagami(kategorie.at(i).template1,"srai")];
        else
            znajdz[kategorie.at(i).pattern1]=kategorie.at(i).template1;
    }

    //cout<<'                      '<<a<<'\n';
    // cout<<'                      '<<kategorie.at(1).pattern1;

    if(znajdz[a]=="") return ("nie rozpoznano komendy");
    else return znajdz[a];
}




string Aiml::implode(vector<string> & elements, char delimiter)
{
    string full;
    for (vector<string>::iterator it = elements.begin(); it != elements.end(); ++it)
    {
        full += (*it);
        if (it != elements.end()-1)
            full += delimiter;

    }
    return full;
}



vector < string > Aiml::CzesciowaKomenda(vector < string > dana)
{
    //funkcja sprawdza czy istnieje wogóle podana komenda ewentualnie dzieli na dwie czesci
    //i zwraca drug¹ czeœ


    string komenda;

    komenda="";
    //  cout<<" komenda nie pelna  sprwadze czy czesciowo dobra \n";
    for( size_t i = 0; i < dana.size(); i++ )
    {

        komenda=komenda+" "+trim(dana[i]);
        if("nie rozpoznano komendy"==znajdowanie(trim(komenda)) )
        {
            //        cout<<i<<" "<<komenda<<" "<<znajdowanie(trim(komenda))<<" \n";
        }
        else
        {
            //      cout<<"rozpoznano komende \n";
            //    cout<<znajdowanie(trim(komenda));

            dana.assign(dana.begin()+i+1,dana.end()); ///to usuwa wszystkie elemnty przed znalezion¹ komend¹
        }
    }
    return dana;
}

string Aiml::CzesciowaKomendajaka(vector < string > dana)
{
    //funkcja sprawdza czy istnieje wogóle podana komenda i zwraca odpowiedz nie komende !!!
    string komenda;

    komenda="";
    // cout<<" komenda nie pelna  sprwadze czy czesciowo dobra \n";
    for( size_t i = 0; i < dana.size(); i++ )
    {

        komenda=komenda+" "+trim(dana[i]);
        if("nie rozpoznano komendy"==znajdowanie(trim(komenda)) )
        {
            //    cout<<i<<" "<<command<<" "<<znajdowanie(trim(command))<<" \n";
        }
        else
        {
            //   cout<<"rozpoznano komende \n";
            //   cout<<znajdowanie(trim(komenda));
            return znajdowanie(trim(komenda));

//            dana.assign(dana.begin()+i+1,dana.end()); ///to usuwa wszystkie elemnty przed znalezion¹ komend¹
        }
    }
    return "czesciowa komneda jaka?";
}






int Aiml::string_to_int(string a)
{
    int i;
    istringstream iss(a);///zamienia string na liczbe ale jezeli jest string to zwraca zero
    iss >> i;

    return i;

}

bool Aiml::czyliczba(int i)
{
    if (i!=0)
        return true; //próba naprawy ulomnej funkcji string to int
}





void Aiml::wypisz(vector < string > tablica)
{
    cout<<"\n";
    for( size_t i = 0; i < tablica.size(); i++ )
        cout<<tablica[i]<<'['<<i<<']'<<',';
    cout<<"\n";

}


string Aiml::weToZrob(string komedna)
{
    //funkcja ogarnia caly ten smiatnik


vector < string > dane;
string command=komedna,odpowiedz="";

destination cel;
    kierunek k;
    map<string, destination> objekty;
    vector < string > TablicaZnazwamiObjektow;
    vector <string> kierunkiSwiata;
    kierunkiSwiata.push_back("polnoc");
    kierunkiSwiata.push_back("poludnie");
    kierunkiSwiata.push_back("wschod");
    kierunkiSwiata.push_back("zachod");
    kierunkiSwiata.push_back("prawo");
    kierunkiSwiata.push_back("lewo");
    kierunkiSwiata.push_back("dol");
    kierunkiSwiata.push_back("gora");


    destination objektyJakoCele;
    objektyJakoCele.nazwa="wulkan";
    objektyJakoCele.x=3;
    objektyJakoCele.y=7;
    objekty[objektyJakoCele.nazwa]=objektyJakoCele;
    TablicaZnazwamiObjektow.push_back(objektyJakoCele.nazwa);

    objektyJakoCele.nazwa="jezioro";
    objektyJakoCele.x=8;
    objektyJakoCele.y=2;
    objekty[objektyJakoCele.nazwa]=objektyJakoCele;
    TablicaZnazwamiObjektow.push_back(objektyJakoCele.nazwa);

    objektyJakoCele.nazwa="UAM";
    objektyJakoCele.x=100;
    objektyJakoCele.y=300;
    objekty[objektyJakoCele.nazwa]=objektyJakoCele;
    TablicaZnazwamiObjektow.push_back(objektyJakoCele.nazwa);

     dane=explode(command,' ');
    command=implode(dane,' ');


    if("nie rozpoznano komendy"==znajdowanie(command) )
    {



        if(dane.size()==CzesciowaKomenda(dane).size() ) //sprawdza czy jest możliwe chociaż cześciowo znaleźc odpowiadajaca komende
        {
            cout<<"nie ma na koncu dancyh sprawdze czy sa jakies liczby w srodku zdania";

            vector<string> dane2;
            for( size_t i = 0; i < dane.size(); i++ )
            {
                if(czyliczba(string_to_int(dane.at(i)))|| (in_array(dane.at(i), TablicaZnazwamiObjektow)) ) //sprawdza czy w komedzie podane slowo jest liczba lub objektem ztablicy objektow
                    dane2.push_back(dane.at(i));
                else
                {

                    odpowiedz=odpowiedz+ " "+dane.at(i); //sklada czesciowa komedze z wyrazow ktore nie sa ani liczba ani komenda
                }
            }
            odpowiedz=znajdowanie(trim(odpowiedz)); //wstawia znaki % lub # w miejsca w ktorych zabrano liczby i objekty
            dane=dane2;
        }
        else
        {
            odpowiedz=CzesciowaKomendajaka(dane); //znaleziono komende ktora odpowiada plikowi
            dane=CzesciowaKomenda(dane); //wektor zostal skrocony do wartosci ktora nie zostala jeszcze przetworzona

        }


        if(odpowiedz.find('%') != string::npos) //tutaj powinno byc '#'==odpowiedz.at(odpowiedz.find('#'))&&'#'==odpowiedz.at(odpowiedz.find('#')+1) ale jest out of range
        {

            if (dane.size()==2)
            {
                //dwie wspórzedne

                if(czyliczba(string_to_int(dane[0]))||czyliczba(string_to_int(dane[1])))
                {
                    cel.x=string_to_int(dane[0]);
                    cel.y=string_to_int(dane[1]);
                }
                else
                {
                    cel.nazwa="dane nie moga byc uznane za poprawne";
                    cel.error=true;
                    //cout<<"dane nie moga byc uznane za poprawne";
                }

            }
            else
            {
                if (dane.size()==1)
                {
                    //jeden objekt


                    // if(objekty[dane[0]]==null) cout<<"nie ma takiego objektu";
                    // else
                    // {

                    if(czyliczba(string_to_int(dane.front())))
                    {
                        cel.nazwa="za malo wspozednych";
                        cel.error=true;
                    }
                    else
                    {
                        cel = objekty[dane.front()];
                        if(cel.x==0 && cel.y==0) //naprawde slabe rozwiazanie
                        {
                            cel.nazwa="nie znaleziono objektu";
                            cel.error=true;
                        }

                    }

                    //  }
                }
                else
                {
                    cel.nazwa="dane sa nie poprawne ale nie wiem dla czego moze za duzo?";
                    cel.error=true;

                }
            }
        }
        else
        {

            if(odpowiedz.find('#') != string::npos)
            {

               // for( size_t i = 0; i < dane.size(); i++ )
                    //        cout<<dane[i]<<'['<<i<<']'<<',';
                    //    cout<<"\n";
                    if (dane.size()!=4)
                    {
                        k.error="podano zbyt dużo argumentow ale byc może gdzies dojedziemy";
                    }

                wypisz(dane);


                if( dane[0]=="o" )
                    if( czyliczba(string_to_int(dane[1])))
                    {
                        k.odleglosc=string_to_int(dane[1]);
                        k.sprojnik=dane[2];
                        if(in_array(dane[3],kierunkiSwiata))
                            k.kierunek=dane[3];
                        else
                        {
                            k.error="Nie ma takiego kierunku swiata";
                        }
                    }
                    else
                    {
                        k.error="podana wartosc nie jest liczba";
                    }


                if( dane[2]=="o" )
                {
                    if( czyliczba(string_to_int(dane[3])))
                    {
                        k.odleglosc=string_to_int(dane[3]);
                        k.sprojnik=dane[0];
                        if(in_array(dane[1],kierunkiSwiata))
                            k.kierunek=dane[1];
                        else
                        {
                            k.error="nie ma takiego kierunku swiata";
                        }
                    }
                    else
                    {
                        k.error="podana wartosc nie jest liczba";
                    }
                }

            }
            else
            {
                // kolejny symbol
            }
        }

    }
    else
    {
        //  cout<<" \n rozpoznano komende ";
        //     cout<<znajdowanie(command);
    }

 //   printf( "\n\nKoniec\n" );

//  for( size_t i = 0; i < dane.size(); i++ )
//         cout<<dane[i]<<'['<<i<<']'<<',';
//   cout<<"\n";

//   cout<<(odpowiedz.find("%") != string::npos);
//   cout<<(odpowiedz.find("#") != string::npos); //zwraca 0 gdy istnieje

    if(odpowiedz.find('#') != string::npos)
    {

        if ( k.error!="")

        {
            cout<<k.toString();
            return k.toString();
        }
        else
        {
            odpowiedz.erase(odpowiedz.find("#"),odpowiedz.find(odpowiedz)+1);
            cout<< trim(odpowiedz)<<" "<<k.toString();




            if(k.kierunek=="lewo")
                taskManager->move(-k.odleglosc,0);

             if(k.kierunek=="prawo")
                taskManager->move(k.odleglosc,0);

              if(k.kierunek=="gora")
                taskManager->move(0,-k.odleglosc);

             if(k.kierunek=="dol")
                taskManager->move(0,k.odleglosc);



            return trim(odpowiedz)+" "+k.toString();
        }
    }
    else if(odpowiedz.find('%') != string::npos)
    {
        if ( cel.error)
        {
            cout<<cel.toString();
            return cel.toString();
        }
        else
        {


                  odpowiedz.erase(odpowiedz.find("%"),odpowiedz.find(odpowiedz)+1);

             taskManager->goCoordinates(cel.x,cel.y);
            cout<< trim(odpowiedz)<<" "<<cel.toString();


           // return trim(odpowiedz)+" "+cel.toString();

          ostringstream ss,ssq;
        ss << cel.x;
        string xs = ss.str();

        ssq << cel.y;
        string ys = ssq.str();



             return trim(odpowiedz)+" "+cel.toString();
           // return "auto "+xs+" "+ys;  // jeżeli chcesz istnieje potrzeba modyfikacji odkpmentuj powyzsza linnie
        }
    }
    else if(odpowiedz.find('^') != string::npos)
    {
        if(dane.size()==1)
            if (in_array(dane[0],kierunkiSwiata))
            {
                odpowiedz.erase(odpowiedz.find("^"),odpowiedz.find(odpowiedz)+1);
                cout<<trim(odpowiedz)<<" "<<dane[0];
                return trim(odpowiedz)+" "+dane[0];
            }
            else
            {
                cout<<" nie isnieje taki kierunek swiata ";
                return " nie isnieje taki kierunek swiata ";
            }
        else
        {
            cout<<" raczej za duzo argumentow";
            return " raczej za duzo argumentow";
        }

    }
    else if(znajdowanie(command).find('%') != string::npos|| znajdowanie(command).find('#') != string::npos)
    {
        cout<<"komende znaleziono ale nie podano argumentow";
        // cout<<znajdowanie(command)<<"wypisywanie";

        return "komende znaleziono ale nie podano argumentow";
    }
    else
    {
        //  cout<<" \n rozpoznano komende ";
        cout<<znajdowanie(command);
        return znajdowanie(command);
    }
   // printf( "\n\nKoniec\n" );





}


bool Aiml::in_array(const string &needle, const vector< string > &haystack)
{
    int max=haystack.size();

    if (max==0) return false;

    for(int i=0; i<max; i++)
        if (haystack[i]==needle)
            return true;
    return false;
}
