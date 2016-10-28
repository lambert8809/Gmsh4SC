

#ifndef _CALLBACKS_H
#define _CALLBACKS_H

#include <vector>
#include <string>
#include "parasolid_kernel.h"
#include "kernel_interface.h"

using namespace std;


class constant_meshsize_data{
  public:
    static void set_mesh_size(double d){meshsize=d;};
    static double get_mesh_size(){return meshsize;};
  private:
    static double meshsize;
};

class cyl_data{
  public:
    double radius, x,y,z, u,v,w, meshsize;// xyz=one point on the axis, uvw=axis direction
};

bool edge_xyz_from_t(const PK_EDGE_t edge, double t, vector<double> &res);
bool vertex_mesh_size(const PK_VERTEX_t vertex, double *size, void *user_data);
bool vertex_xyz(const PK_VERTEX_t vertex, vector<double> &res);
bool edge_parBounds(const PK_EDGE_t edge, double &s0,double &s1);
bool face_periodic_info(const PK_FACE_t face, bool &per_u, bool &per_v, double &period_u, double &period_v);
bool face_geomType(const PK_FACE_t face, string &s);
bool edge_geomType(const PK_FACE_t face, string &s);
bool edge_degenerate(const PK_EDGE_t e, bool &res);
bool edge_firstder_from_par(const PK_EDGE_t e, double par, vector<double> &res);
bool edge_curvature_from_par(const PK_EDGE_t e, double par, double &curvature);
bool edge_closestPointOrthogonal(const PK_EDGE_t e, const vector<double> &coord, double &param, vector<double> &res, bool &is_on_edge);
bool edge_containsPointFromT(const PK_EDGE_t edge, const double param, bool &res);
bool edge_is3D(const PK_EDGE_t edge, bool &res);
bool face_UVFromXYZ(const PK_FACE_t face, const vector<double> &coord, vector<double> &res);
bool face_closestPointOnFaceOrthogonal(const PK_FACE_t f, const vector<double> &coord, vector<double> &xyzres, vector<double> &uvres);
bool face_containsPointFromXYZ(const PK_FACE_t face, const vector<double> &xyz, bool &res);
bool face_containsPointFromUV(const PK_FACE_t face, const vector<double> &uv, bool &res);
bool face_XYZFromUV(const PK_FACE_t face, const vector<double> &uvcoord, vector<double> &xyzres);
bool face_parBounds(const PK_FACE_t face, const int dir, double &s0, double &s1);
bool face_curvatures(const PK_FACE_t face, const vector<double> &uvcoord, vector<double> &dirmax, vector<double> &dirmin, double &maxcurv, double &mincurv);
bool face_normal(const PK_FACE_t face, const vector<double> &uvcoord, vector<double> &normale);
bool face_firstDer(const PK_FACE_t face,const vector<double> &uv,vector<double> &deru,vector<double> &derv);
bool face_secondDer(const PK_FACE_t face, const vector<double> &uv, vector<double> &deruu,vector<double> &dervv,vector<double> &deruv);
bool edge_reparamOnFace(const PK_EDGE_t edge, const PK_FACE_t f, const double par, const int dir, vector<double> &res);
bool get_fin_from_edge_and_face(const PK_EDGE_t &edge, const PK_FACE_t &f, PK_FIN_t &res);
bool cylinder_field_callback(double x,double y,double z, void *user_data, double &size);


#endif
