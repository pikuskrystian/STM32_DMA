# STM32_DMA
Direct Memory Access

Wyobraźmy sobie okienko pocztowe z długą kolejką klientów. Urzędnik obsługuje po kolei każdego klienta. Jednak między jednym, a drugim musi udać się do innego pomieszczenia i przenieść paczkę z samochodu na regał. Dopiero wtedy może wrócić do biurka i zająć się sprawami innej osoby. Rozwiązania działa, ale jest powolne, bo tracimy czas wykonując zbędną pracę.


![alt text](https://cdn.forbot.pl/blog/wp-content/uploads/2015/11/animacjaDMA_bezDMA.gif)


Natomiast w wersji z DMA moglibyśmy zatrudnić drugiego pracownika, który będzie działał w tle (innym pomieszczeniu). To on będzie za nas przenosił paczki. Dzięki temu pracownik przy okienku zyskuje czas, może przeznaczyć go na coś innego - przykładowo na szybszą obsługę reszty osób. Chociaż akurat w naszym, analogiczym przykładzie urzędnik stwierdził, że zaoszczędzony czas przeznaczy na krótką drzemkę.


![alt text](https://cdn.forbot.pl/blog/wp-content/uploads/2015/11/animacjaDMA_zDMA.gif)


-----------------------------------------------------------------------------------------------------------------------------------------------------------

Na początek zapoznajmy się z nieco prostszą funkcją DMA jaką jest kopiowanie bloków pamięci. W wielu programach konieczne jest czasami kopiowanie dużych bloków danych, np. buforów ekranu, czy odebranych informacji.

Możemy do tego celu wykorzystać funkcję memcpy() lub napisać prostą pętlę:


```
bajojajo
```
