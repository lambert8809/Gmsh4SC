/* ============================================================================

  Copyright 2009 Siemens Product Lifecycle Management Software Inc.
  All rights reserved.
  This software and related documentation are proprietary to
  Siemens Product Lifecycle Management Software Inc.

  Example Foreign Geometry support routines

  Code last modified : 25 April 1997

  Siemens Product Lifecycle Management Software assumes no responsibility for
  the use or reliability of this software. It is provided in order to give
  application writers access to an example of a how to build Foreign
  Geometry support into a working Frustrum.

  NOTE: a Frustrum will be inherently machine-specific; however for this
  example much of this type of code has been omitted.

============================================================================ */

/* Imports */

#include <math.h>
#include <ctype.h>

/*
    VMS:    CC/INCLUDE=(PARASOLID:)
    Unix:   cc -I$PARASOLID
*/

#include "frustrum_ifails.h"
#include "frustrum_tokens.h"

/* ============================================================================
   Summary of Codes & Tokens

The following frustrum ifail values & tokens are used in this file:

 FGOPOK      Foreign geometry operation successful
 FGOPFA      Foreign geometry operation failed
 FGEVIN      Foreign geometry evaluation incomplete
 FGPROP      Use default properties for foreign geometry
 FGGEOM      Foreign geometry not found
 FGDATA      Foreign geometry data retrieve error
 FGFILE      Foreign geometry data file error
 FGIERR      Foreign geometry integer data error
 FGRERR      Foreign geometry real data error

 FGEVTR      Triangular evaluation matrix required
 FGEVSQ      Square evaluation matrix required
 FGPRBD      Geometry parameterisation is bounded
 FGPRPE      Geometry parameterisation is periodic

============================================================================ */


/* Useful #defines */

#define  square(value) ( (value)*(value) )
#define  pi            ( 3.1415926535897932384626434 )
#define  two_pi        ( 2.0 * pi )
#define  four_pi       ( 4.0 * pi )
#define  TRUE     1
#define  FALSE    0
#define  NULL_PTR 0


/* Exported functions */

extern void FGCRCU(const char *, int *, int *, int *, int *,
double *, int *, double *, int *);
extern void FGCRSU(const char *, int *, int *, int *, int *,
double *, int *, double *, int *);
extern void FGEVCU(int *, double *, double *, double *, int *,
double *, int *);
extern void FGEVSU(int *, double *, double *, double *, double *
, int *, int *, int *, double *, int *);
extern void FGPRCU(int *, double *, double *, double *, int *,
int *);
extern void FGPRSU(int *, double *, double *, double *, int *,
int *);

/* Typedefs */

typedef void (*curve_evaluator)( int [], double [], double [],
                                   double*, int*, double [], int*);
typedef void (*surface_evaluator)( int [], double [], double*, double*,
                                   double*, int*, int*, int*, double [],
                                   int*);


/* ============================================================================
   UTILITIES for surface evaluation array indices

The following functions are designed to assist (surface evaluator functions
called by) FGEVSU which returns surface evaluations. They assess if a
derivative is required based upon the numbers of u & v derivatives requested,
nu & nv, and the triangular flag tri.

The value TRUE is returned if an evaluation is required, otherwise FALSE
is returned.

If TRUE is returned then the value of n is also modified to point to the
correct place in the results array to place the actual evaluations.
============================================================================ */


static int su_P( int* n, int nu, int nv, int tri) /* Index for surface positon P */
{ *n = 0; return TRUE; }

static int su_dP_du(int* n, int nu, int nv, int tri)   /* Index for surface u derivative dP/du */
{
 int do_eval = FALSE;
 if (nu > 0) { *n = 3; do_eval = TRUE; }
 return do_eval;
}


static int su_dP2_du2( int* n, int nu, int nv, int tri) /* Index surface 2nd u derivative d2P/du2 */
{
 int do_eval;
 do_eval = FALSE;
 if (nu > 1) { *n = 6; do_eval = TRUE; }
 return do_eval;
}


static int su_dP_dv( int* n, int nu, int nv, int tri)  /* Index for surface v derivative dP/dv */
{
 int do_eval;
 do_eval = FALSE;
 if (nv > 0) {*n = 3 * (nu + 1); do_eval = TRUE; }
 return do_eval;
}


