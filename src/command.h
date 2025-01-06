/**
 * @file command.h
 * @brief Komut işleme işlevlerinin tanımları.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "memory_manager.h"

/**
 * @brief Giriş satırını parçalarına ayırır.
 *
 * @param input_line Giriş satırı.
 * @param memoryList Bellek listesi.
 * @param ptrs Pointer listesi.
 * @return Parça sayısı.
 */
void process_command(char* input_line, memoryList* list, std::vector<d_ptr>& ptrs);

#endif // COMMANDS_H
