/*
  Parasolid Typedefs

  Copyright 2013 Siemens Product Lifecycle Management Software Inc. All rights reserved.
  This software and related documentation are proprietary to 
  Siemens Product Lifecycle Management Software Inc.

*/

#ifndef PARASOLID_TYPEDEFS_H_INCLUDED
#define PARASOLID_TYPEDEFS_H_INCLUDED

typedef int

    KI_cod_error,
    KI_cod_logical,

    KI_cod_ty,
    KI_cod_tyen,
    KI_cod_tyge,
    KI_cod_typt,
    KI_cod_tycu,
    KI_cod_tysu,
    KI_cod_tybl,
    KI_cod_tyto,
    KI_cod_tyas,
    KI_cod_tyin,
    KI_cod_tyad,
    KI_cod_tyat,
    KI_cod_tyfe,
    KI_cod_tysa,
    KI_cod_tyua,
    KI_cod_tyli,
    KI_cod_rq,
    KI_cod_rqac,
    KI_cod_rqap,
    KI_cod_en,
    KI_cod_enve,
    KI_cod_ened,
    KI_cod_enlo,
    KI_cod_ensh,
    KI_cod_enby,
    KI_cod_enwr,
    KI_cod_ense,
    KI_cod_enst,
    KI_cod_encl,
    KI_cod_slip,
    KI_cod_slmp,
    KI_cod_slab,
    KI_cod_sler,
    KI_cod_slst,
    KI_cod_sllo,
    KI_cod_rtlo,
    KI_cod_slfi,
    KI_cod_slcp,
    KI_cod_slba,
    KI_cod_slle,
    KI_cod_slpk,
    KI_cod_rrop,
    KI_cod_papr,
    KI_cod_rtst,
    KI_cod_srop,
    KI_cod_maop,
    KI_cod_oufo,
    KI_cod_atop,
    KI_cod_mdop,
    KI_cod_bbev,
    KI_cod_bbop,
    KI_cod_cicl,
    KI_cod_clop,
    KI_cod_cfcl,
    KI_cod_imop,
    KI_cod_idop,
    KI_cod_rtto,
    KI_cod_byty,
    KI_cod_padi,
    KI_cod_rtcl,
    KI_cod_rtmd,
    KI_cod_mdfa,
    KI_cod_rtkn,
    KI_cod_cbop,
    KI_cod_boop,
    KI_cod_blec,
    KI_cod_blcc,
    KI_cod_inop,
    KI_cod_crop,
    KI_cod_sicl,
    KI_cod_tsop,
    KI_cod_rtts,
    KI_cod_idty,
    KI_cod_chop,
    KI_cod_sltr,
    KI_cod_shop,
    KI_cod_loch,
    KI_cod_rtof,
    KI_cod_pfop,
    KI_cod_rttl,
    KI_cod_trsh,
    KI_cod_fxft,
    KI_cod_fxfe,
    KI_cod;

typedef char

    KI_chr_key,
    KI_chr_name,
    KI_chr_filename,
    KI_chr_string,
    KI_chr;

typedef double

    KI_dbl_angle,
    KI_dbl_box,
    KI_dbl_coefficients,
    KI_dbl_curvature,
    KI_dbl_distance,
    KI_dbl_knots,
    KI_dbl_parameter,
    KI_dbl_radius,
    KI_dbl_sc_fact,
    KI_dbl_tensor,
    KI_dbl_transf_mx,
    KI_dbl_view_mx,
    KI_dbl;

typedef int

    KI_int_bbitem,
    KI_int_dimension,
    KI_int_id,
    KI_int_index,
    KI_int_nchars,
    KI_int_nitems,
    KI_int_order,
    KI_int_ufdval,
    KI_int;

typedef int

    KI_tag_assembly,             KI_tag_list_assembly,
    KI_tag_attribute,            KI_tag_list_attribute,
    KI_tag_attrib_def,           KI_tag_list_attrib_def,
    KI_tag_b_curve,              KI_tag_list_b_curve,
    KI_tag_b_surface,            KI_tag_list_b_surface,
    KI_tag_body,                 KI_tag_list_body,
    KI_tag_curve,                KI_tag_list_curve,
    KI_tag_edge,                 KI_tag_list_edge,
    KI_tag_entity,               KI_tag_list_entity,
    KI_tag_face,                 KI_tag_list_face,
    KI_tag_feature,              KI_tag_list_feature,
    KI_tag_geometry,             KI_tag_list_geometry,
    KI_tag_instance,             KI_tag_list_instance,
    KI_tag_list,                 KI_tag_list_list,
    KI_tag_loop,                 KI_tag_list_loop,
    KI_tag_paracurve,            KI_tag_list_paracurve,
    KI_tag_parasurf,             KI_tag_list_parasurf,
    KI_tag_part,                 KI_tag_list_part,
    KI_tag_point,                KI_tag_list_point,
    KI_tag_shell,                KI_tag_list_shell,
    KI_tag_sp_curve,             KI_tag_list_sp_curve,
    KI_tag_surface,              KI_tag_list_surface,
    KI_tag_topology,             KI_tag_list_topology,
    KI_tag_transform,            KI_tag_list_transform,
    KI_tag_vertex,               KI_tag_list_vertex,
    KI_tag_list_int,             KI_tag_list_dbl,
    KI_tag,                      KI_tag_list_tag;

typedef double KI_vector[3];
typedef KI_vector

    KI_vec_axis,
    KI_vec_direction,
    KI_vec_normal,
    KI_vec_displacement,
    KI_vec_position,
    KI_vec_derivatives,
    KI_vec_centre,
    KI_vec;

#endif /* PARASOLID_TYPEDEFS_H_INCLUDED */
