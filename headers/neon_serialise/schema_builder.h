#ifndef SCHEMA_BUILDER_H
#define SCHEMA_BUILDER_H

/* Generated by flatcc 0.6.1-dev FlatBuffers schema compiler for C by dvide.com */

#ifndef SCHEMA_READER_H
#include "schema_reader.h"
#endif
#ifndef FLATBUFFERS_COMMON_BUILDER_H
#include "flatbuffers_common_builder.h"
#endif
#include "flatcc/flatcc_prologue.h"
#ifndef flatbuffers_identifier
#define flatbuffers_identifier 0
#endif
#ifndef flatbuffers_extension
#define flatbuffers_extension "bin"
#endif

static const flatbuffers_voffset_t __Neon_BinaryEncoding_variables_type_required[] = { 0 };
typedef flatbuffers_ref_t Neon_BinaryEncoding_variables_type_ref_t;
static Neon_BinaryEncoding_variables_type_ref_t Neon_BinaryEncoding_variables_type_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_variables_type_table_t t);
__flatbuffers_build_table(flatbuffers_, Neon_BinaryEncoding_variables_type, 1)

static const flatbuffers_voffset_t __Neon_BinaryEncoding_frame_map_required[] = { 0 };
typedef flatbuffers_ref_t Neon_BinaryEncoding_frame_map_ref_t;
static Neon_BinaryEncoding_frame_map_ref_t Neon_BinaryEncoding_frame_map_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_frame_map_table_t t);
__flatbuffers_build_table(flatbuffers_, Neon_BinaryEncoding_frame_map, 3)

static const flatbuffers_voffset_t __Neon_BinaryEncoding_function_map_required[] = { 0 };
typedef flatbuffers_ref_t Neon_BinaryEncoding_function_map_ref_t;
static Neon_BinaryEncoding_function_map_ref_t Neon_BinaryEncoding_function_map_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_function_map_table_t t);
__flatbuffers_build_table(flatbuffers_, Neon_BinaryEncoding_function_map, 2)

static const flatbuffers_voffset_t __Neon_BinaryEncoding_map_required[] = { 0 };
typedef flatbuffers_ref_t Neon_BinaryEncoding_map_ref_t;
static Neon_BinaryEncoding_map_ref_t Neon_BinaryEncoding_map_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_map_table_t t);
__flatbuffers_build_table(flatbuffers_, Neon_BinaryEncoding_map, 4)

#define __Neon_BinaryEncoding_variables_type_formal_args , flatbuffers_uint64_vec_ref_t v0
#define __Neon_BinaryEncoding_variables_type_call_args , v0
static inline Neon_BinaryEncoding_variables_type_ref_t Neon_BinaryEncoding_variables_type_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_variables_type_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, Neon_BinaryEncoding_variables_type, Neon_BinaryEncoding_variables_type_file_identifier, Neon_BinaryEncoding_variables_type_type_identifier)

#define __Neon_BinaryEncoding_frame_map_formal_args , uint64_t v0, Neon_BinaryEncoding_variables_type_ref_t v1, flatbuffers_uint64_vec_ref_t v2
#define __Neon_BinaryEncoding_frame_map_call_args , v0, v1, v2
static inline Neon_BinaryEncoding_frame_map_ref_t Neon_BinaryEncoding_frame_map_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_frame_map_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, Neon_BinaryEncoding_frame_map, Neon_BinaryEncoding_frame_map_file_identifier, Neon_BinaryEncoding_frame_map_type_identifier)

#define __Neon_BinaryEncoding_function_map_formal_args , Neon_BinaryEncoding_variables_type_ref_t v0, uint64_t v1
#define __Neon_BinaryEncoding_function_map_call_args , v0, v1
static inline Neon_BinaryEncoding_function_map_ref_t Neon_BinaryEncoding_function_map_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_function_map_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, Neon_BinaryEncoding_function_map, Neon_BinaryEncoding_function_map_file_identifier, Neon_BinaryEncoding_function_map_type_identifier)

#define __Neon_BinaryEncoding_map_formal_args , Neon_BinaryEncoding_function_map_vec_ref_t v0, Neon_BinaryEncoding_frame_map_vec_ref_t v1, flatbuffers_uint8_vec_ref_t v2, Neon_BinaryEncoding_variables_type_ref_t v3
#define __Neon_BinaryEncoding_map_call_args , v0, v1, v2, v3
static inline Neon_BinaryEncoding_map_ref_t Neon_BinaryEncoding_map_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_map_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, Neon_BinaryEncoding_map, Neon_BinaryEncoding_map_file_identifier, Neon_BinaryEncoding_map_type_identifier)

__flatbuffers_build_vector_field(0, flatbuffers_, Neon_BinaryEncoding_variables_type_indexes, flatbuffers_uint64, uint64_t, Neon_BinaryEncoding_variables_type)

static inline Neon_BinaryEncoding_variables_type_ref_t Neon_BinaryEncoding_variables_type_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_variables_type_formal_args)
{
    if (Neon_BinaryEncoding_variables_type_start(B)
        || Neon_BinaryEncoding_variables_type_indexes_add(B, v0)) {
        return 0;
    }
    return Neon_BinaryEncoding_variables_type_end(B);
}

