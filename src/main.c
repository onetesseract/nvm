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
    map_t map;
    uint8_t first_index;

    int return_val;

    if (file == NULL) {
        printf("File not found");
        return_val = 1;
    } else {
        map = new_map_from_file(file);
        debug("fns: %u, frames: %u\n", map.function_count, map.frame_count);
        debug("const len: %d, const index #1: %lu\n", map.frames[0].const_len, map.frames[0].const_indexes[0]);
        debug("index: %d, argc: %d\n", map.functions[0].frame_index, map.functions[0].argcount);
        first_index = map.functions[0].frame_index;
        debug("should be 18: %d\n", map.data_section[0]);
        debug("should be 10: %d\n", map.data_section[1]);
        debug("should be 20: %d\n", map.data_section[2]);
        run_frame(file, &map, first_index);
        // todo: return codes
        return_val = 0;
    }

    return return_val;

}

uint8_t run_frame(FILE* file, map_t* map, uint8_t frame_index) {
    frame_t frame;

    uint8_t return_val;

    if (map->frame_count <= frame_index) {
        printf("no kekw"); return_val = 1;
    } else {
        fseek(file, map->frames[frame_index].start_index, map->len);
        frame.values = (void*) malloc(sizeof(void*)*map->frames[frame_index].varcount);
        return_val = run_chain_off_file(file, &frame, &map->frames[frame_index], map);
    }
    return return_val;
}

uint8_t run_chain_off_file(FILE* file, frame_t* frame, frame_map_t* map_frame, map_t* map) { // just runs code from the given file, using the given frame, map etc
    int getc;

    int return_val = -1;
    while(-1 == return_val) {
        getc = fgetc(file);
        debug("gotten c: %i\n", getc);
        switch (getc) {
            case -1: // EOF oh no
                return_val = 1;
                break;
            case 0: { // u8-add
                uint8_t ret = fgetc(file);
                uint8_t add_to = fgetc(file);
                uint8_t add_by = fgetc(file);

                uint8_t add_to_val;
                uint8_t add_by_val;

                debug("Read U8-Add: ret: %d, add_to: %d, add_by: %d", ret, add_to, add_by);
                add_to_val = get_val(frame, map_frame, add_to, map);
                add_by_val = get_val(frame, map_frame, add_by, map);
                debug("values: %d %d\n", add_to_val, add_by_val);
                set_val(frame, map_frame, ret, add_to_val + add_by_val);
                debug("ok so this is set: %d\n", get_val(frame, map_frame, ret, map));
                break;
            }
            case 1: { // u8-sub
                uint8_t ret = fgetc(file);
                uint8_t sub_from = fgetc(file);
                uint8_t sub_by = fgetc(file);

                uint8_t sub_from_val = get_val(frame, map_frame, sub_from, map);
                uint8_t sub_by_val = get_val(frame, map_frame, sub_by, map);

                set_val(frame, map_frame, ret, sub_from_val-sub_by_val);
                debug("set from U8-sub: %d", get_val(frame, map_frame, ret, map));
                break;
            }
            case 2: { // u8-mul
                uint8_t ret = fgetc(file);
                uint8_t mul_from = fgetc(file);
                uint8_t mul_by = fgetc(file);

                uint8_t mul_from_val = get_val(frame, map_frame, mul_from, map);
                uint8_t mul_by_val = get_val(frame, map_frame, mul_by, map);

                set_val(frame, map_frame, ret, mul_from_val*mul_by_val);
                debug("set from U8-mul: %d", get_val(frame, map_frame, ret, map));
                break;
            }
            case 3: { // u8-div
            return_val = 1;
                break; // we cannot handle floats yet oh noes
            }
            default: {
                printf("I don't know how to run %d as bytecode!", getc);
                return_val = 1;
                break;
            }
        }
    }
    return return_val;
}

uint8_t get_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, map_t* map) { // gets value at index within a frame - handles accessing constants
    uint8_t return_val;

    if(map_frame->const_len > index) {
        uint64_t const_index = map_frame->const_indexes[index];
        debug("constant access\n");
        return_val = map->data_section[const_index];
        debug("return val: %d\n", return_val);
    } else {
        return_val = *(uint8_t*) frame->values[index - map_frame->const_len];
    }
    return return_val;
}

uint8_t set_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, uint8_t value) { // handles setting variables of a frame given an index
    uint8_t return_val = 0;

    if(map_frame->const_len > index) {
        printf("Tried to set a constant variable (index: %d, value: %d)", index, value); // we could overwrite constant variables, but that isnt the point of a constant...
        return_val = 1;
    }

    frame->values[index - map_frame->const_len] = (void*) &value; // this is tricky. We should not set it directly to the value, but to a pointer to that, so we can handle things of indefinite bitwidth
    return return_val;                                   // but thats effort and you get a lot of *((void*) (&map->...)) or something else complicated
}