static int su_dP2_dv2( int* n, int nu, int nv, int tri) /* Index surface 2nd v derivative d2P/dv2 */
{
 int triang, do_eval;

 do_eval = FALSE; triang = (tri == FGEVSQ) ? 0 : 1;
 if (nv > 1) { *n = ( 6*nu + 3*(2-triang) ); do_eval = TRUE; }

 return do_eval;
}


static int su_dP2_dudv( int* n, int nu, int nv, int tri) /* Index for mixed derivative d2P/duduv */
{
 int triang, do_eval;

 do_eval = FALSE; triang = (tri == FGEVSQ) ? 0 : 1;

 if ((nu > 0 && nv > 0 && triang == 0) ||(nu > 1 && triang == 1 ))
    { *n = (3 * (nu + 2)); do_eval = TRUE;}

 return do_eval;
}



/* ============================================================================
   UTILITIES for curve evaluation array indices

The following functions are designed to assist the function FGEVCU which
returns curve evaluations. They modify the value of n, which is an index into
the results array, based upon the numbers of t derivatives requested, nt.

The value TRUE is returned if an evaluation is required, otherwise FALSE
is returned.

If TRUE is returned then the value of n is modified to point to the correct
place in the results array to begin filling in data.
============================================================================ */


static int cu_P( int* n, int nt)        /* Array index for curve position P */
{ *n = 0; return TRUE; }

static int cu_dP_dt( int* n, int nt)    /* Array index for curve 1st derivative dP/dt */
{
 int do_eval; do_eval = FALSE;
 if (nt > 0) { *n = 3; do_eval = TRUE; }
 return do_eval;
}


static int cu_dP2_dt2( int* n, int nt) /* Array index for curve 2nd derivative d2P/dt2 */
{
 int do_eval; do_eval = FALSE;
 if (nt > 1){ *n = 6; do_eval = TRUE; }
 return do_eval;
}



/* ============================================================================
   UTILITIES for checking parameters of call to FGEVCU, FGEVSU

The following two functions, su_check_params & cu_check_params are called by
FGEVSU, FGEVCU respectively to check on the status of the evaluations
requested by Parasolid. The ifail status is modified accordingly.

Return ifail codes:
    FGOPOK     Operation successful
    FGOPFA     Operation fails
    FGEVIN     Evaluation incomplete

============================================================================ */


static int su_check_params( int ifail, int nu, int nv, int triang)
{
 return
    (ifail == FGOPOK)
    ? ( ( (triang != FGEVSQ && (nu > 2 || nv > 2)) ||
          (triang == FGEVSQ && ((nu + nv) >= 3)
      ) )
        ? FGEVIN
        : FGOPOK
      )
    : FGOPFA;
}


static int cu_check_params( int ifail, int nt)
{
 return( (ifail == FGOPOK)
         ? ((nt > 2)
             ? FGEVIN
             : FGOPOK )
         : FGOPFA );
}



/* ============================================================================
   UTILITY for key handling

This function compares the first n characters of s1 and s2
and returns TRUE if they are all equal. The function is not sensitive to the
case of the characters in s1, s2
============================================================================ */


static int keycmpu( char* s1, const char* s2, int n)
{
 int i, result;
 result = TRUE;
 i = n;
 while (i-- > 0 && result)
  {
  char c1 = s1[i], c2 = s2[i];
  /* Note: some versions of toupper always add 64 regardless */
  if (islower( c1 )) c1 = toupper( c1 );
  if (islower( c2 )) c2 = toupper( c2 );
  if (c1 != c2)
   result = FALSE;
  }
 return result;
}



/* ============================================================================
   EXAMPLE CURVE EVALUATORS

The following section contains example curve evaluators.
============================================================================ */


static void sine( int ki_ints[], double ki_reals[], double pe_data[],
                  double* t, int* nderivs, double results[], int* ifail)
