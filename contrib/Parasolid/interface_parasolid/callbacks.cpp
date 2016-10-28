

#include "callbacks.h"
#include<iostream>
#include<math.h>
#include "GmshMessage.h"

using namespace std;


//------------------------------------------------------------------------

double constant_meshsize_data::meshsize = 0.05;

//------------------------------------------------------------------------

// for periodic surfs, ensures that th returned parameters are in the range of the Face (not just the curve)
void check_validity_for_periodic(const PK_FACE_t &face, PK_UV_t &uv){
  double umin,umax,vmin,vmax;
  face_parBounds(face, 0, umin,umax);
  face_parBounds(face, 1, vmin,vmax);
  double tol;
  PK_SESSION_ask_precision(&tol);
  bool ok_u = ((uv.param[0]<=(umax+3.*tol)) && (uv.param[0]>=(umin-3.*tol)));
  bool ok_v = ((uv.param[1]<=(vmax+3.*tol)) && (uv.param[1]>=(vmin-3.*tol)));
  if ((!ok_u)||(!ok_v)){
    PK_SURF_t surf;
    PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
    PK_PARAM_sf_t params[2];
    PK_SURF_ask_params(surf,params);
    double period;

    //if (!ok_u && ok_v)
    if (!ok_u){
      period = fabs(params[0].range.value[1] - params[0].range.value[0]);
      uv.param[0] += period;
//      cout << "fixing u periodic issue " << endl;
    }
    //else if (!ok_v && ok_u){
    if (!ok_v){
      period = fabs(params[1].range.value[1] - params[1].range.value[0]);
      uv.param[1] += period;
//      cout << "fixing v periodic issue " << endl;
    }
  }
}

//------------------------------------------------------------------------

void print_face_info(const PK_FACE_t &face){
  double u0,u1,v1,v0;
  cout << "-----------------------------------------" << endl;
  cout << "------------  Face Infos ----------------" << endl;
  cout << "-----------------------------------------" << endl;
  cout << "Native ID: " << face << endl;
  string s;
  face_geomType(face,s);
  cout << "Geom Type: " << s << endl;
  if ((face_parBounds(face, 0, u0,u1)) && (face_parBounds(face, 1, v0,v1))){
    cout << "Param Bounds: [" << u0 << "," << u1 << "] [" << v0 << ',' << v1 << "]" << endl;
  }
  else{
    cout << "face_parBounds crash !!!" << endl;
  }
  int nedges;
  PK_EDGE_t *edges;
  PK_FACE_ask_edges(face,&nedges,&edges);
  cout << "# edges: " << nedges << endl;
  for (int i=0;i<nedges;i++){
    cout << "   edge id: " << edges[i];
    edge_geomType(edges[i],s);
    cout << "  type: " << s  << endl;
  }
  cout << "-----------------------------------------" << endl;
  cout << "-----------------------------------------" << endl;
}

//------------------------------------------------------------------------

PK_ERROR_code_t get_curve(const PK_EDGE_t &edge, PK_CURVE_t &curve, PK_LOGICAL_t &sense){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  //err = PK_EDGE_ask_curve(e,&curve);
  //if (err!=PK_ERROR_no_errors) return false;

  PK_LOGICAL_t want_interval = PK_LOGICAL_false;
  PK_CLASS_t class_edge;
  PK_VECTOR_t ends[2];
  PK_INTERVAL_t t_int;

  err = PK_EDGE_ask_geometry(edge, want_interval, &curve, &class_edge, ends, &t_int, &sense);
  if (curve==PK_ENTITY_null){
    cout << "get_curve : curve is NULL" << endl;
    throw;
  }
  return err;
}

//------------------------------------------------------------------------

PK_ERROR_code_t get_edge_interval(const PK_EDGE_t &edge, PK_INTERVAL_t &inter, PK_LOGICAL_t &sense){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_CURVE_t curve;
  PK_LOGICAL_t want_interval = PK_LOGICAL_true;
  PK_CLASS_t class_edge;
  PK_VECTOR_t ends[2];

  err = PK_EDGE_ask_geometry(edge, want_interval, &curve, &class_edge, ends, &inter, &sense);
  // d'après la doc, "always increasing parameter along the CURVE " !!! for ends and inter.
  if (curve==PK_ENTITY_null){
    cout << "get_edge_interval : curve is NULL" << endl;
    throw;
  }
  return err;
}

//------------------------------------------------------------------------

