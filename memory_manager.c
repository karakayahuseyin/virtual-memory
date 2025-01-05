#include "memory_manager.h"

memoryList* initializeList(char start_address, size_t total_size) {
    memoryList* list = (memoryList*)malloc(sizeof(memoryList));
    if (!list) {
        printf("Liste oluşturulamadi!\n");
        free(list);
        return NULL;
    }

    memoryBlock* block = (memoryBlock*)malloc(sizeof(memoryBlock));
    if (!block) {
        printf("Blok oluşturulamadi!\n");
        free(block);
        return NULL;
    }

    block->address = start_address;
    block->size = total_size;
    block->data = 0;
    block->next = NULL;
    list->head = block;
    list->total_size = total_size;
    return list;
}

d_ptr allocate(d_type type, char name[2], d_byte buf[4], memoryList* list) {
    d_size size = get_size(type); // Istenen boyutu al

    memoryBlock* block = findBlock(list, (int)size); // Blok bul

    if (!block) {
        printf("Blok bulunamadi!\n");
        return create_ptr(type, "00", 0);
    }

    char addr = (char)block->address;
    block->data = buf;
    d_ptr ptr = create_ptr(type, name, addr);
    return ptr;
}


