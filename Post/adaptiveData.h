// Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#ifndef _ADAPTIVE_DATA_H_
#define _ADAPTIVE_DATA_H_

#include <list>
#include <set>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "fullMatrix.h"

class PViewData;
class PViewDataList;
class GMSH_PostPlugin;

class adaptiveVertex {
 public:
  float  x, y, z;        //!< parametric coordinates
  double X, Y, Z;        //!< cartesian coordinates
  double val,valy,valz;  //!< maximal three values
 public:
  static adaptiveVertex *add(double x, double y, double z,
                             std::set<adaptiveVertex> &allVertice);
  bool operator < (const adaptiveVertex &other) const
  {
    if(other.x < x) return true;
    if(other.x > x) return false;
    if(other.y < y) return true;
    if(other.y > y) return false;
    if(other.z < z) return true;
    return false;
  }
};

class adaptivePoint {
 public:
  bool visible;
  adaptiveVertex *p[1];
  adaptivePoint *e[1];
  static std::list<adaptivePoint*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptivePoint(adaptiveVertex *p1)
    : visible(false)
  {
    p[0] = p1;
    e[0] = 0;
  }
  inline double V() const
  {
    return p[0]->val;
  }
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    sf(0) = 1;
  }
  static void create(int maxlevel);
  static void recurCreate(adaptivePoint *e, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptivePoint *e, double AVG, double tol);
};

class adaptiveLine {
 public:
  bool visible;
  adaptiveVertex *p[2];
  adaptiveLine *e[2];
  static std::list<adaptiveLine*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptiveLine(adaptiveVertex *p1, adaptiveVertex *p2)
    : visible(false)
  {
    p[0] = p1;
    p[1] = p2;
    e[0] = e[1] = 0;
  }
  inline double V() const
  {
    return (p[0]->val + p[1]->val) / 2.;
  }
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    sf(0) = (1 - u) / 2.;
    sf(1) = (1 + u) / 2.;
  }
  static void create(int maxlevel);
  static void recurCreate(adaptiveLine *e, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptiveLine *e, double AVG, double tol);
};

class adaptiveTriangle {
 public:
  bool visible;
  adaptiveVertex *p[3];
  adaptiveTriangle *e[4];
  static std::list<adaptiveTriangle*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptiveTriangle(adaptiveVertex *p1, adaptiveVertex *p2, adaptiveVertex *p3)
    : visible(false)
  {
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    e[0] = e[1] = e[2] = e[3] = 0;
  }
  inline double V() const
  {
    return (p[0]->val + p[1]->val + p[2]->val) / 3.;
  }
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    sf(0) = 1. - u - v;
    sf(1) = u;
    sf(2) = v;
  }
  static void create(int maxlevel);
  static void recurCreate(adaptiveTriangle *t, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptiveTriangle *t, double AVG, double tol);
};

class adaptiveQuadrangle {
 public:
  bool visible;
  adaptiveVertex *p[4];
  adaptiveQuadrangle *e[4];
  static std::list<adaptiveQuadrangle*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptiveQuadrangle(adaptiveVertex *p1, adaptiveVertex *p2,
                     adaptiveVertex *p3, adaptiveVertex *p4)
    : visible(false)
  {
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
    e[0] = e[1] = e[2] = e[3] = 0;
  }
  inline double V() const
  {
    return (p[0]->val + p[1]->val + p[2]->val + p[3]->val) / 4.;
  }
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    sf(0) = 0.25 * (1. - u) * (1. - v);
    sf(1) = 0.25 * (1. + u) * (1. - v);
    sf(2) = 0.25 * (1. + u) * (1. + v);
    sf(3) = 0.25 * (1. - u) * (1. + v);
  }
  static void create(int maxlevel);
  static void recurCreate(adaptiveQuadrangle *q, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptiveQuadrangle *q, double AVG, double tol);
};

