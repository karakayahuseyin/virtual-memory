#include "data.h"
#include <stdlib.h>

// Return the size of the object based on its type
d_size get_size(d_type type)
{
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

// Return the type of the object as a string
const char* get_type(d_obj obj)
{
    switch (obj.type) {
        case D8:
            return "D8";
        case D16:
            return "D16";
        case D32:
            return "D32";
        case D64:
            return "D64";
        default:
            return "UNKNOWN";
    }
}

// Create and return a data object
d_obj create_obj(d_type type, char name[2], d_byte buf[4], char addr)
{
    d_ref ref;
    ref.name[0] = name[0];
    ref.name[1] = name[1];
    // ref.ref = addr;

    d_obj obj;
    obj.type = type;
    obj.ref = ref;
    obj.buf[0] = buf[0];
    obj.buf[1] = buf[1];
    obj.buf[2] = buf[2];
    obj.buf[3] = buf[3];

    return obj;
}

// Create and return a pointer-like object
d_ptr create_ptr(d_type type, char name[2], char addr)
{
    d_ptr ptr;
    ptr.type = type;
    ptr.name[0] = name[0];
    ptr.name[1] = name[1];
    ptr.addr = addr;
    return ptr;
}
