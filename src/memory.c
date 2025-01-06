/**
 * @file memory.c
 * @brief Bellek yönetimi için işlevlerin uygulamaları.
 */

#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Uygun boyutta bir bellek bloğu bulur.
 *
 * @param list Bellek listesi.
 * @param size İstenen boyut.
 * @return Uygun bellek bloğu ya da NULL.
 */
memoryBlock* findBlock(memoryList* list, size_t size) {
    if (!list || !list->head) {
        return NULL;
    }

    memoryBlock* current = list->head;

    while (current != NULL) {
        if (current->data == NULL && current->size >= size) {
            if (current->size > size) {
                memoryBlock* new_block = (memoryBlock*)malloc(sizeof(memoryBlock));
                if (!new_block) {
                    return NULL;
                }

                new_block->size = current->size - size;
                new_block->data = NULL;
                new_block->address = current->address + size;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }
            return current;
        }
        current = current->next;
    }

    return NULL;
}

/**
 * @brief Yeni bir bellek bloğu oluşturur.
 *
 * @param previous Önceki bellek bloğu.
 * @param size Yeni bloğun boyutu.
 * @return Yeni bellek bloğu ya da NULL.
 */
memoryBlock* createMemoryBlock(memoryBlock* previous, size_t size) {
    if (!previous || previous->size < size) {
        return NULL;
    }

    memoryBlock* new_block = (memoryBlock*)malloc(sizeof(memoryBlock));
    if (!new_block) {
        return NULL;
    }

    new_block->size = size;
    new_block->data = NULL;
    new_block->address = previous->address;
    new_block->next = previous->next;

    previous->size -= size;
    previous->address += size;
    previous->next = new_block;

    return new_block;
}

/**
 * @brief Boş bellek bloklarını birleştirir.
 *
 * @param list Bellek listesi.
 */
void mergeFreeBlocks(memoryList* list) {
    if (!list || !list->head) {
        return;
    }

    memoryBlock* current = list->head;
    while (current != NULL && current->next != NULL) {
        if (current->data == NULL && current->next->data == NULL) {
            current->size += current->next->size;
            memoryBlock* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

/**
 * @brief Bellek listesindeki blokları yazdırır.
 *
 * @param list Bellek listesi.
 */
void printMemoryList(memoryList* list) {
    memoryBlock* block = list->head;
    while (block) {
        printf("[%d] Boyut: %zu, Durum: %s\n",
               block->address,
               block->size,
               block->data ? "Dolu" : "Bos");
        block = block->next;
    }
}

#ifdef __cplusplus
}
#endif