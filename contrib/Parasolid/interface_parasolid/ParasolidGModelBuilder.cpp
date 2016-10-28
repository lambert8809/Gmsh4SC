#include "ParasolidGModelBuilder.h"
#include "callbacks.h"

#include <iostream>
#include <exception>
#include <algorithm>
#include <list>


// gmsh includes
#include "GModel.h"
#include "GEntity.h"
#include "GenericVertex.h"
#include "GenericFace.h"
#include "GenericEdge.h"
#include "GenericRegion.h"
#include "GEdge.h"
#include "GFaceCompound.h"
#include "Field.h"

#include "Range.h"
#include "GPoint.h"
#include "Context.h"
#include "OpenFile.h"
#include "Gmsh.h"



//------------------------------------------------------------------------

ParasolidGModelBuilder::ParasolidGModelBuilder(ParasolidDataBase *_db):db(_db),fields(NULL),cd(NULL),cd2(NULL){
  model = new GModel();
  GmshInitialize(0,NULL);
  CTX::instance()->terminal = 1;
  CTX::instance()->noPopup = 1;
  CTX::instance()->geom.tolerance  = db->get_parasolid_session_precision()*0.7;
  CTX::instance()->mesh.lcIntegrationPrecision  = CTX::instance()->geom.tolerance * 1.e-3;
  
}

//------------------------------------------------------------------------

ParasolidGModelBuilder::~ParasolidGModelBuilder(){
  delete cd;
  delete cd2;
  delete model;
}

//------------------------------------------------------------------------

void ParasolidGModelBuilder::set_alternative_tag(PK_TOPOL_t original, int alternative)const{
  alternative2original_tags[alternative].insert(original);
  original2alternative_tags[original] = alternative;
}

//------------------------------------------------------------------------

