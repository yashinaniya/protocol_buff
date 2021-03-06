/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9 at Sat Dec 16 21:02:12 2017. */

#ifndef PB_SENSOR_PB_H_INCLUDED
#define PB_SENSOR_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _Data {
    pb_callback_t SensorID;
    pb_callback_t ChannelID;
    int32_t Status;
    pb_callback_t Value;
/* @@protoc_insertion_point(struct:Data) */
} Data;

/* Default values for struct fields */

/* Initializer values for message structs */
#define Data_init_default                        {{{NULL}, NULL}, {{NULL}, NULL}, 0, {{NULL}, NULL}}
#define Data_init_zero                           {{{NULL}, NULL}, {{NULL}, NULL}, 0, {{NULL}, NULL}}

/* Field tags (for use in manual encoding/decoding) */
#define Data_SensorID_tag                        1
#define Data_ChannelID_tag                       2
#define Data_Status_tag                          3
#define Data_Value_tag                           4

/* Struct field encoding specification for nanopb */
extern const pb_field_t Data_fields[5];

/* Maximum encoded size of messages (where known) */
/* Data_size depends on runtime parameters */

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define SENSOR_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
