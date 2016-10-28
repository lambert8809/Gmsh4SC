/*
  Parasolid Ifails

  Copyright 2013 Siemens Product Lifecycle Management Software Inc. All rights reserved.
  This software and related documentation are proprietary to 
  Siemens Product Lifecycle Management Software Inc.

*/

#ifndef PARASOLID_IFAILS_H_INCLUDED
#define PARASOLID_IFAILS_H_INCLUDED

#define KI_no_errors                        0
#define PK_ERROR_no_errors               ((PK_ERROR_code_t)    0)
#define KI_bad_angle                        1
#define PK_ERROR_bad_angle               ((PK_ERROR_code_t)    1)
#define KI_buffer_overflow                  2
#define PK_ERROR_buffer_overflow         ((PK_ERROR_code_t)    2)
#define KI_radii_both_0                     3
#define PK_ERROR_radii_both_0            ((PK_ERROR_code_t)    3)
#define KI_cone_too_sharp                   4
#define PK_ERROR_cone_too_sharp          ((PK_ERROR_code_t)    4)
#define KI_has_no_name                      7
#define PK_ERROR_has_no_name             ((PK_ERROR_code_t)    7)
#define KI_has_no_owner                     8
#define PK_ERROR_has_no_owner            ((PK_ERROR_code_t)    8)
#define KI_wrong_entity                    10
#define PK_ERROR_wrong_entity            ((PK_ERROR_code_t)   10)
#define KI_bad_name                        11
#define PK_ERROR_bad_name                ((PK_ERROR_code_t)   11)
#define KI_bad_type_combn                  12
#define PK_ERROR_bad_type_combn          ((PK_ERROR_code_t)   12)
#define KI_not_unique                      13
#define PK_ERROR_not_unique              ((PK_ERROR_code_t)   13)
#define KI_distance_lt_0                   14
#define PK_ERROR_distance_lt_0           ((PK_ERROR_code_t)   14)
#define KI_distance_le_0                   15
#define PK_ERROR_distance_le_0           ((PK_ERROR_code_t)   15)
#define KI_radius_le_0                     16
#define PK_ERROR_radius_le_0             ((PK_ERROR_code_t)   16)
#define KI_radius_lt_0                     18
#define PK_ERROR_radius_lt_0             ((PK_ERROR_code_t)   18)
#define KI_not_found                       19
#define PK_ERROR_not_found               ((PK_ERROR_code_t)   19)
#define KI_not_connected                   20
#define PK_ERROR_not_connected           ((PK_ERROR_code_t)   20)
#define KI_not_a_tag                       22
#define PK_ERROR_not_a_tag               ((PK_ERROR_code_t)   22)
#define KI_null_axis                       25
#define PK_ERROR_null_axis               ((PK_ERROR_code_t)   25)
#define KI_cant_open_jrnl                  27
#define PK_ERROR_cant_open_jrnl          ((PK_ERROR_code_t)   27)
#define KI_has_parent                      28
#define PK_ERROR_has_parent              ((PK_ERROR_code_t)   28)
#define KI_bad_index                       29
#define PK_ERROR_bad_index               ((PK_ERROR_code_t)   29)
#define KI_bad_type                        30
#define PK_ERROR_bad_type                ((PK_ERROR_code_t)   30)
#define KI_null_direction                  31
#define PK_ERROR_null_direction          ((PK_ERROR_code_t)   31)
#define KI_rot_angle_eq_0                  32
#define PK_ERROR_rot_angle_eq_0          ((PK_ERROR_code_t)   32)
#define KI_lt_3_sides                      33
#define PK_ERROR_lt_3_sides              ((PK_ERROR_code_t)   33)
#define KI_is_attached                     34
#define PK_ERROR_is_attached             ((PK_ERROR_code_t)   34)
#define KI_dont_intersect                  35
#define PK_ERROR_dont_intersect          ((PK_ERROR_code_t)   35)
#define KI_majaxi_not_perpn                36
#define PK_ERROR_majaxi_not_perpn        ((PK_ERROR_code_t)   36)
#define KI_wrong_transf                    37
#define PK_ERROR_wrong_transf            ((PK_ERROR_code_t)   37)
#define KI_bad_selection_code              38
#define PK_ERROR_bad_selection_code      ((PK_ERROR_code_t)   38)
#define KI_bad_value                       39
#define PK_ERROR_bad_value               ((PK_ERROR_code_t)   39)
#define KI_sc_factor_le_0                  40
#define PK_ERROR_sc_factor_le_0          ((PK_ERROR_code_t)   40)
#define KI_su_are_coincident               41
#define PK_ERROR_su_are_coincident       ((PK_ERROR_code_t)   41)
#define KI_bulletinb_is_off                42
#define PK_ERROR_bulletinb_is_off        ((PK_ERROR_code_t)   42)
#define KI_none_mergeable                  48
#define PK_ERROR_none_mergeable          ((PK_ERROR_code_t)   48)
#define KI_cant_do_tweak                   50
#define PK_ERROR_cant_do_tweak           ((PK_ERROR_code_t)   50)
#define KI_inconsistent_geom               51
#define PK_ERROR_inconsistent_geom       ((PK_ERROR_code_t)   51)
#define KI_not_on_face                     54
#define PK_ERROR_not_on_face             ((PK_ERROR_code_t)   54)
#define KI_impossible_swing                55
#define PK_ERROR_impossible_swing        ((PK_ERROR_code_t)   55)
#define KI_impossible_sweep                57
#define PK_ERROR_impossible_sweep        ((PK_ERROR_code_t)   57)
#define KI_key_not_found                   58
#define PK_ERROR_key_not_found           ((PK_ERROR_code_t)   58)
#define KI_not_in_same_part                59
#define PK_ERROR_not_in_same_part        ((PK_ERROR_code_t)   59)
#define KI_no_geometry                     61
#define PK_ERROR_no_geometry             ((PK_ERROR_code_t)   61)
#define KI_geom_topol_mismatch             62
#define PK_ERROR_geom_topol_mismatch     ((PK_ERROR_code_t)   62)
#define KI_receive_failed                  63
#define PK_ERROR_receive_failed          ((PK_ERROR_code_t)   63)
#define KI_geom_not_needed                 64
#define PK_ERROR_geom_not_needed         ((PK_ERROR_code_t)   64)
#define KI_not_on_curve                    67
#define PK_ERROR_not_on_curve            ((PK_ERROR_code_t)   67)
#define KI_still_referenced                68
#define PK_ERROR_still_referenced        ((PK_ERROR_code_t)   68)
#define KI_fragment                        73
#define PK_ERROR_fragment                ((PK_ERROR_code_t)   73)
#define KI_cant_find_su                    77
#define PK_ERROR_cant_find_su            ((PK_ERROR_code_t)   77)
#define KI_empty_list                      79
#define PK_ERROR_empty_list              ((PK_ERROR_code_t)   79)
#define KI_not_a_list                      80
#define PK_ERROR_not_a_list              ((PK_ERROR_code_t)   80)
#define KI_mass_eq_0                       82
#define PK_ERROR_mass_eq_0               ((PK_ERROR_code_t)   82)
#define KI_density_le_0                    85
#define PK_ERROR_density_le_0            ((PK_ERROR_code_t)   85)
#define KI_dont_make_solid                 87
#define PK_ERROR_dont_make_solid         ((PK_ERROR_code_t)   87)
#define KI_missing_geom                    96
#define PK_ERROR_missing_geom            ((PK_ERROR_code_t)   96)
#define KI_attr_not_found                  99
#define PK_ERROR_attr_not_found          ((PK_ERROR_code_t)   99)
#define KI_not_solid                      101
#define PK_ERROR_not_solid               ((PK_ERROR_code_t)  101)
#define KI_corrupt_body                   103
#define PK_ERROR_corrupt_body            ((PK_ERROR_code_t)  103)
#define KI_bad_geom_topol                 105
#define PK_ERROR_bad_geom_topol          ((PK_ERROR_code_t)  105)
#define KI_negative_body                  106
#define PK_ERROR_negative_body           ((PK_ERROR_code_t)  106)
#define KI_bad_char_string                109
#define PK_ERROR_bad_char_string         ((PK_ERROR_code_t)  109)
#define KI_bad_spec_code                  110
#define PK_ERROR_bad_spec_code           ((PK_ERROR_code_t)  110)
#define KI_weight_le_0                    111
#define PK_ERROR_weight_le_0             ((PK_ERROR_code_t)  111)
#define KI_illegal_degeneracy             116
#define PK_ERROR_illegal_degeneracy      ((PK_ERROR_code_t)  116)
#define KI_bad_parameter                  120
#define PK_ERROR_bad_parameter           ((PK_ERROR_code_t)  120)
#define KI_discontinuous_surface          129
#define PK_ERROR_discontinuous_surface   ((PK_ERROR_code_t)  129)
#define KI_discontinuous_curve            131
#define PK_ERROR_discontinuous_curve     ((PK_ERROR_code_t)  131)
#define KI_order_lt_2                     132
#define PK_ERROR_order_lt_2              ((PK_ERROR_code_t)  132)
#define KI_bad_dimension                  135
#define PK_ERROR_bad_dimension           ((PK_ERROR_code_t)  135)
#define KI_su_self_intersect              141
#define PK_ERROR_su_self_intersect       ((PK_ERROR_code_t)  141)
#define KI_cant_do_intersect              157
#define PK_ERROR_cant_do_intersect       ((PK_ERROR_code_t)  157)
#define KI_cant_fix_blends                330
#define PK_ERROR_cant_fix_blends         ((PK_ERROR_code_t)  330)
#define KI_bad_blend_bound                334
#define PK_ERROR_bad_blend_bound         ((PK_ERROR_code_t)  334)
#define KI_not_blended                    335
#define PK_ERROR_not_blended             ((PK_ERROR_code_t)  335)
#define KI_blend_didnt_check              336
#define PK_ERROR_blend_didnt_check       ((PK_ERROR_code_t)  336)
#define KI_bad_request_code               350
#define PK_ERROR_bad_request_code        ((PK_ERROR_code_t)  350)
#define KI_wrong_entity_in_list           357
#define PK_ERROR_wrong_entity_in_list    ((PK_ERROR_code_t)  357)
#define KI_not_same_length                359
#define PK_ERROR_not_same_length         ((PK_ERROR_code_t)  359)
#define KI_bad_view_mx                    360
#define PK_ERROR_bad_view_mx             ((PK_ERROR_code_t)  360)
#define KI_bad_pixel_map                  361
#define PK_ERROR_bad_pixel_map           ((PK_ERROR_code_t)  361)
#define KI_bad_light_source               364
#define PK_ERROR_bad_light_source        ((PK_ERROR_code_t)  364)
#define KI_eye_in_box                     367
#define PK_ERROR_eye_in_box              ((PK_ERROR_code_t)  367)
#define KI_cyclic_assy                    503
#define PK_ERROR_cyclic_assy             ((PK_ERROR_code_t)  503)
#define KI_anon_sub_part                  504
#define PK_ERROR_anon_sub_part           ((PK_ERROR_code_t)  504)
#define KI_different_types                505
#define PK_ERROR_different_types         ((PK_ERROR_code_t)  505)
#define KI_existing_attr_type             506
#define PK_ERROR_existing_attr_type      ((PK_ERROR_code_t)  506)
#define KI_majrad_minrad_mismatch         507
#define PK_ERROR_majrad_minrad_mismatch  ((PK_ERROR_code_t)  507)
#define KI_radius_sum_le_0                508
#define PK_ERROR_radius_sum_le_0         ((PK_ERROR_code_t)  508)
#define KI_wrong_list_type                509
#define PK_ERROR_wrong_list_type         ((PK_ERROR_code_t)  509)
#define KI_bad_tag_in_list                510
#define PK_ERROR_bad_tag_in_list         ((PK_ERROR_code_t)  510)
#define KI_duplicate_list_item            511
#define PK_ERROR_duplicate_list_item     ((PK_ERROR_code_t)  511)
#define KI_not_in_feat                    512
#define PK_ERROR_not_in_feat             ((PK_ERROR_code_t)  512)
#define KI_wrong_type_for_feat            513
#define PK_ERROR_wrong_type_for_feat     ((PK_ERROR_code_t)  513)
#define KI_list_too_short                 519
#define PK_ERROR_list_too_short          ((PK_ERROR_code_t)  519)
#define KI_already_in_feat                520
#define PK_ERROR_already_in_feat         ((PK_ERROR_code_t)  520)
#define KI_attr_mismatch                  522
#define PK_ERROR_attr_mismatch           ((PK_ERROR_code_t)  522)
#define KI_list_wrong_length              523
#define PK_ERROR_list_wrong_length       ((PK_ERROR_code_t)  523)
#define KI_part_not_keyed                 524
#define PK_ERROR_part_not_keyed          ((PK_ERROR_code_t)  524)
#define KI_cant_heal_wound                525
#define PK_ERROR_cant_heal_wound         ((PK_ERROR_code_t)  525)
#define KI_already_loaded                 528
#define PK_ERROR_already_loaded          ((PK_ERROR_code_t)  528)
#define KI_already_saved                  529
#define PK_ERROR_already_saved           ((PK_ERROR_code_t)  529)
#define KI_key_in_use                     530
#define PK_ERROR_key_in_use              ((PK_ERROR_code_t)  530)
#define KI_closed_faces                   531
#define PK_ERROR_closed_faces            ((PK_ERROR_code_t)  531)
#define KI_at_singularity                 532
#define PK_ERROR_at_singularity          ((PK_ERROR_code_t)  532)
#define KI_size_mismatch                  533
#define PK_ERROR_size_mismatch           ((PK_ERROR_code_t)  533)
#define KI_duplicate_tools                540
#define PK_ERROR_duplicate_tools         ((PK_ERROR_code_t)  540)
#define KI_instanced_tools                541
#define PK_ERROR_instanced_tools         ((PK_ERROR_code_t)  541)
#define KI_mixed_sheets_solids            542
#define PK_ERROR_mixed_sheets_solids     ((PK_ERROR_code_t)  542)
#define KI_cant_unite_solid_sheet         543
#define PK_ERROR_cant_unite_solid_sheet  ((PK_ERROR_code_t)  543)
#define KI_same_tool_and_target           545
#define PK_ERROR_same_tool_and_target    ((PK_ERROR_code_t)  545)
#define KI_invalid_bodies                 546
#define PK_ERROR_invalid_bodies          ((PK_ERROR_code_t)  546)
#define KI_non_manifold                   547
#define PK_ERROR_non_manifold            ((PK_ERROR_code_t)  547)
#define KI_t_sheet                        549
#define PK_ERROR_t_sheet                 ((PK_ERROR_code_t)  549)
#define KI_wrong_sub_type                 553
#define PK_ERROR_wrong_sub_type          ((PK_ERROR_code_t)  553)
#define KI_attr_defn_mismatch             555
#define PK_ERROR_attr_defn_mismatch      ((PK_ERROR_code_t)  555)
#define KI_cant_find_file                 557
#define PK_ERROR_cant_find_file          ((PK_ERROR_code_t)  557)
#define KI_get_snapshot_failed            558
#define PK_ERROR_get_snapshot_failed     ((PK_ERROR_code_t)  558)
#define KI_transmit_failed                560
#define PK_ERROR_transmit_failed         ((PK_ERROR_code_t)  560)
#define KI_bad_filename                   561
#define PK_ERROR_bad_filename            ((PK_ERROR_code_t)  561)
#define KI_save_snapshot_failed           562
#define PK_ERROR_save_snapshot_failed    ((PK_ERROR_code_t)  562)
#define KI_bad_key                        565
#define PK_ERROR_bad_key                 ((PK_ERROR_code_t)  565)
#define KI_journal_not_open               566
#define PK_ERROR_journal_not_open        ((PK_ERROR_code_t)  566)
#define KI_bad_state_combn                570
#define PK_ERROR_bad_state_combn         ((PK_ERROR_code_t)  570)
#define KI_rollmark_failed                850
#define PK_ERROR_rollmark_failed         ((PK_ERROR_code_t)  850)
#define KI_no_rollmark                    854
#define PK_ERROR_no_rollmark             ((PK_ERROR_code_t)  854)
#define KI_roll_is_off                    855
#define PK_ERROR_roll_is_off             ((PK_ERROR_code_t)  855)
#define KI_roll_forward_fail              856
#define PK_ERROR_roll_forward_fail       ((PK_ERROR_code_t)  856)
#define KI_impossible_taper               860
#define PK_ERROR_impossible_taper        ((PK_ERROR_code_t)  860)
#define KI_system_error                   900
#define PK_ERROR_system_error            ((PK_ERROR_code_t)  900)
#define KI_memory_full                    901
#define PK_ERROR_memory_full             ((PK_ERROR_code_t)  901)
#define KI_nitems_lt_0                    902
#define PK_ERROR_nitems_lt_0             ((PK_ERROR_code_t)  902)
#define KI_nitems_le_0                    903
#define PK_ERROR_nitems_le_0             ((PK_ERROR_code_t)  903)
#define KI_modified_sub_part              904
#define PK_ERROR_modified_sub_part       ((PK_ERROR_code_t)  904)
#define KI_part_not_isolated              905
#define PK_ERROR_part_not_isolated       ((PK_ERROR_code_t)  905)
#define KI_null_arg_address               906
#define PK_ERROR_null_arg_address        ((PK_ERROR_code_t)  906)
#define KI_bad_option_data                907
#define PK_ERROR_bad_option_data         ((PK_ERROR_code_t)  907)
#define KI_not_a_logical                  908
#define PK_ERROR_not_a_logical           ((PK_ERROR_code_t)  908)
#define KI_bad_box                        909
#define PK_ERROR_bad_box                 ((PK_ERROR_code_t)  909)
#define KI_bad_position                   911
#define PK_ERROR_bad_position            ((PK_ERROR_code_t)  911)
#define KI_empty_assy                     912
#define PK_ERROR_empty_assy              ((PK_ERROR_code_t)  912)
#define KI_keyed_part_mismatch            913
#define PK_ERROR_keyed_part_mismatch     ((PK_ERROR_code_t)  913)
#define KI_unsuitable_entity              914
#define PK_ERROR_unsuitable_entity       ((PK_ERROR_code_t)  914)
#define KI_not_on_surface                 915
#define PK_ERROR_not_on_surface          ((PK_ERROR_code_t)  915)
#define KI_bad_shared_entity              916
#define PK_ERROR_bad_shared_entity       ((PK_ERROR_code_t)  916)
#define KI_bad_shared_dep                 917
#define PK_ERROR_bad_shared_dep          ((PK_ERROR_code_t)  917)
#define KI_attr_type_not_defined          919
#define PK_ERROR_attr_type_not_defined   ((PK_ERROR_code_t)  919)
#define KI_bad_blend_param                920
#define PK_ERROR_bad_blend_param         ((PK_ERROR_code_t)  920)
#define KI_bad_sharing                    921
#define PK_ERROR_bad_sharing             ((PK_ERROR_code_t)  921)
#define KI_corrupt_file                   922
#define PK_ERROR_corrupt_file            ((PK_ERROR_code_t)  922)
#define KI_wrong_version                  923
#define PK_ERROR_wrong_version           ((PK_ERROR_code_t)  923)
#define KI_not_at_rollmark                924
#define PK_ERROR_not_at_rollmark         ((PK_ERROR_code_t)  924)
#define KI_radius_eq_0                    925
#define PK_ERROR_radius_eq_0             ((PK_ERROR_code_t)  925)
#define KI_radius_too_large               926
#define PK_ERROR_radius_too_large        ((PK_ERROR_code_t)  926)
#define KI_distance_too_large             927
#define PK_ERROR_distance_too_large      ((PK_ERROR_code_t)  927)
#define KI_cant_open_file                 928
#define PK_ERROR_cant_open_file          ((PK_ERROR_code_t)  928)
#define KI_at_terminator                  929
#define PK_ERROR_at_terminator           ((PK_ERROR_code_t)  929)
#define KI_bad_precision                  930
#define PK_ERROR_bad_precision           ((PK_ERROR_code_t)  930)
#define KI_modeller_not_started           931
#define PK_ERROR_modeller_not_started    ((PK_ERROR_code_t)  931)
#define KI_modeller_not_stopped           932
#define PK_ERROR_modeller_not_stopped    ((PK_ERROR_code_t)  932)
#define KI_bad_user_field_size            933
#define PK_ERROR_bad_user_field_size     ((PK_ERROR_code_t)  933)
#define KI_recursive_call                 934
#define PK_ERROR_recursive_call          ((PK_ERROR_code_t)  934)
#define KI_bad_hull                       935
#define PK_ERROR_bad_hull                ((PK_ERROR_code_t)  935)
#define KI_usfd_mismatch                  936
#define PK_ERROR_usfd_mismatch           ((PK_ERROR_code_t)  936)
#define KI_wrong_format                   937
#define PK_ERROR_wrong_format            ((PK_ERROR_code_t)  937)
#define KI_wire_body                      938
#define PK_ERROR_wire_body               ((PK_ERROR_code_t)  938)
#define KI_not_sheet                      939
#define PK_ERROR_not_sheet               ((PK_ERROR_code_t)  939)
#define KI_bad_wire                       940
#define PK_ERROR_bad_wire                ((PK_ERROR_code_t)  940)
#define KI_bad_end_points                 941
#define PK_ERROR_bad_end_points          ((PK_ERROR_code_t)  941)
#define KI_crossing_edge                  942
#define PK_ERROR_crossing_edge           ((PK_ERROR_code_t)  942)
#define KI_crossing_vertex                943
#define PK_ERROR_crossing_vertex         ((PK_ERROR_code_t)  943)
#define KI_bad_vertex                     944
#define PK_ERROR_bad_vertex              ((PK_ERROR_code_t)  944)
#define KI_aborted                        945
#define PK_ERROR_aborted                 ((PK_ERROR_code_t)  945)
#define KI_not_interrupted                946
#define PK_ERROR_not_interrupted         ((PK_ERROR_code_t)  946)
#define KI_run_time_error                 947
#define PK_ERROR_run_time_error          ((PK_ERROR_code_t)  947)
#define KI_fatal_error                    948
#define PK_ERROR_fatal_error             ((PK_ERROR_code_t)  948)
#define KI_no_user_fields                 949
#define PK_ERROR_no_user_fields          ((PK_ERROR_code_t)  949)
#define KI_wrong_surface                  950
#define PK_ERROR_wrong_surface           ((PK_ERROR_code_t)  950)
#define KI_opposed_sheets                 951
#define PK_ERROR_opposed_sheets          ((PK_ERROR_code_t)  951)
#define KI_coplanar                       952
#define PK_ERROR_coplanar                ((PK_ERROR_code_t)  952)
#define KI_bad_accuracy                   956
#define PK_ERROR_bad_accuracy            ((PK_ERROR_code_t)  956)
#define KI_coincident                     957
#define PK_ERROR_coincident              ((PK_ERROR_code_t)  957)
#define KI_atol_too_small                 958
#define PK_ERROR_atol_too_small          ((PK_ERROR_code_t)  958)
#define KI_ctol_too_small                 959
#define PK_ERROR_ctol_too_small          ((PK_ERROR_code_t)  959)
#define KI_stol_too_small                 960
#define PK_ERROR_stol_too_small          ((PK_ERROR_code_t)  960)
#define KI_wrong_direction                961
#define PK_ERROR_wrong_direction         ((PK_ERROR_code_t)  961)
#define KI_non_orth_matrix                962
#define PK_ERROR_non_orth_matrix         ((PK_ERROR_code_t)  962)
#define KI_bad_component                  963
#define PK_ERROR_bad_component           ((PK_ERROR_code_t)  963)
#define KI_bad_rollfile_size              964
#define PK_ERROR_bad_rollfile_size       ((PK_ERROR_code_t)  964)
#define KI_cant_be_aborted                965
#define PK_ERROR_cant_be_aborted         ((PK_ERROR_code_t)  965)
#define KI_hulls_intersect                966
#define PK_ERROR_hulls_intersect         ((PK_ERROR_code_t)  966)
#define KI_abort_from_go                  967
#define PK_ERROR_abort_from_go           ((PK_ERROR_code_t)  967)
#define KI_all_faces_in_body              969
#define PK_ERROR_all_faces_in_body       ((PK_ERROR_code_t)  969)
#define KI_schema_access_error            970
#define PK_ERROR_schema_access_error     ((PK_ERROR_code_t)  970)
#define KI_schema_corrupt                 971
#define PK_ERROR_schema_corrupt          ((PK_ERROR_code_t)  971)
#define KI_cant_intsc_solid_sheet         972
#define PK_ERROR_cant_intsc_solid_sheet  ((PK_ERROR_code_t)  972)
#define KI_file_access_error              973
#define PK_ERROR_file_access_error       ((PK_ERROR_code_t)  973)
#define KI_bad_file_format                974
#define PK_ERROR_bad_file_format         ((PK_ERROR_code_t)  974)
#define KI_bad_file_guise                 975
#define PK_ERROR_bad_file_guise          ((PK_ERROR_code_t)  975)
#define KI_bad_rolling_ball               976
#define PK_ERROR_bad_rolling_ball        ((PK_ERROR_code_t)  976)
#define KI_coincident_points              977
#define PK_ERROR_coincident_points       ((PK_ERROR_code_t)  977)
#define KI_bad_knots                      978
#define PK_ERROR_bad_knots               ((PK_ERROR_code_t)  978)
#define KI_bad_derivative                 979
#define PK_ERROR_bad_derivative          ((PK_ERROR_code_t)  979)
#define KI_wrong_number_knots             980
#define PK_ERROR_wrong_number_knots      ((PK_ERROR_code_t)  980)
#define KI_wrong_number_derivs            981
#define PK_ERROR_wrong_number_derivs     ((PK_ERROR_code_t)  981)
#define KI_incompatible_props             982
#define PK_ERROR_incompatible_props      ((PK_ERROR_code_t)  982)
#define KI_repeated_knots                 983
#define PK_ERROR_repeated_knots          ((PK_ERROR_code_t)  983)
#define KI_curves_dont_meet               984
#define PK_ERROR_curves_dont_meet        ((PK_ERROR_code_t)  984)
#define KI_insufficient_curves            985
#define PK_ERROR_insufficient_curves     ((PK_ERROR_code_t)  985)
#define KI_bad_curves                     986
#define PK_ERROR_bad_curves              ((PK_ERROR_code_t)  986)
#define KI_bad_order                      987
#define PK_ERROR_bad_order               ((PK_ERROR_code_t)  987)
#define KI_insufficient_points            988
#define PK_ERROR_insufficient_points     ((PK_ERROR_code_t)  988)
#define KI_bad_parametric_prop            989
#define PK_ERROR_bad_parametric_prop     ((PK_ERROR_code_t)  989)
#define KI_illegal_owner                  990
#define PK_ERROR_illegal_owner           ((PK_ERROR_code_t)  990)
#define KI_unchecked_entity               991
#define PK_ERROR_unchecked_entity        ((PK_ERROR_code_t)  991)
#define KI_incompatible_curves            992
#define PK_ERROR_incompatible_curves     ((PK_ERROR_code_t)  992)
#define KI_cant_make_bspline              993
#define PK_ERROR_cant_make_bspline       ((PK_ERROR_code_t)  993)
#define KI_cu_are_coincident              994
#define PK_ERROR_cu_are_coincident       ((PK_ERROR_code_t)  994)
#define KI_withdrawn_surface              995
#define PK_ERROR_withdrawn_surface       ((PK_ERROR_code_t)  995)
#define KI_face_not_planar                996
#define PK_ERROR_face_not_planar         ((PK_ERROR_code_t)  996)
#define KI_request_not_supported          997
#define PK_ERROR_request_not_supported   ((PK_ERROR_code_t)  997)
#define KI_contradictory_request          998
#define PK_ERROR_contradictory_request   ((PK_ERROR_code_t)  998)
#define KI_invalid_geometry               999
#define PK_ERROR_invalid_geometry        ((PK_ERROR_code_t)  999)
#define KI_file_already_exists           1000
#define PK_ERROR_file_already_exists     ((PK_ERROR_code_t) 1000)
#define KI_too_many_control_pts          1001
#define PK_ERROR_too_many_control_pts    ((PK_ERROR_code_t) 1001)
#define KI_bad_string                    1002
#define PK_ERROR_bad_string              ((PK_ERROR_code_t) 1002)
#define KI_mend_attempt_failure          1003
#define PK_ERROR_mend_attempt_failure    ((PK_ERROR_code_t) 1003)
#define KI_bad_tag_in_list_tree          1004
#define PK_ERROR_bad_tag_in_list_tree    ((PK_ERROR_code_t) 1004)
#define KI_bad_list_tree                 1005
#define PK_ERROR_bad_list_tree           ((PK_ERROR_code_t) 1005)
#define KI_cyclic_list_reference         1006
#define PK_ERROR_cyclic_list_reference   ((PK_ERROR_code_t) 1006)
#define KI_empty_list_in_tree            1007
#define PK_ERROR_empty_list_in_tree      ((PK_ERROR_code_t) 1007)
#define KI_cant_make_trimmed_sf          1008
#define PK_ERROR_cant_make_trimmed_sf    ((PK_ERROR_code_t) 1008)
#define KI_bad_entity_event_comb         1009
#define PK_ERROR_bad_entity_event_comb   ((PK_ERROR_code_t) 1009)
#define KI_too_many_derivatives          1010
#define PK_ERROR_too_many_derivatives    ((PK_ERROR_code_t) 1010)
#define KI_bad_deriv_vertices            1011
#define PK_ERROR_bad_deriv_vertices      ((PK_ERROR_code_t) 1011)
#define KI_bad_degen_vertices            1012
#define PK_ERROR_bad_degen_vertices      ((PK_ERROR_code_t) 1012)
#define KI_not_on_edge                   1013
#define PK_ERROR_not_on_edge             ((PK_ERROR_code_t) 1013)
#define KI_closest_approach_failed       1014
#define KI_cant_do_clash                 1015
#define PK_ERROR_cant_do_clash           ((PK_ERROR_code_t) 1015)
#define KI_targ_faces_many_bodies        1016
#define PK_ERROR_targ_faces_many_bodies  ((PK_ERROR_code_t) 1016)
#define KI_tool_faces_many_bodies        1017
#define PK_ERROR_tool_faces_many_bodies  ((PK_ERROR_code_t) 1017)
#define KI_cant_do_imprint               1018
#define PK_ERROR_cant_do_imprint         ((PK_ERROR_code_t) 1018)
#define KI_topol_not_from_body           1019
#define PK_ERROR_topol_not_from_body     ((PK_ERROR_code_t) 1019)
#define KI_inconsistent_facesets         1020
#define PK_ERROR_inconsistent_facesets   ((PK_ERROR_code_t) 1020)
#define KI_FG_evaluator_not_found        1021
#define PK_ERROR_FG_evaluator_not_found  ((PK_ERROR_code_t) 1021)
#define KI_FG_data_alloc_error           1022
#define PK_ERROR_FG_data_alloc_error     ((PK_ERROR_code_t) 1022)
#define KI_FG_data_not_found             1023
#define PK_ERROR_FG_data_not_found       ((PK_ERROR_code_t) 1023)
#define KI_FG_evaluator_error            1024
#define PK_ERROR_FG_evaluator_error      ((PK_ERROR_code_t) 1024)
#define KI_FG_modelling_error            1025
#define PK_ERROR_FG_modelling_error      ((PK_ERROR_code_t) 1025)
#define KI_solid_body                    1026
#define PK_ERROR_solid_body              ((PK_ERROR_code_t) 1026)
#define KI_different_bodies              1027
#define PK_ERROR_different_bodies        ((PK_ERROR_code_t) 1027)
#define KI_wrong_number_edges            1028
#define PK_ERROR_wrong_number_edges      ((PK_ERROR_code_t) 1028)
#define KI_cant_blend_vertex             1029
#define PK_ERROR_cant_blend_vertex       ((PK_ERROR_code_t) 1029)
#define KI_blends_overlap                1030
#define PK_ERROR_blends_overlap          ((PK_ERROR_code_t) 1030)
#define KI_edges_intersect               1031
#define PK_ERROR_edges_intersect         ((PK_ERROR_code_t) 1031)
#define KI_not_in_same_body              1032
#define PK_ERROR_not_in_same_body        ((PK_ERROR_code_t) 1032)
#define KI_unsuitable_topology           1033
#define PK_ERROR_unsuitable_topology     ((PK_ERROR_code_t) 1033)
#define KI_cu_self_intersect             1034
#define PK_ERROR_cu_self_intersect       ((PK_ERROR_code_t) 1034)
#define KI_linear_multi_seg              1035
#define PK_ERROR_linear_multi_seg        ((PK_ERROR_code_t) 1035)
#define KI_no_eds_from_target            1036
#define PK_ERROR_no_eds_from_target      ((PK_ERROR_code_t) 1036)
#define KI_cant_offset                   1037
#define PK_ERROR_cant_offset             ((PK_ERROR_code_t) 1037)
#define KI_FG_real_data_error            1038
#define PK_ERROR_FG_real_data_error      ((PK_ERROR_code_t) 1038)
#define KI_FG_integer_data_error         1039
#define PK_ERROR_FG_integer_data_error   ((PK_ERROR_code_t) 1039)
#define KI_partial_coi_found             1040
#define PK_ERROR_partial_coi_found       ((PK_ERROR_code_t) 1040)
#define KI_bodies_dont_knit              1041
#define PK_ERROR_bodies_dont_knit        ((PK_ERROR_code_t) 1041)
#define KI_pattern_invalid               1042
#define PK_ERROR_pattern_invalid         ((PK_ERROR_code_t) 1042)
#define KI_bad_tolerance                 1043
#define PK_ERROR_bad_tolerance           ((PK_ERROR_code_t) 1043)
#define KI_cant_extract_geom             1044
#define PK_ERROR_cant_extract_geom       ((PK_ERROR_code_t) 1044)
#define KI_bad_basis_surf                1045
#define PK_ERROR_bad_basis_surf          ((PK_ERROR_code_t) 1045)
#define KI_FG_receive_failure            1046
#define PK_ERROR_FG_receive_failure      ((PK_ERROR_code_t) 1046)
#define KI_FG_snapshot_failure           1047
#define PK_ERROR_FG_snapshot_failure     ((PK_ERROR_code_t) 1047)
#define KI_cant_create_pattern           1048
#define PK_ERROR_cant_create_pattern     ((PK_ERROR_code_t) 1048)
#define KI_tag_limit_exceeded            1049
#define PK_ERROR_tag_limit_exceeded      ((PK_ERROR_code_t) 1049)
#define KI_tag_limit_out_of_range        1050
#define PK_ERROR_tag_limit_out_of_range  ((PK_ERROR_code_t) 1050)
#define KI_cant_find_extreme             1051
#define PK_ERROR_cant_find_extreme       ((PK_ERROR_code_t) 1051)
#define KI_disc_full                     1052
#define PK_ERROR_disc_full               ((PK_ERROR_code_t) 1052)
#define KI_cant_find_derivs              1053
#define PK_ERROR_cant_find_derivs        ((PK_ERROR_code_t) 1053)
#define KI_too_many_targets              1054
#define PK_ERROR_too_many_targets        ((PK_ERROR_code_t) 1054)
#define KI_duplicate_targets             1055
#define PK_ERROR_duplicate_targets       ((PK_ERROR_code_t) 1055)
#define KI_curve_already_trimmed         1056
#define PK_ERROR_curve_already_trimmed   ((PK_ERROR_code_t) 1056)
#define KI_curve_too_short               1057
#define PK_ERROR_curve_too_short         ((PK_ERROR_code_t) 1057)
#define KI_boolean_failure               1058
#define PK_ERROR_boolean_failure         ((PK_ERROR_code_t) 1058)
#define KI_duplicate_item                1059
#define PK_ERROR_duplicate_item          ((PK_ERROR_code_t) 1059)
#define KI_failed_to_trim                1060
#define PK_ERROR_failed_to_trim          ((PK_ERROR_code_t) 1060)
#define KI_unsuitable_loop               1061
#define PK_ERROR_unsuitable_loop         ((PK_ERROR_code_t) 1061)
#define KI_failed_to_replace             1062
#define PK_ERROR_failed_to_replace       ((PK_ERROR_code_t) 1062)
#define KI_failed_to_create_sp           1063
#define PK_ERROR_failed_to_create_sp     ((PK_ERROR_code_t) 1063)
#define KI_tolerances_too_tight          1064
#define PK_ERROR_tolerances_too_tight    ((PK_ERROR_code_t) 1064)
#define KI_fru_error                     1065
#define PK_ERROR_fru_error               ((PK_ERROR_code_t) 1065)
#define KI_incorrect_mc_conf             1066
#define PK_ERROR_incorrect_mc_conf       ((PK_ERROR_code_t) 1066)
#define KI_partial_no_intersect          1067
#define PK_ERROR_partial_no_intersect    ((PK_ERROR_code_t) 1067)
#define KI_none_shared                   1068
#define PK_ERROR_none_shared             ((PK_ERROR_code_t) 1068)
#define KI_cant_hollow                   1069
#define PK_ERROR_cant_hollow             ((PK_ERROR_code_t) 1069)
#define KI_not_in_same_shell             1070
#define PK_ERROR_not_in_same_shell       ((PK_ERROR_code_t) 1070)
#define KI_general_body                  1071
#define PK_ERROR_general_body            ((PK_ERROR_code_t) 1071)
#define KI_bad_thickness                 1072
#define PK_ERROR_bad_thickness           ((PK_ERROR_code_t) 1072)
#define KI_non_smooth_edge               1073
#define PK_ERROR_non_smooth_edge         ((PK_ERROR_code_t) 1073)
#define KI_degenerate_vertex             1074
#define PK_ERROR_degenerate_vertex       ((PK_ERROR_code_t) 1074)
#define KI_cant_thicken                  1075
#define PK_ERROR_cant_thicken            ((PK_ERROR_code_t) 1075)
#define KI_crossing_face                 1076
#define PK_ERROR_crossing_face           ((PK_ERROR_code_t) 1076)
#define KI_not_in_region                 1077
#define PK_ERROR_not_in_region           ((PK_ERROR_code_t) 1077)
#define KI_empty_body                    1078
#define PK_ERROR_empty_body              ((PK_ERROR_code_t) 1078)
#define KI_sheet_untrimmed               1079
#define PK_ERROR_sheet_untrimmed         ((PK_ERROR_code_t) 1079)
#define KI_fxf_blend_failed              1080
#define PK_ERROR_fxf_blend_failed        ((PK_ERROR_code_t) 1080)
#define KI_fxf_blend_bad_token           1081
#define PK_ERROR_fxf_blend_bad_token     ((PK_ERROR_code_t) 1081)
#define KI_file_read_corruption          1082
#define PK_ERROR_file_read_corruption    ((PK_ERROR_code_t) 1082)
#define KI_trim_loop_degenerate          1083
#define PK_ERROR_trim_loop_degenerate    ((PK_ERROR_code_t) 1083)
#define KI_solid_has_void                1084
#define PK_ERROR_solid_has_void          ((PK_ERROR_code_t) 1084)
#define KI_fru_missing                   1085
#define PK_ERROR_fru_missing             ((PK_ERROR_code_t) 1085)
#define KI_not_in_same_partition         1086
#define PK_ERROR_not_in_same_partition   ((PK_ERROR_code_t) 1086)
#define KI_instanced_body                1087
#define PK_ERROR_instanced_body          ((PK_ERROR_code_t) 1087)
#define KI_entity_not_new                1088
#define PK_ERROR_entity_not_new          ((PK_ERROR_code_t) 1088)
#define KI_applio_not_registered         1089
#define PK_ERROR_applio_not_registered   ((PK_ERROR_code_t) 1089)
#define KI_more_than_one_part            1090
#define PK_ERROR_more_than_one_part      ((PK_ERROR_code_t) 1090)
#define KI_bad_field_conversion          1091
#define PK_ERROR_bad_field_conversion    ((PK_ERROR_code_t) 1091)
#define KI_bad_text_conversion           1092
#define PK_ERROR_bad_text_conversion     ((PK_ERROR_code_t) 1092)
#define KI_not_licensed                  1093
#define PK_ERROR_not_licensed            ((PK_ERROR_code_t) 1093)
#define KI_schema_incompatible           1094
#define PK_ERROR_schema_incompatible     ((PK_ERROR_code_t) 1094)
#define KI_write_memory_full             1095
#define PK_ERROR_write_memory_full       ((PK_ERROR_code_t) 1095)
#define KI_compound_body                 1096
#define PK_ERROR_compound_body           ((PK_ERROR_code_t) 1096)
#define PK_ERROR_ok                      ((PK_ERROR_code_t)    0)

#endif /* PARASOLID_IFAILS_H_INCLUDED */