static Neon_BinaryEncoding_variables_type_ref_t Neon_BinaryEncoding_variables_type_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_variables_type_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (Neon_BinaryEncoding_variables_type_start(B)
        || Neon_BinaryEncoding_variables_type_indexes_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, Neon_BinaryEncoding_variables_type_end(B));
}

__flatbuffers_build_scalar_field(0, flatbuffers_, Neon_BinaryEncoding_frame_map_start_index, flatbuffers_uint64, uint64_t, 8, 8, UINT64_C(0), Neon_BinaryEncoding_frame_map)
__flatbuffers_build_table_field(1, flatbuffers_, Neon_BinaryEncoding_frame_map_variables, Neon_BinaryEncoding_variables_type, Neon_BinaryEncoding_frame_map)
__flatbuffers_build_vector_field(2, flatbuffers_, Neon_BinaryEncoding_frame_map_constant_indexes, flatbuffers_uint64, uint64_t, Neon_BinaryEncoding_frame_map)

static inline Neon_BinaryEncoding_frame_map_ref_t Neon_BinaryEncoding_frame_map_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_frame_map_formal_args)
{
    if (Neon_BinaryEncoding_frame_map_start(B)
        || Neon_BinaryEncoding_frame_map_start_index_add(B, v0)
        || Neon_BinaryEncoding_frame_map_variables_add(B, v1)
        || Neon_BinaryEncoding_frame_map_constant_indexes_add(B, v2)) {
        return 0;
    }
    return Neon_BinaryEncoding_frame_map_end(B);
}

static Neon_BinaryEncoding_frame_map_ref_t Neon_BinaryEncoding_frame_map_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_frame_map_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (Neon_BinaryEncoding_frame_map_start(B)
        || Neon_BinaryEncoding_frame_map_start_index_pick(B, t)
        || Neon_BinaryEncoding_frame_map_variables_pick(B, t)
        || Neon_BinaryEncoding_frame_map_constant_indexes_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, Neon_BinaryEncoding_frame_map_end(B));
}

__flatbuffers_build_table_field(0, flatbuffers_, Neon_BinaryEncoding_function_map_variables, Neon_BinaryEncoding_variables_type, Neon_BinaryEncoding_function_map)
__flatbuffers_build_scalar_field(1, flatbuffers_, Neon_BinaryEncoding_function_map_entry_frame_index, flatbuffers_uint64, uint64_t, 8, 8, UINT64_C(0), Neon_BinaryEncoding_function_map)

static inline Neon_BinaryEncoding_function_map_ref_t Neon_BinaryEncoding_function_map_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_function_map_formal_args)
{
    if (Neon_BinaryEncoding_function_map_start(B)
        || Neon_BinaryEncoding_function_map_entry_frame_index_add(B, v1)
        || Neon_BinaryEncoding_function_map_variables_add(B, v0)) {
        return 0;
    }
    return Neon_BinaryEncoding_function_map_end(B);
}

static Neon_BinaryEncoding_function_map_ref_t Neon_BinaryEncoding_function_map_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_function_map_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (Neon_BinaryEncoding_function_map_start(B)
        || Neon_BinaryEncoding_function_map_entry_frame_index_pick(B, t)
        || Neon_BinaryEncoding_function_map_variables_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, Neon_BinaryEncoding_function_map_end(B));
}

__flatbuffers_build_table_vector_field(0, flatbuffers_, Neon_BinaryEncoding_map_functions, Neon_BinaryEncoding_function_map, Neon_BinaryEncoding_map)
__flatbuffers_build_table_vector_field(1, flatbuffers_, Neon_BinaryEncoding_map_frames, Neon_BinaryEncoding_frame_map, Neon_BinaryEncoding_map)
__flatbuffers_build_vector_field(2, flatbuffers_, Neon_BinaryEncoding_map_data, flatbuffers_uint8, uint8_t, Neon_BinaryEncoding_map)
__flatbuffers_build_table_field(3, flatbuffers_, Neon_BinaryEncoding_map_data_shape, Neon_BinaryEncoding_variables_type, Neon_BinaryEncoding_map)

static inline Neon_BinaryEncoding_map_ref_t Neon_BinaryEncoding_map_create(flatbuffers_builder_t *B __Neon_BinaryEncoding_map_formal_args)
{
    if (Neon_BinaryEncoding_map_start(B)
        || Neon_BinaryEncoding_map_functions_add(B, v0)
        || Neon_BinaryEncoding_map_frames_add(B, v1)
        || Neon_BinaryEncoding_map_data_add(B, v2)
        || Neon_BinaryEncoding_map_data_shape_add(B, v3)) {
        return 0;
    }
    return Neon_BinaryEncoding_map_end(B);
}

static Neon_BinaryEncoding_map_ref_t Neon_BinaryEncoding_map_clone(flatbuffers_builder_t *B, Neon_BinaryEncoding_map_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (Neon_BinaryEncoding_map_start(B)
        || Neon_BinaryEncoding_map_functions_pick(B, t)
        || Neon_BinaryEncoding_map_frames_pick(B, t)
        || Neon_BinaryEncoding_map_data_pick(B, t)
        || Neon_BinaryEncoding_map_data_shape_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, Neon_BinaryEncoding_map_end(B));
}

#include "flatcc/flatcc_epilogue.h"
#endif /* SCHEMA_BUILDER_H */