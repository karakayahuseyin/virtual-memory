#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

memoryBlock* findBlock(memoryList* list, size_t size) {
    if (!list || !list->head) {
        printf("Liste bos!\n");
        return NULL;
    }

    memoryBlock* current = list->head;

    while (current != NULL) {
        if (current->data == 0 && current->size >= size) { // Uygun boş blok bulundu
            if (current->size > size) { // Blok bölünebilir
                memoryBlock* new_block = (memoryBlock*)malloc(sizeof(memoryBlock));
                if (!new_block) {
                    printf("Yeni blok oluşturulamadi!\n");
                    return NULL;
                }

                new_block->size = current->size - size;
                new_block->data = 0;
                new_block->address = (char)((unsigned char)current->address + (unsigned int)size);
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            return current;
        }
        current = current->next;
    }

    return NULL; // Uygun blok bulunamadı
}

memoryBlock* createMemoryBlock(memoryBlock* previous, size_t size) {
    if (!previous || previous->size < size) {
        printf("Hata: Önceki blok geçersiz veya yetersiz boyut!\n");
        return NULL;
    }

    // Yeni blok için bellek ayır
    memoryBlock* new_block = (memoryBlock*)malloc(sizeof(memoryBlock));
    if (!new_block) {
        printf("Hata: Yeni blok oluşturulamadi!\n");
        return NULL;
    }

    // Yeni bloğu yapılandır
    new_block->size = size;
    new_block->data = 0; // Varsayılan olarak boş
    new_block->address = previous->address; // Önceki bloğun başlangıcını al
    new_block->next = previous->next; // Önceki bloğun 'next' pointer'ını al

    // Önceki bloğu güncelle
    previous->size -= size; // Önceki bloktan istenen boyut çıkar
    previous->address += size; // Önceki bloğun başlangıcını kaydır
    previous->next = new_block; // Önceki bloğun 'next' pointer'ını yeni bloğa bağla

    return new_block; // Yeni bloğu döndür
}

void mergeFreeBlocks(memoryList* list) {
    if (!list || !list->head)
    {
        /* code */
        printf("Liste bos!\n");
        return;
    }
    
    memoryBlock* current = list->head;
    while (current != NULL && current->next != NULL) {
        if (current->data == 0 && current->next->data == 0) { //Hem mevcut hemde sonraki blok free ise birlestirir.
            current->size += current->next->size;
            memoryBlock* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// void printMemoryBlocks(memoryList* list) {
//     if (!list || !list->head)
//     {
//         /* code */
//         printf("Liste bos!\n");
//         return;
//     }
    
//     memoryBlock* current = list->head;
//     int block_count = 0;
//     while (current != NULL) {
//         printf("Blok %d:\n", ++block_count);
//         printf("  Adres: %p\n", current->address);
//         printf("  Boyut: %zu byte\n", current->size);
//         // printf("  Durum: %s\n", isFree(current) ? "Serbest" : "Dolu");
//         printf("  Sonraki: %p\n\n", (void*)current->next);
//         current = current->next;
//     }
// }