#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <map.h>
#include <frame.h>


uint8_t run_chain_off_file(FILE* file, frame_t* frame, frame_map_t* map_frame, map_t* map); // I should probably put this in a header, but it seems to work ok here
uint8_t run_frame(FILE* file, map_t* map, uint8_t frame_index); 
uint8_t get_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, map_t* map);
uint8_t set_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, uint8_t value);

int main(void) {
    FILE* file = fopen("prog.neonbin", "rb");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    map_t map = new_map_from_file(file);
    debug("fns: %u, frames: %u\n", map.function_count, map.frame_count);
    debug("const len: %d, const index #1: %lu\n", map.frames[0].const_len, map.frames[0].const_indexes[0]);
    debug("index: %d, argc: %d\n", map.functions[0].frame_index, map.functions[0].argcount);
    uint8_t first_index = map.functions[0].frame_index;
    run_frame(file, &map, first_index);
    // todo: return codes
}

uint8_t run_frame(FILE* file, map_t* map, uint8_t frame_index) {
    if (frame_index > map->frame_count) { printf("no kekw"); return 1; }
    fseek(file, map->frames[frame_index].start_index, map->len);
    frame_t frame;
    frame.values = (uint8_t*) malloc(sizeof(uint8_t)*map->frames[frame_index].varcount);
    return run_chain_off_file(file, &frame, &map->frames[frame_index], map);
}

uint8_t run_chain_off_file(FILE* file, frame_t* frame, frame_map_t* map_frame, map_t* map) { // just runs code from the given file, using the given frame, map etc
    int getc = fgetc(file);
    debug("gotten c: %u\n", getc);
    switch (getc) {
        case -1: // EOF oh no
            return 1;
            break;
        case 0: { // int-add
            uint8_t ret = fgetc(file);
            uint8_t add_to = fgetc(file);
            uint8_t add_by = fgetc(file);
            
            debug("Read Int-Add: ret: %d, add_to: %d, add_by: %d", ret, add_to, add_by);
            uint8_t add_to_val = get_val(frame, map_frame, add_to, map);
            uint8_t add_by_val = get_val(frame, map_frame, add_by, map);
            debug("values: %d %d\n", add_to_val, add_by_val);
            set_val(frame, map_frame, ret, add_to_val + add_by_val);
            debug("ok so this is set: %d\n", get_val(frame, map_frame, ret, map));
            break;
        }
        default: {
            printf("I don't know how to run %d as bytecode!", getc);
            return 1;
        }
    }
    return 0;
}

uint8_t get_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, map_t* map) { // gets value at index within a frame - handles accessing constants
    if(index < map_frame->const_len) {
        debug("constant access\n");
        uint64_t const_index = map_frame->const_indexes[index];
        return map->data_section[const_index];
    }
    return frame->values[index - map_frame->const_len];
}

uint8_t set_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, uint8_t value) { // handles setting variables of a frame given an index
    if(index < map_frame->const_len) {
        printf("Tried to set a constant variable (index: %d, value: %d)", index, value); // we could overwrite constant variables, but that isnt the point of a constant...
        return 1;
    }

    frame->values[index - map_frame->const_len] = value; // this is tricky. We should not set it directly to the value, but to a pointer to that, so we can handle things of indefinite bitwidth
    return 0;                                            // but thats effort and you get a lot of *((void*) (&map->...)) or something else complicated


}