void ParasolidGModelBuilder::buildGModel() const{

  // - ---------------------- treating vertices -----------------------
  // set callbacks
  GenericVertex::setVertexXYZ(vertex_xyz);
  GenericVertex::setVertexMeshSize(vertex_mesh_size);

  int numv = model->getMaxElementaryNumber(0) + 1;
  for (ParasolidDataBase::vertex_iter it = db->vertexbegin();it!=db->vertexend();it++){
    cout << "Vertex :) " << endl;
    // create new vertex
    GenericVertex *v = new GenericVertex(model, numv, *it);
    //    v->setPrescribedMeshSizeAtVertex(0.1);// now overloaded by setVertexMeshSize callback
    numv++;
    // add to GModel
    model->add(v);
    // databade PK -> ptr
    int2ptr[(*it)] = v;
  }

  //  ----------------------- treating edges -----------------------
  // set callbacks
  GenericEdge::setEdgeEvalXYZFromT(edge_xyz_from_t);
  GenericEdge::setEdgeEvalParBounds(edge_parBounds);
  GenericEdge::setEdgeGeomType(edge_geomType);
  GenericEdge::setEdgeDegenerated(edge_degenerate);
  GenericEdge::setEdgeEvalFirstDer(edge_firstder_from_par);
  GenericEdge::setEdgeEvalCurvature(edge_curvature_from_par);
  GenericEdge::setEdgeClosestPoint(edge_closestPointOrthogonal);
  GenericEdge::setEdgeIs3D(edge_is3D);
  GenericEdge::setEdgeReparamOnFace(edge_reparamOnFace);

  int nume = model->getMaxElementaryNumber(0) + 1;
  for (ParasolidDataBase::edge_iter it = db->edgebegin();it!=db->edgeend();it++){
    cout << "Edge :) " << endl;
    // recovering vertices id's
    bool ringtest=false;
    pair<PK_VERTEX_t,PK_VERTEX_t> verts = db->getVertices((*it));
    if (verts.first==PK_ENTITY_null){
      cout << "WARNING !!!!!!  Ring Edge ! -> no vertices ! " << endl;
      cout << "need to set v0=v1" << endl;
      ringtest=true;
    }
    GenericVertex *v0=NULL;
    GenericVertex *v1=NULL;
    map<PK_TOPOL_t,void*>::iterator itfind = int2ptr.find(verts.first);
    if (itfind!=int2ptr.end())
      v0 = (GenericVertex*)(itfind->second);
    itfind = int2ptr.find(verts.second);
    if (itfind!=int2ptr.end())
      v1 = (GenericVertex*)(itfind->second);
    if ((!v0)||(!v1))
      cout << " Missing vertex !!!!!!!" << endl;

    // create new edge 
    GenericEdge *e = new GenericEdge(model, nume, *it,v0,v1);
    nume++;
    // add to GModel
    model->add(e);
    // databade PK -> ptr
    int2ptr[*it] = e;
    if (ringtest) ring_edges[*it] = e;
  }

  // ---------------------- treating faces -----------------------
  // set callbacks
  GenericFace::setFaceGeomType(face_geomType);
  GenericFace::setFacePeriodicInfo(face_periodic_info);
  GenericFace::setFaceUVFromXYZ(face_UVFromXYZ);
  GenericFace::setFaceClosestPoint(face_closestPointOnFaceOrthogonal);
  GenericFace::setFaceContainsPointFromXYZ(face_containsPointFromXYZ);
  GenericFace::setFaceContainsPointFromUV(face_containsPointFromUV);
  GenericFace::setFaceXYZFromUV(face_XYZFromUV);
  GenericFace::setFaceParBounds(face_parBounds);
  GenericFace::setFaceCurvatures(face_curvatures);
  GenericFace::setFaceEvalNormal(face_normal);
  GenericFace::setFaceFirstDer(face_firstDer);
  GenericFace::setFaceSecondDer(face_secondDer);

  vector<int> doneentity;
  map<int,void*> found_ring_edges;
  int numf = model->getMaxElementaryNumber(0) + 1;
  for (ParasolidDataBase::face_iter it = db->facebegin();it!=db->faceend();it++){
    cout << "Face :) " << endl;
    // create new face 
    GenericFace *current_face = new GenericFace(model,numf,*it);
    numf++;
    model->add(current_face);
    // databade PK -> ptr
    int2ptr[*it] = current_face;



    // recover loops
    // this replaces the "OCCFace->setup"
    int nloops;
    PK_LOOP_t *loops;
    doneentity.clear();
    PK_ERROR_code_t err = PK_FACE_ask_loops(*it,&nloops,&loops);

    cout << "face " << current_face->getNativeInt() << " - " << current_face->tag() << endl;
    cout << "# loops:" << nloops << endl;

    list<PK_EDGE_t> edges;
    list<int> signs;

    // check for ring edges
    found_ring_edges.clear();
    GEdge *cylindre_edge=NULL;
    for(int i=0;i<nloops;i++){// Cube face: find 1 loop with 4 edges. Cylindre central face: find 2 loops with 1 edge each
      edges.clear();
      signs.clear();
      db->getEdgesAndSigns(loops[i],edges, signs);
      checkForRingEdges(edges, found_ring_edges);
    }
    if (found_ring_edges.size()){
      treat_ring_edges(current_face,found_ring_edges,numv,nume,cylindre_edge);
    }

    if (cylindre_edge==NULL){
      for(int i=0;i<nloops;i++){
        cout << "loop " << i << endl;
        edges.clear();
        signs.clear();
        db->getEdgesAndSigns(loops[i],edges, signs);
        cout << "edges.size()=" << edges.size() << endl;

        list<int>::iterator its=signs.begin();
        list<int>::iterator ite=edges.begin();
        for (;ite!=edges.end();ite++,its++){
          if (doneentity.end()!=std::find(doneentity.begin(),doneentity.end(),*ite)) continue;// entity already added
          map<PK_TOPOL_t,void*>::iterator itfind = int2ptr.find(*ite);
          if (itfind==int2ptr.end()){
            cout << "int2ptr: edge not found !!!" << endl;
            throw;
          }
          current_face->addBndInfo(i,(GenericEdge*)(itfind->second),*its);
          doneentity.push_back(*ite);

          /////////////////////////
          GenericEdge *e = (GenericEdge*)(itfind->second);
          if ((*its) > 0 ){
            cout << "edge " << e->getNativeInt() << " v " <<  e->getBeginVertex()->getNativeInt() << " -> " << e->getEndVertex()->getNativeInt() << endl;
          }
          else{
            cout << "edge " << e->getNativeInt() << " v " <<  e->getEndVertex()->getNativeInt() << " -> " << e->getBeginVertex()->getNativeInt() << endl;
          }
          /////////////////////////
        }
      }
    }
    else{// HACK pour cylindre
      map<int,void*>::iterator ite = found_ring_edges.begin();
      GenericEdge *firstedge = (GenericEdge*)ite->second;
      current_face->addBndInfo(0,firstedge,1);

      int signe = 1;
      if (firstedge->getEndVertex() == cylindre_edge->getEndVertex()) signe = -1;
      current_face->addBndInfo(0,cylindre_edge,signe);

      ite++;
      GenericEdge *secondedge = (GenericEdge*)ite->second;
      int signe2=1;
      if (secondedge->getEndVertex() == cylindre_edge->getEndVertex()) signe2 = -1;
      current_face->addBndInfo(0,secondedge,signe2);
      
      current_face->addBndInfo(0,cylindre_edge,-signe);
    }
    current_face->createLoops();
  }

  // ----------------------- treating regions -----------------------
  int numr = model->getMaxElementaryNumber(0) + 1;
  for (ParasolidDataBase::region_iter it = db->regionbegin();it!=db->regionend();it++){
    cout << "Region :) " << endl;
    // create new region 
    GenericRegion *r = new GenericRegion(model,numr,*it);
    numr++;
    model->add(r);
    // databade PK -> ptr
    int2ptr[*it] = r;

    // this replaces the "OCCRegion->setup"
    int nshells;
    PK_SHELL_t *shells;
    PK_REGION_ask_shells(*it,&nshells,&shells);
    doneentity.clear();
    for(int i=0;i<nshells;i++){
      PK_FACE_t *fset ;
      PK_LOGICAL_t *orients;
      int nfaces;
      PK_SHELL_ask_oriented_faces(shells[i],&nfaces,&fset,&orients);
      for (int iface=0;iface<nfaces;iface++){
        if (doneentity.end()!=std::find(doneentity.begin(),doneentity.end(),fset[iface])) continue;// entity already added
        map<PK_TOPOL_t,void*>::iterator itfind = int2ptr.find(fset[iface]);
        if (itfind==int2ptr.end()){
          cout << "int2ptr: face not found !!!" << endl;
          throw;
        }
        r->addFace((GenericFace*)(itfind->second), ((orients[iface]==PK_LOGICAL_true) ? 1 : -1));
        doneentity.push_back(fset[iface]);
      }
    }
  }

  //  ParasolidDataBase::topo_iter it = db->topobegin();
  //  ParasolidDataBase::class_iter itclass = db->classbegin();
  //  for (;it!=db->topoend();it++,itclass++){
  //
  //    switch((*itclass)){
  //      case PK_CLASS_body:
  //        break;
  //      case PK_CLASS_region:
  //        break;
  //      case PK_CLASS_shell:
  //        break;
  //      case PK_CLASS_face:
  //        break;
  //      case PK_CLASS_loop:
  //        break;
  //      case PK_CLASS_fin:
  //        break;
  //      case PK_CLASS_edge:
  //        break;
  //      case PK_CLASS_vertex:
  //        break;
  //      default:
  //        break;
  //    }
  //
  //  }




}