class adaptivePrism {
 public:
  bool visible;
  adaptiveVertex *p[6];
  adaptivePrism *e[8];
  static std::list<adaptivePrism*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptivePrism(adaptiveVertex *p1, adaptiveVertex *p2, adaptiveVertex *p3,
                adaptiveVertex *p4, adaptiveVertex *p5, adaptiveVertex *p6)
    : visible(false)
  {
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
    p[4] = p5;
    p[5] = p6;
    e[0] = e[1] = e[2]  = e[3]  = NULL;
    e[4] = e[5] = e[6]  = e[7]  = NULL;
  }
  inline double V() const
  {
    return (p[0]->val + p[1]->val + p[2]->val + p[3]->val + p[4]->val + p[5]->val) / 6.;
  }
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    sf(0) = (1. - u - v) * (1 - w) / 2;
    sf(1) = u * (1-w)/2;
    sf(2) = v*(1-w)/2;
    sf(3) = (1. - u - v)*(1+w)/2;
    sf(4) = u*(1+w)/2;
    sf(5) = v*(1+w)/2;
  }
  static void create(int maxlevel);
  static void recurCreate(adaptivePrism *p, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptivePrism *p, double AVG, double tol);
};

class adaptiveTetrahedron {
 public:
  bool visible;
  adaptiveVertex *p[4];
  adaptiveTetrahedron *e[8];
  static std::list<adaptiveTetrahedron*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptiveTetrahedron(adaptiveVertex *p1, adaptiveVertex *p2,
                      adaptiveVertex *p3, adaptiveVertex *p4)
    : visible(false)
  {
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
    e[0] = e[1] = e[2] = e[3] = 0;
    e[4] = e[5] = e[6] = e[7] = 0;
  }
  inline double V() const
  {
    return (p[0]->val + p[1]->val + p[2]->val + p[3]->val) / 4.;
  }
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    sf(0) = 1. - u - v - w;
    sf(1) = u;
    sf(2) = v;
    sf(3) = w;
  }
  static void create(int maxlevel);
  static void recurCreate(adaptiveTetrahedron *t, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptiveTetrahedron *t, double AVG, double tol);
};

class adaptiveHexahedron {
 public:
  bool visible;
  adaptiveVertex *p[8];
  adaptiveHexahedron *e[8];
  static std::list<adaptiveHexahedron*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptiveHexahedron(adaptiveVertex *p1, adaptiveVertex *p2, adaptiveVertex *p3,
                     adaptiveVertex *p4, adaptiveVertex *p5, adaptiveVertex *p6,
                     adaptiveVertex *p7, adaptiveVertex *p8)
    : visible(false)
  {
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
    p[4] = p5;
    p[5] = p6;
    p[6] = p7;
    p[7] = p8;
    e[0] = e[1] = e[2] = e[3] = 0;
    e[4] = e[5] = e[6] = e[7] = 0;
  }
  inline double V() const
  {
    return (p[0]->val + p[1]->val + p[2]->val+ p[3]->val +
            p[4]->val + p[5]->val + p[6]->val+ p[7]->val) / 8.;
  }
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    sf(0) = 0.125 * (1 - u) * (1 - v) * (1 - w);
    sf(1) = 0.125 * (1 + u) * (1 - v) * (1 - w);
    sf(2) = 0.125 * (1 + u) * (1 + v) * (1 - w);
    sf(3) = 0.125 * (1 - u) * (1 + v) * (1 - w);
    sf(4) = 0.125 * (1 - u) * (1 - v) * (1 + w);
    sf(5) = 0.125 * (1 + u) * (1 - v) * (1 + w);
    sf(6) = 0.125 * (1 + u) * (1 + v) * (1 + w);
    sf(7) = 0.125 * (1 - u) * (1 + v) * (1 + w);
  }
  static void create(int maxlevel);
  static void recurCreate(adaptiveHexahedron *h, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptiveHexahedron *h, double AVG, double tol);
};

// modif koen.hillewaert@cenaero.be, 31/07/2014

