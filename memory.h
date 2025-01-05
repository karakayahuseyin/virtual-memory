#pragma once //Bu header dosyasının birden fazla kullanılmasını engeller.

#include <stddef.h>
#include "data.h"

typedef struct s_memoryBlock
{
    /* data */
    size_t size;                            //boyut
    d_byte* data;                            //veri
    char address;                        //baslangic adresi
    struct s_memoryBlock* next;             //sonraki blok
} memoryBlock;

typedef struct s_memoryList
{
    /* data */
    memoryBlock* head;          //baslangic
    size_t total_size;          //boyut
} memoryList;

// memoryList* initializeList(void* start_address, size_t total_size);  //Sıfırdan liste olusuturur
memoryBlock* findBlock(memoryList* list, size_t size);        //First in uygulanacak ve ilk gelen bellek bloğu eşleşecek.
void mergeFreeBlocks(memoryList* list);                              //Serbest blokları birlestirir.  
// void printMemoryBlocks(memoryList* list);                            //Memory listesini yazdırır.
