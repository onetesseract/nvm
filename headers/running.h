#ifndef RUNNING_H
#define RUNNING_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <map.h>
#include <string.h>
#include <frame.h>
#include <values.h>

uint8_t run_root_frame(FILE* file, map_t* map, uint64_t frame_index);
uint8_t run_nonroot_frame(FILE* file, map_t* map, uint64_t frame_index, frame_t* root);
uint8_t run_chain_off_file(FILE* file, frame_t* frame, frame_map_t* map_frame, map_t* map);

#endif