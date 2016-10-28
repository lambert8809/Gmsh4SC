/*
  Copyright 2013 Siemens Product Lifecycle Management Software Inc. All rights reserved.
  This software and related documentation are proprietary to 
  Siemens Product Lifecycle Management Software Inc.
*/

#ifndef PARASOLID_DEBUG_H_INCLUDED
#define PARASOLID_DEBUG_H_INCLUDED


#include "parasolid_kernel.h"


/*********************************************************************/
/* TYPEDEFS */
/*********************************************************************/


/* PK_DEBUG_BODY_compare_o_t */


struct PK_DEBUG_BODY_compare_o_s
    {
    int                         o_t_version;        /* version number */
    int                         max_diffs;          /* maximum no. face pairs */
    PK_LOGICAL_t                all_tests;          /* perform all local tests */
    PK_LOGICAL_t                num_tests;          /* perform numerical tests */
    PK_LOGICAL_t                acc_dev_tests;      /* perform accurate */
    PK_LOGICAL_t                tol_dev_tests;      /* perform tolerant */
    PK_LOGICAL_t                tol_tests;          /* perform tolerance tests */
    PK_LOGICAL_t                class_tests;        /* perform class tests */
    PK_LOGICAL_t                sense_tests;        /* perform sense tests */
    PK_LOGICAL_t                missing_tests;      /* perform missing entity */
    PK_LOGICAL_t                non_match_tests;    /* perform non-matched */
    };

typedef struct PK_DEBUG_BODY_compare_o_s PK_DEBUG_BODY_compare_o_t;



/* PK_DEBUG_BODY_compare_o_m */

#define PK_DEBUG_BODY_compare_o_m(options)                 \
       ((options).o_t_version       = 1,                   \
        (options).max_diffs         = 0,                   \
        (options).all_tests         = PK_LOGICAL_true,     \
        (options).num_tests         = PK_LOGICAL_true,     \
        (options).acc_dev_tests     = PK_LOGICAL_true,     \
        (options).tol_dev_tests     = PK_LOGICAL_false,    \
        (options).tol_tests         = PK_LOGICAL_true,     \
        (options).class_tests       = PK_LOGICAL_true,     \
        (options).sense_tests       = PK_LOGICAL_true,     \
        (options).missing_tests     = PK_LOGICAL_true,     \
        (options).non_match_tests   = PK_LOGICAL_true      \
       )


/* PK_DEBUG_global_diffs_r_t */


struct PK_DEBUG_global_diffs_r_s
    {
    PK_DEBUG_diff_t          diff;
    int                      n_masters;
    int                      n_similars;
    };

typedef struct PK_DEBUG_global_diffs_r_s PK_DEBUG_global_diffs_r_t;




/* PK_DEBUG_local_diffs_r_t */


struct PK_DEBUG_local_diffs_r_s
    {
    PK_DEBUG_diff_t                 diff;
    PK_ENTITY_t                     master_entity;
    int                             master_int;
    double                          master_double;
    PK_CLASS_t                      master_class;
    PK_LOGICAL_t                    master_logical;
    PK_ENTITY_t                     similar_entity;
    int                             similar_int;
    double                          similar_double;
    PK_CLASS_t                      similar_class;
    PK_LOGICAL_t                    similar_logical;
    };

typedef struct PK_DEBUG_local_diffs_r_s PK_DEBUG_local_diffs_r_t;




/* PK_DEBUG_face_pair_r_t */


struct PK_DEBUG_face_pair_r_s
    {
    PK_FACE_t                       master_face;
    PK_FACE_t                       similar_face;
    int                             n_local_diffs;
    PK_DEBUG_local_diffs_r_t       *local_diffs;
    };

typedef struct PK_DEBUG_face_pair_r_s PK_DEBUG_face_pair_r_t;



/* PK_DEBUG_BODY_compare_r_t */