//------------------------------------------------------------------------

bool ParasolidGModelBuilder::checkForRingEdges(const list<int> &edges, map<int,void*> &found_ring_edges)const{
  bool found=false;
  list<int>::const_iterator ite=edges.begin();
  for (;ite!=edges.end();ite++){
    map<PK_TOPOL_t,void*>::const_iterator itfind = ring_edges.find(*ite);
    if (itfind!=ring_edges.end()){// edge found
      found_ring_edges[itfind->first] = itfind->second;
      found=true;
    }
  }
  return found;
};

//------------------------------------------------------------------------

void ParasolidGModelBuilder::treat_ring_edges(GenericFace *current_face,map<int,void*> &found_ring_edges,int &numv,int &nume, GEdge *&cylindre_edge)const{
  PK_ERROR_code_t err = PK_ERROR_no_errors;
  // HACK pour cylindre
//  vector<GenericVertex*>temp;

  // for now, simply creating vertices at the end of the ring edges !  
  for (map<int,void*>::iterator it=found_ring_edges.begin();it!=found_ring_edges.end();it++){
    // recover edge bounds
    PK_EDGE_t edge = it->first;
    double s0,s1;
    bool e = edge_parBounds(edge, s0, s1);
    if (!e){
      cout << "treat_ring_edges: can't recover edge bounds ! " << endl;
      throw;
    }
    // get point at minimum bound
    vector<double> coord(3,0.);
    e = edge_xyz_from_t(edge, s0, coord);
    // create new point, add it to edge
    // TODO: quel native ID passer ? Si on passe -1 on peut identifier après, dans les call back ??? -> Parasoli ne donne jamais -1 comme numéro ??? Sinon, créer objet GenericRingVertex ? pfff...
    // ou juste créer GVertex ?!?
    GenericVertex *v = new GenericVertex(model, numv, 0, coord);
    numv++;
    model->add(v);
    static_cast<GenericEdge*>(it->second)->replaceEndingPoints(v,v);

    // HACK pour cylindre
//    temp.push_back(v);
  }

  // HACK pour cylindre
//  if (found_ring_edges.size()==2){
//    cylindre_edge = new LinearSeamEdge(model, nume,temp[0],temp[1]);
//    //current_face->computePeriodicity();
//    nume++;
//    // add to GModel
//    model->add(cylindre_edge);
//    //    GenericEdge *e2 = new GenericEdge(model, nume, 0,temp[1],temp[0]);
//    //    nume++;
//    //    // add to GModel
//    //    model->add(e2);
//  }


  //  if (found_ring_edges.size()==1){// if only one ring edge -> planar face, add one vertex
  //  }
  //  else if (found_ring_edges.size()==2){// if two ring edges -> add two vertices, compute "seam curve"
  //    // recover PK_FACE
  //    PK_FACE_t face = current_face->getNativeInt();
  //    // recover face's surf
  //    PK_SURF_t surf;
  //    err=PK_FACE_ask_surf(face,&surf);
  //    if (err!=PK_ERROR_no_errors){
  //      cout << "treat_ring_edges: can't recover pk_surf !" << endl;
  //      throw;
  //    }
  //    // get face bounds
  //    // get isoparam curve
  //
  //    err = PK_SURF_make_curve_isoparam(surf,);
  //    (
  //     --- received arguments ---
  //     PK_SURF_t                              surf,    --- surface
  //     double                                 param,   --- parameter
  //     PK_PARAM_direction_t                   u_or_v,  --- which direction
  //     --- is constant
  //     const PK_SURF_make_curve_isoparam_o_t *options, --- option structure
  //
  //     --- returned arguments ---
  //     PK_CURVE_t                      *const curve,   --- curve
  //     PK_INTERVAL_t                   *const interval --- portion of curve
  //     --- on surface
  //    )
  //
  //  }
}

