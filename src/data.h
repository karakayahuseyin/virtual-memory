#ifndef DATA_H
#define DATA_H

#include <stddef.h>

// Typedefs
typedef short int d_size;
typedef char d_byte;

typedef enum {
    D8,
    D16,
    D32,
    D64
} d_type;

typedef struct {
    char name[2];
    char ref[2];
} d_ref;

typedef struct {
    d_type type;
    char name[2];
    char addr;
} d_ptr;

typedef struct {
    d_type type;
    d_ref ref;
    d_byte buf[4];
} d_obj;

// Function prototypes
// d_size get_size(d_obj obj);
d_size get_size(d_type type);
const char* get_type(d_obj obj);
d_obj create_obj(d_type type, char name[2], d_byte buf[4], char addr);
d_ptr create_ptr(d_type type, char name[2], char addr);

#endif // DATA_H
