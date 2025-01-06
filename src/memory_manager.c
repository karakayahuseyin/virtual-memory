/**
 * @file memory_manager.c
 * @brief Bellek yönetim işlevlerinin uygulamaları.
 */

#include "memory_manager.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Bellek listesini başlatır.
 *
 * @param start_address Başlangıç adresi.
 * @param total_size Listenin toplam boyutu.
 * @return Başlatılmış bellek listesi ya da NULL.
 */
memoryList* initializeList(int start_address, size_t total_size) {
    memoryList* list = (memoryList*)malloc(sizeof(memoryList));
    if (!list) {
        return NULL;
    }

    memoryBlock* block = (memoryBlock*)malloc(sizeof(memoryBlock));
    if (!block) {
        free(list);
        return NULL;
    }

    block->address = start_address;
    block->size = total_size;
    block->data = NULL;
    block->next = NULL;
    list->head = block;
    list->total_size = total_size;
    return list;
}

/**
 * @brief Bir bellek bloğunu tahsis eder.
 *
 * @param type Bellek bloğunun türü.
 * @param name Bellek bloğu için tanımlayıcı ad.
 * @param buf Veri içeriği.
 * @param list Bellek listesi.
 * @return Tahsis edilen bloğu temsil eden d_ptr yapısı.
 */
d_ptr allocate(d_type type, char name[2], d_byte buf[4], memoryList* list) {
    d_size size = get_size(type);
    memoryBlock* block = findBlock(list, (int)size);

    if (!block) {
        return create_ptr(type, "00", 0);
    }

    block->data = (d_byte*)malloc(size);  // Bellek bloğu için yeni alan tahsis et
    if (!block->data) {
        return create_ptr(type, "00", 0);
    }

    memcpy(block->data, buf, size);  // Veriyi kopyala
    d_ptr ptr = create_ptr(type, name, block->address);
    return ptr;
}

/**
 * @brief Bir bellek bloğunun tahsisini kaldırır.
 *
 * @param pointer Kaldırılacak bellek bloğuna işaretçi.
 * @param list Bellek listesi.
 * @return İşlem başarılıysa true, aksi halde false.
 */
bool de_allocate(d_ptr pointer, memoryList* list) {
    if (!list || !list->head) {
        return false;
    }

    memoryBlock* current = list->head;
    while (current != NULL) {
        if (current->address == pointer.addr) {
            current->data = NULL;
            mergeFreeBlocks(list);
            return true;
        }
        current = current->next;
    }
    return false;
}

/**
 * @brief Bir bellek bloğunun içeriğini getirir.
 *
 * @param pointer Bellek bloğuna işaretçi.
 * @param list Bellek listesi.
 * @return Veriyi içeren d_byte pointer ya da NULL.
 */
d_byte* get_data(d_ptr pointer, memoryList* list) {
    if (!list || !list->head) {
        return NULL;
    }

    memoryBlock* current = list->head;
    while (current) {
        if (current->address == pointer.addr) {
            return current->data;
        }
        current = current->next;
    }

    return NULL;
}

/**
 * @brief Bir bellek bloğunun içeriğini günceller.
 *
 * @param pointer Bellek bloğuna işaretçi.
 * @param data Yeni veri içeriği.
 * @param list Bellek listesi.
 * @return İşlem başarılıysa true, aksi halde false.
 */
bool set_data(d_ptr pointer, d_byte* data, memoryList* list) {
    if (!list || !list->head) {
        return false;
    }

    memoryBlock* current = list->head;
    while (current) {
        if (current->address == pointer.addr) {
            d_size size = get_size(pointer.type);
            if (!current->data) {
                current->data = (d_byte*)malloc(size);  // Veri yoksa yeni alan ayır
            }
            memcpy(current->data, data, size);  // Veriyi güncelle
            return true;
        }
        current = current->next;
    }

    return false;
}


#ifdef __cplusplus
}
#endif