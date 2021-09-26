#include "map.h"
#include "values.h"
#include <running.h>
#include <stdint.h>

uint8_t run_root_frame(FILE* file, map_t* map, uint64_t frame_index) {
    frame_t frame;
    frame.root = &frame;
    frame.child = NULL;

    uint8_t return_val;

    if (map->frame_count <= frame_index) {
        printf("no kekw\n"); return_val = 1;
    } else {
        fseek(file, map->frames[frame_index].start_index, map->len);
        frame.values = (void*) malloc(sizeof(void*)*map->frames[frame_index].variables.index_len);
        frame.varcount = map->frames[frame_index].variables.index_len;
        debug("Variables len: %lu\n", map->frames[frame_index].variables.index_len);
        for (int i = 0; i < map->frames[frame_index].variables.index_len; i++) {
            frame.values[i] = NULL; // theres gotta be a better way than this
        }
        return_val = run_chain_off_file(file, &frame, &map->frames[frame_index], map);
    }
    return return_val;
}

uint8_t run_nonroot_frame(FILE* file, map_t* map, uint64_t frame_index, frame_t* root) {
    frame_t frame;
    frame.root = root;
    frame.child = NULL;

    uint8_t return_val;

    debug("Jumping to frame index %lu\n", frame_index);
    // malloc(sizeof(uint8_t) * 64); // needless malloc to test something

    if (map->frame_count <= frame_index) { // todo: unduplicate logic
        debug("Trying to jump to frame index %lu but the frame count is %lu\n", frame_index, map->frame_count);
        printf("no kekw\n"); return_val = 1;
    } else {
        debug("fseeking to %lu with offset %lu\n", map->frames[frame_index].start_index, map->len + 8); // add 8 to account for the size of the map len indicator itself
        fseek(file, map->frames[frame_index].start_index + map->len + 8, SEEK_SET);
        frame.values = (void*) malloc(sizeof(void*)*map->frames[frame_index].variables.index_len);
        debug("Set frame values pointer as %p\n", frame.values);
        frame.varcount = map->frames[frame_index].variables.index_len;
        debug("Variables len: %lu\n", map->frames[frame_index].variables.index_len);
        for (int i = 0; i < map->frames[frame_index].variables.index_len; i++) { // todo: refactor into memset?
            frame.values[i] = NULL;
        }
        return_val = run_chain_off_file(file, &frame, &map->frames[frame_index], map);
    }
    return return_val;
}

void frame_free(frame_t* frame) {
    for (int i = 0; i < frame->varcount; i++) {
        if(frame->values[i] != NULL) {
            free(frame->values[i]);
        }
    }
    free(frame->values);
}

