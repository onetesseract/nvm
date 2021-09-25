#include <stdint.h>
#pragma once 
// double protection!
#ifndef FRAME_H
#define FRAME_H

typedef struct frame_t { // where values are stored in runtime for a frame
    void** values;
    struct frame_t* root;
    struct frame_t* child;
    uint64_t varcount;
} frame_t;

#endif