class adaptivePyramid {
 public:
  bool visible;
  adaptiveVertex *p[5];
  adaptivePyramid *e[10];
  static std::list<adaptivePyramid*> all;
  static std::set<adaptiveVertex> allVertices;
  static int numNodes, numEdges;
 public:
  adaptivePyramid(adaptiveVertex *p1,
                  adaptiveVertex *p2,
                  adaptiveVertex *p3,
                  adaptiveVertex *p4,
                  adaptiveVertex *p5)
    : visible(false)
  {
    p[0] = p1;
    p[1] = p2;
    p[2] = p3;
    p[3] = p4;
    p[4] = p5;
    for (int i=0;i<10;i++) e[i] = NULL;
  }
  inline double V() const
  {
    return (p[0]->val +
            p[1]->val +
            p[2]->val +
            p[3]->val +
            p[4]->val) / 5.;
  }
  // barycentric coordinates ?
  inline static void GSF(double u, double v, double w, fullVector<double> &sf)
  {
    double ww = 0.25 / std::max(1e-14,1.-w);
    sf(0) = (1 - u - w) * (1 - v - w) * ww;
    sf(1) = (1 + u - w) * (1 - v - w) * ww;
    sf(2) = (1 + u - w) * (1 + v - w) * ww;
    sf(3) = (1 - u - w) * (1 + v - w) * ww;
    sf(4) = w;
  }
  static void create(int maxlevel);
  static void recurCreate(adaptivePyramid *h, int maxlevel, int level);
  static void error(double AVG, double tol);
  static void recurError(adaptivePyramid *h, double AVG, double tol);
};

class PCoords {
 public:
  double c[3];
  PCoords(double x, double y, double z)
  {
    c[0] = x; c[1] = y; c[2] = z;
  }
};

class PValues{
 public:
  double v[3];
  PValues(double vx)
  {
    v[0] = vx;
  }
  PValues(double vx, double vy, double vz)
  {
    v[0] = vx; v[1] = vy; v[2] = vz;
  }
};

template <class T>
class adaptiveElements {
 private:
  fullMatrix<double> *_coeffsVal, *_eexpsVal, *_interpolVal;
  fullMatrix<double> *_coeffsGeom, *_eexpsGeom, *_interpolGeom;
 public:
  adaptiveElements(std::vector<fullMatrix<double>*> &interpolationMatrices);
  ~adaptiveElements();
  // create the _interpolVal and _interpolGeom matrices at the given
  // refinement level
  void init(int level);
  // process the element data in coords/values and return the refined
  // elements in coords/values
  void adapt(double tol, int numComp,
             std::vector<PCoords> &coords, std::vector<PValues> &values,
             double &minVal, double &maxVal, GMSH_PostPlugin *plug=0,
             bool onlyComputeMinMax=false);
  // adapt all the T-type elements in the input view and add the
  // refined elements in the output view (we will remove this when we
  // switch to true on-the-fly local refinement in drawPost())
  void addInView(double tol, int step, PViewData *in, PViewDataList *out,
                 GMSH_PostPlugin *plug=0);
};

class adaptiveData {
 private:
  int _step, _level;
  double _tol;
  PViewData *_inData;
  PViewDataList *_outData;
  adaptiveElements<adaptivePoint> *_points;
  adaptiveElements<adaptiveLine> *_lines;
  adaptiveElements<adaptiveTriangle> *_triangles;
  adaptiveElements<adaptiveQuadrangle> *_quadrangles;
  adaptiveElements<adaptiveTetrahedron> *_tetrahedra;
  adaptiveElements<adaptiveHexahedron> *_hexahedra;
  adaptiveElements<adaptivePrism> *_prisms;
  adaptiveElements<adaptivePyramid> *_pyramids;
 public:
  static double timerInit, timerAdapt;
  adaptiveData(PViewData *data);
  ~adaptiveData();
  PViewData *getData(){ return (PViewData*)_outData; }
  void changeResolution(int step, int level, double tol, GMSH_PostPlugin *plug=0);
};

#endif
