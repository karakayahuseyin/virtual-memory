/**
 * @file main.cpp
 * @brief Programın giriş noktası.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "memory_manager.h"
#include "command.h"

#define MAX_INPUT_SIZE 256

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Kullanim: %s --cli | --file <filename>\n", argv[0]);
        return 1;
    }

    memoryList* list = initializeList(0x01, 2048);
    std::vector<d_ptr> ptrs;

    if (strcmp(argv[1], "--cli") == 0) {
        while (1) {
            printf(">> ");
            fflush(stdout);

            char input_line[MAX_INPUT_SIZE];
            if (!fgets(input_line, sizeof(input_line), stdin)) {
                break;
            }

            process_command(input_line, list, ptrs);
        }
    } else if (strcmp(argv[1], "--file") == 0 && argc == 3) {
        FILE* file = fopen(argv[2], "r");
        if (!file) {
            printf("Hata: Dosya acilamadi: %s\n", argv[2]);
            return 1;
        }

        char input_line[MAX_INPUT_SIZE];
        while (fgets(input_line, sizeof(input_line), file)) {
            process_command(input_line, list, ptrs);
        }

        fclose(file);
    } else {
        printf("Hata: Gecersiz argumanlar. Kullanim: %s --cli | --file <filename>\n", argv[0]);
        return 1;
    }

    return 0;
}