bool edge_xyz_from_t(const PK_EDGE_t edge, double t, vector<double> &res){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  // recover the curve from the edge
  PK_CURVE_t curve;
  PK_LOGICAL_t sense = PK_LOGICAL_true;
  err = get_curve(edge,curve,sense);
  if (err!=PK_ERROR_no_errors){
    cout << "edge_xyz_from_t : get_curve error=" << err << endl;
    return false;
  }
  if (curve==PK_ENTITY_null) return false;

  // ask the curve
  PK_VECTOR_t vec[1];
  // WARNING: NEED TO REVERSE COORDINATE TO CALL PK_FUNCTIONS, NOT TO CALL CALLBACK FUNCTIONS !!! 
  if (sense==PK_LOGICAL_false){// reverse param coordinate
    double s0,s1;
    edge_parBounds(edge,s0,s1);
    t = s0 + s1 - t;
  }
  err = PK_CURVE_eval(curve, t, 0, vec);
  if (err!=PK_ERROR_no_errors){
    cout << "edge_xyz_from_t : PK_CURVE_eval error=" << err << endl;
    return false;
  }

  for (int i=0;i<3;i++)
    res[i] = vec[0].coord[i];
  return true;
}

//------------------------------------------------------------------------

bool vertex_mesh_size(const PK_VERTEX_t vertex, double *size, void *user_data){
  // HERE: insert fcts from VirfacLib.MeshGemsInterface... :
  // size_on_point(vertex, size, user_data)
  // for now, overloading:

  *size = constant_meshsize_data::get_mesh_size();//125;
  return true;
}

//------------------------------------------------------------------------

bool vertex_xyz(const PK_VERTEX_t vertex, vector<double> &res){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_POINT_sf_t point_sf;
  PK_POINT_t point;
  err=PK_VERTEX_ask_point(vertex,&point);
  if (err!=PK_ERROR_no_errors) return false;
  if (point==PK_ENTITY_null) return false;
  err=PK_POINT_ask(point,&point_sf);
  if (err!=PK_ERROR_no_errors) return false;
  for (int i=0;i<3;i++)
    res[i] = point_sf.position.coord[i];
  return true;
}

//------------------------------------------------------------------------

bool edge_parBounds(const PK_EDGE_t edge, double &s0,double &s1, PK_LOGICAL_t &sense){
  PK_INTERVAL_t inter;
  //  PK_ERROR_code_t err = PK_EDGE_find_interval(edge,&inter);
  PK_ERROR_code_t err = get_edge_interval(edge, inter,sense);

  if ((err==PK_ERROR_missing_geom)||(err!=PK_ERROR_no_errors)){
    cout << "edge_parBounds::get_edge_interval error = " << err << endl;
    return false;
  }
  // d'après la doc, "always increasing parameter along the CURVE " !!! for ends and inter.
  // --> s0 < s1, toujours !
  s0 = inter.value[0];
  s1 = inter.value[1];

//  if (inter.value[0]>inter.value[1]){
//    Msg::Error("throw min max !!!");
//  }
//  s0 = std::min(inter.value[0],inter.value[1]);
//  s1 = std::max(inter.value[0],inter.value[1]);
  return true;
}

//------------------------------------------------------------------------

bool edge_parBounds(const PK_EDGE_t edge, double &s0,double &s1){
  PK_LOGICAL_t sense;
  return (edge_parBounds(edge, s0, s1, sense));
}

//------------------------------------------------------------------------

bool edge_geomType(const PK_EDGE_t e,string &s){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_CURVE_t curve;
  PK_LOGICAL_t sense = PK_LOGICAL_true;
  err = get_curve(e,curve,sense);
  if (err!=PK_ERROR_no_errors){
    cout << "callback edge_geomType:: PK_ERROR_t get_curve " << err << endl;
    return false;
  }

  PK_CLASS_t classe;
  err=PK_ENTITY_ask_class(curve,&classe);// marche pour une curve, mais pas pour une edge !!!! WTF ??? !!!
  if (err!=PK_ERROR_no_errors){
    cout << "callback edge_geomType:: PK_ERROR_t ask_class " << err << endl;
    return false;
  }


  bool result = true;

  switch (classe){
    case PK_CLASS_line:
      s.assign("Line");
      break;
    case PK_CLASS_circle:
      s.assign("Circle");
      break;
    case PK_CLASS_ellipse:
      s.assign("Ellipse");
      break;
    case PK_CLASS_bcurve:// BSpline-type curve ...
      {
        PK_BCURVE_sf_t bcurve_sf;
        PK_BCURVE_ask(curve,&bcurve_sf);

        switch(bcurve_sf.form){
          case PK_BCURVE_form_parabolic_c:
            s.assign("Parabola");
            break;
          case PK_BCURVE_form_hyperbolic_c:
            s.assign("Hyperbola");
            break;
        }
        if (bcurve_sf.knot_type == PK_knot_piecewise_bezier_c){
          s.assign("Bezier");
          break;
        }
        else{
          s.assign("BSpline");
          break;
        }
        break;
      }
    case PK_CLASS_trcurve:
      s.assign("TrimmedCurve");
      break;
    case PK_CLASS_spcurve:
      s.assign("SP_curve (something weird in parasolid, helping defining tolerance and precision on curves ??? Not required in Gmsh ??? ");
      PK_SPCURVE_sf_t spcurve_sf;
      PK_SPCURVE_ask(curve,&spcurve_sf);
      err=PK_ENTITY_ask_class(spcurve_sf.curve,&classe);
      switch (classe){
        case PK_CLASS_line:
          s.assign("Line");
          break;
        case PK_CLASS_circle:
          s.assign("Circle");
          break;
        case PK_CLASS_ellipse:
          s.assign("Ellipse");
          break;
        case PK_CLASS_bcurve:// BSpline-type curve ...
          {
            PK_BCURVE_sf_t bcurve_sf;
            PK_BCURVE_ask(spcurve_sf.curve,&bcurve_sf);

            switch(bcurve_sf.form){
              case PK_BCURVE_form_parabolic_c:
                s.assign("Parabola");
                break;
              case PK_BCURVE_form_hyperbolic_c:
                s.assign("Hyperbola");
                break;
            }
            if (bcurve_sf.knot_type == PK_knot_piecewise_bezier_c){
              s.assign("Bezier");
              break;
            }
            else{
              s.assign("BSpline");
              break;
            }
            break;
          }
        default:
          s.assign("Unknown");
          result=false;
          break;
      }
      break;
    case PK_CLASS_cpcurve:
      s.assign("No info on what is cpcurve ???? Can't find anything in the doc...");
      break;
    case PK_CLASS_fcurve:
      s.assign("Foreign geometry curve");
      break;
    case PK_CLASS_icurve:
      s.assign("Intersection curve");
      break;
    default:
      s.assign("Unknown");
      result = false;
      break;
  }

  if (!result){
    cout << "callback edge_geomType:: Class not referenced in the switch" << endl;
    cout << "returning:\"" << s << "\"" << endl;
  }
  if (s.empty()) throw;
  return result;

  // TODO: question:
  // pourquoi on peut avoir un type "Cylindre", et un type "BSurf -> de type cylindre"... ???

  //TODO: what are these in gmsh ????????
  //  return OffsetCurve;
  //  return Conic;// il y a deja hyperbole, ellipse, cercle et parabole pourtant...




}