struct PK_DEBUG_BODY_compare_r_s
    {
    PK_DEBUG_global_res_t           global_result;
    int                             n_global_diffs;
    PK_DEBUG_global_diffs_r_t      *global_diffs;
    PK_DEBUG_local_res_t            local_result;
    int                             n_face_pairs;
    PK_DEBUG_face_pair_r_t         *face_pairs;
    };

typedef struct PK_DEBUG_BODY_compare_r_s PK_DEBUG_BODY_compare_r_t;




/* PK_DEBUG_data_t */

struct PK_DEBUG_data_s
    {
    PK_LOGICAL_t             is_geom_array;    /* whether geom_array has data */
    PK_GEOM_array_t          geom_array;       /* array of geoms */
    PK_LOGICAL_t             is_trim_data;     /* whether trim_data has data */
    PK_SURF_trim_data_t      trim_data;        /* trim data information */
    };

typedef struct PK_DEBUG_data_s PK_DEBUG_data_t;



/* PK_DEBUG_data_m */

#define PK_DEBUG_data_m(options)                                \
    (                                                           \
       (options).is_geom_array        = PK_LOGICAL_false,       \
       (options).geom_array.length    = 0,                      \
       (options).geom_array.array     = NULL,                   \
       (options).is_trim_data         = PK_LOGICAL_false,       \
       (options).trim_data.n_spcurves = 0,                      \
       (options).trim_data.spcurves   = NULL,                   \
       (options).trim_data.intervals  = NULL,                   \
       (options).trim_data.trim_loop  = NULL,                   \
       (options).trim_data.trim_set   = NULL                    \
    )


/* PK_DEBUG_report_start_o_t */

struct PK_DEBUG_report_start_o_s
    {
    int             o_t_version;           /* options structure version number */
    PK_LOGICAL_t    transmit_parts;        /* whether to transmit parts */
    PK_LOGICAL_t    output_as_journal;     /* whether to output the report */
    PK_LOGICAL_t    output_binary_parts;   /* whether to embed part files in */
    PK_DEBUG_output_session_t
                    output_session;        /* whether to include session data */
    PK_DEBUG_report_cb_t
                    report_cb;             /* whether to include debug */
    };
typedef struct PK_DEBUG_report_start_o_s PK_DEBUG_report_start_o_t;




/* PK_DEBUG_report_start_o_m */

#define PK_DEBUG_report_start_o_m(options)                                  \
    (                                                                       \
        (options).o_t_version              = 4,                             \
        (options).transmit_parts           = PK_LOGICAL_true,               \
        (options).output_as_journal        = PK_LOGICAL_false,              \
        (options).output_binary_parts      = PK_LOGICAL_true,               \
        (options).output_session           = PK_DEBUG_output_session_no_c,  \
        (options).report_cb                = PK_DEBUG_report_cb_no_c        \
    )


/* PK_DEBUG_shuffle_start_o_t */

struct PK_DEBUG_shuffle_start_o_s
    {
    int         o_t_version;     /* options structure version number */
    int         value;           /* shuffle behaviour value (0) */
    };
typedef struct PK_DEBUG_shuffle_start_o_s PK_DEBUG_shuffle_start_o_t;


/* PK_DEBUG_shuffle_start_o_m */

#define PK_DEBUG_shuffle_start_o_m(options) \
       ((options).o_t_version   = 1,        \
        (options).value         = 0         \
       )


/* PK_DEBUG_try_error_handler_f_t */

typedef void (*PK_DEBUG_try_error_handler_f_t)(PK_POINTER_t);


/* PK_DEBUG_try_error_handler_o_t */

struct PK_DEBUG_try_error_handler_o_s
    {
    int                         o_t_version;        /* version number */
    PK_LOGICAL_t                use_protected;      /* Call from protected code */
    PK_DEBUG_try_smp_t          smp;                /* SMP style */
    PK_LOGICAL_t                call_from_one;      /* Call from just one SMP */
    PK_LOGICAL_t                use_locks;          /* With SMP lock(s) on */
    };

typedef struct PK_DEBUG_try_error_handler_o_s PK_DEBUG_try_error_handler_o_t;



