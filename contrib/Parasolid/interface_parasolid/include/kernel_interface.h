/*
  Copyright 2013 Siemens Product Lifecycle Management Software Inc. All rights reserved.
  This software and related documentation are proprietary to 
  Siemens Product Lifecycle Management Software Inc.
*/

#ifndef KERNEL_INTERFACE_H_INCLUDED
#define KERNEL_INTERFACE_H_INCLUDED

#include "parasolid_typedefs.h"
#include "parasolid_tokens.h"
#include "parasolid_ifails.h"

/****************************************************/
/*                   FUNCTIONS                      */
/****************************************************/

#ifdef __cplusplus
#define KI_linkage_m extern "C"
#else
#define KI_linkage_m extern
#endif


KI_linkage_m void ADPAPE
(
/* received */                            
KI_tag_geometry            * /*pg*/,       /* B-curve or B-surface */
KI_dbl_parameter           * /*t*/,        /* split parameter */
KI_cod_papr                * /*uorv*/,     /* parameter in which to split */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ADVXED
(
/* received */                            
KI_tag_edge                * /*edge*/,     /* edge to which vertex is added */
KI_vec_position              /*point*/,    /* position vector for new vertex */
/* returned */                            
KI_tag_vertex              * /*newvrx*/,   /* new vertex added */
KI_tag_edge                * /*newedg*/,   /* new edge added */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void APPTRA
(
/* received */                            
KI_tag_list_entity         * /*entity*/,   /* entity or list of entities */
KI_tag_transform           * /*transf*/,   /* transformation to apply */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ATGETO
(
/* received */                            
int                        * /*ntopol*/,   /* number of topological entities */
KI_tag_topology              /*topol*/[],  /* topological entities */
KI_cod_logical               /*sense*/[],  /* face senses */
int                        * /*ngeom*/,    /* number of topological entities */
KI_tag_geometry              /*geom*/[],   /* geometric entities */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ATTGEO
(
/* received */                            
KI_tag_topology            * /*topol*/,    /* topological entity */
KI_tag_geometry            * /*geom*/,     /* geometric entity */
KI_cod_logical             * /*sense*/,    /* face sense */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLECHK
(
/* received */                            
KI_tag_list_edge           * /*edges*/,    /* edges to check */
int                        * /*full*/,     /* level of checking */
/* returned */                            
KI_int_nitems              * /*nerror*/,   /* number of invalid blends */
KI_tag_list_int            * /*errors*/,   /* list of failure codes, the */
                                           /* codes are given below */
KI_tag_list_edge           * /*erreds*/,   /* list of invalid edges */
KI_tag_list_entity         * /*topols*/,   /* list of tags associated with */
                                           /* the failure codes */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLECRB
(
/* received */                            
KI_tag_list_edge           * /*edges*/,    /* edges to be blended */
int                        * /*type*/,     /* blend type */
KI_dbl                     * /*range1*/,   /* blend range 1 */
KI_dbl                     * /*range2*/,   /* blend range 2 */
KI_int_nitems              * /*nprops*/,   /* number of blend properties */
KI_cod_blec                  /*props*/[],  /* array of blend properties */
KI_tag_list                  /*pvals*/[],  /* array of tags of data lists */
/* returned */                            
KI_tag_list_edge           * /*blends*/,   /* list of edges to which blends */
                                           /* have been attached */
int                        * /*nblend*/,   /* number of edges to which blends */
                                           /* have been attached */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLECVR
(
/* received */                            
KI_tag_edge                * /*edge*/,     /* edge to be blended */
KI_int_nitems              * /*npts*/,     /* number of data points */
KI_vec_position              /*points*/[], /* data points */
double                       /*values*/[], /* data values */
KI_int_nitems              * /*nprops*/,   /* number of blend properties */
KI_cod_blec                  /*props*/[],  /* array of blend properties */
KI_tag_list                  /*pvals*/[],  /* array of tags of data lists */
/* returned */                            
KI_tag_list_edge           * /*blends*/,   /* list of edges to which blends */
                                           /* have been attached */
int                        * /*nblend*/,   /* number of edges to which blends */
                                           /* have been attached */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLEENQ
(
/* received */                            
KI_tag_edge                * /*edge*/,     /* edge whose blend is required */
/* returned */                            
KI_tag_face                * /*face1*/,    /* face to left of edge */
KI_tag_face                * /*face2*/,    /* face to right of edge */
int                        * /*type*/,     /* type of blend */
double                     * /*range1*/,   /* range of blend on face1 */
double                     * /*range2*/,   /* range of blend on face2 */
KI_int_nitems              * /*nprops*/,   /* number of blend properties */
KI_tag_list_int            * /*props*/,    /* blend properties */
KI_tag_list_list           * /*pvals*/,    /* blend property values */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLEFIX
(
/* received */                            
KI_tag_body                * /*body*/,     /* body to fix blends in */
/* returned */                            
KI_int_nitems              * /*nblend*/,   /* number of blend faces */
KI_tag_list_face           * /*blends*/,   /* list of created blend faces */
KI_tag_list_list           * /*faces*/,    /* list of underlying faces */
KI_tag_list_int            * /*edges*/,    /* list of (dead) tags of edges */
KI_cod_blcc                * /*error*/,    /* first error from blending body */
KI_tag_edge                * /*err_ed*/,   /* edge associated with error */
KI_tag_topology            * /*topol*/,    /* topology associated with error */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLEFXF
(
/* received */                            
KI_tag_list_face           * /*l_wall*/,   /* list of faces in left wall */
KI_tag_list_face           * /*r_wall*/,   /* list of faces in right wall */
KI_cod_logical             * /*l_rev*/,    /* blend direction from left wall */
KI_cod_logical             * /*r_rev*/,    /* blend direction from right wall */
KI_int_nitems              * /*ntokens*/,  /* number of blending tokens */
KI_cod_fxft                  /*tokens*/[], /* blending tokens */
KI_tag_list                  /*bdata*/[],  /* data associated with tokens */
/* returned */                            
KI_cod_fxfe                * /*status*/,   /* blend success status flag */
KI_tag_list_entity         * /*s_data*/,   /* data associated with status flag */
KI_tag_list_body           * /*sheets*/,   /* the blend sheets created */
KI_int_nitems              * /*nblend*/,   /* number of blend faces created */
KI_tag_list_face           * /*blends*/,   /* the blend faces */
KI_tag_list_list           * /*unders*/,   /* list of lists of underlying data */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLEREM
(
/* received */                            
KI_tag_list_edge           * /*edges*/,    /* list of edges to remove blends from */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLNAFF
(
/* received */                            
KI_tag_edge                * /*edge*/,     /* edge */
/* returned */                            
KI_tag_list_edge           * /*iedge*/,    /* list of affected edges */
KI_int_nitems              * /*nedge*/,    /* number of edges in 'iedge' */
KI_tag_list_face           * /*iface*/,    /* list of affected faces */
KI_int_nitems              * /*nface*/,    /* number of faces in 'iface' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BLNDVX
(
/* received */                            
KI_tag_list_vertex         * /*vertex*/,   /* vertex or vertices to blend */
KI_dbl_distance            * /*radius*/,   /* blend radius */
/* returned */                            
KI_tag_list_edge           * /*neweds*/,   /* list of new edges */
KI_tag_list_vertex         * /*newvxs*/,   /* list of new vertices */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BOPBYS
(
/* received */                            
KI_tag_list_entity         * /*target*/,   /* target body or list of faces */
KI_tag_list_entity         * /*tools*/,    /* tool bodies or faces of tool body */
KI_int_nitems              * /*nopts*/,    /* number of boolean options */
KI_cod_boop                  /*opts*/[],   /* boolean option codes */
KI_tag_list_entity           /*optdta*/[], /* boolean option data lists */
/* returned */                            
KI_tag_list_body           * /*bodys*/,    /* resulting bodies */
KI_int_nitems              * /*nbodys*/,   /* number of bodies */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void BOPOLD
(
/* received */                            
KI_tag_list_entity         * /*target*/,   /* target body or list of faces */
KI_tag_list_entity         * /*tools*/,    /* tool bodies or faces of tool body */
KI_int_nitems              * /*nopts*/,    /* number of boolean options */
KI_cod_boop                  /*opts*/[],   /* boolean option codes */
KI_tag_list_entity           /*optdta*/[], /* boolean option data lists */
/* returned */                            
KI_tag_list_body           * /*bodys*/,    /* resulting bodies */
KI_int_nitems              * /*nbodys*/,   /* number of bodies */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CCLIST
(
/* received */                            
KI_tag_list                * /*head*/,     /* list to be extended */
KI_tag_list                * /*tail*/,     /* list to be appended */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CHCKEN
(
/* received */                            
KI_tag_list_entity         * /*entity*/,   /* entity (or pair of entities) to check */
KI_int_nitems              * /*mxflts*/,   /* maximum number of faults to return */
KI_int_nitems              * /*nopts*/,    /* number of option codes */
KI_cod_chop                  /*option*/[], /* array of option codes */
/* returned */                            
KI_tag_list_int            * /*faults*/,   /* tokens describing faults in body */
KI_tag_list_entity         * /*tags*/,     /* faulty components */
KI_tag_list_list           * /*pdata*/,    /* list of data lists */
KI_int_nitems              * /*nfault*/,   /* number of faults returned */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CLABYS
(
/* received */                            
KI_tag_body                * /*body1*/,    /* first body */
KI_tag_transform           * /*trans1*/,   /* transformation for 'body1' */
KI_tag_body                * /*body2*/,    /* second body */
KI_tag_transform           * /*trans2*/,   /* transformation for 'body2' */
KI_cod_logical             * /*lfull*/,    /* true if exhaustive test required */
/* returned */                            
KI_tag_list_face           * /*fclst1*/,   /* list of faces in 'body1' which */
                                           /* clash with 'body2' */
KI_tag_list_face           * /*fclst2*/,   /* list of faces in 'body2' which */
                                           /* clash with 'body1' */
KI_int_nitems              * /*nclash*/,   /* length of face lists */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CLENEN
(
/* received */                            
KI_tag_list_entity         * /*ents1*/,    /* 1st entity/list of entities */
KI_tag_list_entity         * /*ents2*/,    /* 2nd entity/list of entities */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_clop                  /*iopts*/[],  /* options */
KI_tag_list_dbl              /*optdta*/[], /* option data */
/* returned */                            
KI_dbl_distance            * /*mdist*/,    /* minimum distance */
KI_tag_list_entity         * /*elist1*/,   /* entity list */
KI_tag_list_entity         * /*elist2*/,   /* entity list */
KI_vec_position              /*entpt1*/,   /* point on 1st entity */
KI_vec_position              /*entpt2*/,   /* point on 2nd entity */
KI_dbl                       /*parms1*/[], /* parameter/s related to entpt1 */
KI_dbl                       /*parms2*/[], /* parameter/s related to entpt2 */
KI_tag_list_int            * /*props1*/,   /* properties ( 1st entity) */
KI_int_nitems              * /*nprop1*/,   /* no of properties in props1 */
KI_tag_list_int            * /*props2*/,   /* properties (2nd entity) */
KI_int_nitems              * /*nprop2*/,   /* no of properties in props2 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CLENEX
(
/* received */                            
KI_tag_list_entity         * /*ents1*/,    /* 1st entity/list of entities */
KI_tag_list_entity         * /*ents2*/,    /* 2nd entity/list of entities */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_clop                  /*iopts*/[],  /* options */
KI_tag_list_dbl              /*optdta*/[], /* option data */
/* returned */                            
KI_int_nitems              * /*nmins*/,    /* number of minima returned */
KI_tag_list_dbl            * /*min_dists*/, /* distances */
KI_tag_list_list           * /*elists1*/,  /* lists of entities */
KI_tag_list_list           * /*elists2*/,  /* lists of entities */
KI_tag_list_list           * /*entpts1*/,  /* point on 1st entity */
KI_tag_list_list           * /*entpts2*/,  /* point on 2nd entity */
KI_tag_list_list           * /*parms1*/,   /* parameter/s related to entpt1 */
KI_tag_list_list           * /*parms2*/,   /* parameter/s related to entpt2 */
KI_tag_list_list           * /*props1*/,   /* properties ( 1st entity) */
KI_tag_list_int            * /*nprops1*/,  /* no of properties in props1 */
KI_tag_list_list           * /*props2*/,   /* properties (2nd entity) */
KI_tag_list_int            * /*nprops2*/,  /* no of properties in props2 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CLPTEN
(
/* received */                            
KI_vec_position              /*point*/,    /* point */
KI_tag_list_entity         * /*ents*/,     /* entities */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_clop                  /*iopts*/[],  /* options */
KI_tag_list_dbl              /*optdta*/[], /* option data */
/* returned */                            
KI_dbl_distance            * /*mdist*/,    /* minimum distance */
KI_tag_list_entity         * /*elist*/,    /* entity list */
KI_vec_position              /*epoint*/,   /* point on entity */
KI_dbl                       /*csparm*/[], /* curve or surface parameters */
KI_tag_list_int            * /*props*/,    /* properties */
KI_int_nitems              * /*nprops*/,   /* no. of properties */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CLPTEX
(
/* received */                            
KI_vec_position              /*point*/,    /* point */
KI_tag_list_entity         * /*ents*/,     /* entity/list of entities */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_clop                  /*iopts*/[],  /* options */
KI_tag_list_dbl              /*optdta*/[], /* option data */
/* returned */                            
KI_int_nitems              * /*nmins*/,    /* number of minima returned */
KI_tag_list_dbl            * /*min_dists*/, /* distances */
KI_tag_list_list           * /*elists*/,   /* lists of entities */
KI_tag_list_list           * /*entpts*/,   /* point on entity */
KI_tag_list_list           * /*parms*/,    /* parameter/s related to entity */
KI_tag_list_list           * /*props*/,    /* properties ( 1st entity) */
KI_tag_list_int            * /*nprops*/,   /* no of properties in props */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CLPTFA
(
/* received */                            
KI_vec_position              /*point*/,    /* point */
KI_tag_face                * /*face*/,     /* face */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_clop                  /*iopts*/[],  /* estimation options */
KI_tag_list                  /*optdta*/[], /* option data */
/* returned */                            
KI_vec_position              /*fpoint*/,   /* Point on face */
KI_dbl_parameter             /*params*/[], /* surface parameters at 'point' */
KI_tag_entity              * /*topol*/,    /* topology at closest point */
KI_cod_logical             * /*ortho*/,    /* indicates whether soln orthogonal */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void COFEAT
(
/* received */                            
KI_tag_feature             * /*featre*/,   /* feature */
/* returned */                            
KI_int_nitems              * /*nitems*/,   /* number of items in feature */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void COLIST
(
/* received */                            
KI_tag_list                * /*list*/,     /* list in which to count items */
/* returned */                            
KI_int_nitems              * /*nitems*/,   /* number of items in list */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void COMENT
(
/* received */                            
KI_int_nitems              * /*nchars*/,   /* number of chars in 'coment' */
KI_chr_string                /*coment*/[], /* comment string */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void COPYEN
(
/* received */                            
KI_tag_entity              * /*oldent*/,   /* entity to be copied */
/* returned */                            
KI_tag_entity              * /*newent*/,   /* copy of entity */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRATDF
(
/* received */                            
KI_int_nitems              * /*namlen*/,   /* length of 'name' */
KI_chr_string                /*name*/[],   /* name of attribute type */
KI_int_nitems              * /*nopts*/,    /* number of option codes */
KI_cod_atop                  /*option*/[], /* array of option codes */
KI_tag_list                  /*opdata*/[], /* corresponding lists of data */
/* returned */                            
KI_tag_attrib_def          * /*type*/,     /* attribute type */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void CRBSPC
(
/* received */                            
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*order*/,    /* order of curve */
KI_int_nitems              * /*nctrl*/,    /* number of control points */
KI_dbl_coefficients          /*ctrl*/[],   /* control points */
KI_dbl_knots                 /*knots*/[],  /* knot vector */
KI_int_nitems              * /*nprops*/,   /* number of curve properties */
KI_cod_papr                  /*props*/[],  /* array of curve properties */
/* returned */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRBSPS
(
/* received */                            
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*uorder*/,   /* order of surface in u */
KI_int_order               * /*vorder*/,   /* order of surface in v */
KI_int_nitems              * /*ncol*/,     /* number of cols of control points */
KI_int_nitems              * /*nrow*/,     /* number of rows of control points */
KI_dbl_coefficients          /*ctrl*/[],   /* control points */
KI_dbl_knots                 /*uknots*/[], /* knot vector for the rows */
KI_dbl_knots                 /*vknots*/[], /* knot vector for the columns */
KI_int_nitems              * /*nprops*/,   /* number of surface properties */
KI_cod_papr                  /*props*/[],  /* array of surface properties */
/* returned */                            
KI_tag_b_surface           * /*bs*/,       /* B-surface */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRBXSO
(
/* received */                            
KI_vec_position              /*centre*/,   /* centre of base of box */
KI_vec_axis                  /*axis*/,     /* axis of box */
KI_dbl_distance            * /*width*/,    /* width of box */
KI_dbl_distance            * /*length*/,   /* length of box */
KI_dbl_distance            * /*height*/,   /* height of box */
/* returned */                            
KI_tag_body                * /*box1*/,     /* box */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRBYGE
(
/* received */                            
KI_tag_geometry            * /*geom*/,     /* curve or surface */
KI_int_nitems              * /*nopts*/,    /* number of options supplied */
KI_cod_cbop                  /*popts*/[],  /* array of options */
KI_tag_list                  /*pdata*/[],  /* array of option data */
/* returned */                            
KI_tag_body                * /*by*/,       /* wire or sheet body */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRCAPO
(
/* received */                            
double                     * /*x*/,        /* X coordinate value */
double                     * /*y*/,        /* Y coordinate value */
double                     * /*z*/,        /* Z coordinate value */
/* returned */                            
KI_tag_point               * /*point*/,    /* cartesian point */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRCICU
(
/* received */                            
KI_vec_centre                /*centre*/,   /* centre of circle */
KI_vec_axis                  /*axis*/,     /* axis direction */
KI_dbl_radius              * /*radius*/,   /* radius of circle */
/* returned */                            
KI_tag_curve               * /*circle*/,   /* circular curve */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRCMPC
(
/* received */                            
KI_int_nitems              * /*nbcs*/,     /* number of B-curves */
KI_tag_b_curve               /*bcs*/[],    /* array of B-curves */
/* returned */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRCOSO
(
/* received */                            
KI_vec_position              /*centre*/,   /* centre of base of cone */
KI_vec_axis                  /*axis*/,     /* axis of cone */
KI_dbl_radius              * /*basrad*/,   /* radius of base of cone */
KI_dbl_radius              * /*toprad*/,   /* radius of top of cone */
KI_dbl_distance            * /*height*/,   /* height of cone */
/* returned */                            
KI_tag_body                * /*cone*/,     /* cone */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRCOSU
(
/* received */                            
KI_vec_centre                /*posn*/,     /* position on cone axis */
KI_vec_axis                  /*axis*/,     /* axis direction */
KI_dbl_radius              * /*radpsn*/,   /* radius of cone at 'posn' */
KI_dbl_angle               * /*angle*/,    /* half-angle of cone ( radians ) */
/* returned */                            
KI_tag_surface             * /*cone*/,     /* conical surface */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRCPCU
(
/* received */                            
KI_tag_surface             * /*surf*/,     /*  Underlying surface. */
KI_cod_papr                * /*uorv*/,     /*  Constant parameter. */
KI_dbl                     * /*param*/,    /*  Constant parameter value. */
/* returned */                            
KI_tag_curve               * /*curve*/,    /*  Constant parameter line curve. */
KI_cod_error               * /*ifail*/     /*  failure indicator. */
);

KI_linkage_m void CRCUPC
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* general curve */
KI_vec_position              /*bounds*/[], /* start and end of curve */
/* returned */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
KI_int_nitems              * /*nseg*/,     /* number of segments used */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRCYSO
(
/* received */                            
KI_vec_position              /*centre*/,   /* centre of base of cylinder */
KI_vec_axis                  /*axis*/,     /* axis of cylinder */
KI_dbl_radius              * /*radius*/,   /* radius of cylinder */
KI_dbl_distance            * /*height*/,   /* height of cylinder */
/* returned */                            
KI_tag_body                * /*cylind*/,   /* cylinder */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRCYSU
(
/* received */                            
KI_vec_position              /*posn*/,     /* position on axis */
KI_vec_axis                  /*axis*/,     /* axis direction */
KI_dbl_radius              * /*radius*/,   /* cylinder radius */
/* returned */                            
KI_tag_surface             * /*cylind*/,   /* cylindrical surface */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CREASS
(
/* received */                            
KI_cod_tyas                * /*type*/,     /* type of assembly to create */
/* returned */                            
KI_tag_assembly            * /*assemb*/,   /* new assembly */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CREATT
(
/* received */                            
KI_tag_list_entity         * /*owners*/,   /* entity or list of entities to */
                                           /* which the attribute is to be */
                                           /* attached */
KI_tag_attrib_def          * /*type*/,     /* type of attribute */
KI_int_nitems              * /*nints*/,    /* number of integer values */
int                          /*ivals*/[],  /* array of integer values */
KI_int_nitems              * /*nreals*/,   /* number of real values */
double                       /*rvals*/[],  /* array of real values */
KI_int_nitems              * /*nstrng*/,   /* number of strings */
KI_int_nitems                /*slens*/[],  /* array of string lengths */
KI_int_nitems              * /*nchars*/,   /* number of characters */
KI_chr_string                /*chars*/[],  /* array of data for string fields */
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void CREFEA
(
/* received */                            
KI_cod_tyfe                * /*type*/,     /* type of feature */
KI_tag_part                * /*part*/,     /* part which will own feature */
/* returned */                            
KI_tag_feature             * /*featre*/,   /* newly created feature */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CREINS
(
/* received */                            
KI_tag_assembly            * /*owner*/,    /* owning assembly of new instance */
KI_tag_part                * /*part*/,     /* part to be instanced */
KI_tag_transform           * /*transf*/,   /* transform of instance */
KI_cod_tyin                * /*type*/,     /* type of instance */
/* returned */                            
KI_tag_instance            * /*instnc*/,   /* new instance */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRELCU
(
/* received */                            
KI_vec_centre                /*centre*/,   /* centre of ellipse */
KI_vec_axis                  /*axis*/,     /* axis direction */
KI_dbl_radius              * /*majrad*/,   /* major radius */
KI_vec_axis                  /*majaxi*/,   /* major axis */
KI_dbl_radius              * /*minrad*/,   /* minor radius */
/* returned */                            
KI_tag_curve               * /*elipse*/,   /* elliptical curve */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CREQSC
(
/* received */                            
KI_dbl_sc_fact             * /*scale*/,    /* scaling factor */
KI_vec_position              /*centre*/,   /* centre of scaling */
/* returned */                            
KI_tag_transform           * /*transf*/,   /* equal scaling transformation */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CREREF
(
/* received */                            
KI_vec_position              /*posn*/,     /* position on plane */
KI_vec_normal                /*normal*/,   /* normal direction */
/* returned */                            
KI_tag_transform           * /*transf*/,   /* reflection transformation */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CREROT
(
/* received */                            
KI_vec_position              /*posn*/,     /* position on axis */
KI_vec_axis                  /*axis*/,     /* axis direction */
KI_dbl_angle               * /*angle*/,    /* rotation angle (radians) */
/* returned */                            
KI_tag_transform           * /*transf*/,   /* rotation transformation */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRETFM
(
/* received */                            
double                       /*matrix*/[], /* transformation components */
/* returned */                            
KI_tag_transform           * /*transf*/,   /* the transformation */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRETRA
(
/* received */                            
KI_vec_direction             /*direct*/,   /* direction */
KI_dbl                     * /*dist*/,     /* distance */
/* returned */                            
KI_tag_transform           * /*transf*/,   /* translation transformation */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CREXSU
(
/* received */                            
KI_tag_curve               * /*profil*/,   /* curve to be extruded */
KI_vec_direction             /*direct*/,   /* extrusion direction vector */
KI_cod_logical             * /*smplfy*/,   /* simplification flag */
/* returned */                            
KI_tag_surface             * /*extsur*/,   /* resulting extruded surface */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void CRFASU
(
/* received */                            
KI_tag_face                * /*face*/,     /* face to be fixed */
/* returned */                            
KI_cod_tysu                * /*sutype*/,   /* type of surface fixed to face */
KI_tag_surface             * /*surfac*/,   /* new surface fixed to face */
KI_cod_rtlo                * /*state*/,    /* state of the body */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRFGCU
(
/* received */                            
KI_int_nchars              * /*keylen*/,   /* Length of curve key */
KI_chr_key                   /*key*/[],    /* curve key */
KI_int_nitems              * /*nspace*/,   /* Space required by foreign curve */
                                           /* (specified in doubles) */
KI_int_nitems              * /*nints*/,    /* Number of integer values */
int                          /*ivals*/[],  /* Array of integer values */
KI_int_nitems              * /*nreals*/,   /* Number of real values */
double                       /*rvals*/[],  /* Array of real values */
/* returned */                            
KI_tag_curve               * /*curve*/,    /* curve. */
KI_cod_error               * /*ifail*/     /* Failure indicator */
);

KI_linkage_m void CRFGSU
(
/* received */                            
KI_int_nchars              * /*keylen*/,   /* Length of surface key */
KI_chr_key                   /*key*/[],    /* Surface key */
KI_int_nitems              * /*nspace*/,   /* Space required by foreign surface */
                                           /* (specified in doubles) */
KI_int_nitems              * /*nints*/,    /* Number of integer values */
int                          /*ivals*/[],  /* Array of integer values */
KI_int_nitems              * /*nreals*/,   /* Number of real values */
double                       /*rvals*/[],  /* Array of real values */
/* returned */                            
KI_tag_surface             * /*surf*/,     /* surface. */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRINCU
(
/* received */                            
KI_tag_surface             * /*surf1*/,    /* surfaces to be */
KI_tag_surface             * /*surf2*/,    /* intersected */
KI_dbl_box                   /*intbox*/[], /* box of interest */
/* returned */                            
KI_tag_list_curve          * /*curves*/,   /* list of curves */
KI_int_nitems              * /*ncurve*/,   /* number of curves returned */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRKNPA
(
/* received */                            
KI_tag_list_body           * /*bods*/,     /* list of bodies */
/* returned */                            
KI_tag_list_edge           * /*eds1*/,     /* list of edges forming pattern */
KI_tag_list_edge           * /*eds2*/,     /* list of edges forming pattern */
KI_int_nitems              * /*neds*/,     /* number of edge pairs in pattern */
KI_tag_list_body           * /*negs*/,     /* list of bodies to be negated */
KI_int_nitems              * /*nnegs*/,    /* number of bodies in 'negs' */
KI_tag_list_body           * /*over*/,     /* list of bodies with no edges */
                                           /* in the pattern */
KI_int_nitems              * /*nover*/,    /* number of bodies in 'over' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRLFPS
(
/* received */                            
KI_int_nitems              * /*nbcs*/,     /* number of curves supplied */
KI_tag_b_curve               /*bcs*/[],    /* array of B-curves */
KI_int_nitems              * /*nprops*/,   /* number of surface properties */
KI_cod_papr                  /*props*/[],  /* array of surface properties */
KI_tag_list                  /*pdata*/[],  /* array of tags of data lists */
/* returned */                            
KI_tag_b_surface           * /*bs*/,       /* B-surface */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRLICU
(
/* received */                            
KI_vec_position              /*posn*/,     /* position on line */
KI_vec_direction             /*direct*/,   /* line direction */
/* returned */                            
KI_tag_curve               * /*line*/,     /* linear curve */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRLIST
(
/* received */                            
KI_cod_tyli                * /*lstype*/,   /* type of list to be created, */
                                           /* from range TYLI00 */
/* returned */                            
KI_tag_list                * /*list*/,     /* new list */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRMINO
(
/* returned */                            
KI_tag_body                * /*minob*/,    /* new minimum object */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CROFSU
(
/* received */                            
KI_tag_surface             * /*undrly*/,   /* underlying surface */
double                     * /*dstnce*/,   /* offset distance */
/* returned */                            
KI_tag_surface             * /*offsur*/,   /* offset surface */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRPLSU
(
/* received */                            
KI_vec_position              /*posn*/,     /* position on plane */
KI_vec_normal                /*normal*/,   /* normal direction */
/* returned */                            
KI_tag_surface             * /*plane*/,    /* planar surface */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRPRSO
(
/* received */                            
KI_vec_position              /*centre*/,   /* centre of prism */
KI_vec_axis                  /*axis*/,     /* axis of prism */
KI_dbl_radius              * /*radius*/,   /* radius of enclosing cylinder */
int                        * /*nsides*/,   /* number of sides */
KI_dbl_distance            * /*height*/,   /* height of prism */
/* returned */                            
KI_tag_body                * /*prism*/,    /* prism */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRPWPC
(
/* received */                            
KI_int_dimension           * /*dim*/,      /* dimension of defining vectors */
KI_int_order               * /*order*/,    /* order of curve */
KI_int_nitems              * /*nsegs*/,    /* number of segments in curve */
KI_dbl_coefficients          /*coeffs*/[],
                                           /* vectors defining the curve */
KI_cod_slba                * /*basis*/,    /* representation method */
/* returned */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRPWPS
(
/* received */                            
KI_int_dimension           * /*dim*/,      /* dimension of defining vectors */
KI_int_order               * /*uorder*/,   /* order of surface in u */
KI_int_order               * /*vorder*/,   /* order of surface in v */
KI_int_nitems              * /*ncol*/,     /* number of columns of patches */
KI_int_nitems              * /*nrow*/,     /* number of rows of patches */
KI_dbl_coefficients          /*coeffs*/[],
                                           /* vectors defining the surface */
KI_cod_slba                * /*basis*/,    /* representation method */
/* returned */                            
KI_tag_b_surface           * /*bs*/,       /* B-surface */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRRVSU
(
/* received */                            
KI_tag_curve               * /*profil*/,   /* curve to revolve */
KI_vec_position              /*point*/,    /* point on revolution axis */
KI_vec_axis                  /*direct*/,   /* direction of revolution axis */
KI_int_nitems              * /*nopts*/,    /* number of options supplied */
KI_cod_crop                  /*opts*/[],   /* array of options */
KI_tag_list                  /*optdta*/[], /* array of option data */
/* returned */                            
KI_tag_surface             * /*revsur*/,   /* resulting surface of revolution */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void CRSEPS
(
/* received */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve to sweep */
KI_vec_displacement          /*path*/,     /* translation vector */
/* returned */                            
KI_tag_b_surface           * /*bs*/,       /* result of sweep */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRSHFA
(
/* received */                            
KI_tag_list_face           * /*faces*/,    /* faces to use in sheet */
/* returned */                            
KI_tag_body                * /*sheet*/,    /* new body */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRSIPS
(
/* received */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve to swing */
KI_vec_position              /*point*/,    /* point on axis of rotation */
KI_vec_axis                  /*direct*/,   /* direction of axis of rotation */
KI_dbl_angle               * /*angle*/,    /* angle of swing (in radians) */
/* returned */                            
KI_tag_b_surface           * /*bs*/,       /* result of swing */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRSOFA
(
/* received */                            
KI_tag_list_face           * /*faces*/,    /* face(s) to copy into new body(s) */
KI_cod_sllo                * /*action*/,   /* type of action to mend wounds */
                                           /*   SLLOCP => cap */
                                           /*   SLLOGR => grow */
                                           /*   SLLOGP => grow from parent */
                                           /*   SLLORB => leave rubber */
/* returned */                            
KI_tag_list_body           * /*bodys*/,    /* new body(s) */
KI_int_nitems              * /*nbodys*/,   /* number of new bodies */
KI_tag_list_int            * /*sbodys*/,   /* state(s) of the body(s) */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRSPCU
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* basis surface for SP-curve */
int                        * /*dim*/,      /* dimension of control points */
KI_int_order               * /*order*/,    /* order of curve */
KI_int_nitems              * /*nctrl*/,    /* number of control points */
KI_dbl_coefficients          /*ctrl*/[],   /* control points */
KI_dbl_knots                 /*knots*/[],  /* knot vector */
KI_cod_logical             * /*period*/,   /* periodic flag */
KI_cod_logical             * /*split*/,    /* split flag */
/* returned */                            
KI_int_nitems              * /*nspc*/,     /* number of SP-curves returned */
KI_tag_list_curve          * /*spc*/,      /* SP-curves */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRSPPC
(
/* received */                            
KI_int_nitems              * /*npts*/,     /* number of points supplied */
KI_vec_position              /*pts*/[],    /* array of points to spline */
KI_int_nitems              * /*nprops*/,   /* number of curve properties */
KI_cod_papr                  /*props*/[],  /* array of curve properties */
KI_tag_list                  /*pdata*/[],  /* array of tags of data lists */
/* returned */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRSPPS
(
/* received */                            
KI_int_nitems              * /*ncol*/,     /* number of columns of points */
KI_int_nitems              * /*nrow*/,     /* number of rows of points */
KI_vec_position              /*pts*/[],    /* mesh of points to spline */
KI_int_nitems              * /*nprops*/,   /* number of surface properties */
KI_cod_papr                  /*props*/[],  /* array of surface properties */
KI_tag_list                  /*pdata*/[],  /* array of tags of data lists */
/* returned */                            
KI_tag_b_surface           * /*bs*/,       /* B-surface */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRSPSO
(
/* received */                            
KI_vec_position              /*centre*/,   /* centre of sphere */
KI_dbl_radius              * /*radius*/,   /* radius of sphere */
/* returned */                            
KI_tag_body                * /*sphere*/,   /* sphere */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRSPSU
(
/* received */                            
KI_vec_centre                /*centre*/,   /* centre position */
KI_dbl_radius              * /*radius*/,   /* radius of sphere */
/* returned */                            
KI_tag_surface             * /*sphere*/,   /* new spherical surface */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRSPTC
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* surface upon which 't_cu' lies */
KI_tag_curve               * /*t_cu*/,     /* trimmed curve to approximate */
double                     * /*tol*/,      /* required tolerance */
KI_cod_logical             * /*degens*/,   /* create degenerate SP-Curves */
KI_cod_logical             * /*sense*/,    /* SP_Curve sense */
/* returned */                            
KI_int_nitems              * /*nspc*/,     /* number of SP-curves returned */
KI_tag_list_curve          * /*spc*/,      /* SP-curves */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRTOBY
(
/* received */                            
KI_cod_byty                * /*b_type*/,   /* body type */
KI_tag_list_int            * /*types*/,    /* topology types */
KI_tag_list_int            * /*ids*/,      /* integer id's of entities */
KI_tag_list_list           * /*childs*/,   /* children of entities */
/* returned */                            
KI_tag_list_topology       * /*topols*/,   /* tags of created entities */
KI_cod_rtto                * /*retcod*/,   /* fault found */
KI_int_id                  * /*failid*/,   /* id of faulty  entity */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRTOSO
(
/* received */                            
KI_vec_position              /*centre*/,   /* centre of torus */
KI_vec_axis                  /*axis*/,     /* axis of torus */
KI_dbl_radius              * /*majrad*/,   /* major radius */
KI_dbl_radius              * /*minrad*/,   /* minor radius */
/* returned */                            
KI_tag_body                * /*torus*/,    /* torus */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void CRTOSU
(
/* received */                            
KI_vec_centre                /*centre*/,   /* centre position */
KI_vec_axis                  /*axis*/,     /* axis direction */
double                     * /*majrad*/,   /* annular radius */
KI_dbl_radius              * /*minrad*/,   /* radius of generating circle */
/* returned */                            
KI_tag_surface             * /*torus*/,    /* toroidal surface */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRTRCU
(
/* received */                            
KI_tag_curve               * /*basis_curve*/, /* underlying basis curve */
KI_dbl_parameter           * /*parm_1*/,   /* start parameter */
KI_dbl_parameter           * /*parm_2*/,   /* end parameter */
/* returned */                            
KI_tag_curve               * /*trimmed_curve*/, /* trimmed basis curve */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void CRTSFA
(
/* received */                            
KI_tag_surface             * /*sf*/,       /* surface of face */
KI_cod_logical             * /*sense*/,    /* sense of face */
KI_tag_list_list           * /*curves*/,   /* curves, one list for each */
                                           /* loop of face */
double                     * /*etol*/,     /* 3-space distance tolerance, */
                                           /* stored on each edge */
double                     * /*ftol*/,     /* 3-space distance tolerance */
                                           /* stored on the face */
KI_int_nitems              * /*nopts*/,    /* number of checking options */
KI_cod_tsop                  /*chopts*/[], /* checking options */
/* returned */                            
KI_tag_body                * /*body*/,     /* sheet body created */
KI_tag_face                * /*face*/,     /* face of 'by' */
KI_cod_rtts                * /*state*/,    /* state code */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void DEFCON
(
/* received */                            
KI_tag_topology            * /*parent*/,   /* parent entity */
KI_tag_entity              * /*child*/,    /* dependent entity */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DEHOSH
(
/* received */                            
KI_tag_body                * /*sheet*/,    /* Sheet body */
KI_tag_list_loop           * /*loops*/,    /* loops to be deleted */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DELCON
(
/* received */                            
KI_tag_topology            * /*parent*/,   /* parent entity */
KI_tag_entity              * /*child*/,    /* dependent entity */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DELENT
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity to delete */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DELFAS
(
/* received */                            
KI_tag_list_face           * /*faces*/,    /* face(s) to be deleted */
KI_int_nitems              * /*nopts*/,    /* number of actions in 'optdta' */
KI_cod_sllo                  /*optdta*/[], /* type of action to mend wounds */
                                           /*   SLLOCP => cap */
                                           /*   SLLOGR => grow only */
                                           /*   SLLOGS => allow shrinkage */
                                           /*   SLLORB => leave rubber */
                                           /*   SLLOLT => loops together */
                                           /*   SLLOLI => loops independent */
/* returned */                            
KI_tag_list_body           * /*bodys*/,    /* remaining body(s) */
KI_int_nitems              * /*nbodys*/,   /* number of bodies */
KI_tag_list_int            * /*sbodys*/,   /* state(s) of the body(s) */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DELIST
(
/* received */                            
KI_tag_list                * /*list*/,     /* list to delete */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DELIVL
(
/* received */                            
KI_tag_list                * /*list*/,     /* list from which to delete items */
KI_int_index               * /*startx*/,   /* position in list at which to */
                                           /* start deleting items */
KI_int_nitems              * /*nvals*/,    /* number of items to delete */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void DELSEN
(
/* received */                            
KI_tag_geometry            * /*gm*/,       /* geometry to delete */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DETGEO
(
/* received */                            
KI_tag_topology            * /*topol*/,    /* topology to detach from */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void DLENFE
(
/* received */                            
KI_tag_feature             * /*featre*/,   /* feature */
KI_tag_entity              * /*entity*/,   /* entity to be removed */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void DLORPH
(
/* received */                            
KI_cod_ty                  * /*entype*/,   /* type of orphans to be deleted, */
                                           /* TYENGE or TYADLI */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENBXEN
(
/* received */                            
KI_tag_topology            * /*entity*/,   /* entity whose box is required */
/* returned */                            
KI_dbl_box                   /*entbox*/[], /* box containing entity */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENBYTY
(
/* received */                            
KI_tag_body                * /*body*/,     /* body */
/* returned */                            
KI_cod_enby                * /*bdytyp*/,   /* type-code of body, */
                                           /* from range ENBY00 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENCONT
(
/* received */                            
KI_tag_point               * /*point*/,    /* point */
KI_tag_entity              * /*entity*/,   /* entity */
/* returned */                            
KI_cod_encl                * /*enclos*/,   /* enclosure code */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENCUPA
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* Curve for enquiry */
/* returned */                            
KI_dbl                       /*range*/[],  /* Parameter range */
KI_cod_papr                  /*bounds*/[], /* Types of bound */
KI_tag_list_int            * /*props*/,    /* Parametrisation properties */
KI_int_nitems              * /*nprops*/,   /* Number of properties */
KI_cod_error               * /*ifail*/     /* Failure code */
);

KI_linkage_m void ENDFAT
(
/* received */                            
KI_tag_attribute           * /*attrib*/,   /* attribute */
/* returned */                            
KI_tag_attrib_def          * /*type*/,     /* attribute type */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void ENDFNM
(
/* received */                            
KI_int_nitems              * /*namlen*/,   /* length of 'name' */
KI_chr_string                /*name*/[],   /* name of attribute type */
/* returned */                            
KI_tag_attrib_def          * /*type*/,     /* attribute type */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void ENDIPE
(
/* received */                            
KI_tag_geometry            * /*geom*/,     /* free form geometry */
KI_cod_padi                * /*disc*/,     /* discontinuities to return */
/* returned */                            
KI_int_nitems              * /*ndisc*/,    /* number of discontinuities found */
KI_tag_list_int            * /*uorv*/,     /* list of discontinuity types */
KI_tag_list_dbl            * /*param*/,    /* list of parameters */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENEDTY
(
/* received */                            
KI_tag_edge                * /*edge*/,     /* edge */
/* returned */                            
KI_cod_ened                * /*edtype*/,   /* type-code of edge, */
                                           /* from range ENED00 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENENTY
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity */
KI_int_nitems              * /*ltypes*/,   /* maximum length of types array */
/* returned */                            
KI_cod_ty                    /*types*/[],  /* type-codes of entity */
KI_int_nitems              * /*ntypes*/,   /* number of type-codes returned */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENEQGE
(
/* received */                            
KI_tag_geometry            * /*geom1*/,    /* first geometric item */
KI_tag_geometry            * /*geom2*/,    /* second geometric item */
/* returned */                            
KI_cod_logical             * /*same*/,     /* result. KI_true if same */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENEXEN
(
/* received */                            
KI_tag_topology            * /*entity*/,   /* face or edge */
KI_vec_direction             /*dir1*/,     /* first direction */
KI_vec_direction             /*dir2*/,     /* second direction */
KI_vec_direction             /*dir3*/,     /* third direction */
/* returned */                            
KI_vec_position              /*posn*/,     /* position of extreme point */
KI_tag_topology            * /*ext*/,      /* face, edge or vertex on */
                                           /* which extreme lies */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENFAPR
(
/* received */                            
KI_tag_face                * /*face*/,     /* face */
/* returned */                            
KI_cod_logical             * /*rectan*/,   /* parametrically rectangular flag */
KI_dbl                       /*urange*/[], /* Parameter range in u */
KI_dbl                       /*vrange*/[], /* Parameter range in v */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENLOTY
(
/* received */                            
KI_tag_loop                * /*loop*/,     /* loop */
/* returned */                            
KI_cod_enlo                * /*lptype*/,   /* type-code of loop, */
                                           /* from range ENLO00 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENPAPC
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* curve */
KI_vec_position              /*coords*/,   /* coordinates of point on curve */
/* returned */                            
KI_dbl                     * /*t*/,        /* parameter of 'coords' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENPAPS
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* surface */
KI_vec_position              /*coords*/,   /* coordinates of point on surface */
/* returned */                            
KI_dbl                     * /*u*/,        /* u parameter of 'coords' */
KI_dbl                     * /*v*/,        /* v parameter of 'coords' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENPBEN
(
/* received */                            
KI_tag_topology            * /*entity*/,   /* entity whose parametric box */
                                           /* is required */
/* returned */                            
KI_dbl                       /*ulimit*/[], /* u parametric limits */
KI_dbl                       /*vlimit*/[], /* v parametric limits */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENPIFA
(
/* received */                            
KI_tag_face                * /*face*/,     /* face */
KI_int_nitems              * /*nparms*/,   /* number of parameter pairs */
double                       /*params*/[], /* u v parameter pairs */
KI_int_nitems              * /*npvecs*/,   /* number of pvecs */
double                       /*pvecs*/[],  /* pvecs */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_pfop                  /*opts*/[],   /* options */
KI_tag_list_entity           /*optdata*/[], /* option data */
/* returned */                            
KI_cod_encl                  /*enclos*/[], /* enclosure */
KI_tag_topology              /*topol*/[],  /* sub topology */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENPOGC
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* curve enquired of */
KI_vec_position              /*coords*/,   /* position of interest on curve */
/* returned */                            
KI_vec_normal                /*tangnt*/,   /* tangent direction ratio */
KI_vec_direction             /*prnorm*/,   /* normal direction ratio */
KI_vec_normal                /*binorm*/,   /* binormal direction ratio */
KI_dbl_curvature           * /*curvat*/,   /* curvature */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENPOGS
(
/* received */                            
KI_tag_surface             * /*surfac*/,   /* surface being enquired of */
KI_vec_position              /*coords*/,   /* position of interest on surface */
/* returned */                            
KI_vec_normal                /*normal*/,   /* surface normal */
KI_vec_direction             /*prdir1*/,   /* principal direction1 */
KI_vec_direction             /*prdir2*/,   /* principal direction2 */
KI_dbl_curvature           * /*prcur1*/,   /* principal curvature1 */
KI_dbl_curvature           * /*prcur2*/,   /* principal curvature2 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENPOPC
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* curve */
KI_dbl                     * /*t*/,        /* parameter of required point */
KI_int_nitems              * /*ndrvs*/,    /* number of derivatives required */
/* returned */                            
KI_vec_derivatives           /*p*/[],      /* point and derivatives */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENPOPS
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* surface */
KI_dbl                     * /*u*/,        /* u parameter of required point */
KI_dbl                     * /*v*/,        /* v parameter of required point */
KI_int_nitems              * /*nudrvs*/,   /* number of derivs wrt u required */
KI_int_nitems              * /*nvdrvs*/,   /* number of derivs wrt v required */
KI_cod_logical             * /*nreq*/,     /* request for normal */
/* returned */                            
KI_vec_derivatives           /*p*/[],     
                                           /* point and derivatives */
KI_vec_normal                /*norm*/,     /* surface normal */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ENSHTY
(
/* received */                            
KI_tag_shell               * /*shell*/,    /* shell */
/* returned */                            
KI_cod_ensh                * /*shtype*/,   /* type-code of shell, */
                                           /* from range ENSH00 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void ENSUPA
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* Surface for enquiry */
/* returned */                            
KI_dbl                       /*urange*/[], /* Parameter range in u */
KI_dbl                       /*vrange*/[], /* Parameter range in v */
KI_cod_papr                  /*ubound*/[], /* Types of bound for u */
KI_cod_papr                  /*vbound*/[], /* Types of bound for v */
KI_tag_list_int            * /*uprops*/,   /* u parametrisation properties */
KI_int_nitems              * /*nuprop*/,   /* Number of properties in u */
KI_tag_list_int            * /*vprops*/,   /* v parametrisation properties */
KI_int_nitems              * /*nvprop*/,   /* Number of properties in v */
KI_cod_error               * /*ifail*/     /* Failure code */
);

KI_linkage_m void ENVETY
(
/* received */                            
KI_tag_vertex              * /*vertex*/,   /*  vertex */
/* returned */                            
KI_cod_enve                * /*vetype*/,   /* type-code of vertex, */
                                           /* from range ENVE00 */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void FIXIDS
(
/* received */                            
KI_tag_part                * /*part*/,     /* part in which to fix identifiers */
/* returned */                            
KI_int_nitems              * /*nfault*/,   /* number of entries in lists */
KI_tag_list_entity         * /*entys*/,    /* entities with new identifiers */
KI_tag_list_int            * /*oldids*/,   /* previous identifiers */
KI_tag_list_int            * /*newids*/,   /* new identifiers */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void FNENFE
(
/* received */                            
KI_tag_feature             * /*featre*/,   /* feature */
KI_tag_entity              * /*entity*/,   /* entity to be looked for */
/* returned */                            
KI_cod_logical             * /*found*/,    /* true if entity is in feature */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void GETMND
(
/* received */                            
KI_int_nchars              * /*keylen*/,   /* length of key */
KI_chr_key                   /*key*/[],    /* key of part */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_mdop                  /*opts*/[],   /* option codes */
/* returned */                            
KI_tag_part                * /*part*/,     /* recovered part */
KI_tag_list_int            * /*mend*/,     /* tokens describing mends */
KI_tag_list_int            * /*fault*/,    /* tokens describing faults */
KI_tag_list_entity         * /*mcomp*/,    /* mended components */
KI_tag_list_entity         * /*fcomp*/,    /* faulty components */
KI_int_nitems              * /*nmend*/,    /* number of mends returned */
KI_int_nitems              * /*nfault*/,   /* number of faults returned */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void GETMOD
(
/* received */                            
KI_int_nchars              * /*keylen*/,   /* length of key */
KI_chr_key                   /*key*/[],    /* key of part */
/* returned */                            
KI_tag_part                * /*part*/,     /* received part */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void GETSNP
(
/* received */                            
KI_int_nchars              * /*nchars*/,   /* number of characters in filename */
KI_chr_filename              /*filnam*/[], /* filename for snapshot */
int                        * /*histfl*/,   /* unused: should be zero */
KI_cod_logical             * /*statfl*/,   /* true to restore interface params */
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void GTINLI
(
/* received */                            
KI_tag_list_int            * /*list*/,     /* list from which to extract items */
KI_int_index               * /*startx*/,   /* position in list from which first */
                                           /* value is to be extracted */
KI_int_nitems              * /*nvals*/,    /* number of values to extract */
                                           /* from list */
/* returned */                            
int                          /*ivals*/[],  /* values extracted from list */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void GTRLLI
(
/* received */                            
KI_tag_list_dbl            * /*list*/,     /* list from which to extract items */
KI_int_index               * /*startx*/,   /* position in list from which first */
                                           /* value is to be extracted */
KI_int_nitems              * /*nvals*/,    /* number of values to extract */
                                           /* from list */
/* returned */                            
double                       /*rvals*/[],  /* values extracted from list */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void GTTGLI
(
/* received */                            
KI_tag_list_tag            * /*list*/,     /* list from which to extract tags */
KI_int_index               * /*startx*/,   /* position in list from which first */
                                           /* tag is to be extracted */
KI_int_nitems              * /*ntags*/,    /* number of tags to extract */
                                           /* from list */
/* returned */                            
KI_tag                       /*tags*/[],   /* values extracted from list */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void HOLLBY
(
/* received */                            
KI_tag_body                * /*body*/,     /* body to be hollowed */
KI_dbl                     * /*offset*/,   /* default offset */
KI_cod_logical             * /*check*/,    /* level of checking required */
KI_tag_list_face           * /*pierce*/,   /* faces not to be offset */
KI_tag_list_face           * /*faces*/,    /* faces offset by other amounts */
KI_tag_list_dbl            * /*dists*/,    /* list of other offset distances */
KI_dbl_distance            * /*tol*/,      /* maximum applied tolerance */
KI_int_nitems              * /*mxflts*/,   /* maximum number of entities in badtag */
/* returned */                            
KI_tag_list_entity         * /*oldfas*/,   /* list of original faces offset */
KI_tag_list_entity         * /*newfas*/,   /* list of corresponding new faces */
KI_tag_list_entity         * /*badtag*/,   /* entities which caused problems */
KI_cod_rtof                * /*state*/,    /* state of body after hollow */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void IDATEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity in which to look */
KI_tag_attrib_def          * /*type*/,     /* type of attribute to look for */
/* returned */                            
KI_tag_attribute           * /*attrib*/,   /* attribute */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void IDATLS
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity in which to look */
KI_tag_attrib_def          * /*type*/,     /* type of attribute to look for */
/* returned */                            
KI_tag_list_attribute      * /*atlist*/,   /* list of attributes */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void IDATPA
(
/* received */                            
KI_tag_part                * /*part*/,     /* part in which to look */
KI_tag_attrib_def          * /*type*/,     /* type of attribute to look for */
/* returned */                            
KI_tag_list_attribute      * /*atlist*/,   /* list of attributes */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void IDCCEN
(
/* received */                            
KI_tag_entity              * /*enty1*/,    /* first entity to look in */
KI_tag_entity              * /*enty2*/,    /* second entity to look in */
KI_cod_idty                * /*idty*/,     /* type of connection */
/* returned */                            
KI_tag_list_entity         * /*entys*/,    /* Returned list of entities */
KI_int_nitems              * /*nitems*/,   /* Number of returned entities */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDCOEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity to look in */
KI_cod_ty                  * /*contyp*/,   /* type of desired entities */
/* returned */                            
KI_tag_list_entity         * /*entys*/,    /* connected entities found */
KI_int_nitems              * /*nentys*/,   /* number found */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDCOFE
(
/* received */                            
KI_tag_edge                * /*edge*/,     /* edge */
/* returned */                            
KI_tag_curve               * /*curve*/,    /* curve */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDENID
(
/* received */                            
KI_tag_part                * /*contxt*/,   /* entity giving context for search */
KI_int_id                  * /*id*/,       /* id of required entity */
KI_cod_ty                  * /*srtype*/,   /* type of required entity */
                                           /* ( one of TYTOIN, TYTORG, TYTOSH, */
                                           /*  TYTOFA, TYTOLO, TYTOED, TYTOVX, */
                                           /*  TYGESU, TYGECU, TYGEPT, TYGETF, */
                                           /*  TYADAT, TYADLI, TYADFE ) */
/* returned */                            
KI_tag_entity              * /*entity*/,   /* required entity */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void IDFSEN
(
/* received */                            
KI_tag_body                * /*target*/,   /* target body */
KI_tag_body                * /*tool*/,     /* tool body */
KI_tag_list_edge           * /*targed*/,   /* list of common edges on target */
KI_tag_list_edge           * /*tooled*/,   /* list of common edges on tool */
KI_tag_list_vertex         * /*targvx*/,   /* list of common points on target */
KI_tag_list_vertex         * /*toolvx*/,   /* list of common points on tool */
KI_int_nitems              * /*nopts*/,    /* number of options */
KI_cod_idop                  /*opts*/[],   /* option codes */
KI_tag_list_topology       * /*topol*/,    /* topology in selected facesets */
/* returned */                            
KI_tag_list_list           * /*targsu*/,   /* surviving facesets on target */
KI_tag_list_list           * /*toolsu*/,   /* surviving facesets on tool */
KI_tag_list_edge           * /*targbo*/,   /* bounds of facesets on target */
KI_tag_list_edge           * /*toolbo*/,   /* bounds of facesets on tool */
KI_tag_list_list           * /*targrj*/,   /* rejected facesets on target */
KI_tag_list_list           * /*toolrj*/,   /* rejected facesets on tool */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void IDKYPA
(
/* received */                            
KI_int_nchars              * /*keylen*/,   /* length of key */
KI_chr_key                   /*key*/[],    /* key of part to find */
/* returned */                            
KI_tag_list_part           * /*parts*/,    /* parts found with given key */
KI_tag_list_int            * /*states*/,   /* states of parts found */
KI_int_nitems              * /*nparts*/,   /* number of parts found */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDLSID
(
/* received */                            
KI_tag_part                * /*contxt*/,   /* entity giving context for search */
KI_tag_list_int            * /*ids*/,      /* ids of required entities */
KI_cod_ty                  * /*srtype*/,   /* type of required entities */
                                           /* ( one of TYTOIN, TYTORG, TYTOSH, */
                                           /*  TYTOFA, TYTOLO, TYTOED, TYTOVX, */
                                           /*  TYGESU, TYGECU, TYGEPT, TYGETF, */
                                           /*  TYADAT, TYADLI, TYADFE ) */
/* returned */                            
KI_tag_list_entity         * /*entys*/,    /* required entities */
KI_int_nitems              * /*nitems*/,   /* number of entries in 'entys' */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void IDNCEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity to look in */
KI_cod_ty                  * /*contyp*/,   /* type of desired entities */
/* returned */                            
KI_int_nitems              * /*nentys*/,   /* number of entities found */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDPOFV
(
/* received */                            
KI_tag_vertex              * /*vertex*/,   /* vertex */
/* returned */                            
KI_tag_point               * /*point*/,    /* point */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDSCEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity to look in */
KI_cod_ty                  * /*contyp*/,   /* type of desired entity */
/* returned */                            
KI_tag_entity              * /*conent*/,   /* entity found */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDSCLS
(
/* received */                            
KI_tag_list_entity         * /*entys*/,    /* entities to look in */
KI_cod_ty                  * /*contyp*/,   /* type of desired entity */
/* returned */                            
KI_tag_list_entity         * /*conent*/,   /* entities found */
KI_int_nitems              * /*nitems*/,   /* Number of items returned */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IDSOFF
(
/* received */                            
KI_tag_face                * /*face*/,     /*  face */
/* returned */                            
KI_tag_surface             * /*surfac*/,   /* surface */
KI_cod_logical             * /*revers*/,   /* true if face normal */
                                           /* opposed to surface normal */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void IMPRNT
(
/* received */                            
KI_tag_list_entity         * /*target*/,   /* target body or list of faces */
KI_tag_list_entity         * /*tool*/,     /* tool body or list of faces */
KI_int_nitems              * /*nopts*/,    /* number of imprinting options */
KI_cod_imop                  /*opts*/[],   /* option codes */
/* returned */                            
KI_tag_list_edge           * /*targed*/,   /* corresponding edges on target */
KI_tag_list_edge           * /*tooled*/,   /* corresponding edges on tool */
KI_int_nitems              * /*nedges*/,   /* number of edges */
KI_tag_list_vertex         * /*targvx*/,   /* corresponding vertices on target */
KI_tag_list_vertex         * /*toolvx*/,   /* corresponding vertices on tool */
KI_int_nitems              * /*nverts*/,   /* number of vertices */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void INCUCU
(
/* received */                            
KI_tag_curve               * /*cu1*/,      /* curve 1 */
KI_vec_position              /*bound1*/[], /* start and end of curve 1 */
KI_tag_curve               * /*cu2*/,      /* curve 2 */
KI_vec_position              /*bound2*/[], /* start and end of curve 2 */
KI_tag_surface             * /*surf*/,     /* surface containing both curves */
KI_dbl_box                   /*intbox*/[], /* box of interest */
/* returned */                            
KI_tag_list_dbl            * /*intpts*/,   /* points of intersection */
KI_tag_list_dbl            * /*ipars1*/,   /* parameters of intersections */
                                           /* on 'cu1' */
KI_tag_list_dbl            * /*ipars2*/,   /* parameters of intersections */
                                           /* on 'cu2' */
KI_tag_list_int            * /*incods*/,   /* tokens describing intersections */
KI_int_nitems              * /*nintpt*/,   /* number of points returned */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void INCUFA
(
/* received */                            
KI_tag_curve               * /*cu*/,       /* curve */
KI_vec_position              /*bound*/[],  /* start and end of curve */
KI_tag_face                * /*face*/,     /* face */
/* returned */                            
KI_tag_list_dbl            * /*intpts*/,   /* points of intersection */
KI_tag_list_dbl            * /*cuparm*/,   /* curve parameters at ints. */
KI_tag_list_dbl            * /*suparm*/,   /* surface parameters at ints. */
KI_tag_list_int            * /*incods*/,   /* tokens describing intersections */
KI_tag_list_entity         * /*topol*/,    /* entity intersected */
KI_int_nitems              * /*nintpt*/,   /* number of points returned */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void INCUSU
(
/* received */                            
KI_tag_curve               * /*cu*/,       /* curve */
KI_vec_position              /*bound*/[],  /* start and end of curve */
KI_tag_surface             * /*surf*/,     /* surface */
KI_dbl_box                   /*intbox*/[], /* box of interest */
/* returned */                            
KI_tag_list_dbl            * /*intpts*/,   /* points of intersection */
KI_tag_list_dbl            * /*cuparm*/,   /* curve parameters at ints. */
KI_tag_list_dbl            * /*suparm*/,   /* surface parameters at ints. */
KI_tag_list_int            * /*incods*/,   /* tokens describing intersections */
KI_int_nitems              * /*nintpt*/,   /* number of points returned */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void INFAFA
(
/* received */                            
KI_tag_face                * /*face1*/,    /* face 1 */
KI_tag_face                * /*face2*/,    /* face 2 */
KI_int_nitems              * /*nopts*/,    /* number of options supplied */
KI_cod_inop                  /*opts*/[],   /* array of options */
KI_tag_list_dbl              /*optdat*/[], /* options data */
/* returned */                            
KI_int_nitems              * /*npts*/,     /* number of intersection points */
KI_tag_list_dbl            * /*pts*/,      /* list of intersection pts */
KI_int_nitems              * /*nintcu*/,   /* number of intersection curves */
KI_tag_list_curve          * /*intcu*/,    /* list of intersection curves */
KI_tag_list                * /*intty*/,    /* list of types of int curves */
KI_cod_error               * /*ifail*/     /* returned - failure indicator */
);

KI_linkage_m void INSUFA
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* surface */
KI_tag_face                * /*face*/,     /* face */
KI_int_nitems              * /*nopts*/,    /* number of options supplied */
KI_cod_inop                  /*opts*/[],   /* array of options */
KI_tag_list_dbl              /*optdat*/[], /* options data */
/* returned */                            
KI_int_nitems              * /*npts*/,     /* number of intersection points */
KI_tag_list_dbl            * /*pts*/,      /* list of intersection pts */
KI_int_nitems              * /*nintcu*/,   /* number of intersection curves */
KI_tag_list_curve          * /*intcu*/,    /* list of intersection curves */
KI_tag_list                * /*intty*/,    /* list of types of int curves */
KI_cod_error               * /*ifail*/     /* returned - failure indicator */
);

KI_linkage_m void INSUSU
(
/* received */                            
KI_tag_surface             * /*surf1*/,    /* surface 1 */
KI_tag_surface             * /*surf2*/,    /* surface 2 */
KI_int_nitems              * /*nopts*/,    /* number of options supplied */
KI_cod_inop                  /*opts*/[],   /* array of options */
KI_tag_list_dbl              /*optdat*/[], /* options data */
/* returned */                            
KI_int_nitems              * /*npts*/,     /* number of intersection points */
KI_tag_list_dbl            * /*pts*/,      /* list of intersection pts */
KI_int_nitems              * /*nintcu*/,   /* number of intersection curves */
KI_tag_list_curve          * /*intcu*/,    /* list of intersection curves */
KI_tag_list                * /*intty*/,    /* list of types of int curves */
KI_cod_error               * /*ifail*/     /* returned - failure indicator */
);

KI_linkage_m void INTBYS
(
/* received */                            
KI_tag_body                * /*targby*/,   /* body to be modified */
KI_tag_list_body           * /*tolbys*/,   /* body or list of bodies */
                                           /* to modify 'targby' */
/* returned */                            
KI_tag_assembly            * /*assemb*/,   /* assembly of resulting bodies */
KI_int_nitems              * /*nbodys*/,   /* number of bodies in 'assemb' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void KABORT
(
/* received */                            
KI_cod_slab                * /*reason*/,   /* specifies reason for abort : */
                                           /*   SLABUI for user-interrupt */
                                           /*   SLABRE for run-time error */
                                           /*   SLABFE for Frustrum error */
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void KNITEN
(
/* received */                            
KI_cod_byty                * /*type*/,     /* type of result body (solid/sheet) */
KI_tag_body                * /*target*/,   /* desired result body */
KI_tag_list_edge           * /*eds1*/,     /* edges to be knitted which survive */
KI_tag_list_edge           * /*eds2*/,     /* and those which are destroyed */
KI_cod_logical             * /*shchk*/,    /* KI_true if a shell connectivity */
                                           /* check required on result body */
/* returned */                            
KI_cod_rtkn                * /*state*/,    /* ok (RTKNOK) / incomplete (RTKNIN) */
KI_tag_list_edge           * /*fldeds*/,   /* list of unknitted edges */
KI_int_nitems              * /*nfld*/,     /* number in above list */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void LEVASS
(
/* received */                            
KI_tag_assembly            * /*assemb*/,   /* assembly to level */
/* returned */                            
KI_tag_assembly            * /*result*/,   /* new levelled assembly */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void MASSPR
(
/* received */                            
KI_tag_list_entity         * /*entity*/,   /* entity or list of entities */
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_maop                  /*iopts*/[],  /* mass property request options */
double                     * /*accrcy*/,   /* accuracy parameter, 0.0 - 1.0 */
/* returned */                            
KI_tag_list_dbl            * /*periph*/,   /* size of periphery of entity */
KI_tag_list_dbl            * /*amount*/,   /* size of entity */
KI_tag_list_dbl            * /*mass*/,     /* mass */
KI_tag_list_dbl            * /*cofg*/,     /* centre of gravity */
KI_tag_list_dbl            * /*inert*/,    /* inertia tensor at cofg */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void MENDEN
(
/* received */                            
KI_tag_list_topology       * /*topol*/,    /* body or list of edges */
KI_cod_logical             * /*repopt*/,   /* option to replace all geometry */
/* returned */                            
KI_tag_list_edge           * /*fixeds*/,   /* list of fixed edges */
KI_tag_list_vertex         * /*fixvxs*/,   /* list of fixed vertices */
KI_tag_list_edge           * /*ftyeds*/,   /* list of faulty edges */
KI_tag_list_vertex         * /*ftyvxs*/,   /* list of faulty vertices */
KI_tag_list_int            * /*edtoks*/,   /* token list for faulty edges */
KI_tag_list_int            * /*vxtoks*/,   /* token list for faulty vertices */
KI_tag_list_geometry       * /*oldgeo*/,   /* list of discarded geometry */
KI_int_nitems              * /*nfixed*/,   /* number of fixed edges */
KI_int_nitems              * /*nfixvx*/,   /* number of fixed vertices */
KI_int_nitems              * /*nftyed*/,   /* number of faulty edges */
KI_int_nitems              * /*nftyvx*/,   /* number of faulty vertices */
KI_int_nitems              * /*nold*/,     /* number of discarded geometries */
KI_cod_rtmd                * /*retcod*/,   /* final state of body */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void MERGEN
(
/* received */                            
KI_tag_topology            * /*entity*/,   /* entity to merge */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void NEGENT
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity to be negated */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OFFABY
(
/* received */                            
KI_tag_body                * /*body*/,     /* body to be offset */
KI_dbl                     * /*offset*/,   /* default offset */
KI_cod_logical             * /*check*/,    /* level of checking required */
KI_tag_list_face           * /*fixed*/,    /* faces not to be offset */
KI_tag_list_face           * /*faces*/,    /* faces offset by other amounts */
KI_tag_list_dbl            * /*dists*/,    /* list of other offset distances */
KI_dbl_distance            * /*tol*/,      /* maximum applied tolerance */
KI_int_nitems              * /*mxflts*/,   /* maximum number of entities in badtag */
/* returned */                            
KI_tag_list_entity         * /*badtag*/,   /* entities which caused problems */
KI_cod_rtof                * /*state*/,    /* state of body after offset */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUATDF
(
/* received */                            
KI_tag_attrib_def          * /*type*/,     /* attribute type */
KI_int_nitems              * /*bufsiz*/,   /* amount of space available for */
                                           /* name */
/* returned */                            
KI_chr_string                /*name*/[],   /* name of type */
KI_int_nitems              * /*namlen*/,   /* length of type name */
KI_tag_list_int            * /*option*/,   /* list of option codes */
KI_tag_list_list           * /*opdata*/,   /* corresponding list of data-lists */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUBBCO
(
/* returned */                            
KI_tag_list_int            * /*ents*/,     /* entity types being bulletined */
KI_tag_list_list           * /*events*/,   /* their bulletinning events */
KI_int_nitems              * /*nents*/,    /* length of the above lists */
KI_tag_list_int            * /*opts*/,     /* current control options */
KI_int_nitems              * /*nopts*/,    /* no of control options */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUBBEV
(
/* received */                            
KI_cod_logical             * /*empty*/,    /* true if bulletin board is to */
                                           /* be emptied after being output */
/* returned */                            
KI_int_nitems              * /*nevent*/,   /* no of recorded events */
KI_tag_list_int            * /*events*/,   /* recorded event tokens */
KI_tag_list_int            * /*nperev*/,   /* no of entities at each event */
KI_int_nitems              * /*nents*/,    /* total no of entities recorded */
KI_tag_list_tag            * /*ents*/,     /* entities recorded */
KI_tag_list_int            * /*enttyp*/,   /* entity types */
KI_tag_list_int            * /*usflds*/,   /* entity user fields */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUBLSS
(
/* received */                            
KI_tag_surface             * /*surfac*/,   /* blending surface */
/* returned */                            
KI_cod_tybl                * /*bltype*/,   /* blend type */
KI_tag_surface             * /*ssurf1*/,   /* first supporting surface */
KI_tag_surface             * /*ssurf2*/,   /* second supporting surface */
KI_tag_surface             * /*ssurf3*/,   /* third supporting surface */
KI_tag_list_int            * /*iipa12*/,   /* integer parameters for ssurf1,2 */
KI_tag_list_int            * /*iipa23*/,   /* integer parameters for ssurf2,3 */
KI_tag_list_int            * /*iipa31*/,   /* integer parameters for ssurf3,1 */
KI_int_nitems              * /*nipars*/,   /* length of int parameter lists */
KI_tag_list_dbl            * /*irpa12*/,   /* double parameters for ssurf1,2 */
KI_tag_list_dbl            * /*irpa23*/,   /* double parameters for ssurf2,3 */
KI_tag_list_dbl            * /*irpa31*/,   /* double parameters for ssurf3,1 */
KI_int_nitems              * /*nrpars*/,   /* length of real parameter lists */
KI_cod_logical             * /*sense*/,    /* surface sense. explained below */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUBSCU
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* curve */
KI_dbl_distance            * /*tol*/,      /* tolerance for approximation */
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_srop                  /*iopts*/[],  /* conversion options */
/* returned */                            
KI_tag_list_dbl            * /*ctrl*/,     /* control points */
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*order*/,    /* order of bspline curve */
KI_int_nitems              * /*nctrl*/,    /* number of control points */
KI_tag_list_dbl            * /*knots*/,    /* knot vector */
KI_tag_list_int            * /*props*/,    /* list of curve properties */
KI_int_nitems              * /*nprops*/,   /* number of curve properties */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUBSED
(
/* received */                            
KI_tag_edge                * /*edge*/,     /* edge of curve */
KI_dbl_distance            * /*tol*/,      /* tolerance for approximation */
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_srop                  /*iopts*/[],  /* conversion options */
/* returned */                            
KI_tag_list_dbl            * /*ctrl*/,     /* control points */
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*order*/,    /* order of bspline curve */
KI_int_nitems              * /*nctrl*/,    /* number of control points */
KI_tag_list_dbl            * /*knots*/,    /* knot vector */
KI_tag_list_int            * /*props*/,    /* list of curve properties */
KI_int_nitems              * /*nprops*/,   /* number of curve properties */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUBSFA
(
/* received */                            
KI_tag_face                * /*face*/,     /* face */
KI_dbl_distance            * /*tol*/,      /* tolerance for approximations */
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_srop                  /*iopts*/[],  /* conversion options */
/* returned */                            
KI_tag_list_dbl            * /*ctrl*/,     /* control points */
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*uorder*/,   /* order of surface patches in u */
KI_int_order               * /*vorder*/,   /* order of surface patches in v */
KI_int_nitems              * /*ncol*/,     /* number of cols of control points */
KI_int_nitems              * /*nrow*/,     /* number of rows of control points */
KI_tag_list_dbl            * /*uknots*/,   /* knot vector in the u direction */
KI_tag_list_dbl            * /*vknots*/,   /* knot vector in the v direction */
KI_tag_list_int            * /*props*/,    /* list of surface properties */
KI_int_nitems              * /*nprops*/,   /* number of surface properties */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUBSPC
(
/* received */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
/* returned */                            
KI_tag_list_dbl            * /*ctrl*/,     /* control points */
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*order*/,    /* order of curve */
KI_int_nitems              * /*nctrl*/,    /* number of control points */
KI_tag_list_dbl            * /*knots*/,    /* knot values */
KI_tag_list_int            * /*props*/,    /* list of curve properties */
KI_int_nitems              * /*nprops*/,   /* number of curve properties */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUBSPS
(
/* received */                            
KI_tag_b_surface           * /*bs*/,       /* B-surface */
/* returned */                            
KI_tag_list_dbl            * /*ctrl*/,     /* control points */
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*uorder*/,   /* order of surface in u */
KI_int_order               * /*vorder*/,   /* order of surface in v */
KI_int_nitems              * /*ncol*/,     /* number of cols of control points */
KI_int_nitems              * /*nrow*/,     /* number of rows of control points */
KI_tag_list_dbl            * /*uknots*/,   /* knot vector in the u direction */
KI_tag_list_dbl            * /*vknots*/,   /* knot vector in the v direction */
KI_tag_list_int            * /*props*/,    /* list of surface properties */
KI_int_nitems              * /*nprops*/,   /* number of surface properties */
KI_cod_logical             * /*sense*/,    /* surface sense */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUBSSU
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* surface */
KI_dbl                       /*urange*/[], /* urange of surface */
KI_dbl                       /*vrange*/[], /* vrange of surface */
KI_dbl_distance            * /*tol*/,      /* tolerance for approximations */
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_srop                  /*iopts*/[],  /* conversion options */
/* returned */                            
KI_tag_list_dbl            * /*ctrl*/,     /* control points */
KI_int_dimension           * /*dim*/,      /* dimension of control points */
KI_int_order               * /*uorder*/,   /* order of surface patches in u */
KI_int_order               * /*vorder*/,   /* order of surface patches in v */
KI_int_nitems              * /*ncol*/,     /* number of cols of control points */
KI_int_nitems              * /*nrow*/,     /* number of rows of control points */
KI_tag_list_dbl            * /*uknots*/,   /* knot vector in the u direction */
KI_tag_list_dbl            * /*vknots*/,   /* knot vector in the v direction */
KI_tag_list_int            * /*props*/,    /* list of surface properties */
KI_int_nitems              * /*nprops*/,   /* number of surface properties */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUCOCU
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* curve to be output */
KI_vec_position              /*start*/,    /* starts from here */
KI_vec_position              /*end*/,      /* ends here */
double                     * /*ctol*/,     /* max permitted chordal error */
double                     * /*atol*/,     /* max permitted angular error */
double                     * /*stol*/,     /* max permitted step length */
/* returned */                            
KI_tag_list_dbl            * /*posns*/,    /* list of vector components */
KI_int_nitems              * /*npos*/,     /* number of items in list */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUCPCU
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* Tag of constant parameter curve */
/* returned */                            
KI_tag_surface             * /*surf*/,     /* Underlying surface */
KI_cod_papr                * /*uorv*/,     /* Constant u or constant v */
KI_dbl                     * /*param*/,    /* Parameter value */
KI_cod_logical             * /*sense*/,    /* Curve sense */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUEXSU
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* extruded surface to output */
/* returned */                            
KI_tag_curve               * /*profil*/,   /* curve extruded */
KI_vec_direction             /*path*/,     /* direction of sweep */
KI_cod_logical             * /*sense*/,    /* surface sense */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUFEAT
(
/* received */                            
KI_tag_feature             * /*featre*/,   /* feature */
/* returned */                            
KI_cod_tyfe                * /*fetype*/,   /* type-code of feature */
KI_tag_list_entity         * /*entys*/,    /* list of entities in feature */
KI_int_nitems              * /*nentys*/,   /* number of items in 'entys' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUFGCU
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* Foreign curve. */
KI_int_nchars              * /*arrlen*/,   /* Length of input key array. */
/* returned */                            
KI_chr_key                   /*key*/[],    /* Curve key. */
KI_int_nchars              * /*keylen*/,   /* Length of curve key. */
KI_tag_list_int            * /*ivals*/,    /* List of integer values. */
KI_tag_list_dbl            * /*rvals*/,    /* List of real values. */
KI_cod_logical             * /*sense*/,    /* Curve sense. */
KI_tag_transform           * /*tf*/,       /* Curve transformation. */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUFGSU
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* Foreign surface. */
KI_int_nchars              * /*arrlen*/,   /* Length of input key array. */
/* returned */                            
KI_chr_key                   /*key*/[],    /* Surface key. */
                                           /* (truncated if necessary) */
KI_int_nchars              * /*keylen*/,   /* True length of surface key. */
KI_tag_list_int            * /*ivals*/,    /* List of integer values. */
KI_tag_list_dbl            * /*rvals*/,    /* List of real values. */
KI_cod_logical             * /*sense*/,    /* Surface sense. */
KI_tag_transform           * /*tf*/,       /* Surface transformation. */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUFINF
(
/* received */                            
KI_int_nchars              * /*nchars*/,   /* number of characters in filename */
KI_chr_filename              /*filnam*/[], /* filename */
int                        * /*guise*/,    /* what sort of file it is */
int                        * /*format*/,   /* text or binary */
KI_cod_slfi                * /*selcod*/,   /* selection code specifying what */
                                           /* information is wanted */
/* returned */                            
int                        * /*ival*/,     /* returned information (integer) */
double                     * /*rval*/,     /* not yet used */
char                         /*string*/[], /* not yet used */
KI_int_nchars              * /*nstrng*/,   /* not yet used */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUGEEF
(
/* received */                            
KI_tag_topology            * /*ed_fn*/,    /* edge or fin being queried */
KI_cod_logical             * /*parms*/,    /* request for parameters */
/* returned */                            
KI_tag_curve               * /*curve*/,    /* tag of curve */
KI_cod_tycu                * /*cutype*/,   /* type of curve */
KI_vec_position              /*start*/,    /* start position */
KI_dbl                     * /*st_t*/,     /* parameter of 'start' */
KI_vec_position              /*end*/,      /* end position */
KI_dbl                     * /*end_t*/,    /* parameter of 'end' */
KI_cod_logical             * /*sense*/,    /* true if 'curve' is in same */
                                           /* direction as 'ed_fn' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUGESU
(
/* received */                            
KI_tag_surface             * /*surfac*/,   /* surface to output */
/* returned */                            
KI_tag_list_int            * /*sftype*/,   /* type and subtypes of surface */
KI_int_nitems              * /*ntypes*/,   /* number of entries in 'sftype' */
KI_tag_list_int            * /*codes*/,    /* codes formatting return data */
KI_int_nitems              * /*ncode*/,    /* number of format codes */
KI_tag_list_int            * /*ints*/,     /* integer data */
KI_tag_list_dbl            * /*reals*/,    /* real data */
KI_tag_list_geometry       * /*geoms*/,    /* underlying geometries */
KI_tag_list_curve          * /*singc*/,    /* list of singular curves */
KI_int_nitems              * /*nsingc*/,   /* number of singular curves */
KI_tag_list_dbl            * /*singp*/,    /* singularities */
KI_tag_list_curve          * /*singo*/,    /* owners of singularities */
KI_int_nitems              * /*nsingp*/,   /* number of singularities */
KI_cod_logical             * /*sense*/,    /* surface sense */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUIDEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* entity whose id is required */
/* returned */                            
KI_int_id                  * /*id*/,       /* id of specified entity */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUIDLS
(
/* received */                            
KI_tag_list_entity         * /*entys*/,    /* entities whose ids are required */
/* returned */                            
KI_tag_list_int            * /*ids*/,      /* ids of specified entities */
KI_int_nitems              * /*nids*/,     /* number of entries in 'ids' */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUINTP
(
/* received */                            
KI_cod_slip                * /*pnum*/,     /* parameter code */
/* returned */                            
int                        * /*ival*/,     /* integer value of parameter */
double                     * /*rval*/,     /* real value of parameter */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OULERR
(
/* received */                            
KI_cod_sler                * /*selcod*/,   /* enquiry code */
/* returned */                            
int                        * /*ival*/,     /* integer value */
char                         /*string*/[], /* null-terminated character string */
KI_int_nchars              * /*nchars*/,   /* length of character string */
                                           /* (excluding terminal null) */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUMODP
(
/* received */                            
KI_cod_slmp                * /*pnum*/,     /* parameter code */
/* returned */                            
int                        * /*ival*/,     /* integer value of parameter */
double                     * /*rval*/,     /* real value of parameter */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUOFSU
(
/* received */                            
KI_tag_surface             * /*offset*/,   /* offset surface */
/* returned */                            
KI_tag_surface             * /*under*/,    /* underlying surface */
KI_dbl                     * /*dist*/,     /* offset distance */
KI_cod_logical             * /*sense*/,    /* surface sense */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUPART
(
/* received */                            
KI_tag_part                * /*part*/,     /* part to output */
KI_int_nchars              * /*buflen*/,   /* length of key array */
/* returned */                            
KI_int_nchars              * /*keylen*/,   /* length of key */
KI_chr_key                   /*key*/[],    /* key of part */
KI_cod_enst                * /*state*/,    /* state of part */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUPWPC
(
/* received */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
KI_cod_slba                * /*basis*/,    /* representation method */
/* returned */                            
KI_tag_list_dbl            * /*coeffs*/,   /* vectors defining the curve */
KI_int_dimension           * /*dim*/,      /* dimension of defining vectors */
KI_int_order               * /*order*/,    /* order of curve */
KI_int_nitems              * /*nseg*/,     /* number of segments in curve */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUPWPS
(
/* received */                            
KI_tag_b_surface           * /*bs*/,       /* B-surface */
KI_cod_slba                * /*basis*/,    /* representation method */
/* returned */                            
KI_tag_list_dbl            * /*coeffs*/,   /* vectors defining the surface */
KI_int_dimension           * /*dim*/,      /* dimension of defining vectors */
KI_int_order               * /*uorder*/,   /* order of surface in u */
KI_int_order               * /*vorder*/,   /* order of surface in v */
KI_int_nitems              * /*ncol*/,     /* number of columns of patches */
KI_int_nitems              * /*nrow*/,     /* number of rows of patches */
KI_cod_logical             * /*sense*/,    /* surface sense */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OURVSU
(
/* received */                            
KI_tag_surface             * /*surf*/,     /* spun surface to output */
/* returned */                            
KI_tag_curve               * /*profil*/,   /* curve revolved */
KI_vec_position              /*point*/,    /* point on revolution axis */
KI_vec_axis                  /*direct*/,   /* direction of revolution axis */
KI_cod_logical             * /*sense*/,    /* surface sense */
KI_int_nitems              * /*nsings*/,   /* number of singularities */
KI_tag_list_dbl            * /*parms*/,    /* parameter range on profile */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUSPCU
(
/* received */                            
KI_tag_curve               * /*spc*/,      /* SP-curve */
/* returned */                            
KI_tag_surface             * /*surf*/,     /* basis surface of SP-curve */
KI_tag_list_dbl            * /*ctrl*/,     /* control points */
int                        * /*dim*/,      /* vertex dimension (2 or 3) */
KI_int_order               * /*order*/,    /* order of curve */
KI_int_nitems              * /*nctrl*/,    /* number of control points */
KI_tag_list_dbl            * /*knots*/,    /* knot values */
KI_cod_logical             * /*period*/,   /* periodic flag */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUSPPC
(
/* received */                            
KI_tag_b_curve             * /*bc*/,       /* B-curve */
/* returned */                            
KI_tag_list_dbl            * /*pts*/,      /* spline points */
KI_int_nitems              * /*npts*/,     /* number of spline points */
KI_tag_list_int            * /*props*/,    /* curve properties */
KI_tag_list_list           * /*pdata*/,    /* list of data lists */
KI_int_nitems              * /*nprops*/,   /* number of curve properties */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUSPPS
(
/* received */                            
KI_tag_b_surface           * /*bs*/,       /* B-surface */
/* returned */                            
KI_tag_list_dbl            * /*pts*/,      /* mesh of spline points */
KI_int_nitems              * /*ncol*/,     /* number of columns of points */
KI_int_nitems              * /*nrow*/,     /* number of rows of points */
KI_tag_list_int            * /*props*/,    /* surface properties */
KI_tag_list_list           * /*pdata*/,    /* list of data lists */
KI_int_nitems              * /*nprops*/,   /* number of surface properties */
KI_cod_logical             * /*sense*/,    /* surface sense */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUSTAT
(
/* received */                            
KI_cod_slst                * /*selcod*/,   /* selection code specifying what */
                                           /* information is wanted */
/* returned */                            
int                        * /*ival*/,     /* returned information (integer) */
double                     * /*rval*/,     /* returned information (double) */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUTATT
(
/* received */                            
KI_tag_attribute           * /*attrib*/,   /* attribute */
KI_int_nitems              * /*bufsiz*/,   /* amount of space available in */
                                           /* chars */
/* returned */                            
KI_tag_entity              * /*owner*/,    /* entity to which attribute is */
                                           /* attached */
KI_tag_list_int            * /*ivals*/,    /* list of integer values */
KI_tag_list_dbl            * /*rvals*/,    /* list of real values */
KI_tag_list_int            * /*slens*/,    /* list of string lengths */
KI_chr_string                /*chars*/[],  /* array of data for string fields */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUTBUB
(
/* received */                            
KI_cod_logical             * /*empty*/,    /* true if bulletin board is to */
                                           /* be emptied after being output */
/* returned */                            
KI_tag_list_tag            * /*nwtags*/,   /* tags of new entities */
KI_tag_list_tag            * /*chtags*/,   /* tags of changed entities */
KI_tag_list_tag            * /*dltags*/,   /* tags of deleted entities */
KI_tag_list_int            * /*nwtyps*/,   /* types of new entities */
KI_tag_list_int            * /*chtyps*/,   /* types of changed entities */
KI_tag_list_int            * /*dltyps*/,   /* types of deleted entities */
KI_tag_list_int            * /*nwufds*/,   /* user fields of new entities */
KI_tag_list_int            * /*chufds*/,   /* user fields of changed entities */
KI_tag_list_int            * /*dlufds*/,   /* user fields of deleted entities */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void OUTCUR
(
/* received */                            
KI_tag_curve               * /*curve*/,    /* curve to be output */
/* returned */                            
KI_cod_tycu                * /*cutype*/,   /* type of curve */
KI_vec                       /*vec1*/,     /* first vector defining curve */
KI_vec                       /*vec2*/,     /* second vector defining curve */
KI_vec                       /*vec3*/,     /* third vector defining curve */
double                     * /*d1*/,       /* first double defining curve */
double                     * /*d2*/,       /* second double defining curve */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUTLEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* can be face, edge or vertex */
/* returned */                            
double                     * /*tol*/,      /* returned tolerance value */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUTPOI
(
/* received */                            
KI_tag_point               * /*point*/,    /* point to be output */
/* returned */                            
KI_cod_typt                * /*pttype*/,   /* type of point */
KI_vec_position              /*defn*/,     /* point coords */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUTRAN
(
/* received */                            
KI_tag_transform           * /*transf*/,   /* transformation to be output */
/* returned */                            
double                       /*matrix*/[], /* transformation matrix array */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUTRCU
(
/* received */                            
KI_tag_curve               * /*trimmed_curve*/, /* trimmed curve to be output */
/* returned */                            
KI_tag_curve               * /*basis_curve*/, /* underlying curve */
KI_vec_position              /*point_1*/,  /* start point */
KI_vec_position              /*point_2*/,  /* end point */
KI_dbl_parameter           * /*parm_1*/,   /* start parameter */
KI_dbl_parameter           * /*parm_2*/,   /* end parameter */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUTSFA
(
/* received */                            
KI_tag_face                * /*face*/,     /* face to be represented */
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_srop                  /*iopts*/[],  /* options */
KI_tag_list_dbl              /*optdta*/[], /* option data lists */
/* returned */                            
KI_tag_surface             * /*surface*/,  /* surface underlying SP-surves */
KI_int_nitems              * /*ntrims*/,   /* number of non-empty trim loop sets */
KI_tag_list_list           * /*spcus*/,    /* lists of trimmed SP-curves */
KI_tag_list_list           * /*geoms*/,    /* lists of corresponding geometries */
KI_tag_list_list           * /*topols*/,   /* lists of corresponding topologies */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void OUTSUR
(
/* received */                            
KI_tag_surface             * /*surfac*/,   /* surface to be output */
/* returned */                            
KI_cod_tysu                * /*sftype*/,   /* surface type */
KI_vec                       /*vec1*/,     /* first vector defining surface */
KI_vec                       /*vec2*/,     /* second vector defining surface */
double                     * /*d1*/,       /* first double defining surface */
double                     * /*d2*/,       /* second double defining surface */
KI_cod_logical             * /*sense*/,    /* surface sense. see below */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void OUUFEN
(
/* received */                            
KI_tag                     * /*tag*/,      /* tag whose user field */
                                           /* is required */
/* returned */                            
KI_int_ufdval                /*ufdval*/[], /* user-field value - */
                                           /* array length is the user-field */
                                           /* size set by STAMOD */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void PICKEN
(
/* received */                            
KI_tag_list_part           * /*palist*/,   /* part or list of parts */
KI_tag_list_transform      * /*transf*/,   /* transformation or */
                                           /* list of transformations */
KI_vec                       /*point*/,    /* point through which axis passes */
KI_vec_direction             /*axis*/,     /* axis of cylindrical volume */
KI_dbl_radius              * /*rad*/,      /* radius of cylindrical volume */
KI_cod_slpk                * /*opt*/,      /* ray options */
KI_cod_ty                  * /*entype*/,   /* type of entity to pick */
/* returned */                            
KI_int_nitems              * /*nhiten*/,   /* number of picked entities */
KI_tag_list_entity         * /*hitlis*/,   /* list of picked entities */
KI_tag_list_int            * /*indlis*/,   /* list of indices of the */
                                           /* owning parts */
KI_tag_list_dbl            * /*dislis*/,   /* list of minimum distances */
                                           /* from picked entities to ray */
KI_tag_list_dbl            * /*hitpts*/,   /* points on ray axis */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void PIERCE
(
/* received */                            
KI_tag_face                * /*face*/,     /* face to remove */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void PTENFE
(
/* received */                            
KI_tag_feature             * /*featre*/,   /* feature */
KI_tag_list_entity         * /*entity*/,   /* entities to be added */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void PTINLI
(
/* received */                            
KI_tag_list_int            * /*list*/,     /* list in which to put items */
KI_int_index               * /*startx*/,   /* position in list where first */
                                           /* value is to be put */
KI_int_nitems              * /*nvals*/,    /* number of values to be put */
                                           /* into list */
int                          /*ivals*/[],  /* values to put into list */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void PTRLLI
(
/* received */                            
KI_tag_list_dbl            * /*list*/,     /* list in which to put items */
KI_int_index               * /*startx*/,   /* position in list where first */
                                           /* value is to be put */
KI_int_nitems              * /*nvals*/,    /* number of values to be put */
                                           /* into list */
double                       /*rvals*/[],  /* values to put into list */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void PTTGLI
(
/* received */                            
KI_tag_list_tag            * /*list*/,     /* list in which to put tags */
KI_int_index               * /*startx*/,   /* position in list where first */
                                           /* value is to be put */
KI_int_nitems              * /*ntags*/,    /* number of tags to be put */
                                           /* into list */
KI_tag                       /*tags*/[],   /* tags to put into list */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void RAYFIR
(
/* received */                            
KI_tag_list_part           * /*palist*/,   /* entities to fire ray through */
KI_tag_list_transform      * /*transf*/,   /* part transformations */
KI_int_nitems              * /*wchhit*/,   /* number of intersections wanted */
KI_vec                       /*point*/,    /* point from which ray is fired */
KI_vec_direction             /*direct*/,   /* direction of ray */
/* returned */                            
KI_int_nitems              * /*nhitpt*/,   /* number of points returned */
KI_tag_list_dbl            * /*hitpts*/,   /* points where ray hit bodies */
KI_tag_list_face           * /*hitfas*/,   /* faces hit by ray */
KI_tag_list_int            * /*indces*/,   /* indices of bodies hit by ray */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void REDINS
(
/* received */                            
KI_tag_instance            * /*instnc*/,   /* instance to redirect */
KI_tag_part                * /*part*/,     /* part it should instance */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void REEDSH
(
/* received */                            
KI_tag_body                * /*sheet*/,    /* Sheet body */
KI_dbl                       /*urange*/[], /* urange of face */
KI_dbl                       /*vrange*/[], /* vrange of face */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void RESUSH
(
/* received */                            
KI_tag_body                * /*sheet*/,    /* Sheet body */
KI_tag_surface             * /*surf*/,     /* new surface for sheet body */
KI_dbl_distance            * /*tol*/,      /* tolerance of SP_curves */
/* returned */                            
KI_tag_list_edge           * /*edges*/,    /* edges converted to SP_curves */
KI_int_nitems              * /*nedges*/,   /* number of converted edges */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void RETLEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* edge */
/* returned */                            
KI_cod_rttl                * /*retcod*/,   /* status of operation */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void RMFASO
(
/* received */                            
KI_tag_list_face           * /*faces*/,    /* faces to be removed */
KI_cod_sllo                * /*actpar*/,   /* action to mend holes on parents */
                                           /*   SLLOCP => cap */
                                           /*   SLLOGR => grow */
                                           /*   SLLORB => leave rubber */
KI_cod_sllo                * /*actoff*/,   /* action to mend holes on offspring */
                                           /*   SLLOCP => cap */
                                           /*   SLLOGR => grow */
                                           /*   SLLOGP => grow from parent */
                                           /*   SLLORB => leave rubber */
/* returned */                            
KI_tag_list_body           * /*parnts*/,   /* parent body fragments */
KI_int_nitems              * /*nprnts*/,   /* number of parent fragments */
KI_tag_list_int            * /*sprnts*/,   /* state of parent fragments */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_tag_list_body           * /*offspg*/,   /* offspring bodies */
KI_int_nitems              * /*nofspg*/,   /* number of offspring */
KI_tag_list_int            * /*sofspg*/,   /* state of offspring */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void ROLBFN
(
/* received */                            
int                        * /*nsteps*/,   /* number of steps to be rolled */
                                           /* forward (> 0) or back (< 0) */
/* returned */                            
int                        * /*asteps*/,   /* actual number of steps rolled */
                                           /* forward (> 0) or back (< 0) */
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void ROLBLM
(
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void ROLSMK
(
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void RRFCET
(
/* received */                            
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_rrop                  /*iopts*/[],  /* rendering options */
KI_tag_list_dbl              /*optdta*/[], /* option data lists */
KI_tag_list_entity         * /*entys*/,    /* entities to render */
KI_tag_list_transform      * /*transf*/,   /* entity transforms */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void RRHIDL
(
/* received */                            
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_rrop                  /*iopts*/[],  /* rendering options */
KI_tag_list_dbl              /*optdta*/[], /* option data lists */
KI_tag_list_entity         * /*entys*/,    /* entities to render */
KI_tag_list_transform      * /*transf*/,   /* entity transforms */
KI_dbl_view_mx               /*vmatrx*/[], /* viewing transform matrix */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void RRPIXL
(
/* received */                            
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_rrop                  /*iopts*/[],  /* rendering options */
KI_tag_list_dbl              /*optdta*/[], /* option data lists */
KI_tag_list_entity         * /*entys*/,    /* entities to render */
KI_tag_list_transform      * /*transf*/,   /* entity transforms */
KI_dbl_view_mx               /*vmatrx*/[], /* viewing transform matrix */
KI_tag_list_dbl            * /*pixdef*/,   /* image to pixel map */
KI_tag_list_list           * /*litdef*/,   /* light source definitions */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void RRVDEP
(
/* received */                            
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_rrop                  /*iopts*/[],  /* rendering options */
KI_tag_list_dbl              /*optdta*/[], /* option data lists */
KI_tag_list_entity         * /*entys*/,    /* entities to render */
KI_tag_list_transform      * /*transf*/,   /* entity transforms */
KI_dbl_view_mx               /*vmatrx*/[], /* viewing transform matrix */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void RRVIND
(
/* received */                            
KI_int_nitems              * /*nopts*/,    /* number of options in 'iopts' */
KI_cod_rrop                  /*iopts*/[],  /* rendering options */
KI_tag_list_dbl              /*optdta*/[], /* option data lists */
KI_tag_list_entity         * /*entys*/,    /* entities to render */
KI_tag_list_transform      * /*transf*/,   /* entity transforms */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SAVMOD
(
/* received */                            
KI_tag_part                * /*part*/,     /* part to transmit */
KI_int_nchars              * /*keylen*/,   /* length of key */
KI_chr_key                   /*key*/[],    /* key of part */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SAVSNP
(
/* received */                            
KI_int_nchars              * /*nchars*/,   /* number of characters in filename */
KI_chr_filename              /*filnam*/[], /* filename for snapshot */
int                        * /*histfl*/,   /* unused: should be zero */
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void SCRIBE
(
/* received */                            
KI_tag_topology            * /*topol*/,    /* face, region or body to scribe curve on */
KI_tag_curve               * /*curve*/,    /* curve to scribe */
KI_vec_position              /*startp*/,   /* start position */
KI_vec_position              /*endp*/,     /* end position */
/* returned */                            
KI_tag_list_edge           * /*newedg*/,   /* list of new edges */
KI_int_nitems              * /*nedges*/,   /* number of new edges */
KI_tag_list_face           * /*newfac*/,   /* list of new faces, if any */
KI_int_nitems              * /*nfaces*/,   /* number of new faces */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SEBBCO
(
/* received */                            
KI_int_nitems              * /*nents*/,    /* length of 'ents' array */
KI_cod_ty                    /*ents*/[],   /* entity types to be bulletined */
KI_tag_list_int              /*events*/[], /* corresponding events to record */
KI_int_nitems              * /*nopts*/,    /* no of control options */
KI_cod_bbop                  /*opts*/[],   /* control options */
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void SECTBY
(
/* received */                            
KI_tag_list_body           * /*bodies*/,   /* body or list of bodies */
                                           /* to be sectioned */
KI_tag_surface             * /*surfac*/,   /* sectioning surface */
/* returned */                            
KI_tag_list_body           * /*front*/,    /* bodies in front of surface */
KI_tag_list_body           * /*back*/,     /* bodies behind surface */
KI_tag_list_face           * /*newfas*/,   /* new faces */
KI_int_nitems              * /*nfaces*/,   /* number of faces in 'newfas' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void SEINTP
(
/* received */                            
KI_cod_slip                * /*pnum*/,     /* parameter code */
int                        * /*ival*/,     /* integer value of parameter */
double                     * /*rval*/,     /* real value of parameter */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SEMODP
(
/* received */                            
KI_cod_slmp                * /*pnum*/,     /* parameter code */
int                        * /*ival*/,     /* integer value of parameter */
double                     * /*rval*/,     /* real value of parameter */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SESTPA
(
/* received */                            
KI_tag_part                * /*part*/,     /* part to change */
KI_cod_enst                * /*state*/,    /* desired new state of the part */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SETLEN
(
/* received */                            
KI_tag_entity              * /*entity*/,   /* can be face, edge or vertex */
double                     * /*tol*/,      /* new tolerance value */
/* returned */                            
KI_tag_list_edge           * /*edges*/,    /* list of new edges */
KI_int_nitems              * /*nedges*/,   /* number of edges */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SEUFEN
(
/* received */                            
KI_tag                     * /*tag*/,      /* tag whose user field */
                                           /* is to be set */
KI_int_ufdval                /*ufdval*/[], /* user-field value: */
                                           /* array length is the user-field */
                                           /* size set by STAMOD */
/* returned */                            
KI_cod_error               * /*ifail*/     /* error code */
);

KI_linkage_m void SHAREN
(
/* received */                            
KI_tag_body                * /*body*/,     /* body on which to attempt sharing */
KI_int_nitems              * /*nopts*/,    /* number of options in opts */
KI_cod_shop                  /*opts*/[],   /* sharing control options */
/* returned */                            
KI_int_nitems              * /*ngeom*/,    /* number of geometries removed */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void SIMPEN
(
/* received */                            
KI_tag_body                * /*body*/,     /* body to simplify */
KI_cod_slle                * /*level*/,    /* level of simplification */
/* returned */                            
KI_tag_list_entity         * /*geom*/,     /* list of new geometric entities */
KI_int_nitems              * /*ngeom*/,    /* number of new entities */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SPLTEN
(
/* received */                            
KI_tag_body                * /*body*/,     /* body */
/* returned */                            
KI_int_nitems              * /*nfaces*/,   /* number of faces that have been split */
KI_tag_list_face           * /*faces*/,    /* list of original faces that were split */
KI_tag_list_list           * /*new_faces*/, /* list for each new set of faces, */
                                           /* corresponding to each of the old faces */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SRCHIL
(
/* received */                            
KI_tag_list_int            * /*list*/,     /* list which is to be searched */
int                        * /*value*/,    /* value to be looked for */
KI_int_index               * /*start*/,    /* starting position to look for */
                                           /* integer */
/* returned */                            
KI_int_index               * /*index*/,    /* index of first item in list */
                                           /* which matches given value */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SRCHRL
(
/* received */                            
KI_tag_list_dbl            * /*list*/,     /* list which is to be searched */
double                     * /*value*/,    /* value to be looked for */
KI_int_index               * /*start*/,    /* starting position to look for */
                                           /* real */
/* returned */                            
KI_int_index               * /*index*/,    /* index of first item in list */
                                           /* which matches given value */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SRCHTG
(
/* received */                            
KI_tag_list_tag            * /*list*/,     /* list which is to be searched */
KI_tag                     * /*value*/,    /* entity to be looked for */
KI_int_index               * /*start*/,    /* starting position to look for tag */
/* returned */                            
KI_int_index               * /*index*/,    /* index of item in list which */
                                           /* matches given value */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void STAMOD
(
/* received */                            
KI_cod_logical             * /*kijon*/,    /* flags whether to write journal */
                                           /* file or not */
KI_int_nchars              * /*nchars*/,   /* number of characters in journal */
                                           /* file name (used only if kijon is */
                                           /* set to true) */
KI_chr_filename              /*jfilnm*/[], /* name of journal file */
int                        * /*usrfld*/,   /* size of user fields (in integers) */
/* returned */                            
KI_tag_entity              * /*world*/,    /* world */
int                        * /*kivrsn*/,   /* version number of interface being */
                                           /* invoked */
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void STOMOD
(
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);

KI_linkage_m void SUBBYS
(
/* received */                            
KI_tag_body                * /*targby*/,   /* body to be modified */
KI_tag_list_body           * /*tolbys*/,   /* body or list of bodies */
                                           /* used to modify 'targby' */
/* returned */                            
KI_tag_assembly            * /*assemb*/,   /* assembly of resulting bodies */
KI_int_nitems              * /*nbodys*/,   /* number of bodies in 'assemb' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void SWEENT
(
/* received */                            
KI_tag_list_topology       * /*swept*/,    /* body, vertex, face or list of */
                                           /* faces to sweep */
KI_vec_displacement          /*path*/,     /* translation vector */
/* returned */                            
KI_tag_list_topology       * /*latrls*/,   /* lateral edge or face(s) */
KI_tag_list_topology       * /*extent*/,   /* extruded vertex or edge(s) */
KI_int_nitems              * /*nlatrl*/,   /* number of laterals */
KI_cod_rtlo                * /*state*/,    /* state of body after sweep */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void SWIENT
(
/* received */                            
KI_tag_list_topology       * /*swung*/,    /* body, vertex, face or list of */
                                           /* faces to swing */
KI_vec_position              /*point*/,    /* point on axis of rotation */
KI_vec_axis                  /*direct*/,   /* direction of axis of rotation */
KI_dbl_angle               * /*angle*/,    /* angle of swing (in radians) */
/* returned */                            
KI_tag_list_topology       * /*latrls*/,   /* lateral edge or face(s) */
KI_tag_list_topology       * /*extent*/,   /* extruded vertex or edge(s) */
KI_int_nitems              * /*nlatrl*/,   /* number of laterals */
KI_cod_rtlo                * /*state*/,    /* state of the body after the swing */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void TAPFAS
(
/* received */                            
KI_tag_list_face           * /*faces*/,    /* face(s) to be tapered */
KI_vec_position              /*point*/,    /* point on taper plane */
KI_vec_direction             /*direct*/,   /* normal to taper plane */
KI_dbl_angle               * /*angle*/,    /* taper angle (in radians) */
/* returned */                            
KI_tag_list_face           * /*flist*/,    /* tapered face(s) */
KI_int_nitems              * /*nfaces*/,   /* number of tapered faces */
KI_cod_rtlo                * /*state*/,    /* state of the body */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void THIKEN
(
/* received */                            
KI_tag_body                * /*body*/,     /* body to be thickened */
KI_dbl                     * /*front*/,    /* thickness on front of faces */
KI_dbl                     * /*back*/,     /* thickness on back of faces */
KI_cod_logical             * /*check*/,    /* level of checking required */
KI_dbl_distance            * /*tol*/,      /* tol of SP curve conversions */
KI_int_nitems              * /*mxflts*/,   /* maximum number of entities in badtag */
/* returned */                            
KI_tag_list_entity         * /*oldtop*/,   /* original topology */
KI_tag_list_entity         * /*newtop*/,   /* new topology */
KI_tag_list_entity         * /*badtag*/,   /* entities which caused problems */
KI_cod_rtof                * /*state*/,    /* state of body after offset */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void TRIMSH
(
/* received */                            
KI_tag_body                * /*sheet*/,    /* Sheet body to trim */
KI_int_nitems              * /*ncurvs*/,   /* number of curves supplied */
KI_tag_curve                 /*curvs*/[],  /* curves to trim sheet */
KI_int_nitems              * /*nopts*/,    /* no of trimming options supplied */
KI_cod_sltr                  /*opts*/[],   /* trimming options */
KI_tag_list                  /*optdata*/[], /* trimming option data */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void TRSHCU
(
/* received */                            
KI_tag_body                * /*sheet*/,    /* Sheet body to trim */
KI_int_nitems              * /*ncurvs*/,   /* number of curves supplied */
KI_tag_curve                 /*curvs*/[],  /* curves to trim sheet */
KI_int_nitems              * /*nopts*/,    /* no of trimming options supplied */
KI_cod_trsh                  /*opts*/[],   /* trimming options */
KI_vec_direction             /*direct*/,   /* direction of projection */
/* returned */                            
KI_tag_list_edge           * /*edges*/,    /* edges imprinted */
KI_int_nitems              * /*nedges*/,   /* number of edges */
KI_tag_list_curve          * /*which*/,    /* which curve edge is derived from */
KI_tag_list_int            * /*original*/, /* whether edge is original */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void TWEFAC
(
/* received */                            
KI_tag_list_entity         * /*faces*/,    /* face(s) to be transformed */
KI_tag_list_transform      * /*transf*/,   /* list of transforms */
                                           /* (move and/or rotate only) */
/* returned */                            
KI_cod_rtlo                * /*state*/,    /* state of the body */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void TWSUFA
(
/* received */                            
KI_tag_list_face           * /*faces*/,    /* face(s) to tweak */
KI_tag_list_surface        * /*surfs*/,    /* new surface(s) for face(s) */
KI_tag_list_int            * /*senses*/,   /* senses for surfaces */
/* returned */                            
KI_cod_rtlo                * /*state*/,    /* state of the body */
                                           /*   RTLOOK => Valid */
                                           /*   RTLONG => Negated */
                                           /*   RTLOSX => Self-Intersecting */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void UNIBYS
(
/* received */                            
KI_tag_body                * /*targby*/,   /* target body */
KI_tag_list_body           * /*tolbys*/,   /* body or list of bodies used */
                                           /* to modify 'targby' */
/* returned */                            
KI_tag_assembly            * /*assemb*/,   /* assembly of resulting bodies */
KI_int_nitems              * /*nbodys*/,   /* number of bodies in 'assemb' */
KI_cod_error               * /*ifail*/     /* failure code */
);

KI_linkage_m void UNLDPA
(
/* received */                            
KI_tag_part                * /*part*/,     /* part to unload */
/* returned */                            
KI_cod_error               * /*ifail*/     /* failure indicator */
);


#undef  KI_linkage_m

#endif /* KERNEL_INTERFACE_H_INCLUDED */

