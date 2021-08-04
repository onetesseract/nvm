#pragma once

#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <root.h>

typedef struct frame_map_t { // what is read as a frame from the file - todo: rename to avoid confusion with frame.h::frame
    uint64_t start_index;
    uint8_t varcount;
    uint8_t const_len;
    uint64_t* const_indexes; // where constant variables are within the data section
} frame_map_t;

typedef struct function_t { // what is read as a function from the file
    uint8_t argcount;
    uint8_t frame_index;
} function_t;

typedef struct map_t { // the map as it is read from the file
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

#endif