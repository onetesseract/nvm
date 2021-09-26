// #include "flatbuffers_common_reader.h"
#include <map.h> // todo: change when stuff works
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <serialise.h>

variables_map_t read_variables(FILE* file);

variables_map_t from_flat(ns(variables_type_table_t) flat_variables);

map_t new_map_from_file(FILE* file) { // reads a map from a file. has no "invalidity" checks as such.
    uint64_t map_len;
    uint8_t len_buff[8];

    uint8_t* main_buff;

    map_t map;

    fgets((char*) len_buff, 9, file);
    memcpy(&map_len, len_buff, sizeof(map_len));

    main_buff = (uint8_t*) malloc(sizeof(uint8_t) * map_len);
    // fgets((char*) main_buff, map_len + 1, file);
    for(int i = 0; i < map_len; i++) {
        main_buff[i] = fgetc(file); // FOR GOD SAKE I HATE FGETS IT CANNOT DO ITS ONE BLOOMIN JOB
    }
    debug("Some sanity checks: 1st %d 9th %d\n", main_buff[0], main_buff[8]);

    ns(map_table_t) flat_map = ns(map_as_root(main_buff));

    map.len = map_len;

    ns(frame_map_vec_t) frame_vec = ns(map_frames(flat_map));

    map.frame_count = ns(frame_map_vec_len)(frame_vec);

    map.frames = malloc(sizeof(frame_map_t) * map.frame_count);

    for (int i = 0; i < map.frame_count; i++) {
        map.frames[i].start_index = ns(frame_map_start_index(ns(frame_map_vec_at(frame_vec, i))));
        ns(variables_type_table_t) flat_variables = ns(frame_map_variables)(ns(frame_map_vec_at(frame_vec, i)));
        map.frames[i].variables = from_flat(flat_variables);
        debug("Frame index len %lu\n", map.frames[i].variables.index_len);
    }

    ns(function_map_vec_t) func_vec = ns(map_functions(flat_map));

    map.function_count = ns(function_map_vec_len)(func_vec);

    map.functions = malloc(sizeof(function_t) * map.function_count);

    for (int i = 0; i < map.function_count; i++) {
        map.functions[i].frame_index = ns(function_map_entry_frame_index)(ns(function_map_vec_at)(func_vec, i));
        map.functions[i].arguments = from_flat(ns(function_map_variables)(ns(function_map_vec_at)(func_vec, i)));
    }

    map.data_shape = from_flat(ns(map_data_shape)(flat_map));
    map.data_len = flatbuffers_uint8_vec_len(ns(map_data)(flat_map));

    debug("Map data len: %lu\n", map.data_len);

    map.data_section = (uint8_t*) malloc(sizeof(uint8_t) * map.data_len);

    for (int i = 0; i < map.data_len; i++) {
        map.data_section[i] = ns(map_data)(flat_map)[i];
        debug("map data #%li: %d\n", i, ns(map_data)(flat_map)[i]);
    }

    return map;
}

variables_map_t from_flat(ns(variables_type_table_t) flat_variables) {
    variables_map_t variables;
    flatbuffers_uint64_vec_t vec = ns(variables_type_indexes)(flat_variables);
    if (vec == NULL) { return variables; }
    variables.index_len = flatbuffers_uint64_vec_len(ns(variables_type_indexes)(flat_variables));
    variables.indexes = (uint64_t*) malloc(sizeof(uint64_t)*variables.index_len);
    variables.max_size = 0;
    for(int i = 0; i < variables.index_len; i++) {
        uint64_t size = ns(variables_type_indexes)(flat_variables)[i];
        variables.indexes[i] = variables.max_size;
        variables.max_size += size;
    }
    return variables;
}

variables_map_t read_variables(FILE* file) {
    variables_map_t variables;
    uint8_t len_buff[8];
    fgets((char*) len_buff, 9, file);
    memcpy(&variables.index_len, len_buff, 8);
    variables.indexes = (uint64_t*) malloc(sizeof(uint64_t)*variables.index_len);
    variables.max_size = 0;
    debug("This one has %lu variables\n", variables.index_len);
    for(int i = 0; i < variables.index_len; i++) {
        fgets((char*) len_buff, 9, file);
        uint64_t size;
        memcpy(&size, len_buff, 8);
        variables.indexes[i] = variables.max_size;
        variables.max_size += size;
    }
    return variables;
}

function_t read_function(FILE* file) { // glorified fgetc wrapper
    function_t func;
    func.arguments = read_variables(file);
    func.frame_index = fgetc(file);
    return func;
}

frame_map_t read_frame(FILE* file) { // another glorified fgetc wrapper
    frame_map_t frame;
    uint8_t val_buf[8];

    fgets((char*) val_buf, 9, file);
    memcpy(&frame.start_index, val_buf, sizeof(uint8_t)*8);
    frame.variables = read_variables(file);
    return frame;
}

uint64_t read_uint64(FILE* file) {
    uint64_t ret;
    uint8_t buff[8];
    for(int i = 0; i < 8; i++) { // I do not trust fgets anymore
        buff[i] = fgetc(file);
    }
    memcpy(&ret, buff, 8);
    return ret;
}
