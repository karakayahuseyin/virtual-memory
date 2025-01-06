/**
 * @file data.c
 * @brief Bellek yönetimi için veri yapılarının ve işlevlerin uygulamaları.
 */

#include "data.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Bellek bloğunun türüne göre boyutunu döndürür.
 *
 * @param type Bellek bloğunun türü.
 * @return Bellek bloğunun boyutu (bayt cinsinden).
 */
d_size get_size(d_type type) {
    switch (type) {
        case D8:
            return 1;
        case D16:
            return 2;
        case D32:
            return 4;
        case D64:
            return 8;
        default:
            return 0;
    }
}

/**
 * @brief Bir bellek bloğuna işaretçi oluşturur.
 *
 * @param type Bellek bloğunun türü.
 * @param name Tanımlayıcı ad (2 karakter).
 * @param addr Bellek bloğunun adresi.
 * @return Bellek bloğunu temsil eden d_ptr yapısı.
 */
d_ptr create_ptr(d_type type, char name[2], int addr) {
    d_ptr ptr;
    ptr.type = type;
    ptr.name[0] = name[0];
    ptr.name[1] = name[1];
    ptr.addr = addr;
    return ptr;
}

#ifdef __cplusplus
}
#endif
