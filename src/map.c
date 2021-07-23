#include <map.h> // todo: change when stuff works
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

map_t new_map_from_file(FILE* file) {
    uint64_t map_len;
    char len_buff[8];
    fgets((char*)len_buff, 8, file);
    map_len = (uint64_t) len_buff;
    
    char* map_buff = (char*)malloc(sizeof(char)*map_len);
    fgets(map_buff, map_len, file);

    uint8_t functions_count;
    uint8_t frames_count;
    functions_count = fgetc(file);
    frames_count = fgetc(file);

    function_t* functions = (function_t*)malloc(sizeof(function_t)*functions_count);
    frame_t* frames = (frame_t*)malloc(sizeof(frame_t)*frames_count);

    for(int i = 0; i < functions_count; i++) {
        functions[i] = read_function(file);
    }

    for(int i = 0; i < frames_count; i++) {
        frames[i] = read_frame(file);
    }
    map_t map;

    map.function_count = functions_count;
    map.frame_count = frames_count;
    map.functions = functions;
    map.frames = frames;
}

function_t read_function(FILE* file) {
    function_t func;
    func.argcount = fgetc(file);
    func.frame_index = fgetc(file);
    return func;
}

frame_t read_frame(FILE* file) {
    frame_t frame;
    char val_buf[8];
    fgets(val_buf, 8, file);
    frame.start_index = (uint64_t) val_buf;
    frame.varcount = fgetc(file);
    return frame;
}
