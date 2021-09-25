#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <map.h>
#include <string.h>
#include <running.h>

int main(void) {
    FILE* file = fopen("prog.neonbin", "rb");
    map_t map;
    uint64_t first_index;

    int return_val;

    if (file == NULL) {
        printf("File not found");
        return_val = 1;
    } else {
        map = new_map_from_file(file);
        debug("fns: %u, frames: %u\n", map.function_count, map.frame_count);
        debug("index: %d, argc: %lu\n", map.functions[0].frame_index, map.functions[0].arguments.index_len);
        first_index = map.functions[0].frame_index;
        debug("should be 18: %d\n", map.data_section[0]);
        debug("should be 10: %d\n", map.data_section[1]);
        debug("should be 20: %d\n", map.data_section[2]);

        debug("some frame info: %lu %lu %lu\n", map.frames[0].variables.index_len, map.frames[0].variables.indexes[0], map.frames[0].variables.indexes[1]);
        run_root_frame(file, &map, first_index);
        // todo: return codes
        return_val = 0;
    }

    return return_val;

}