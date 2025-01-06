/**
 * @file command.cpp
 * @brief Komut işleme işlevlerinin uygulamaları.
 */
#include "command.h"
#include "memory_manager.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <vector>

#define MAX_TOKENS 32
#define MAX_OPERATION_TIME_MS 10

/**
 * @brief Giriş satırını parçalarına ayırır.
 *
 * @param input Giriş satırı.
 * @param tokens Parça dizisi.
 * @param max_tokens Maksimum parça sayısı.
 * @return Parça sayısı.
 */
int tokenize_input(char* input, char* tokens[], int max_tokens) {
    int count = 0;
    char* tok = strtok(input, " \t\r\n");
    while (tok != NULL && count < max_tokens - 1) {
        tokens[count++] = tok;
        tok = strtok(NULL, " \t\r\n");
    }
    tokens[count] = NULL;
    return count;
}

/**
 * @brief Hexadecimal karakteri byte'a çevirir.
 *
 * @param hex Hexadecimal karakter.
 * @return Karşılık gelen byte.
 */
unsigned char hex_to_byte(const char* hex) {
    return (unsigned char)strtol(hex, NULL, 16);
}

/**
 * @brief Komut işleme fonksiyonu.
 *
 * @param input_line Giriş satırı.
 * @param list Bellek listesi.
 * @param ptrs Pointer listesi.
 */
void process_command(char* input_line, memoryList* list, std::vector<d_ptr>& ptrs) {
    Timer* operation_timer = Timer::get_singleton();
    char* tokens[MAX_TOKENS];
    int token_count = tokenize_input(input_line, tokens, MAX_TOKENS);

    if (token_count == 0) return;

    char* command = tokens[0];

    if (strcasecmp(command, "EXIT") == 0) {
        printf("Cikis yapiliyor\n");
        exit(0);
    } else if (strcasecmp(command, "PRINT") == 0) {
        printf("=== MEMORY LIST VIEW ===\n");
        memoryBlock* block = list->head;
        while (block) {
            printf("[ %d ] ", block->address);
            if (block->data) {
                for (size_t i = 0; i < block->size; i++) {
                    printf("0x%02X ", block->data[i] & 0xFF);
                }
            } else {
                printf("FREE");
            }
            printf("\n");
            block = block->next;
        }
    } else if (strcasecmp(command, "HELP") == 0) {
        printf("PRINT                                - Show the memory list\n");
        printf("DATA8/16/32/64 <Name> <HexValues...> - Allocate memory\n");
        printf("FREE <Name>                          - Free allocated memory\n");
        printf("GET <Name>                           - Retrieve data from a pointer\n");
        printf("SET <Name> <HexValues...>            - Update data at a pointer\n");
        printf("EXIT                                 - Exit the program\n");
    } else if (strncasecmp(command, "DATA", 4) == 0) {
        if (token_count < 3) {
            printf("Kullanim: %s <Name> <HexValues...>\n", command);
            return;
        }

        char* name = tokens[1];
        int bits = 0;
        if (strcasecmp(command, "DATA8") == 0) bits = 8;
        else if (strcasecmp(command, "DATA16") == 0) bits = 16;
        else if (strcasecmp(command, "DATA32") == 0) bits = 32;
        else if (strcasecmp(command, "DATA64") == 0) bits = 64;
        else {
            printf("Bilinmeyen DATA komutu: %s\n", command);
            return;
        }

        d_byte data[256];
        int data_count = 0;
        for (int i = 2; i < token_count; i++) {
            data[data_count++] = hex_to_byte(tokens[i]);
        }

        d_type dsize;
        if (bits == 8) dsize = D8;
        else if (bits == 16) dsize = D16;
        else if (bits == 32) dsize = D32;
        else dsize = D64;

        char name_arr[3];
        snprintf(name_arr, sizeof(name_arr), "%s", name);

        operation_timer->start();
        d_ptr ptr = allocate(dsize, name_arr, data, list);
        uint64_t elapsed_time = operation_timer->now_ns();
        if (ptr.addr == 0) {
            printf("[ %d ] Allocation failed. (%" PRIu64 " ns)\n", ptr.addr, elapsed_time);
        } else {
            printf("[ %d ] Allocated (%s). (%" PRIu64 " ns)\n", ptr.addr, name, elapsed_time);
        }
        ptrs.push_back(ptr);

        if (elapsed_time > MAX_OPERATION_TIME_MS * 1000000) {
            printf("Hata: Islem %" PRIu64 " ns'yi asti!\n", elapsed_time);
        }
    } else if (strcasecmp(command, "FREE") == 0) {
        if (token_count < 2) {
            printf("Kullanim: FREE <Name>\n");
            return;
        }

        char* name = tokens[1];
        for (int i = 0; i < ptrs.size(); i++) {
            if (strcmp(ptrs[i].name, name) == 0) {
                operation_timer->start();
                uint64_t elapsed_time = operation_timer->now_ns();
                if (de_allocate(ptrs[i], list)) {
                    printf("[ %d ] Freed (%s). (%" PRIu64 " ns)\n", ptrs[i].addr, name, elapsed_time);
                    ptrs.erase(ptrs.begin() + i);
                } else {
                    printf("[ %d ] Free failed (%s). (%" PRIu64 " ns)\n", ptrs[i].addr, name, elapsed_time);
                }
                return;
            }
        }
        printf("Hata: %s isimli pointer bulunamadi!\n", name);
    } else if (strcasecmp(command, "GET") == 0) {
        if (token_count < 2) {
            printf("Kullanim: GET <Name>\n");
            return;
        }

        char* name = tokens[1];
        for (int i = 0; i < ptrs.size(); i++) {
            if (strcmp(ptrs[i].name, name) == 0) {
                d_byte* data = get_data(ptrs[i], list);
                if (data) {
                    printf("[ %d ] Data: ", ptrs[i].addr);
                    for (size_t j = 0; j < get_size(ptrs[i].type); j++) {
                        printf("0x%02X ", data[j]);
                    }
                    printf("\n");
                } else {
                    printf("Hata: Veri bulunamadi!\n");
                }
                return;
            }
        }
        printf("Hata: %s isimli pointer bulunamadi!\n", name);
    } else if (strcasecmp(command, "SET") == 0) {
        if (token_count < 3) {
            printf("Kullanim: SET <Name> <HexValues...>\n");
            return;
        }

        char* name = tokens[1];
        d_byte data[256];
        int data_count = 0;
        for (int i = 2; i < token_count; i++) {
            data[data_count++] = hex_to_byte(tokens[i]);
        }

        for (int i = 0; i < ptrs.size(); i++) {
            if (strcmp(ptrs[i].name, name) == 0) {
                if (set_data(ptrs[i], data, list)) {
                    printf("[ %d ] Data updated successfully (%s).\n", ptrs[i].addr, name);
                } else {
                    printf("Hata: Veri guncellenemedi!\n");
                }
                return;
            }
        }
        printf("Hata: %s isimli pointer bulunamadi!\n", name);
    } else {
        printf("Hata: Bilinmeyen komut: %s\n", command);
    }
}