//------------------------------------------------------------------------

bool face_periodic_info(const PK_FACE_t face, bool &per_u, bool &per_v, double &period_u, double &period_v){
  PK_PARAM_periodic_t periodic_u,periodic_v;
  PK_ERROR_code_t err = PK_FACE_is_periodic(face,&periodic_u,&periodic_v);
  if (err!=PK_ERROR_no_errors){
    cout << "face_periodic_info : PK_FACE_is_periodic error=" << err << endl;
    return false;
  }
  per_u=false;
  per_v=false;
  if (periodic_u==PK_PARAM_periodic_yes_c) per_u = true;
  if (periodic_v==PK_PARAM_periodic_yes_c) per_v = true;
  
  period_u=0;
  period_v=0;
  if (per_u||per_v){
    double u0,u1,v0,v1;
    if (!face_parBounds(face, 0, u0,u1)) return false;
    if (!face_parBounds(face, 1, v0,v1)) return false;
    period_u = u1-u0;
    period_v = v1-v0;
  }
  return true;
}

//------------------------------------------------------------------------

bool face_geomType(const PK_FACE_t face, string &s){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_SURF_t surf;
  err=PK_FACE_ask_surf(face,&surf);
  if (err!=PK_ERROR_no_errors) return false;

  PK_CLASS_t classe;
  err=PK_ENTITY_ask_class(surf,&classe);
  if (err!=PK_ERROR_no_errors) return false;

  switch (classe){
    case PK_CLASS_plane:
      s.assign("Plane");
      return true;
    case PK_CLASS_cyl:
      s.assign("Cylinder");
      return true;
    case PK_CLASS_cone:
      s.assign("Cone");
      return true;
    case PK_CLASS_sphere:
      s.assign("Sphere");
      return true;
    case PK_CLASS_torus:
      s.assign("Torus");
      return true;
    case PK_CLASS_bsurf:
      {
        PK_BSURF_sf_t bsurf_sf;
        PK_BSURF_ask(surf,&bsurf_sf);
        if ((bsurf_sf.u_knot_type == PK_knot_piecewise_bezier_c)&&(bsurf_sf.v_knot_type == PK_knot_piecewise_bezier_c)){
          s.assign("BezierSurface");
          return true;
        }
        else{
          s.assign("BSplineSurface");
          return true;
        }
      }
    case PK_CLASS_spun:
      s.assign("SurfaceOfRevolution");
      return true;
    case PK_CLASS_offset:
      s.assign("Offset ??? not in gmsh ?");
      return true;
    case PK_CLASS_fsurf:
      s.assign("Foreign Surface");
      return true;
    case PK_CLASS_swept:
      s.assign("Swept surface ??? not in gmsh ?");
      return true;
    case PK_CLASS_blendsf:
      s.assign("Blendsf ??? not in gmsh ?");
      return true;
    default:
      s.assign("Unknown");
  }
  return false;

  // TODO: difference, exactly ??? uknots and vknots, ...???
  //  return BezierSurface;
  //  return BSplineSurface;
}

//------------------------------------------------------------------------