/* PK_DEBUG_try_error_handler_o_m */

#define PK_DEBUG_try_error_handler_o_m(options)                 \
       ((options).o_t_version       = 1,                        \
        (options).use_protected     = PK_LOGICAL_true,          \
        (options).smp               = PK_DEBUG_try_smp_no_c,    \
        (options).call_from_one     = PK_LOGICAL_true,          \
        (options).use_locks         = PK_LOGICAL_false          \
       )


/* PK_DEBUG_SESSION_create_cb_t */

typedef void (*PK_DEBUG_SESSION_create_cb_t)(PK_ITEM_t, PK_CLASS_t);



/* PK_DEBUG_SESSION_destroy_cb_t */

typedef void (*PK_DEBUG_SESSION_destroy_cb_t)(PK_ITEM_t, PK_CLASS_t);



/* PK_DEBUG_check_fault_t */

struct PK_DEBUG_check_fault_s
    {
    PK_check_state_t         state;        /* token indicating fault state */
    PK_ITEM_array_t          item_array;   /* array of fault items */
    };
typedef struct PK_DEBUG_check_fault_s PK_DEBUG_check_fault_t;



/* PK_DEBUG_SESSION_check_o_m */

#define PK_DEBUG_SESSION_check_o_m(options)   \
        ((options).o_t_version       = 1,     \
        (options).max_faults         = 10,    \
        (options).n_partitions       = 0,     \
        (options).partitions         = NULL,  \
        (options).roll_direction     = PK_DEBUG_roll_no_c \
        )


/* PK_DEBUG_SESSION_check_o_t */

struct PK_DEBUG_SESSION_check_o_s
{
    int o_t_version;                           /* version number */
    int max_faults;                            /* maximum number of faults (10) */
    int n_partitions;                          /* number of partitions to check */
    const PK_PARTITION_t *partitions;          /* list of partitions to check */
    PK_DEBUG_roll_direction_t roll_direction;  /* whether and the direction to */

};
typedef struct PK_DEBUG_SESSION_check_o_s PK_DEBUG_SESSION_check_o_t;


/* PK_DEBUG_SESSION_entry_cb_t */

typedef void (*PK_DEBUG_SESSION_entry_cb_t)(const char *, PK_POINTER_t);



/* PK_DEBUG_SESSION_exit_cb_t */

typedef void (*PK_DEBUG_SESSION_exit_cb_t)(const char *, PK_POINTER_t);





/*********************************************************************/
/* FUNCTIONS */
/*********************************************************************/


#ifdef __cplusplus
#define PK_linkage_m extern "C"
#else
#define PK_linkage_m extern
#endif


