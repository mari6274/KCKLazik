Łazik Marsjański
=====================

**Skład grupy**
* Mariusz Mączkowski
* Sławomir Golijasz
* Paweł Pisarek

**Krótki opis projektu:** Łazik marsjański bada Marsa, przemieszcza się po powierzchni Marsa. Wykonuje polecenia komunikacyjne, operacyjne i służące do przemieszczania. Z łazikiem komunikujemy się za pomocą komend wydawanych za pomocą klawiatury skonstruowanych w zdania. Polecenia można łączyć. Łazik może przekazać informacje o tym, że nie może wykonać jakiejś czynności.


**Wykorzystywane technologie**
* C++
* SFML 2.1 - Biblioteka multimedialna (głównie do prezentacji grafiki)
http://www.sfml-dev.org
* AIML -chatbot
* Morfeusz - Narzędzie do analizy morfologicznej
* ESpeak

**Algorytmy**
* A* (AStar)

**Przykład dialogu z agentem:**

    >>> Przesuń się o 100 w lewo
    Nie można przejść gdyż napotkano obiekt: dziura
    >>> Gdzie jesteś
    Aktualna pozycja to: 24 20
    >>> znajdź trasę do 200 120 i kop w lewo
    Podana pozycja jest poza obszarem eksploracji
    //kopie dziure po swojej lewej
    >>> rozłącz
    //wyłancza program