bool edge_degenerate(const PK_EDGE_t e, bool &res){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_CURVE_t curve;
  PK_LOGICAL_t sense;
  err = get_curve(e,curve,sense);
  if (err!=PK_ERROR_no_errors){
    cout << "edge_degenerate : get_curve error=" << err << endl;
    return false;
  }

  PK_CURVE_find_degens_o_t options;
  PK_CURVE_find_degens_o_m(options);
  PK_CURVE_degens_t results;
  err=PK_CURVE_find_degens(curve,&options,&results);
  if (err!=PK_ERROR_no_errors){
    cout << "edge_degenerate : PK_CURVE_find_degens error=" << err << endl;
    return false;
  }

  res = (results.n_degen!=0);
  return true;
}

//------------------------------------------------------------------------

bool edge_firstder_from_par(const PK_EDGE_t e, double par, vector<double> &res){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_CURVE_t curve;
  PK_LOGICAL_t sense = PK_LOGICAL_true;
  err = get_curve(e,curve,sense);
  // WARNING: NEED TO REVERSE COORDINATE TO CALL PK_FUNCTIONS, NOT TO CALL CALLBACK FUNCTIONS !!! 
  if (sense==PK_LOGICAL_false){// reverse param coordinate
    double s0,s1;
    edge_parBounds(e,s0,s1);
    par = s0 + s1 - par;
  }

  //PK_EDGE_ask_geometry ???
  PK_VECTOR_t vec[2];
  err=PK_CURVE_eval(curve, par, 1, vec);
  if (err!=PK_ERROR_no_errors) return false;

  //  cout << "callback: edge first der:";
  for (int i=0;i<3;i++){
    res[i] = vec[1].coord[i];
    //    cout << res[i] << "  ";
  }
  //  cout << endl;
  return true;
}

//------------------------------------------------------------------------

bool edge_curvature_from_par(const PK_EDGE_t e, double par, double &curvature){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_CURVE_t curve;
  PK_LOGICAL_t sense = PK_LOGICAL_true;
  err = get_curve(e,curve,sense);
  if (err!=PK_ERROR_no_errors) return false;
  // WARNING: NEED TO REVERSE COORDINATE TO CALL PK_FUNCTIONS, NOT TO CALL CALLBACK FUNCTIONS !!! 
  if (sense==PK_LOGICAL_false){// reverse param coordinate
    double s0,s1;
    edge_parBounds(e,s0,s1);
    par = s0 + s1 - par;
  }

  PK_VECTOR1_t tangent;
  PK_VECTOR1_t principal_normal;
  PK_VECTOR1_t binormal;
  err=PK_CURVE_eval_curvature(curve, par, &tangent, &principal_normal, &binormal, &curvature);
  if (err!=PK_ERROR_no_errors) return false;
  return true;
}

//------------------------------------------------------------------------

bool edge_containsPointFromT(const PK_EDGE_t edge, const double param, bool &res){
  // check if point corresponding to param lies on edge
  double s0,s1;
  res=true;
  bool ok = edge_parBounds(edge,s0,s1);
  if ((param<s0)||(param>s1)){
    res = false;
    //cout << "    ---> Parameter (" << end.parameters[0] << ") is OUTSIDE edge bounds !!!" << endl;
  }
  //  else{
  //    cout << "    ---> Parameter (" << end.parameters[0] << ") is INSIDE edge bounds !!!" << endl;
  //    cout << "         end_pos = ("<<pos.coord[0] << "," << pos.coord[1] << "," << pos.coord[2] << ")"<<endl;
  //  }
  return ok;

}

//------------------------------------------------------------------------

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// using orthogonal projection to the CURVE !!!!!
// if using PK_TOPOL_range_vector, it projects on the EDGE, not the curve -> not orthogonal, not what we want !!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool edge_closestPointOrthogonal(const PK_EDGE_t e, const vector<double> &coord, double &param, vector<double> &res, bool &is_on_edge){
  // recover the curve
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_CURVE_t curve;
  PK_LOGICAL_t sense = PK_LOGICAL_true;
  err = get_curve(e,curve,sense);
  if (err!=PK_ERROR_no_errors) return false;

  // compute projection
  PK_GEOM_range_vector_o_t    options;
  PK_GEOM_range_vector_o_m(options);
  PK_VECTOR_t vec;
  for (int i=0;i<3;i++)
    vec.coord[i] = coord[i];

  PK_range_result_t rangeres;
  PK_range_1_r_t range;

  err = PK_GEOM_range_vector(curve,vec,&options, &rangeres, &range);
  if (err!=PK_ERROR_no_errors) return false;
  if (rangeres != PK_range_result_found_c) return false;

  //cout << "         distance=" << range.distance << endl;
  PK_range_end_t  end = range.end;
  PK_VECTOR_t  pos = end.vector;

  param=end.parameters[0];

  edge_containsPointFromT(e,param,is_on_edge);

  for (int i=0;i<3;i++)
    res[i] = pos.coord[i];
  return true;
}

//------------------------------------------------------------------------

