#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct frame_t {
    uint64_t start_index;
    uint8_t varcount;
} frame_t;

typedef struct function_t {
    uint8_t argcount;
    uint8_t frame_index;
} function_t;

typedef struct map_t {
    function_t* functions;
    uint32_t function_count;
    frame_t* frames;
    uint32_t frame_count;
} map_t;

map_t new_map_from_file(FILE* file);
function_t read_function(FILE* file);
frame_t read_frame(FILE* file);