/* description: Example evaluator sine

This is the curve  t -> ( t, A * sin(2 * pi * t), 0 )
*/
{
 int n;                        /*   Array index        */
 double A = ki_reals[0];       /*   Amplitude of curve */

 /*   compute P(t) and derivs as requested  */

 if (cu_P( &n, *nderivs ))
  {
   /*   compute position  */
   results[n++] = *t;
   results[n++] = A * sin(two_pi * (*t));
   results[n]   = 0.0;
  }

 if (cu_dP_dt( &n, *nderivs ))
  {
   /*   compute 1st derivs  */
   results[n++] = 1.0;
   results[n++] = A * two_pi * cos(two_pi * (*t));
   results[n]   = 0.0;
  }

 if (cu_dP2_dt2( &n, *nderivs ))
  {
   /*   compute 2nd derivs  */
   results[n++] = 0.0;
   results[n++] = - A * square(two_pi) * sin(two_pi * (*t));
   results[n]   = 0.0;
  }

 *ifail = cu_check_params( *ifail, *nderivs );
 return;
}


static void helix( int ki_ints[], double ki_reals[], double pe_data[],
                   double* t, int* nderivs, double results[], int* ifail)
/* description: Example evaluator helix

This is the curve t ->( cos(4*pi*t), sin(4*pi*t), t )
*/
{
 int n; /*   Array index */

 if (cu_P( &n, *nderivs ))
  {
   /*   compute p(t)  */
   results[n++] = (cos( *t * four_pi ));
   results[n++] = (sin( *t * four_pi ));
   results[n]   = *t;
  }
 if (cu_dP_dt( &n, *nderivs ))
  {
   /*   compute : 1st derivs  */
   results[n++] = - four_pi * sin( *t * four_pi );
   results[n++] =   four_pi * cos( *t * four_pi );
   results[n]   = 1.0;
  }

 if (cu_dP2_dt2( &n, *nderivs ))
  {
   /*   compute : 2nd derivs  */
   results[n++] = - square( four_pi ) * cos( *t * four_pi );
   results[n++] = - square( four_pi ) * sin( *t * four_pi );
   results[n]   = 0.0;
  }

 *ifail = cu_check_params( *ifail, *nderivs );
 return;
}



/* ============================================================================
   EXAMPLE SURFACE EVALUATORS

The following section contains examples of surface evaluators. They are called
directly by FGEVSU and return position and derivatives as requested.
============================================================================ */


static void corrugated( int ki_ints[], double ki_reals[], double* pe_data,
                        double* u, double* v, int* nu, int* nv, int* triang,
                        double results[], int* ifail)