bool edge_is3D(const PK_EDGE_t edge, bool &res){
  PK_LOGICAL_t planar;
  PK_PLANE_t brol;
  PK_ERROR_code_t err = PK_EDGE_is_planar(edge, PK_LOGICAL_false, &planar, &brol);
  if (err!=PK_ERROR_no_errors) return false;

  res=true;
  if (planar==PK_LOGICAL_true) res=false;
  return true;
}

//------------------------------------------------------------------------

bool face_UVFromXYZ(const PK_FACE_t face, const vector<double> &coord, vector<double> &res){
  PK_SURF_t surf;
  PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
  if (err!=PK_ERROR_no_errors) return false;

  PK_UV_t uv;
  PK_VECTOR_t pos = {coord[0],coord[1],coord[2]};
  err = PK_SURF_parameterise_vector(surf,pos,&uv);
  if (err==PK_ERROR_not_on_surface) cout << "PK_ERROR_not_on_surface" << endl;
  if (err!=PK_ERROR_no_errors) return false;


  // WARNING: there must be an easier way... but in the meanwhile, need to solve the periodic issue:
  // a surf goes from 0 to 2 pi, a face from pi to 2pi : this returns 0 instead of 2pi !!!
//  cout << "before check_validity_for_periodic: uv = [" << uv.param[0] << "," << uv.param[1] << "]" << endl;
  check_validity_for_periodic(face,uv);


//  cout << "face_UVFromXYZ: uv = [" << uv.param[0] << "," << uv.param[1] << "]" << endl;


  for (int i=0;i<2;i++)
    res[i] = uv.param[i];
  return true;
}

//------------------------------------------------------------------------

bool face_closestPointOnFaceOrthogonal(const PK_FACE_t f, const vector<double> &coord, vector<double> &xyzres, vector<double> &uvres){
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  PK_SURF_t surf;
  err=PK_FACE_ask_surf(f,&surf);
  if (err!=PK_ERROR_no_errors) return false;

  PK_GEOM_range_vector_o_t    options;
  PK_GEOM_range_vector_o_m(options);
  PK_VECTOR_t vec;
  for (int i=0;i<3;i++)
    vec.coord[i] = coord[i];
  PK_range_result_t rangeres;
  PK_range_1_r_t range;
  err = PK_GEOM_range_vector(surf,vec,&options, &rangeres, &range);
  if (err!=PK_ERROR_no_errors) return false;
  if (rangeres!=PK_range_result_found_c) return false;

  PK_range_end_t  end = range.end;
  PK_VECTOR_t  pos = end.vector;

  for (int i=0;i<2;i++)
    uvres[i] = end.parameters[i];
  for (int i=0;i<3;i++)
    xyzres[i] = pos.coord[i];

  return true;
}

//------------------------------------------------------------------------

bool face_containsPointFromXYZ(const PK_FACE_t face, const vector<double> &xyz, bool &res){
  PK_FACE_contains_vectors_o_t options;
  PK_FACE_contains_vectors_o_m(options);
  PK_TOPOL_t topols[1];
  options.n_vectors = 1;
  PK_VECTOR_t pos = {xyz[0],xyz[1],xyz[2]};
  options.vectors = &pos;
  PK_ERROR_code_t err=PK_FACE_contains_vectors(face,&options,topols);
  if (err!=PK_ERROR_no_errors){
    // try again, assuming the vector is not on the face
    options.is_on_surf = PK_LOGICAL_false;
    PK_ERROR_code_t err2=PK_FACE_contains_vectors(face,&options,topols);
    if (err2!=PK_ERROR_no_errors){
      cout << "face_containsPointFromXYZ : error1 = " << err << " error2=" << err2 << endl;
      return false;
    }
  }

  //    cout << "topols[0]=" << topols[0] << endl;
  //    //////////////////////////////////////////////////////
  //    // just a debug output... 
  //    //////////////////////////////////////////////////////
  //    PK_UVBOX_t uvbox;//umin vmin umax vmax
  //    PK_LOGICAL_t isrect;
  //    PK_FACE_is_uvbox(face,&isrect,&uvbox);
  //    if (isrect==PK_LOGICAL_true){
  //      cout << "RECTANGLE !  BOX=" << uvbox.param[0] << "," <<  uvbox.param[2] << " ... " <<  uvbox.param[1] << "," <<  uvbox.param[3] << endl;
  //    }
  //    //////////////////////////////////////////////////////
  //    //////////////////////////////////////////////////////
  //    //////////////////////////////////////////////////////

  res=true;
  if (topols[0]==PK_ENTITY_null){
    res=false;
    return true;
  }

  //  // type de topols[0] ?
  //  PK_CLASS_t classe;
  //  err=PK_ENTITY_ask_class(topols[0],&classe);
  //  if (err!=PK_ERROR_no_errors) return false;
  //  switch(classe){
  //    case PK_CLASS_edge:
  //      cout << "edge ! " << endl;
  //      break;
  //    case PK_CLASS_vertex:
  //      cout << "vertex !"  << endl;
  //      break;
  //    case PK_CLASS_face:
  //      cout << "face ! " << endl;
  //      break;
  //  }

  return true;
}