uint8_t run_chain_off_file(FILE* file, frame_t* frame, frame_map_t* map_frame, map_t* map) { // just runs code from the given file, using the given frame, map etc
    int getc;
    int return_val = -1;
    while(-1 == return_val) { // TODO: switch to using uint64_ts as variable indexes somehow
        getc = fgetc(file);
        debug("gotten c: %i\n", getc);
        switch (getc) {
            case -1: // EOF oh no
                return_val = 1;
                break;
            case 0x0: { // u8-add
                uint8_t ret = fgetc(file);
                uint8_t add_to = fgetc(file);
                uint8_t add_by = fgetc(file);

                uint8_t add_to_val;
                uint8_t add_by_val;

                uint8_t final;

                debug("Read U8-Add: ret: %d, add_to: %d, add_by: %d\n", ret, add_to, add_by);
                add_to_val = *get_val(frame, map_frame, add_to, map);
                add_by_val = *get_val(frame, map_frame, add_by, map);
                debug("values: %d %d\n", add_to_val, add_by_val);
                final = add_to_val + add_by_val;
                set_val(frame, map_frame, map, ret, &final, 1);
                debug("ok so this is set: %d\n", *get_val(frame, map_frame, ret, map));
                break;
            }
            case 0x1: { // u8-sub
                uint8_t ret = fgetc(file);
                uint8_t sub_from = fgetc(file);
                uint8_t sub_by = fgetc(file);

                uint8_t sub_from_val = *get_val(frame, map_frame, sub_from, map);
                uint8_t sub_by_val = *get_val(frame, map_frame, sub_by, map);
                uint8_t final = sub_from_val-sub_by_val;

                set_val(frame, map_frame, map, ret, &final, 1);
                debug("set from U8-sub: %d\n", *get_val(frame, map_frame, ret, map));
                break;
            }
            case 0x2: { // u8-mul
                uint8_t ret = fgetc(file);
                uint8_t mul_from = fgetc(file);
                uint8_t mul_by = fgetc(file);

                uint8_t mul_from_val = *get_val(frame, map_frame, mul_from, map);
                uint8_t mul_by_val = *get_val(frame, map_frame, mul_by, map);

                uint8_t final = mul_from_val*mul_by_val;

                set_val(frame, map_frame, map, ret, &final, 1);
                debug("set from U8-mul: %d\n", *get_val(frame, map_frame, ret, map));
                break;
            }
            case 0x3: { // u8-div
                return_val = 1;
                break; // we cannot handle floats yet oh noes
            }
            case 0x4: { // u8-comp-eq
                uint8_t ret = fgetc(file);
                uint8_t comp1 = fgetc(file);
                uint8_t comp2 = fgetc(file);

                uint8_t comp1_val = *get_val(frame, map_frame, comp1, map);
                uint8_t comp2_val = *get_val(frame, map_frame, comp2, map);

                uint8_t final = comp1_val == comp2_val;

                set_val(frame, map_frame, map, ret, &final, 1);
                debug("set from U8-comp-eq: %d\n", *get_val(frame, map_frame, ret, map));
                break;
            }
            case 0x5: { // u8-comp-less
                uint8_t ret = fgetc(file);
                uint8_t comp1 = fgetc(file);
                uint8_t comp2 = fgetc(file);

                uint8_t comp1_val = *get_val(frame, map_frame, comp1, map);
                uint8_t comp2_val = *get_val(frame, map_frame, comp2, map);

                uint8_t final = comp1_val < comp2_val;

                set_val(frame, map_frame, map, ret, &final, 1);
                debug("set from U8-comp-less: %d\n", *get_val(frame, map_frame, ret, map));
                break;
            }
            case 0x6: { // u8-comp-leq
                uint8_t ret = fgetc(file);
                uint8_t comp1 = fgetc(file);
                uint8_t comp2 = fgetc(file);

                uint8_t comp1_val = *get_val(frame, map_frame, comp1, map);
                uint8_t comp2_val = *get_val(frame, map_frame, comp2, map);

                uint8_t final = comp1_val <= comp2_val;

                set_val(frame, map_frame, map, ret, &final, 1);
                debug("set from U8-comp-leq: %d\n", *get_val(frame, map_frame, ret, map));
                break;
            }
            case 0xD0: { // if
                uint8_t cond_index = fgetc(file);
                uint8_t index = fgetc(file);
                uint8_t ret;

                uint8_t cond_val = *get_val(frame, map_frame, cond_index, map);
                
                if (cond_val != 0) {
                    ret = run_nonroot_frame(file, map, index, frame);
                }

                if(ret != 0) { // there has been an error
                    return_val = ret;
                }
            }
            case 0xD1: { // if/else
                uint8_t cond_index = fgetc(file);
                uint8_t if_index = fgetc(file);
                uint8_t else_index = fgetc(file);
                uint8_t ret;

                uint8_t cond_val = *get_val(frame, map_frame, cond_index, map);
                
                if (cond_val != 0) {
                    ret = run_nonroot_frame(file, map, if_index, frame);
                } else { // todo: surely this can be neatened
                    ret = run_nonroot_frame(file, map, else_index, frame);
                }

                if(ret != 0) { // there has been an error
                    return_val = ret;
                }
            }
            case 0xF0: { // call
                uint64_t index;
                function_t* function;
                uint8_t* memory_allocated;

                index = read_uint64(file);
                function = &map->functions[index];


                for(int i = 0; i < function->arguments.index_len; i++) {

                }
            }
            case 0xF1: { // jump - no going back to this frame then.
                uint64_t index;
                uint8_t ret;

                index = read_uint64(file);

                frame_free(frame);

                ret = run_nonroot_frame(file, map, index, frame);
                if(ret != 0) { // there has been an error
                    return_val = ret;
                }
                return return_val; // we have freed all the memory, we cannot go back now lol
                break;
            }
            default: {
                printf("I don't know how to run %d as bytecode!\n", getc);
                return_val = 1;
                break;
            }
        }
    }
    return return_val;
}