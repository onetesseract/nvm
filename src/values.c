#include <values.h>

uint8_t* get_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, map_t* map) { // gets value at index within a frame - handles accessing constants
    uint8_t* return_val;
    debug("Consts len: %lu", map->data_shape.index_len);
    if(map->data_shape.index_len > index) {
        uint64_t const_index = map->data_shape.indexes[index];
        debug("constant access\n");
        index = map->data_shape.indexes[const_index];
        return_val = &map->data_section[index];
        debug("return val: %d\n", *return_val);
    } else { // note to self: we don't have to look up sizes within variables because it's an array of pointers you idiot
        frame_t* working_frame = frame->root;
        if(working_frame == NULL) {
            debug("Borked");
            for(;;);
        }
        
        uint64_t variables_passed = 0;
        
        while((variables_passed + working_frame->varcount) < index - map->data_shape.index_len) {
            if(working_frame->child == NULL) {
                printf("Index out of bounds!");
                return NULL; // index out of bounds - todo: remove multiple return points
            }
            variables_passed = working_frame->varcount;
            working_frame = working_frame->child;
            
        }
        
        if(working_frame->values[(index - map->data_shape.index_len) - variables_passed] == NULL) { debug("Accessing undefined variable - will maybe be nullptr! (inb4 segfault)\n"); }
        debug("[GET] This is index: %d, c_len: %lu, vp: %lu\n", index, map->data_shape.index_len, variables_passed);
        return_val = (uint8_t*) working_frame->values[(index - map->data_shape.index_len) - variables_passed];
    }
    return return_val;
}

uint8_t set_val(frame_t* frame, frame_map_t* map_frame, map_t* map, uint8_t index, uint8_t* value, uint64_t size) { // handles setting variables of a frame given an index and size IN BYTES
    uint8_t return_val = 0;

    if(map->data_shape.index_len > index) {
        printf("Tried to set a constant variable (index: %d, value: %d)", index, *value); // we could overwrite constant variables, but that isnt the point of a constant...
        return_val = 1;
    } else {
        frame_t* working_frame = frame->root;
        uint64_t variables_passed = 0;
        if(working_frame == NULL) {
            return_val = 1;
            printf("borked");
            for(;;);
        }
        while(variables_passed + working_frame->varcount < index - map->data_shape.index_len) {
            if(working_frame->child == NULL) {
                return_val = 1; // index out of bounds - todo: remove multiple return points
                break;
            } else {
                variables_passed = working_frame->varcount;
                working_frame = working_frame->child;
            }
        }
        if(working_frame->values[(index - map->data_shape.index_len) - variables_passed] == NULL) {
            working_frame->values[(index - map->data_shape.index_len) - variables_passed] = malloc(sizeof(uint8_t) * size);
        }
        debug("[SET] This is index: %d, c_len: %lu, vp: %lu\n", index, map->data_shape.index_len, variables_passed);
        memcpy(working_frame->values[(index - map->data_shape.index_len) - variables_passed], value, size);
        // frame->values[index - map_frame->const_len]; // this is tricky. We should not set it directly to the value, but to a pointer to that, so we can handle things of indefinite bitwidth
                                                        // but thats effort and you get a lot of *((void*) (&map->...)) or something else complicated
    }
    return return_val;
}   