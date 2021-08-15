#pragma once

#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <root.h>

typedef struct variables_map_t {
    uint64_t index_len;
    uint64_t* indexes;
    uint64_t max_size;
} variables_map_t;

typedef struct frame_map_t { // what is read as a frame from the file - todo: rename to avoid confusion with frame.h::frame
    uint64_t start_index;
    variables_map_t variables;
    uint64_t const_len;
    uint64_t* const_indexes; // where constant variables are within the data section
} frame_map_t;

typedef struct function_t { // what is read as a function from the file
    variables_map_t arguments;
    uint64_t frame_index;
} function_t;

typedef struct map_t { // the map as it is read from the file
    function_t* functions;
    uint64_t function_count;
    frame_map_t* frames;
    uint64_t frame_count;
    uint64_t len;
    uint64_t data_len;
    uint8_t* data_section;
    variables_map_t data_shape;
} map_t;

map_t new_map_from_file(FILE* file);
function_t read_function(FILE* file);
frame_map_t read_frame(FILE* file);

#endif