//------------------------------------------------------------------------

bool face_containsPointFromUV(const PK_FACE_t face, const vector<double> &uv, bool &res){

  //------------------------------------------------------------
  // CE QUI SUIT A L'AIR DE MERDER, JE SAIS PAS POURQUOI !!!!!!!!!!!!!!!!
  // un plan ne contient pas son midpt parametrique ???
  //------------------------------------------------------------

  PK_FACE_contains_vectors_o_t options;
  PK_FACE_contains_vectors_o_m(options);
  PK_TOPOL_t topols[1];
  options.n_uvs = 1;
  PK_UV_t pos = {uv[0],uv[1]};
  options.uvs = &pos;
  PK_ERROR_code_t err=PK_FACE_contains_vectors(face,&options,topols);
  if ((err!=PK_ERROR_no_errors)||(topols[0]==PK_ENTITY_null)){
    cout << "first output null : " << ((topols[0]==PK_ENTITY_null) ? "yes" : "no") << endl;
    // try again, assuming the vector is not on the face
    options.is_on_surf = PK_LOGICAL_false;
    PK_ERROR_code_t err2=PK_FACE_contains_vectors(face,&options,topols);
    if (err2!=PK_ERROR_no_errors){
      cout << "face_containsPointFromUV : error1 = " << err << " error2=" << err2 << endl;
      return false;
    }
    cout << "second output null : " << ((topols[0]==PK_ENTITY_null) ? "yes" : "no") << endl;
    cout << "asking for uv: [" << uv[0] << "," << uv[1] << "]" << endl;
    print_face_info(face);
  }

  //  cout << "topols[0]=" << topols[0] << endl;

  res=true;
  if (topols[0]==PK_ENTITY_null){
    res=false;
    return true;
  }

  return true;


}

//------------------------------------------------------------------------

bool face_XYZFromUV(const PK_FACE_t face, const vector<double> &uvcoord, vector<double> &xyzres){
  PK_SURF_t surf;
  PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
  if (err!=PK_ERROR_no_errors){
    cout << "face_XYZFromUV::PK_FACE_ask_surf error = " << err << endl;
    return false;
  }

  PK_UV_t uv = {uvcoord[0],uvcoord[1]};
  PK_VECTOR_t vec;
  err=PK_SURF_eval(surf,uv,0,0,PK_LOGICAL_false,&vec);
  if (err!=PK_ERROR_no_errors){
    if (err == PK_ERROR_bad_parameter){
      double s0,s1;
      bool test = face_parBounds(face, 0, s0,s1);
      cout << "face bounds u:" << s0 << " " << s1 << endl;
      test = face_parBounds(face, 1, s0,s1);
      cout << "face bounds v:" << s0 << " " << s1 << endl;
      cout << "uv = " << uvcoord[0] << " " << uvcoord[1] << endl;
      cout << "face_XYZFromUV::PK_SURF_eval error = " << err << " , given uv coords are out of range  " << endl;
    }
    else
      cout << "face_XYZFromUV::PK_SURF_eval error = " << err << endl;
    return false;
  }

  for (int i=0;i<3;i++)
    xyzres[i] = vec.coord[i];
  return true;
}

//------------------------------------------------------------------------

bool face_parBounds(const PK_FACE_t face, const int dir, double &s0, double &s1){
  // surf bounds != face bounds !!!!!!!!!!!
  //  PK_SURF_t surf;
  //  PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
  //  if (err!=PK_ERROR_no_errors) return false;

  PK_UVBOX_t uvbox;//umin vmin umax vmax
  PK_ERROR_code_t err=PK_FACE_find_uvbox(face,&uvbox);
  if (err!=PK_ERROR_no_errors){
    cout << "callbacks:: face_parBounds : error: " << err << endl;
    return false;
  }
  //  else cout << "callbacks:: face_parBounds OK" << endl;

  if(dir == 0){
    s0 = uvbox.param[0];
    s1 = uvbox.param[2];
  }
  else{
    s0 = uvbox.param[1];
    s1 = uvbox.param[3];
  }
  return true;
}

//------------------------------------------------------------------------

bool face_curvatures(const PK_FACE_t face, const vector<double> &uvcoord, vector<double> &dirmax, vector<double> &dirmin, double &maxcurv, double &mincurv){
  PK_SURF_t surf;
  PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
  if (err!=PK_ERROR_no_errors) return false;

  PK_UV_t uv = {uvcoord[0],uvcoord[1]};
  PK_VECTOR_t normal, principal_dir_1, principal_dir_2;
  err = PK_SURF_eval_curvature(surf,uv,&normal,&principal_dir_1, &principal_dir_2, &mincurv,&maxcurv);
  for (int i=0;i<3;i++){
    dirmax[i] = principal_dir_2.coord[i];
    dirmin[i] = principal_dir_1.coord[i];
  }
  if (err!=PK_ERROR_no_errors) return false;
  return true;
}

//------------------------------------------------------------------------