//------------------------------------------------------------------------

void ParasolidGModelBuilder::createCompounds()const{
  map<int,set<PK_TOPOL_t> >::iterator it = alternative2original_tags.begin();
  int alt;
  for (;it!=alternative2original_tags.end();it++){// for all compounds
    alt = it->first;
    set<PK_TOPOL_t>::iterator  ito = it->second.begin();
    list<GEdge*> temp;
    list<GFace*> faces;
    PK_TOPOL_t num;
    cout << "composants: ";
    for (;ito!=it->second.end();ito++){// for all entities in the compound
      num = *ito;
      GenericFace *genf = (GenericFace*)(int2ptr[num]);
      cout << "(gen*:" << genf << " ";
      faces.push_back(genf);
      // ito->second->addCompound(f)
      cout << num << " ";
    }
    cout << " -> new GFaceCompound " << alt << " ... " << endl;

    int algo = CTX::instance()->mesh.remeshAlgo;

    // TODO: quel type de param ??? choix auto ???
    GFaceCompound *f = new GFaceCompound(model, alt, faces,temp, GFaceCompound::CONFORMAL_SPECTRAL,algo);
    // typedef enum {HARMONIC_CIRCLE=0, CONFORMAL_SPECTRAL=1, RADIAL_BASIS=2, HARMONIC_PLANE=3, CONVEX_CIRCLE=4,CONVEX_PLANE=5, HARMONIC_SQUARE=6, CONFORMAL_FE=7} typeOfCompound;

    cout << "... done" << endl;

    f->meshAttributes.recombine = faces.back()->meshAttributes.recombine;

    model->add(f);
  }

}

