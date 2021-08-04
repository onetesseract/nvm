#include <stdint.h>
typedef struct frame_t { // where values are stored in runtime for a frame
    uint8_t* values;
} frame_t;