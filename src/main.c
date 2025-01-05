#include "memory_manager.h"
#include <stdio.h>
#include <stdlib.h>

void printMemoryList(memoryList* list) {
    memoryBlock* block = list->head;
    while (block) {
        printf("Adres: %d, Boyut: %zu, Data: ", block->address, block->size);
        if (block->data) {
            for (size_t i = 0; i < block->size; i++) {
                printf("0x%02x ", block->data[i]); // Her byte'ı hex formatında yazdır
            }
        } else {
            printf("(null)"); // Eğer veri tahsis edilmemişse
        }
        printf(", Next: %p\n", (void*)block->next);
        block = block->next;
    }
}

int main() {
    // Bellek listesini başlat
    memoryList* list = initializeList(0x01, 256);

    // Debug: Liste başlangıç durumu
    printf("Liste başlangıç durumu:\n");
    printMemoryList(list);

    // İlk allocate işlemi
    printf("\nD16 boyutunda bellek ayrılıyor...\n");
    d_ptr ptr = allocate(D16, "A1", (d_byte[4]){0x02, 0x03, 0x00, 0x00}, list);

    // Debug: Liste durumu (ilk allocate sonrası)
    printf("\nListe durumu (ilk allocate sonrası):\n");
    printMemoryList(list);

    // İkinci allocate işlemi
    printf("\nD32 boyutunda bellek ayrılıyor...\n");
    d_ptr ptr2 = allocate(D32, "A2", (d_byte[4]){0x03, 0x04, 0x05, 0x00}, list);

    // Debug: Liste durumu (ikinci allocate sonrası)
    printf("\nListe durumu (ikinci allocate sonrası):\n");
    printMemoryList(list);

    // Ayrılmış bellek adreslerini yazdır
    printf("\nAyrılan bellek adresleri:\n");
    printf("Adres 1: %x\n", ptr.addr);
    printf("Adres 2: %x\n", ptr2.addr);

    return 0;
}
