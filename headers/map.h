#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <root.h>

typedef struct frame_map_t {
    uint64_t start_index;
    uint8_t varcount;
    uint8_t const_len;
    uint64_t* const_indexes;
} frame_map_t;

typedef struct function_t {
    uint8_t argcount;
    uint8_t frame_index;
} function_t;

typedef struct map_t {
    function_t* functions;
    uint32_t function_count;
    frame_map_t* frames;
    uint32_t frame_count;
    uint64_t len;
    uint64_t data_len;
    uint8_t* data_section;
} map_t;

map_t new_map_from_file(FILE* file);
function_t read_function(FILE* file);
frame_map_t read_frame(FILE* file);