//------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////
//
// THIS FUNCTION COULD BE IN GMSH: NO REFERENCE TO PARASOLID !!!!
//
///////////////////////////////////////////////////////////////////

void ParasolidGModelBuilder::test() const{

  // tests on edges and vertices
  Range<double> bounds;
  GPoint gp;
  SPoint2 uv;
  double curv;
  double epsil=0.;//1.e-2;
  SVector3 firstder;
  double param;
  for (GModel::eiter it = model->firstEdge();it!=model->lastEdge();it++){
    GEdge *e = *it;
    cout << "------------------ edge " << e->getNativeInt() << endl;
    GEntity::GeomType type = e->geomType();
    cout << "------------- edge type=";
    switch (type){
      case GEntity::Line:
        cout << "Line";
        break;
      case GEntity::Circle:
        cout << "Circle";
        break;
      case GEntity::Ellipse:
        cout << "Ellipse";
        break;
      case GEntity::Parabola:
        cout << "Parabola";
        break;
      case GEntity::Hyperbola:
        cout << "Hyperbola";
        break;
      case GEntity::Bezier:
        cout << "Bezier";
        break;
      case GEntity::BSpline:
        cout << "BSpline";
        break;
      case GEntity::TrimmedCurve:
        cout << "TrimmedCurve";
        break;
      case GEntity::Unknown:
        cout << "Unknown";
        break;
    }
    cout << endl;
    GVertex *v0=e->getBeginVertex();
    GVertex *v1=e->getEndVertex();

    if (v0 && v1)
      cout << "made of vertices (" << v0->x() << "," <<  v0->y() << "," <<  v0->z() << ")  (" <<  v1->x() << "," <<  v1->y() << "," <<  v1->z() << ")" << endl; 
    else cout << "ring edge" << endl;

    bounds = e->parBounds(0);
    cout << "parbounds=[" << bounds.low() << "," << bounds.high() << "]" << endl;
    double midpar=(bounds.low()+bounds.high())/2.;
    gp = e->point(midpar);
    cout << "midpoint=[" << gp.x() << "," << gp.y() << "," << gp.z() << "]" << endl;
    cout << "is degenerated:" << ((e->degenerate(42))==true ? "yes" : "no") << endl;
    firstder = e->firstDer(midpar);
    cout << "mid firstder=[" << firstder[0] << "," << firstder[1] << "," << firstder[2] << "]" << endl;
    curv = e->curvature(midpar);
    cout << "mid curvature=" << curv << endl;
    SPoint3 point(gp.x(),gp.y(),gp.z());
    point[1] += epsil;
    point[2] += epsil;
    GPoint closestPoint;
    GenericEdge *gene;
    LinearSeamEdge *line;
    if (gene = dynamic_cast<GenericEdge*>(e)){
      closestPoint = gene->closestPoint(point,param);
    }
    else if (line = dynamic_cast<LinearSeamEdge*>(e)){
      closestPoint = line->closestPoint(point,param);
    }
    else
      throw;
    cout << "closest point (mid+epsilon) query point=[" << point[0] << "," << point[1] << "," << point[2] << "]" << endl;
    cout << "closest point=[" << closestPoint.x() << "," << closestPoint.y() << "," << closestPoint.z() << "]" << endl;
    cout << "closest point param=" << param << endl; 
    cout << "is3D:" << ((e->is3D()==true) ?  "yes" : "no") << endl;
  }


  // tests on faces
  Pair<SVector3,SVector3> fder;
  double curvmax,curvmin;
  SVector3 normale, dirmin,dirmax,dudu, dvdv, dudv;
  Range<double> ubounds,vbounds;
  SPoint3 random;
  double initialguess[2] = {0.,0.};
  random[0] = 1.;
  random[1] = 2.;
  random[2] = 3.4;
  for (GModel::fiter it = model->firstFace();it!=model->lastFace();it++){
    GFace *f = *it;
    cout << "------------------ face " << f->getNativeInt() << endl;
    std::list<GEdge*> edges = f->edges();
    cout << "#subentities: " << edges.size() << endl;
    GEntity::GeomType type = f->geomType();
    cout << "--------------face type=";
    switch(type){
      case GEntity::Plane:
        cout << "Plane";
        break;
      case GEntity::Cylinder:
        cout << "Cylinder";
        break;
      case GEntity::Cone:
        cout << "Cone";
        break;
      case GEntity::Sphere:
        cout << "Sphere";
        break;
      case GEntity::Torus:
        cout << "Torus";
        break;
      case GEntity::BezierSurface:
        cout << "BezierSurface";
        break;
      case GEntity::BSplineSurface:
        cout << "BSplineSurface";
        break;
      case GEntity::SurfaceOfRevolution:
        cout << "SurfaceOfRevolution";
        break;
      case GEntity::Unknown:
        cout << "Unknown";
        break;
    }
    cout << endl;
    ubounds = f->parBounds(0);
    vbounds = f->parBounds(1);
    cout << "face bounds: [" << ubounds.low() << "," << ubounds.high() << "],[" << vbounds.low() << "," << vbounds.high() << "]" << endl;

    double umid = (ubounds.low()+ubounds.high())/2.;
    double vmid = (vbounds.low()+vbounds.high())/2.;
    cout << "uvmid = " <<  "(" << umid << "," << vmid << ")" << endl;


    //    //------------------------------------------------
    //    //   HACK
    //    //------------------------------------------------
    //    vector<double> brol;
    //    brol.push_back(umid);
    //    brol.push_back(vmid);
    //    bool resu;
    //    bool ok = face_containsPointFromUV(f->getNativeInt(), brol,resu);
    //    cout << "resultat: face_containsPointFromUV: " << resu << endl;
    //    if (!resu) throw;
    //    //------------------------------------------------
    //    //------------------------------------------------





    gp = f->point(umid,vmid);
    SPoint3 point(gp.x(),gp.y(),gp.z());
    cout << "midpt = [" << gp.x() << "," << gp.y() << "," << gp.z() << "]" << endl;
    uv = f->parFromPoint(point,true);
    cout << "parFromPoint uv=" << "(" << uv[0] << "," << uv[1] << ")" << endl;

    cout << "contains random pt: " << ((f->containsPoint(random)==true) ? ("yes") : ("no")) << endl;
    cout << "contains    mid pt: " << ((f->containsPoint(point)==true) ? ("yes") : ("no")) << endl;
    point[1] += epsil;
    point[2] += epsil;
    GPoint closestPoint = f->closestPoint(point,initialguess);
    cout << "closest point (mid+epsilon) query point=[" << point[0] << "," << point[1] << "," << point[2] << "]" << endl;
    cout << "closest point=[" << closestPoint.x() << "," << closestPoint.y() << "," << closestPoint.z() << "]" << endl;

    f->curvatures(uv,&dirmax,&dirmin,&curvmax,&curvmin);
    cout << "curvmax=" << curvmax << "   dirmax=[" << dirmax[0] << "," << dirmax[1] << "," << dirmax[2] << "]" << endl;
    cout << "curvmin=" << curvmin << "   dirmin=[" << dirmin[0] << "," << dirmin[1] << "," << dirmin[2] << "]" << endl;
    curvmax = f->curvatureMax(uv);
    cout << "curvmax=" << curvmax << endl;
    normale = f->normal(uv);
    cout << "normal=[" << normale[0] << "," << normale[1] << "," << normale[2] << "]" << endl;
    fder = f->firstDer(uv);
    cout << "fder.first()=[" << fder.first()[0] << "," << fder.first()[1] << "," << fder.first()[2] << "]" << endl;
    cout << "fder.second()=[" << fder.second()[0] << "," << fder.second()[1] << "," << fder.second()[2] << "]" << endl;
    f->secondDer(uv,&dudu,&dvdv,&dudv);
    cout << "dudu=[" << dudu[0] << "," << dudu[1] << "," << dudu[2] << "]" << endl;
    cout << "dvdv=[" << dvdv[0] << "," << dvdv[1] << "," << dvdv[2] << "]" << endl;
    cout << "dudv=[" << dudv[0] << "," << dudv[1] << "," << dudv[2] << "]" << endl;


    // test exhaustif de GVertex->reparamOnFace
    for (list<GEdge*>::iterator it=edges.begin();it!=edges.end();it++){
      for (int i=0;i<2;i++){
        GVertex *v = (i==0) ? (*it)->getBeginVertex() : (*it)->getEndVertex();
        if (!v){
          cout << "vertex->reparamOnFace: aborting, ring edge ! " << endl;
          continue;
        }
        uv = v->reparamOnFace(f,0);
        cout << "vertex->reparamOnFace uv=" << "(" << uv[0] << "," << uv[1] << ")" << endl;
      }
    }
  }

  // test regions
  if (0){
    for (GModel::riter it = model->firstRegion();it!=model->lastRegion();it++){
      GRegion *region = *it;
      cout << "------------------ region " << region->getNativeInt() << endl;
      std::list<GFace*> fset = region->faces();
      cout << "#subentities: " << fset.size() << endl;
      for (std::list<GFace*>::iterator itf =fset.begin();itf!=fset.end();itf++){
        GFace *f = *itf;
        cout << "--- made of face " << f->getNativeInt() << endl;
        std::list<GEdge*> eset = f->edges();
        cout << "#subentities: " << eset.size() << endl;
        std::list<int> dirs = f->orientations();
        std::list<int>::iterator itdir =dirs.begin();

        for (std::list<GEdge*>::iterator ite =eset.begin();ite!=eset.end();ite++,itdir++){
          GEdge *e = *ite;
          cout << "       made of edge " << e->getNativeInt() << endl;
          for (int ie=0;ie<2;ie++){
            int num = ie;
            if ((*itdir)<0) num = (ie==0) ? 1 : 0;
            GVertex *v = (num==0) ? e->getBeginVertex() : e->getEndVertex();
            if (v)
              cout << "             made of vertex " << v->getNativeInt() << endl;
          }
        }
      }
    }
  }




}