/* description: Example corrugated evaluator

This is the function (u, v) -> (u, v, A * sin( 2.0 * pi * u))
The amplitude A is stored in ki_reals[0]
*/
{
 int    n; /*   Position in results array */
 double A; /*   Amplitude of wave */

 n = 0;
 A = ki_reals[0];  /* Initialise amplitude */

 if (su_P( &n, *nu, *nv, *triang ))
  {
   /*   compute : P  */
   results[n++] = *u;
   results[n++] = *v;
   results[n]   =  A * sin(*u * two_pi);
  }

 if (su_dP_du( &n, *nu, *nv, *triang ))
  {
   /*   compute : Pu  */
   results[n++] = 1.0;
   results[n++] = 0.0;
   results[n]   = two_pi * A * cos(*u * two_pi);
  }

 if (su_dP2_du2( &n, *nu, *nv, *triang ))
  {
   /*   compute : Puu  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n]   = - square(two_pi) * sin(*u * two_pi);
  }

 if (su_dP_dv( &n, *nu, *nv, *triang ))
  {
   /*   compute : Pv  */
   results[n++] = 0.0;
   results[n++] = 1.0;
   results[n]   = 0.0;
  }

 if (su_dP2_dv2( &n, *nu, *nv, *triang ))
  {
   /*   compute : Pvv  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n]   = 0.0;
  }

 if (su_dP2_dudv( &n, *nu, *nv, *triang ))
  {
   /*   compute : Puv  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n] = 0.0;
  }
 *ifail = su_check_params(*ifail, *nu, *nv, *triang);

 return;
}


static void incline( int ki_ints[], double ki_reals[], double* pe_data,
                     double* u, double* v, int* nu, int* nv, int* triang,
                     double results[], int* ifail)
/* description: Example planar evaluator

This is the evaluator (u, v) -> (u, v, u)
*/
{
 int    n; /*   Position in results array */

 n = 0;

 if (su_P( &n, *nu, *nv, *triang ))
  {
   /*   compute : P  */
   results[n++] = *u;
   results[n++] = *v;
   results[n]   = *u;
  }

 if (su_dP_du( &n, *nu, *nv, *triang ))
  {
   /*   compute : Pu  */
   results[n++] = 1.0;
   results[n++] = 0.0;
   results[n]   = 1.0;
  }

 if (su_dP2_du2( &n, *nu, *nv, *triang ))
  {
   /*   compute : Puu  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n]   = 0.0;
  }

 if (su_dP_dv( &n, *nu, *nv, *triang ))
  {
   /*   compute : Pv  */
   results[n++] = 0.0;
   results[n++] = 1.0;
   results[n]   = 0.0;
  }

 if (su_dP2_dv2( &n, *nu, *nv, *triang ))
  {
   /*   compute : Pvv  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n]   = 0.0;
  }

 if (su_dP2_dudv( &n, *nu, *nv, *triang ))
  {
   /*   compute : Puv  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n] = 0.0;
  }
 *ifail = su_check_params(*ifail, *nu, *nv, *triang);

 return;
}


static void franke( int* ki_ints, double* ki_reals, double* pe_data, double* u,
                    double* v, int* nu, int* nv, int* triang, double results[],
                    int* ifail)
/* description: Example evaluator franke

This is a complex analytical surface defined using the exponential function.

*/
{
 int n;         /*   Position in results array                */
 double e[4];   /*   Useful variables for future calculations */
 n = 0;


 e[0] = exp( -( square(9.0*(*u) - 2.0)      + square(9.0*(*v) - 2.0))/4.0);
 e[1] = exp( -( square(9.0*(*u) + 1.0)/49.0 + (9.0*(*v) + 1.0)/10.0)     );
 e[2] = exp( -( square(9.0*(*u) - 7.0)      + square(9.0*(*v) - 3.0))/4.0);
 e[3] = exp( -( square(9.0*(*u) - 4.0)      + square(9.0*(*v) - 7.0))    );

 if (su_P( &n, *nu, *nv, *triang ))
  {
   /*  compute P  */
   results[n++] = *u;
   results[n++] = *v;
   results[n] = 0.75 * e[0] + 0.75 * e[1] + 0.5 * e[2] - 0.2 * e[3];
  }
 if (su_dP_du( &n, *nu, *nv, *triang ))
  {
   /*  compute Pu  */
   results[n++] = 1.0;
   results[n++] = 0.0;
   results[n] =  -3.37500 * (9.0 * (*u) - 2.0) * e[0]
                - 0.27551 * (9.0 * (*u) + 1.0) * e[1]
                - 2.25000 * (9.0 * (*u) - 7.0) * e[2]
                + 3.60000 * (9.0 * (*u) - 4.0) * e[3];
  }

 if (su_dP2_du2( &n, *nu, *nv, *triang ))
  {
   /*  compute Puu  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n] =  -30.375    * e[0]
                + 15.1875   * square(9.0 * (*u) - 2.0) * e[0]
                - 2.47959   * e[1]
                +  0.101208 * square(9.0 * (*u) + 1.0) * e[1]
                - 20.25     * e[2]
                + 10.125    * square(9.0 * (*u) - 7.0) * e[2]
                + 32.4      * e[3]
                - 64.8      * square(9.0 * (*u) - 4.0) * e[3];
  }

 if (su_dP_dv( &n, *nu, *nv, *triang ))
  {
   /*  compute Pv  */
   results[n++] = 0.0;
   results[n++] = 1.0;
   results[n] =  -3.375 * (9.0 * (*v) - 2.0) * e[0]
                - 0.675 * e[1]
                - 2.250 * (9.0 * (*v) - 3.0) * e[2]
                + 3.600 * (9.0 * (*v) - 7.0) * e[3];
  }

 if (su_dP2_dv2( &n, *nu, *nv, *triang ))
  {
   /*   compute Pvv  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n] =  -30.75   * e[0]
                + 15.1875 * square(9.0 * (*v) - 2.0) * e[0]
                + 0.6075  * e[1]
                - 20.25   * e[2]
                + 10.125  * square(9.0 * (*v) - 3.0) * e[2]
                + 32.4    * e[3]
                - 64.8    * square(9.0 * (*v) - 7.0) * e[3];
  }
 if (su_dP2_dudv( &n, *nu, *nv, *triang ))
  {
   /*   compute Puv  */
   results[n++] = 0.0;
   results[n++] = 0.0;
   results[n] =   15.87500 * (9.0 * (*u) - 2.0) * (9.0 * (*v) - 2.0) * e[0]
                +  0.24796 * (9.0 * (*u) + 1.0) * e[1]
                + 10.125   * (9.0 * (*u) - 7.0) * (9.0 * (*v) - 3.0) * e[2]
                - 64.8     * (9.0 * (*u) - 4.0) * (9.0 * (*v) - 7.0) * e[3];
  }

 *ifail = su_check_params( *ifail, *nu, *nv, *triang );
 return;
}



/* ============================================================================
   EXPORTED FUNCTIONS

This final section contains exported functions. These are:

   FGCRCU, FGCRSU for creating foreign geometry curves and surfaces,
   FGEVCU, FGEVSU for creating foreign geometry curves and surfaces,
   FGPRCU, FGPRSU for properties of foreign geometry curves and surfaces.

============================================================================ */


void FGCRCU(const char* key, int* keylen, int* n_kii, int* ki_ints, int* n_kir,
            double* ki_reals, int* n_data, double* fg_data, int* ifail )
/* description: FGCRCU

This function is called when an FG curve is created by the KI function CRFGCU.
The function initialises any data required by the evaluator. A successful call
to this function indicates to Parasolid that evaluations of this curve may be
requested.

ifail return values:

   FGOPOK       Operation successful
   FGOPFA       Operation failed
   FGGEOM       Evaluator not available
   FGDATA       Evaluator data not found
   FGIERR       Error in supplied integer data
   FGRERR       Error in supplied real data
   FGFILE       Evaluator data allocation fault

*/
{
 const char *key_ptr;                       /* define locals & initialise */
 key_ptr = key;
 *(int *) fg_data = NULL_PTR;

 *ifail = FGOPOK;

 /*  select curve evaluator  */

 if (keycmpu( "SDL/sine", key, *keylen ))
   {
   if( *n_kir == 2               /* sine evaluator requires two reals    */
       && ki_reals[1] > 0.0 )    /* of which second needs to be positive */
      *(curve_evaluator *) fg_data = sine;
   else *ifail = FGRERR;
   }
 else
 if (keycmpu( "SDL/helix", key, *keylen ))
   *(curve_evaluator *) fg_data = helix;
 else
  *ifail = FGGEOM;

 if (*ifail == FGOPOK && (*(int *) fg_data) == NULL_PTR )
     *ifail = FGOPFA;

 return;
}


void FGCRSU( const char* key, int* keylen, int* n_kii, int* ki_ints, int* n_kir,
             double* ki_reals, int* n_data, double* fg_data, int* ifail )
/* description: FGCRSU

This function is called when an FG surface is created by the KI function
CRFGSU. The function initialises any data required by the evaluator. A
successful call to this function indicates to Parasolid that evaluations of
this surface may be requested.

ifail return values:

   FGOPOK       Operation successful
   FGOPFA       Operation failed
   FGGEOM       Evaluator not available
   FGDATA       Evaluator data not found
   FGIERR       Error in supplied integer data
   FGRERR       Error in supplied real data
   FGFILE       Evaluator data allocation fault

*/
{
 const char *key_ptr;
 key_ptr = key;
 *(int *) fg_data = NULL_PTR;

 *ifail = FGOPOK;

 if (keycmpu( "SDL/franke", key, *keylen ))       /* select evaluator  */
  *(surface_evaluator *) fg_data = franke;
 else if (keycmpu( "SDL/incline", key, *keylen ))
  *(surface_evaluator *) fg_data = incline;
 else if (keycmpu( "SDL/corrugated", key, *keylen ))
   {
   if ((*n_kir == 3) &&            /* corrugated evaluator requires 3 reals */
       (ki_reals[1] > 0.0) &&      /* of which last two are positive        */
       (ki_reals[2] > 0.0))

          *(surface_evaluator *) fg_data = corrugated;

   else *ifail = FGRERR;
   }
 else
  *ifail = FGGEOM;

 if (*ifail == FGOPOK && (*(int *)fg_data == NULL_PTR))
     *ifail = FGOPFA;

 return;
}


void FGEVCU( int* ki_ints, double* ki_reals, double* fg_data, double* t,
             int* nderiv, double* results, int* ifail)
/* description: FGEVCU

This function evaluates a foreign geometry curve. In this example
implementation this is done by calling the function whose address is stored
in the first element of the fg_data array.

This function is called when an evaluation of an FG curve is required by
Parasolid. The function should be capable of supplying position and up to
second derivatives for an FG curve which has previously been initialised by a
call to FGCRCU.

Specific ifail return values:
  FGEVIN                    Evaluation incomplete
  FGOPFA                    Evaluation failed
  FGOPOK                    Operation successful

*/
{
 curve_evaluator eval;
 eval = *(curve_evaluator *) fg_data; /*   compute : call evaluator  */
 *ifail = FGOPOK;
 (*eval)( ki_ints, ki_reals, fg_data, t, nderiv, results, ifail );
 return;
}


void FGEVSU( int* ki_ints, double* ki_reals, double* fg_data, double* u,
             double* v, int* nu, int* nv, int* triang, double* results,
             int* ifail)
/* description: FGEVSU

This function is called when an evaluation of an FG surface is required by
Parasolid. The function should be capable of supplying position and up to
second derivatives for an FG surface which has previously been initialised by
a call to FGCRSU.

Specific ifail returns:
  FGOPOK                    Operation successful
  FGEVIN                    Evaluation incomplete
  FGOPFA                    Evaluation failed

*/

{
 surface_evaluator eval;


 eval = *(surface_evaluator *) fg_data;     /* initialise evaluator function */
 *ifail = FGOPOK;                           /* initialise ifail */
 (*eval)( ki_ints, ki_reals, fg_data, u, v, /* & call evaluator */
          nu, nv, triang, results, ifail );

 return;
}


void FGPRCU( int* ki_ints, double* ki_reals, double* fg_data, double* range,
             int* period, int* ifail)
/* description: FGPRCU

This function is called, after FGCRCU has initialised the curve, to indicate
to Parasolid some of the parametric properties of the curve. The function can
specify the parameter range of the curve and indicate whether it is to be
treated as periodic.

Note that at Parasolid Version 4.0 release foreign curves may not be closed or
periodic: the periodic argument is included for upwards compatability with
future planned enhancements.

ifail return values:
    FGPROP     Use default properties: i.e. t range = [0, 1]
               Periodicity flag set to FGPRBD (parameterisation bounded)
    FGOPOK     Operation successful
    FGOPFA     Operation failed

*/
{
 curve_evaluator eval;
 eval = *(curve_evaluator *) fg_data;
 *ifail = FGPROP;      /* Use default properties */

 if( eval == sine )    /* unless using sine evaluator */
    {
    range[0] = 0.0;
    range[1] = ki_reals[1];
    *period = FGPRBD;
    *ifail = FGOPOK;
    }

 return;
}


void FGPRSU( int* ki_ints, double* ki_reals, double* fg_data, double* range,
             int* period, int* ifail)
/* description: FGPRSU

This function is called after FGCRSU has initialised the surface and allows
modification of the surface parametric properties. Note that at Parasolid
Version 4.0 the periodicity flags must assume default value FGPRBD since
foreign surfaces may be neither closed nor periodically parameterised at that
version.

ifail return values:
    FGPROP     Use default properties: ie u range = v range = [0, 1]
               Both periodicity flags set to FGPRBD (parameterisation bounded)
    FGOPOK     Operation successful
    FGOPFA     Operation failed

*/
{
 surface_evaluator eval;
 eval = *(surface_evaluator *)fg_data;
 *ifail = FGPROP;                     /* Use default properties */

 if (eval == corrugated)              /* unless using corrugated evaluator */
  {
   range[0] = 0.0;                    /* which has parameter range details */
   range[1] = ki_reals[1];            /* passed in ki_reals array */
   range[2] = 0.0;
   range[3] = ki_reals[2];
   period[0]   = FGPRBD;
   period[1]   = FGPRBD;
   *ifail      = FGOPOK;
  }
 return;
}

