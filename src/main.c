#include <stdio.h>
#include <stdlib.h>
#include <map.h>

int main(void) {
    FILE* file = fopen("prog.neon", "rb");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    map_t map = new_map_from_file(file);
    printf("fns: %i, frames: %i", map.function_count, map.frame_count);
}