bool face_normal(const PK_FACE_t face, const vector<double> &uvcoord, vector<double> &normale){
  PK_SURF_t surf;
  PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
  if (err!=PK_ERROR_no_errors) return false;

  PK_UV_t uv = {uvcoord[0],uvcoord[1]};
  PK_VECTOR_t normal, principal_dir_1, principal_dir_2;
  double mincurv,maxcurv;
  err = PK_SURF_eval_curvature(surf,uv,&normal,&principal_dir_1, &principal_dir_2, &mincurv,&maxcurv);
  for (int i=0;i<3;i++)
    normale[i] = normal.coord[i];
  if (err!=PK_ERROR_no_errors) return false;
  return true;
}

//------------------------------------------------------------------------

bool face_firstDer(const PK_FACE_t face,const vector<double> &uv,vector<double> &deru,vector<double> &derv){
  PK_SURF_t surf;
  PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
  if (err!=PK_ERROR_no_errors) return false;

  PK_UV_t uvs;
  uvs.param[0] = uv[0];
  uvs.param[1] = uv[1];
  PK_VECTOR_t p[3];
  err=PK_SURF_eval(surf,uvs,1,1,PK_LOGICAL_true,p);
  if (err!=PK_ERROR_no_errors) return false;

  for (int i=0;i<3;i++){
    deru[i] = p[1].coord[i];
    derv[i] = p[2].coord[i];
  }
  //  cout << "callback: face first der:" << endl;
  //  for (int i=0;i<3;i++)
  //    cout << deru[i] << "  ";
  //  cout << endl;
  //  for (int i=0;i<3;i++)
  //    cout << derv[i] << "  ";
  //  cout << endl;
  return true;
}

//------------------------------------------------------------------------

bool face_secondDer(const PK_FACE_t face, const vector<double> &uv, vector<double> &deruu,vector<double> &dervv,vector<double> &deruv){
  PK_SURF_t surf;
  PK_ERROR_code_t err = PK_FACE_ask_surf(face,&surf);
  if (err!=PK_ERROR_no_errors) return false;

  PK_UV_t uvs = {uv[0],uv[1]};
  PK_VECTOR_t p[6];
  err=PK_SURF_eval(surf,uvs,2,2,PK_LOGICAL_true,p);
  if (err!=PK_ERROR_no_errors) return false;

  for (int i=0;i<3;i++){
    deruu[i] = p[2].coord[i];
    dervv[i] = p[5].coord[i];
    deruv[i] = p[4].coord[i];
  }
  return true;
}

//------------------------------------------------------------------------

