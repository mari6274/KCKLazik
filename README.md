Łazik Marsjański
=====================

**Skład grupy**
* Mariusz Mączkowski
* Sławomir Golijasz
* Paweł Pisarek

**Krótki opis projektu:** Łazik marsjański bada Marsa, przemieszcza się po powierzchni Marsa. Wykonuje analizy obiektów, gromadzi dane oraz fotografuje teren.
Z łazikiem komunikujemy się za pomocą komend wydawanych za pomocą klawiatury skonstruowanych w zdania. Polecenia można łączyć. Łazik może przekazać informacje o tym, że nie może wykonać jakiejś czynności. Może także podać powód. Dopytuje co zrobić w zaistniałej sytuacji. 

**Wykorzystywane technologie**
* C++
* SFML 2.1 - Biblioteka multimedialna (głównie do prezentacji grafiki)
http://www.sfml-dev.org
* AIML (???)

**Polecenia:**
* znajdź trasę do \<koordynaty\> i idź
* idź po prostej do \<koordynaty\>/\<miejsca\>
* przesuń się \<o ile\>
* opisz otoczenie (wypisanie okolicznych obiektów)
* analizuj próbkę \<nazwa pobranego obiektu\>
* sfotografuj
* obróć się w\<kierunek\>
* przeslij \<dane obiektu\>
* podaj swoje koordynaty
* prezentuj zgromadzone dane
* zbliż się do \<obiekt\>

**Przykładowe polecenie łączone:**
* idź do \<koordynaty\>/\<miejsca\> i opisz otoczenie (wypisanie okolicznych obiektów)
* wykonaj analize \<nazwa pobranego obiektu\> i przeslij \<dane obiektu\>
* przesuń się \<o ile\> i obróć się w\<kierunek\>, a następnie idź do \<koordynaty\>/\<miejsca\> oraz sfotografuj okoliczne obiekty

**Przykład dialogu z agentem**
>
\>\>\> Przesuń się o 100 w lewo  
Po drodze napotkano przeszkodę: skała. Wykonać analizę?  
\>\>\> Tak  
Skała wulkaniczna, wielkość: 30x20, temperatura : -10  
Wyszukać dalszą trasę automatycznie?  
\>\>\> Nie  
\>\>\> Podaj współrzędne  
x = 1578 y = 2421  
\>\>\> znajdź trasę do (200, 120) i idź  
Cel osiągnięty
