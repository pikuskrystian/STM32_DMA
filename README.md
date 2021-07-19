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
for (i = 0; i < BUFFER_SIZE;i++)
    dst_buffer[i] = src_buffer[i];
```

Ponieważ mikrokontrolery mają relatywnie mało pamięci wykorzystywanie DMA jest tutaj trochę na wyrost, jednak spróbujmy porównać czasy wykonywania powyższej pętli oraz kopiowania przy użyciu DMA. Dzięki temu poznamy jak mechanizm ten sprawdza się w praktyce.

Na początek zadeklarujmy 2 bufory – źródłowy i docelowy:

```
#define BUFFER_SIZE 32
 
uint8_t src_buffer[BUFFER_SIZE];
uint8_t dst_buffer[BUFFER_SIZE];

```

Pozostaje przygotować kanał DMA do pracy. Jak zwykle pierwszym krokiem jest uruchomienie zegara modułu peryferyjnego:
```
__HAL_RCC_DMA1_CLK_ENABLE();

```

Następnie deklarujemy zmienną z konfiguracją, ustawiamy pola i inicjalizujemy moduł:

```
DMA_HandleTypeDef dma;
 
 dma.Instance = DMA1_Channel1;
 dma.Init.Direction = DMA_MEMORY_TO_MEMORY;
 dma.Init.PeriphInc = DMA_PINC_ENABLE;
 dma.Init.MemInc = DMA_MINC_ENABLE;
 dma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
 dma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
 dma.Init.Mode = DMA_NORMAL;
 dma.Init.Priority = DMA_PRIORITY_HIGH;
 HAL_DMA_Init(&dma);
 ```