// dir is 1 or -1 !!! edge normal direction or reverse direction, respectively
bool edge_reparamOnFace(const PK_EDGE_t edge, const PK_FACE_t f, const double par, const int dir, vector<double> &res){

  // CHECK if par is in range !
  double s0,s1,tol;
  PK_LOGICAL_t sense = PK_LOGICAL_true;
  if (!edge_parBounds(edge, s0,s1,sense)) return false;
  PK_SESSION_ask_precision(&tol);
  if ((par < (s0-3.*tol)) || (par > (s1+3.*tol))){
    cout << "edge_reparamOnFace error: given parameter " << par << " is out of edge range " << s0 << " " << s1 << endl;
    return false;
  }

  // An edge between two faces has two fins. Each fin is attached to a face. 
  // Need to find the fin corresponding to const PK_FACE_t f ...
  PK_FIN_t fin;
  bool ok = get_fin_from_edge_and_face(edge,f,fin);
  if (!ok){
    cout << "edge_reparamOnFace:: get_fin_from_edge_and_face error" << endl;
    return false;
  }

  // WARNING: the FIN does not always have a curve !!!!
  // if it has no curve... j'en ai marre, j'appelle face_UVFromXYZ !!!
  PK_CURVE_t fin_curve;
  PK_ERROR_t err = PK_FIN_ask_curve(fin,&fin_curve);
  if (fin_curve == PK_ENTITY_null){
//    cout << "edge_reparamOnFace:: Debug : THE FIN HAS NO CURVE ! Using face_UVFromXYZ" << endl;
    double param_to_use = par;
    // WARNING: NEED TO REVERSE COORDINATE TO CALL PK_FUNCTIONS, NOT TO CALL CALLBACK FUNCTIONS !!! ---> non need here !!!
    if (dir==-1){// need to reverse
      param_to_use = s0 + s1 - par;
    }
//    cout << "dir=" << dir << "  par=" << par << "  param_to_use=" << param_to_use << endl;
    vector<double> xyz(3,0.);
    if(!edge_xyz_from_t(edge, param_to_use, xyz)) return false;
//    cout << "-> found xyz = " << xyz[0] << "," <<  xyz[1] << "," <<  xyz[2] << endl; 
    return face_UVFromXYZ(f, xyz, res);
  }

  // ELSE, working from fin...
  // need to know if we need to reverse parameters...
  PK_LOGICAL_t fin_is_positive;
  PK_FIN_is_positive(fin,&fin_is_positive);
  double param_to_use = par;
  if (((dir==-1)&&(fin_is_positive==PK_LOGICAL_true)) || ((dir==1)&&(fin_is_positive==PK_LOGICAL_false))){// need to reverse
//    cout << "edge_reparamOnFace:: Debug : reversing parameter, fin_is_positive=" << ((fin_is_positive==PK_LOGICAL_true) ? "yes" : "no") << " dir=" << dir << endl;
    PK_INTERVAL_t inter;
    PK_FIN_find_interval(fin,&inter);
    param_to_use = inter.value[0] + inter.value[1] - par;
  }
  // in fct PK_FIN_find_surf_parameters, it is said that param is the parameter of the curve !!!, not the fin. 
  // I guess, it already take into account the fact that the fin might be reversed, we don't have to.
  // Except for the "dir" int...
  // UPDATE: guess what ??!!??  NOOOOOOOOOOO !!!! need to reverse if the fin is reversed !!!!!!
  // TWO FUCKING DAYS TRACKING THIS BUG !!!!


  PK_UV_t none;
  PK_UV_t uv;
  err = PK_FIN_find_surf_parameters(fin, param_to_use,PK_LOGICAL_false,none,&uv);
  if (err!=PK_ERROR_no_errors){
    cout << "error from PK_FIN_find_surf_parameters : " << err << endl;
    if (err==PK_ERROR_bad_parameter){
      double s0,s1;
      bool test = edge_parBounds(edge, s0,s1,sense);
      cout << "edge bounds :" << s0 << " " << s1;
      PK_INTERVAL_t inter;
      PK_ERROR_t err2 = PK_FIN_find_interval(fin,&inter);
      if (err2!=PK_ERROR_no_errors)
        cout << "PK_FIN_find_interval error = " << err2 << endl;
      cout << "   fin bounds = " << inter.value[0] << "  " <<  inter.value[1];
      cout << "     param = " << par << " param_to_use " << param_to_use << endl;
      cout << "edge_reparamOnFace::PK_FIN_find_surf_parameters error = " << err << " , given parameter coord is out of range  " << endl;

      //      PK_CURVE_t c;
      //      PK_FIN_ask_curve(fin,&c);
      //      cout << "   fin curve = " << c << endl;
    }
    else
      cout << "edge_reparamOnFace::PK_FIN_find_surf_parameters error = " << err << endl;
    return false;
  }


  // same periodic issue as in face_UVFromXYZ  !!!!!
  // a surf goes from 0 to 2 pi, a face from pi to 2pi : this returns 0 instead of 2pi !!!
  check_validity_for_periodic(f,uv);


  for (int i=0;i<2;i++)
    res[i] = uv.param[i];
  cout << "par=" << par << " param_used = " << param_to_use << endl << "-> found xyz = " << res[0] << "," <<  res[1] << "," <<  res[2] << endl; 
  return true;
}

//------------------------------------------------------------------------

bool get_fin_from_edge_and_face(const PK_EDGE_t &edge, const PK_FACE_t &f, PK_FIN_t &res){
  // An edge between two faces has two fins. Each fin is attached to a face. 
  // Need to find the fin corresponding to const PK_FACE_t f ...

  PK_FIN_t *fins;
  int n_fins;
  PK_ERROR_code_t err = PK_EDGE_ask_fins(edge, &n_fins, &fins);
  if (err!=PK_ERROR_no_errors){
    cout << "get_fin_from_edge_and_face::PK_EDGE_ask_fins error = " << err << endl;
    return false;
  }
  if (n_fins<1){
    cout << "get_fin_from_edge_and_face:: n_fins < 1 !" << err << endl;
    return false;
  }

  int ifin=0;
  bool found_fin=false;
  for (int i=0;i<n_fins;i++){
    PK_FACE_t temp;
    err = PK_FIN_ask_face(fins[i],&temp);
    if (temp==f){
      ifin=i;
      found_fin = true;
      break;
    }
  }// fins[ifin] is now the fin related to the face f
  res = fins[ifin];
  if (!found_fin) cout << "get_fin_from_edge_and_face : ******** fin NOT  FOUND !" << endl;
  return true;
}

//------------------------------------------------------------------------

// creates given density around given cylinder 
// cylinder parameters are inclosed in user_data
bool cylinder_field_callback(double x,double y,double z, void *user_data, double &size){
  cyl_data *cd = static_cast<cyl_data*>(user_data);
  const double u_norme = cd->u*cd->u + cd->v*cd->v + cd->w*cd->w;
  const double vecx = cd->x-x ;
  const double vecy = cd->y-y ;
  const double vecz = cd->z-z ;
  const double distance_points_square = vecx*vecx + vecy*vecy + vecz*vecz;
  const double distance1 = vecx*cd->u/u_norme + vecy*cd->v/u_norme + vecz*cd->w/u_norme;
  const double d = sqrt(distance_points_square - distance1*distance1);
  size = (d<=cd->radius) ? cd->meshsize : 1.e22;
  return true;
}

//------------------------------------------------------------------------

