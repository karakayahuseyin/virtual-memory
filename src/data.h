/**
 * @file data.h
 * @brief Bellek yönetimi için veri yapıları ve yardımcı işlevlerin tanımları.
 */

#ifndef DATA_H
#define DATA_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef d_size
 * @brief Veri bloğunun boyutunu temsil eder.
 */
typedef short int d_size;

/**
 * @typedef d_byte
 * @brief Bir baytlık veri birimini temsil eder.
 */
typedef char d_byte;

/**
 * @enum d_type
 * @brief Veri bloğunun boyutuna göre türünü tanımlar.
 */
typedef enum {
    D8,   /**< 8-bitlik veri bloğu */
    D16,  /**< 16-bitlik veri bloğu */
    D32,  /**< 32-bitlik veri bloğu */
    D64   /**< 64-bitlik veri bloğu */
} d_type;

/**
 * @struct d_ptr
 * @brief Bir bellek bloğuna işaretçi yapısı.
 */
typedef struct {
    d_type type; /**< Bellek bloğunun türü */
    char name[2]; /**< Tanımlayıcı ad (2 karakter) */
    int addr;     /**< Bellek bloğunun adresi */
} d_ptr;

/**
 * @brief Bellek bloğunun türüne göre boyutunu döndürür.
 *
 * @param type Bellek bloğunun türü.
 * @return Bellek bloğunun boyutu (bayt cinsinden).
 */
d_size get_size(d_type type);

/**
 * @brief Bir bellek bloğuna işaretçi oluşturur.
 *
 * @param type Bellek bloğunun türü.
 * @param name Tanımlayıcı ad (2 karakter).
 * @param addr Bellek bloğunun adresi.
 * @return Bellek bloğunu temsil eden d_ptr yapısı.
 */
d_ptr create_ptr(d_type type, char name[2], int addr);

#ifdef __cplusplus
}
#endif

#endif // DATA_H
