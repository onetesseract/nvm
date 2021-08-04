#include <map.h> // todo: change when stuff works
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

map_t new_map_from_file(FILE* file) {
    uint64_t map_len;
    uint8_t len_buff[8];
    fgets(len_buff, 9, file);
    memcpy(&map_len, len_buff, sizeof(map_len));
    for(int i = 0; i < 8; i++) {
        debug("c: %d", len_buff[i]);
    }
    printf("\nMap len: %lu\n", map_len);

    
    uint8_t functions_count = fgetc(file);
    uint8_t frames_count = fgetc(file);
    printf("fn count: %d, frame count: %d", functions_count, frames_count);

    function_t* functions = (function_t*)malloc(sizeof(function_t)*functions_count);
    frame_map_t* frames = (frame_map_t*)malloc(sizeof(frame_map_t)*frames_count);

    for(int i = 0; i < functions_count; i++) {
        printf("reading fn");
        functions[i] = read_function(file);
    }

    for(int i = 0; i < frames_count; i++) {
        printf("reading frame");
        frames[i] = read_frame(file);
    }
    map_t map;

    map.function_count = functions_count;
    map.frame_count = frames_count;
    map.functions = functions;
    map.frames = frames;
    map.len = map_len;

    // uint64_t data_len;
    uint8_t dlen_buff[8];
    fgets((char*) dlen_buff, 9, file);
    memcpy(&map.data_len, dlen_buff, sizeof(map.data_len));
    printf("data len: %lu\n", map.data_len);
    map.data_section = (uint8_t*) malloc(sizeof(uint8_t)*map.data_len);
    fgets((char*) map.data_section, map.data_len+1, file);
    return map;
}

function_t read_function(FILE* file) {
    function_t func;
    func.argcount = fgetc(file);
    func.frame_index = fgetc(file);
    return func;
}

frame_map_t read_frame(FILE* file) {
    frame_map_t frame;
    uint8_t val_buf[8];
    fgets(val_buf, 9, file);
    memcpy(&frame.start_index, val_buf, sizeof(uint8_t)*8);
    frame.varcount = fgetc(file);
    frame.const_len = fgetc(file);
    frame.const_indexes = (uint64_t*)malloc(sizeof(uint64_t)*frame.const_len);
    for(int i = 0; i < frame.const_len; i++) {
        fgets(val_buf, 9, file);
        memcpy(&(frame.const_indexes[i]), val_buf, sizeof(uint8_t)*8);
    }
    return frame;
}
