#include "data.h"
#include "memory.h"

#include <stdlib.h>
#include <stdio.h>


memoryList* initializeList(char start_address, size_t total_size);
d_ptr allocate(d_type type, char name[2], d_byte buf[4], memoryList* list);