PK_linkage_m PK_ERROR_code_t PK_DEBUG_BODY_compare_r_f
(
/* received */
PK_DEBUG_BODY_compare_r_t *const  /*results*/     /* comparison results to free */
);
/*
This function frees the PK memory referenced by the structure.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_BODY_compare
(
/* received */
PK_BODY_t                              /*master*/,          /* master body */
PK_BODY_t                              /*similar*/,         /* similar body */
const PK_DEBUG_BODY_compare_o_t      * /*options*/,         /* options structure */
/* returned */
PK_DEBUG_BODY_compare_r_t      *const  /*results*/          /* results structure */
);
/*
This function outputs the differences between two similar bodies.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_BODY_extract_data
(
/* received */
PK_BODY_t                            /*body*/,        /* body */
/* returned */
PK_DEBUG_data_t              *const  /*data*/         /* saved data */
);
/*
This function extracts any additional data which has been associated with
the body.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_receive
(
/* received */
const char                        * /*key*/,                  /* key string */
const PK_PART_receive_o_t         * /*options*/,              /* receive options */
/* returned */
PK_DEBUG_data_t             *const  /*data*/                  /* debug data */
);
/*
This function receives a transmit file and extracts any additional data,
if no data is associated, the function will return PK_ERROR_no_data.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_transmit
(
/* received */
const char                        * /*key*/,                 /* key string */
const PK_DEBUG_data_t             * /*data*/,                /* debug data */
const PK_PART_transmit_o_t        * /*options*/              /* transmit options */
);
/*
This function saves additional data to a transmit file.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_data_f
(
/* received */
PK_DEBUG_data_t *const  /*data*/     /* data to free */
);
/*
This function frees the PK memory referenced by the structure.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_report_start
(
/* received */
const char                         * /*key*/,         /* key string */
const PK_DEBUG_report_start_o_t    * /*options*/      /* report options */
);
/*
Initialises and starts the output of debug information. Any PK calls made
between a call to this function and PK_DEBUG_report_stop will have debug
information output to the file specified by 'key'.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_report_stop
(
void
);
/*
Stops the output of debug information for PK functions. This function can only
be called after a previous call to PK_DEBUG_report_start
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_report_comment
(
/* received */
const char     * /*comment*/      /* null-terminated string to set */
);
/*
Writes a comment to the debug report file.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_shuffle_start
(
/* received */
const PK_DEBUG_shuffle_start_o_t * /*options*/  /* options structure */
);
/*
Initialises and starts the shuffling of return array arguments for some
PK functions.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_shuffle_stop
(
void
);
/*
Stops the shuffling of return array arguments.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_try_error_handler
(
/* received */
PK_DEBUG_try_error_handler_f_t         /*function*/,     /* function to be called */
PK_POINTER_t                           /*context*/,      /* context for function */
const PK_DEBUG_try_error_handler_o_t * /*options*/       /* options structure */
);
/*
This function calls the supplied function with the supplied
context from within executing Parasolid. The supplied function
is called immediately, rather than being remembered for later
use. The point of this is to allow testing of run-time error
handlers, by calling functions that cause run-time errors, or
call PK_SESSION_abort; it has no use in modelling.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_SESSION_watch_classes
(
/* received */
PK_CLASS_array_t               /*create_classes*/,    /* classes to watch */
PK_DEBUG_SESSION_create_cb_t   /*create_fn*/,         /* create callback */
PK_CLASS_array_t               /*destroy_classes*/,   /* classes to watch */
PK_DEBUG_SESSION_destroy_cb_t  /*destroy_fn*/         /* destroy callback */
);
/*
This function registers arrays of item classes which are to be watched
via two application callback functions.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_SESSION_watch_items
(
/* received */
PK_ITEM_array_t                /*create*/,            /* objects to watch */
PK_DEBUG_SESSION_create_cb_t   /*create_fn*/,         /* create callback */
PK_ITEM_array_t                /*destroy*/,           /* items to watch */
PK_DEBUG_SESSION_destroy_cb_t  /*destroy_fn*/         /* destroy callback */
);
/*
This function registers arrays of tagged items which are to be watched
via two application callback functions.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_SESSION_check
(
/* received */
const PK_DEBUG_SESSION_check_o_t * /*options*/,    /* options structure */
/* returned */
int                        *const  /*n_faults*/,   /* number of faults */
PK_DEBUG_check_fault_t    **const  /*faults*/      /* faults */
);
/*
This function checks the session and a given list of partitions.
*/

PK_linkage_m PK_ERROR_code_t PK_DEBUG_SESSION_watch_fns
(
/* received */
int                           /*n_fns*/,             /* number of functions */
const char                  * /*fns*/[],             /* functions to watch */
PK_POINTER_t                  /*entry_context*/,     /* entry context information */
PK_POINTER_t                  /*exit_context*/,      /* exit context information */
PK_DEBUG_SESSION_entry_cb_t   /*entry_fn*/,          /* entry callback */
PK_DEBUG_SESSION_exit_cb_t    /*exit_fn*/            /* exit callback */
);
/*
This function registers an array of PK functions that are to be watched
via two application callback functions.
*/



#undef PK_linkage_m


#endif /* PARASOLID_DEBUG_H_INCLUDED */


