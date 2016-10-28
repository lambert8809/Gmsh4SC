/*
  Copyright 2013 Siemens Product Lifecycle Management Software Inc. All rights reserved.
  This software and related documentation are proprietary to 
  Siemens Product Lifecycle Management Software Inc.
*/
#ifndef FRUSTRUM_IFAILS_H
#define FRUSTRUM_IFAILS_H

/* Frustrum Ifails */

#define FR_no_errors         (    0) /* operation was successful */
#define FR_bad_name          (    1) /* bad filename */
#define FR_not_found         (    2) /* file of given name does not exist */
#define FR_already_exists    (    3) /* file of given name already exists */
#define FR_end_of_file       (    4) /* file pointer is at end of file */
#define FR_open_fail         (   10) /* unspecified open error, eg, already open, wrong format, protection */
#define FR_disc_full         (   11) /* no space available to extend the file */
#define FR_write_fail        (   12) /* unspecified write error */
#define FR_read_fail         (   13) /* unspecified read error */
#define FR_close_fail        (   14) /* unspecified close error */
#define FR_memory_full       (   15) /* insufficient contiguous virtual memory */
#define FR_bad_header        (   16) /* bad header found opening file for read */
#define FR_write_memory_full (   17) /* insufficient virtual memory for write */
#define FR_rollmark_op_pass  (   20) /* Rollmark operation within frustrum passed */
#define FR_rollmark_op_fail  (   21) /* Rollmark operation within frustrum failed */
#define FR_unspecified       (   99) /* unspecified error, eg, bad function arguments or call sequence */

/* Graphics Ifails */

#define CONTIN (    0) /* Continue: no errors */
#define ABORT  (-1011) /* Abort: return control to caller */

/* Foreign Geometry Ifails */

#define FGOPOK (    0) /* Foreign geometry operation successful */
#define FGOPFA (    1) /* Foreign geometry operation failed */
#define FGEVIN (    2) /* Foreign geometry evaluation incomplete */
#define FGPROP (    3) /* use default properties for foreign geometry */
#define FGGEOM (    4) /* Foreign geometry not found */
#define FGDATA (    5) /* Foreign geometry data retrieve error */
#define FGFILE (    6) /* Foreign geometry data file error */
#define FGRERR (    7) /* Foreign geometry real data error */
#define FGIERR (    8) /* Foreign geometry integer data error */
#endif /* FRUSTRUM_IFAILS_H */

/* End Ifails */

