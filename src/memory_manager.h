/**
 * @file memory_manager.h
 * @brief Bellek yönetim işlevlerinin tanımları.
 */

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "data.h"
#include "memory.h"

#include <stdlib.h>
#include <stdbool.h>

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
memoryList* initializeList(int start_address, size_t total_size);

/**
 * @brief Bir bellek bloğunu tahsis eder.
 *
 * @param type Bellek bloğunun türü.
 * @param name Bellek bloğu için tanımlayıcı ad.
 * @param buf Veri içeriği.
 * @param list Bellek listesi.
 * @return Tahsis edilen bloğu temsil eden d_ptr yapısı.
 */
d_ptr allocate(d_type type, char name[2], d_byte buf[4], memoryList* list);

/**
 * @brief Bir bellek bloğunun tahsisini kaldırır.
 *
 * @param pointer Kaldırılacak bellek bloğuna işaretçi.
 * @param list Bellek listesi.
 * @return İşlem başarılıysa true, aksi halde false.
 */
bool de_allocate(d_ptr pointer, memoryList* list);


/**
 * @brief Bir bellek bloğunun içeriğini getirir.
 *
 * @param pointer Bellek bloğuna işaretçi.
 * @param list Bellek listesi.
 * @return Veriyi içeren d_byte pointer ya da NULL.
 */
d_byte* get_data(d_ptr pointer, memoryList* list);

/**
 * @brief Bir bellek bloğunun içeriğini günceller.
 *
 * @param pointer Bellek bloğuna işaretçi.
 * @param data Yeni veri içeriği.
 * @param list Bellek listesi.
 * @return İşlem başarılıysa true, aksi halde false.
 */
bool set_data(d_ptr pointer, d_byte* data, memoryList* list);


#ifdef __cplusplus
}
#endif

#endif // MEMORY_MANAGER_H