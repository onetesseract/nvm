#ifndef VALUES_H
#define VALUES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <map.h>
#include <string.h>
#include <frame.h>

uint8_t* get_val(frame_t* frame, frame_map_t* map_frame, uint8_t index, map_t* map);
uint8_t set_val(frame_t* frame, frame_map_t* map_frame, map_t* map, uint8_t index, uint8_t* value, uint64_t size);

#endif