//------------------------------------------------------------------------

void ParasolidGModelBuilder::setMeshSizeFields(){

  if (fields) delete fields;
  if (cd) delete cd;
  if (cd2) delete cd2;
  fields = new GenericField(); 


  // cylinder 1
  cd = new cyl_data();
  cd->x = -0.5; 
  cd->y = -1.0; 
  cd->z =  1.0; 
  cd->u =  0.0; 
  cd->v =  1.0; 
  cd->w =  0.0; 
  cd->radius =  0.5; 
  cd->meshsize =  0.08; 
  fields->setCallbackWithData(cylinder_field_callback,cd);

  // cylinder 2
  cd2 = new cyl_data();
  cd2->x = -0.5; 
  cd2->y = -1.0; 
  cd2->z =  1.0; 
  cd2->u =  1.0; 
  cd2->v =  0.0; 
  cd2->w =  0.0; 
  cd2->radius =  0.1; 
  cd2->meshsize =  0.01; 
  fields->setCallbackWithData(cylinder_field_callback,cd2);

  FieldManager *gmshfields = model->getFields();
  gmshfields->reset();
  gmshfields->setBackgroundField(fields);
}

//------------------------------------------------------------------------

void ParasolidGModelBuilder::readandwriteGEO() const{

  ///////////////////////////////////////
  // just a test of read and write geo //
  ///////////////////////////////////////
  GModel *modele = new GModel();
  cout << "readGEO: reading geo" << endl;
  modele->readGEO("hello.geo");

  //  typedef std::set<GVertex*, GEntityLessThan>::iterator viter;
  //  for(viter it = modele->firstVertex(); it != modele->lastVertex(); it++){
  //    double val = (*it)->prescribedMeshSizeAtVertex();
  //    cout << "val=" << val << "  xyz=" << (*it)->x() << "," <<  (*it)->y() << "," <<  (*it)->z() <<  endl;
  //  }


  cout << "readGEO: writting geo" << endl;
  modele->writeGEO("geometry.geo");

  cout << "readGEO: meshing" << endl;
  modele->mesh(2);


  modele->writeMSH("geometrymesh.msh");

  delete modele;
}

