/**
 * @file memory.h
 * @brief Bellek yönetimi için temel yapıların ve işlevlerin tanımları.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include "data.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct memoryBlock
 * @brief Bellek yönetimi için bir blok yapısı.
 */
typedef struct s_memoryBlock {
    size_t size;            /**< Bloğun boyutu (bayt olarak). */
    d_byte* data;           /**< Bloğa atanmış veri. */
    int address;            /**< Bloğun başlangıç adresi. */
    struct s_memoryBlock* next; /**< Sonraki bloğa işaretçi. */
} memoryBlock;

/**
 * @struct memoryList
 * @brief Bellek bloklarını yönetmek için kullanılan liste yapısı.
 */
typedef struct s_memoryList {
    memoryBlock* head;      /**< Listenin ilk bloğuna işaretçi. */
    size_t total_size;      /**< Listenin toplam boyutu. */
} memoryList;

/**
 * @brief Uygun boyutta bir bellek bloğu bulur.
 *
 * @param list Bellek listesi.
 * @param size İstenen boyut.
 * @return Uygun bellek bloğu ya da NULL.
 */
memoryBlock* findBlock(memoryList* list, size_t size);

/**
 * @brief Boş bellek bloklarını birleştirir.
 *
 * @param list Bellek listesi.
 */
void mergeFreeBlocks(memoryList* list);

/**
 * @brief Bellek listesindeki blokları yazdırır.
 *
 * @param list Bellek listesi.
 */
void printMemoryList(memoryList* list);

#ifdef __cplusplus
}
#endif

#endif // MEMORY_H