//------------------------------------------------------------------------

void ParasolidGModelBuilder::mesh(int dim) const{
  cout << "readGEO: writting geo" << endl;
  model->writeGEO("geometry.geo");


  //  return;

  //  cout << "writting geo" << endl;
  //  model->writeGEO("hellobeforemeshing.geo");


  // setting GMSH meshing options
  //  GmshSetOption("Mesh","Algorithm",9.0);// for quad points insertion 
  //  GmshSetOption("Mesh","Algorithm3D",9.0);// for hex points insertion 

  //  GmshSetOption("Mesh","Smoothing",0.0);
  //  GmshSetOption("Mesh","Optimize",0.0);
  //  GmshSetOption("Mesh","OptimizeNetgen",0.0);

  //  GmshSetOption("Mesh","Recombine3DAll",1.0);// for 3D recombination

  //#GmshSetOption("Mesh","RecombineAll",1.0)
  //#GmshSetOption("Mesh","RecombineAll",1.0)
  //#GmshSetOption("Mesh","RecombinationAlgorithm",0.0)# 1 is default=Blossom, 0 is based on better quad quality (greedy, not blossom->less quads)






  // if compounds exist...
  if (alternative2original_tags.size()){
    // sets params for compounds
    GmshSetOption("Mesh","RemeshParametrization",1.); //(0) harmonic (1) conformal 
    GmshSetOption("Mesh","RemeshAlgorithm",0.);  //(0) nosplit (1) automatic (2) split metis
    // create compounds
    createCompounds();
  }


  //  CTX::instance()->mesh.lcMin  = 0.05;
  //  CTX::instance()->mesh.lcMax  = 0.1;


  cout << "***********************************************" << endl;
  cout << "lcIntegrationPrecision = " << CTX::instance()->mesh.lcIntegrationPrecision << endl;
  cout << "toleranceEdgeLength = " << CTX::instance()->mesh.toleranceEdgeLength << endl;
  cout << "tolerance = " << CTX::instance()->geom.tolerance << endl;
  cout << "PK session tolerance : " << db->get_parasolid_session_precision() << endl;
  cout << "***********************************************" << endl;

  CTX::instance()->mesh.lcFromPoints  = 1;
  CTX::instance()->mesh.lcFromCurvature = 0;
  CTX::instance()->mesh.lcExtendFromBoundary = 1;

  if (CTX::instance()->mesh.lcFromCurvature) 
    CTX::instance()->mesh.lcFromPoints  = 1;// Sinon, semble planter ...


  CTX::instance()->mesh.algo2d  = 9.;
  CTX::instance()->mesh.algo3d  = 9.;
  CTX::instance()->mesh.nbSmoothing  = 0.;
  CTX::instance()->mesh.optimize  = 0.;
  CTX::instance()->mesh.optimizeNetgen  = 0.;
  GmshSetOption("Mesh","Recombine3DAll",1.0);// for 3D recombination



  model->mesh(dim);






  model->writeMSH("mesh_from_PKInterface.msh");

}

