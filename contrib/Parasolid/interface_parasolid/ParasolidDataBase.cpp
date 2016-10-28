
#include "ParasolidDataBase.h"
#include <algorithm>
#include <math.h>
#include <list>


using namespace std;

//------------------------------------------------------------------------

ParasolidDataBase::ParasolidDataBase(string _schema_path):fi(NULL){
  schema_path.assign(_schema_path);
  registerFrustrum();
  registerFrustrumDeltas();
  startParasolidSession();
} 

//------------------------------------------------------------------------

ParasolidDataBase::~ParasolidDataBase(){
  delete fi;
}

//------------------------------------------------------------------------

void ParasolidDataBase::registerFrustrum(){

  // PEB interface
  if (!fi){
    fi = new frustrumInterface();
    set_frustrum_interface_ptr(fi);
  }
  fi->set_schema_path(schema_path);
  // end PEB interface



  extern void FSTART( int *);
  extern void FABORT( int *);
  extern void FSTOP( int *);
  extern void FMALLO( int *, char **, int *);
  extern void FMFREE( int *, char **, int *);
  extern void GOSGMT( const int *, const int *, const int *, const int *,
      const double *, const int *, const int *, int *);
  extern void GOOPSG( const int *, const int *, const int *, const int *,
      const double *, const int *, const int *, int *);
  extern void GOCLSG( const int *, const int *, const int *, const int *,
      const double *, const int *, const int *, int *);
  extern void GOPIXL( const int *, const double *, const int *, const int *,
      int *);
  extern void GOOPPX( const int *, const double *, const int *, const int *,
      int *);
  extern void GOCLPX( const int *, const double *, const int *, const int *,
      int *);
  extern void FFOPRD( const int *, const int *, const char *, const int *,
      const int *, int *, int *);
  extern void FFOPWR( const int *, const int *, const char *, const int *,
      const char *, const int *, int *, int *);
  extern void FFCLOS( const int *, const int *, const int *, int *);
  extern void FFREAD( const int *, const int *, const int *, char *, int *,
      int *);
  extern void FFWRIT( const int *, const int *, const int *, const char *,
      int *);
  extern void FFOPRB( const int *, const int *, const int *, int *, int *,
      int *);
  extern void FFSEEK( const int *, const int *, const int *, int *);
  extern void FFTELL( const int *, const int *, int *, int *);
  extern void FGCRCU( const char *, int *, int *, int *, int *, double *,
      int *, double *, int *);
  extern void FGCRSU( const char *, int *, int *, int *, int *, double *,
      int *, double *, int *);
  extern void FGEVCU( int *, double *, double *, double *, int *,
      double *, int *);
  extern void FGEVSU( int *, double *, double *, double *, double *,
      int *, int *, int *, double *, int *);
  extern void FGPRCU( int *, double *, double *, double *, int *, int *);
  extern void FGPRSU( int *, double *, double *, double *, int *, int *);
  printf("Registering Example Frustrum ...\n");
  PK_SESSION_frustrum_o_m( fru );
  fru.fstart = FSTART;
  fru.fabort = FABORT;
  fru.fstop  = FSTOP;
  fru.fmallo = FMALLO;
  fru.fmfree = FMFREE;
  fru.gosgmt = GOSGMT;
  fru.goopsg = GOOPSG;
  fru.goclsg = GOCLSG;
  fru.gopixl = GOPIXL;
  fru.gooppx = GOOPPX;
  fru.goclpx = GOCLPX;
  fru.ffoprd = FFOPRD;
  fru.ffopwr = FFOPWR;
  fru.ffclos = FFCLOS;
  fru.ffread = FFREAD;
  fru.ffwrit = FFWRIT;
  fru.ffoprb = FFOPRB;
  fru.ffseek = FFSEEK;
  fru.fftell = FFTELL;
  fru.fgcrcu = FGCRCU;
  fru.fgcrsu = FGCRSU;
  fru.fgevcu = FGEVCU;
  fru.fgevsu = FGEVSU;
  fru.fgprcu = FGPRCU;
  fru.fgprsu = FGPRSU;
  PK_SESSION_register_frustrum( &fru );
}

//------------------------------------------------------------------------

void ParasolidDataBase::registerFrustrumDeltas(){
  extern PK_ERROR_code_t FRU_delta_open_for_write( PK_PMARK_t pmark, PK_DELTA_t *key );
  extern PK_ERROR_code_t FRU_delta_open_for_read( PK_DELTA_t key );
  extern PK_ERROR_code_t FRU_delta_close( PK_DELTA_t key );
  extern PK_ERROR_code_t FRU_delta_write( PK_DELTA_t key, unsigned n_bytes, const char *bytes);
  extern PK_ERROR_code_t FRU_delta_read( PK_DELTA_t key, unsigned n_bytes, char *bytes);
  extern PK_ERROR_code_t FRU_delta_delete( PK_DELTA_t key );

  delta_fru.open_for_write_fn = FRU_delta_open_for_write;
  delta_fru.open_for_read_fn = FRU_delta_open_for_read;
  delta_fru.close_fn = FRU_delta_close; 
  delta_fru.write_fn = FRU_delta_write;
  delta_fru.read_fn = FRU_delta_read;
  delta_fru.delete_fn = FRU_delta_delete;
  //VERIFY(PK_DELTA_register_callbacks(delta_fru) == PK_ERROR_no_errors);
  PK_DELTA_register_callbacks(delta_fru);
}

//------------------------------------------------------------------------

void ParasolidDataBase::displayErrorMessage(const string &s,const PK_ERROR_code_t &e)const{
  if (e!=PK_ERROR_no_errors)
    cout << "ERROR from " << s << " : " << e << endl;
  else
    cout << s << "   OK :)" << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::startParasolidSession(){  

  err = PK_ERROR_no_errors;

  // Starts the modeller

  PK_SESSION_start_o_m( start_options );

  // PK_SESSION_start also initialises the following interface parameters:
  //		PK_SESSION_set_check_arguments    PK_LOGICAL_true
  //		PK_SESSION_set_check_self_int     PK_LOGICAL_true
  //		PK_SESSION_set_check_continuity   PK_LOGICAL_true
  //		PK_SESSION_set_general_topology   PK_LOGICAL_false
  //		PK_SESSION_set_swept_spun_surfs   PK_LOGICAL_false
  //		PK_SESSION_set_tag_limit          0 (ie: no limit)
  //		PK_SESSION_set_angle_precision    0.00000000001
  //		PK_SESSION_set_precision          0.00000001

  cout << "starting session" << endl;
  err=PK_SESSION_start( &start_options );

  displayErrorMessage("ParasolidDataBase::startParasolidSession::PK_SESSION_start",err);
  cout << "...done starting session" << endl;

  // Check to see if it all started up OK
  PK_LOGICAL_t was_error = PK_LOGICAL_true;
  PK_ERROR_sf_t error_sf;
  PK_ERROR_ask_last( &was_error, &error_sf );
  if ( was_error ){
    cout << "startParasolidSession : there are errors !!!" << endl;
  }
  else
    cout << "startParasolidSession : no error :) " << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::displayBodyConfig()const{
  PK_BODY_config_t body_config;
  err = PK_BODY_ask_config(body, &body_config);
  displayErrorMessage("ParasolidDataBase::readFile::PK_BODY_ask_config",err);
  cout << " BODY config: ";
  switch (body_config){
    case PK_BODY_config_standard_c:
      cout << "PK_BODY_config_standard_c" << endl;
      break;
    case PK_BODY_config_compound_c:
      cout << "PK_BODY_config_compound_c" << endl;
      break;
    case PK_BODY_config_child_c:
      cout << "PK_BODY_config_child_c" << endl;
      break;
    default:
      cout << "Unknown body type: " << body_config << endl;
  }
}

//------------------------------------------------------------------------

void ParasolidDataBase::readFile(const string &path, const string &s){

  cout << "PSDB readfile path=" << path << endl;
  fi->set_filename_path(path);

  num_parts = 0;
  cout << "reading Parasolid file..." << endl;

  // TODO: about difference between key and filename ... how to specify the file path /name ??? See frustrum functions.
  // and how to give the right key... i guess the user will have to do so... unless automatic reading in the file... ?

  PK_PART_receive_o_m(receive_options);
  receive_options.transmit_format = PK_transmit_format_text_c;

  err = PK_PART_receive(s.c_str(), &receive_options , &num_parts , &parts);
  displayErrorMessage("ParasolidDataBase::readFile::PK_PART_receive",err);
  cout << " num_parts=" << num_parts << endl;

  if (num_parts<=0){
    cout << "no parts, aborting ! :( " << endl;
    return;
  }
  //---------------------------
  // reading every body...
  //---------------------------
  for (int ipart=0;ipart<num_parts;ipart++){
    body = parts[ipart];
    //PK_MEMORY_free (parts);

    displayBodyConfig();

    err = PK_ENTITY_ask_class( body, &tClass );
    displayErrorMessage("ParasolidDataBase::readFile::PK_ENTITY_ask_class",err);
    if ( tClass == PK_CLASS_body ){
      cout << " found a body ! :) " << endl;
    }
    else if ( tClass == PK_CLASS_assembly){
      cout << " found an assembly ! :) " << endl;
    }
    else{
      cout << " not a body :(   PK_CLASS_t=" << tClass << endl;
    }



    int npartslocal = 1;
    PK_PART_t *localparts;
    if (tClass == PK_CLASS_assembly){
      // recover parts
      err = PK_ASSEMBLY_ask_parts(body,&npartslocal,&localparts);
      displayErrorMessage("ParasolidDataBase::readFile::PK_ASSEMBLY_ask_parts",err);
      cout << "Assembly has " << npartslocal << " parts" << endl;
    }

    /* "In addition, every face, edge and vertex in a body requires an attached geometric entity – a
       surface, curve or point – for a fully defined, valid model." */

    // A part is a body or an assembly   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    /* And "An assembly can also have construction geometry,..." */

    // I guess we dont want construction stuff, so...   PK_BODY_ask_topology seems the best.
    // Also, PK_BODY_ask_components returns weird stuff as acorn, wire, etc... i guess we don't need that...

    /*NOTE: possible d'avoir les fins, avec ça:
      (pour connaitre orientation des edges dans une loop...
      struct PK_BODY_ask_topology_o_s
      {
      int          o_t_version;     --- version number
      PK_LOGICAL_t want_fins;       --- whether fins required in output
      --- ( PK_LOGICAL_false )
      };
      typedef struct PK_BODY_ask_topology_o_s PK_BODY_ask_topology_o_t;*/

    // Note: il existe:
    /*
       PK_ERROR_code_t     PK_BODY_ask_vertices
       (
       --- received arguments ---
       PK_BODY_t           body,           --- a body

       --- returned arguments ---
       int          *const n_vertices,     --- number of vertices (>= 0)
       PK_VERTEX_t **const vertices        --- vertices (optional)
       )*/

    for (int ilocal=0;ilocal<npartslocal;ilocal++){
      if (tClass == PK_CLASS_assembly){
        cout << "Treating assembly number " << ilocal+1 << "." << endl;
        body = localparts[ilocal];
      }

      PK_BODY_ask_topology_o_m(topo_ask_options);
      int n_topols_temp;
      PK_TOPOL_t *topols_temp;
      PK_CLASS_t *classes_temp;
      int  n_relations;
      int *parents;
      int *children;
      PK_TOPOL_sense_t *senses;
      err=PK_BODY_ask_topology(body, &topo_ask_options,
          &n_topols_temp,    
          &topols_temp,      
          &classes_temp,     
          &n_relations, 
          &parents,     
          &children,    
          &senses       
          );
      displayErrorMessage("ParasolidDataBase::readFile::PK_BODY_ask_topology",err);
      cout << " reading body " << ipart << " number of topological entities=" << n_topols_temp << endl;

      for (int itop=0;itop<n_topols_temp;itop++){

        //check
        vector<PK_TOPOL_t>::iterator itfind = find(topols.begin(),topols.end(),topols_temp[itop]);
        if (itfind!=topols.end()){
          cout << " *** WARNING ***  topological entity " << topols_temp[itop] << " already exists ! Shouldn't happen ! " << endl;
        }
        if (find(topols.begin(),topols.end(),topols_temp[itop]) == topols.end()){
          topols.push_back(topols_temp[itop]);
          classes.push_back(classes_temp[itop]);
        }
        else
          cout << "entity " << topols_temp[itop] << " already exists, not adding entity" << endl;

        //      cout << "-----------------------" << endl;
        //      cout << "itop=" << itop << ":" << endl;
        //      cout << "topols_temp[itop]= " << topols_temp[itop] << endl;

        int id;
        PK_ENTITY_ask_identifier(topols_temp[itop],&id);

        //      cout << "id=" << id << endl;


      }// end reading every topol entity






      // also creating list of vertices, edges, faces and regions... maybe redundant... anyway...
      int num;
      PK_VERTEX_t *v;
      err = PK_BODY_ask_vertices(body,&num,&v);
      fillVector(vertices,num,v,err,"ParasolidDataBase::readFile::PK_BODY_ask_vertices");
      PK_EDGE_t *e;
      err = PK_BODY_ask_edges(body,&num,&e);
      fillVector(edges,num,e,err,"ParasolidDataBase::readFile::PK_BODY_ask_edges");
      PK_FACE_t *f;
      err = PK_BODY_ask_faces(body,&num,&f);
      fillVector(faces,num,f,err,"ParasolidDataBase::readFile::PK_BODY_ask_faces");
      PK_REGION_t *r;
      err = PK_BODY_ask_regions(body,&num,&r);
      fillVector(regions,num,r,err,"ParasolidDataBase::readFile::PK_BODY_ask_regions");

    }
  }// end reading every body
  cout << "reading done " << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::getEdgesAndSigns(const PK_LOOP_t &loop, list<PK_EDGE_t> &edges, list<int> &signs)const{
  int nfins;
  PK_FIN_t *fins;
  PK_ERROR_code_t err = PK_LOOP_ask_fins(loop,&nfins,&fins);// returns ORDERED fins !
  for (int ifin=0;ifin<nfins;ifin++){
    PK_EDGE_t e;
    err = PK_FIN_ask_edge(fins[ifin],&e);
    edges.push_back(e);
    PK_LOGICAL_t res;
    err = PK_FIN_is_positive(fins[ifin],&res);
    signs.push_back(((res==PK_LOGICAL_true) ? 1 : -1));
  }
  return;
}

//------------------------------------------------------------------------

void ParasolidDataBase::fillVector(vector<PK_ENTITY_t> &e, int num, const PK_ENTITY_t *original, const PK_ERROR_code_t &err, const string &s){

  displayErrorMessage(s.c_str(),err);
  cout << " number of entities=" << num << endl;
  for (int inum=0;inum<num;inum++){
    // check if already exists...
    if (find(e.begin(),e.end(),original[inum]) == e.end()){
      PK_CLASS_t classe;
      PK_ENTITY_ask_class(original[inum],&classe);
      if (classe==PK_CLASS_region){
        PK_LOGICAL_t is_solid;
        PK_REGION_is_solid(original[inum],&is_solid);
        if (is_solid==PK_LOGICAL_false) continue;// this region is void... outside the body of interest...
      }
      e.push_back(original[inum]);
    }
    else
      cout << "entity " << original[inum] << " already exists, not adding" << endl;
  }
}

//------------------------------------------------------------------------

pair<PK_VERTEX_t,PK_VERTEX_t> ParasolidDataBase::getVertices(const PK_EDGE_t &edge)const{
  PK_VERTEX_t vertices[2];
  PK_EDGE_ask_vertices(edge,vertices);

  return make_pair(vertices[0],vertices[1]);
}

//------------------------------------------------------------------------

void ParasolidDataBase::createTwoBlocks(){
  cout << "creating 2 blocks... ";
  PK_AXIS2_sf_t basis_set;
  PK_BODY_t primitive;
  PK_BODY_t primitive2;

  PK_VECTOR_t location = {0.,0.,1.};
  PK_AXIS2_sf_t second_set;
  PK_VECTOR1_t unit1 = {0.,0.,1.};
  PK_VECTOR1_t unit2 = {1.,0.,0.};

  cout << "basis_set.location:" << endl;
  cout << basis_set.location.coord[0] << " " << basis_set.location.coord[1] << " "   << basis_set.location.coord[2] << " "    << endl;


  second_set.location = location;
  second_set.axis = unit1;
  second_set.ref_direction = unit2;

  double x=1.;
  double y=2.;
  double z=1.;
  PK_ERROR_code_t err=PK_BODY_create_solid_block(x,y,z, NULL, &primitive );
  err=PK_BODY_create_solid_block(x,y,z, &second_set, &primitive2 );
  if (err==PK_ERROR_no_errors) cout << " done." << endl;
  else cout << "err=" << err << endl;
}

//------------------------------------------------------------------------


void ParasolidDataBase::createCutBlock(){

  PK_LINE_sf_t form1,form2,form3,form4,form5,form6,form7;
  PK_VECTOR1_t v1 = {1.,0.,0.};
  PK_VECTOR1_t v2 = {0.,1.,0.};
  PK_VECTOR1_t v3 = {-1.,0.,0.};
  PK_VECTOR1_t v4 = {0.,-1.,0.};
  PK_VECTOR_t p1 = {-1.,-1,0.};
  PK_VECTOR_t p2 = {1,-1.,0.};
  PK_VECTOR_t p3 = {1.,1.,0.};
  PK_VECTOR_t p4 = {-1.,1.,0.};
  PK_VECTOR_t p5 = {-2.,1.,0.};
  PK_VECTOR_t p6 = {-2.,-1.,0.};
  form1.basis_set.location = p1;
  form1.basis_set.axis = v1;
  form2.basis_set.location = p2;
  form2.basis_set.axis = v2;
  form3.basis_set.location = p3;
  form3.basis_set.axis = v3;
  form4.basis_set.location = p4;
  form4.basis_set.axis = v4;

  form5.basis_set.location = p1;
  form5.basis_set.axis = v3;
  form6.basis_set.location = p6;
  form6.basis_set.axis = v2;
  form7.basis_set.location = p5;
  form7.basis_set.axis = v1;


  PK_LINE_t lines[4];
  PK_LINE_t lines2[4];
  //PK_LINE_t lines2[3];
  PK_LINE_create(&form1,&lines[0]);
  PK_LINE_create(&form2,&lines[1]);
  PK_LINE_create(&form3,&lines[2]);
  PK_LINE_create(&form4,&lines[3]);

  PK_LINE_create(&form5,&lines2[0]);
  PK_LINE_create(&form6,&lines2[1]);
  PK_LINE_create(&form7,&lines2[2]);
  lines2[3] = lines[3];


  PK_EDGE_t *edges,*edges2;
  PK_EDGE_t edges3[4];
  int *indices,*indices2;
  int N,N2;
  //  PK_ENTITY_track_r_t track;

  PK_INTERVAL_t intervals[4];
  PK_INTERVAL_t intervals2[4];
  //  PK_INTERVAL_t intervals2[3];
  intervals[0].value[0] = 0.;
  intervals[0].value[1] = 2.;
  intervals[1].value[0] = 0.;
  intervals[1].value[1] = 2.;
  intervals[2].value[0] = 0.;
  intervals[2].value[1] = 2.;
  intervals[3].value[0] = 0.;
  intervals[3].value[1] = 2.;

  intervals2[0].value[0] = 0.;
  intervals2[0].value[1] = 1.;
  intervals2[1].value[0] = 0.;
  intervals2[1].value[1] = 2.;
  intervals2[2].value[0] = 0.;
  intervals2[2].value[1] = 1.;
  intervals2[3].value[0] = 0.;
  intervals2[3].value[1] = 2.;

  PK_CURVE_make_wire_body_o_t opt;
  PK_CURVE_make_wire_body_o_m(opt);
  opt.want_edges = PK_LOGICAL_true;

  PK_BODY_t bod;

  err=PK_CURVE_make_wire_body_2(4,lines,intervals,&opt,&bod,&N,&edges,&indices);
  if (err!=PK_ERROR_no_errors)
    cout << "err PK_CURVE_make_wire_body_2 =" << err << endl;

  err=PK_CURVE_make_wire_body_2(4,lines2,intervals2,&opt,&bod,&N2,&edges2,&indices2);
  //err=PK_CURVE_make_wire_body_2(3,lines2,intervals2,&opt,&bod,&N2,&edges2,&indices2);
  if (err!=PK_ERROR_no_errors)
    cout << "err PK_CURVE_make_wire_body_2 =" << err << endl;
  cout << "N2=" << N2 << endl;






  //  PK_INTERVAL_t intervalsbis[7];
  //  int *indicesbis;
  //  PK_LINE_t linesbis[7];
  //  for (int i=0;i<4;i++){
  //    intervalsbis[i] = intervals[i];
  //    linesbis[i] = lines[i];
  //  }
  //  for (int i=0;i<3;i++){
  //    intervalsbis[4+i] = intervals2[i];
  //    linesbis[4+i] = lines2[i];
  //  }
  //  PK_EDGE_t *edgesbis;
  //  int Nbis;
  //  err=PK_CURVE_make_wire_body_2(7,linesbis,intervalsbis,&opt,&bod,&Nbis,&edgesbis,&indicesbis);
  //  if (err!=PK_ERROR_no_errors)
  //    cout << "err PK_CURVE_make_wire_body_2 BIS =" << err << endl;
  //  cout << "Nbis=" << Nbis << endl;


















  // creating orientations... :(
  PK_LOGICAL_t orientations[1];
  for (int i=0;i<1;i++)
    orientations[i] = PK_LOGICAL_true;
  int shared_loop[1];
  for (int i=0;i<1;i++)
    shared_loop[i] = -1;


  edges3[0] = edges2[0];
  edges3[1] = edges2[1];
  edges3[2] = edges2[2];
  edges3[3] = edges[3];


  PK_FACE_t face1 = PK_ENTITY_null;
  PK_FACE_t face2 = PK_ENTITY_null;

  err = PK_EDGE_make_faces_from_wire(1,&edges[0],orientations,shared_loop,&face1);
  if (err!=PK_ERROR_no_errors)
    cout << "err PK_EDGE_make_faces_from_wire=" << err << endl;


  //err = PK_EDGE_make_faces_from_wire(1,&edges2[0],orientations,shared_loop,&face2);
  err = PK_EDGE_make_faces_from_wire(1,&edges3[0],orientations,shared_loop,&face2);
  if (err!=PK_ERROR_no_errors)
    cout << "err PK_EDGE_make_faces_from_wire=" << err << endl;

  // Create a surface to fit and attach to the face.
  PK_local_check_t result_local_check;
  PK_FACE_attach_surf_fitting(face1, PK_LOGICAL_true, &result_local_check);
  PK_FACE_attach_surf_fitting(face2, PK_LOGICAL_true, &result_local_check);







  cout << "creating block : DONE !  " << endl;

}

//------------------------------------------------------------------------

void ParasolidDataBase::createBlock(){
  cout << "creating block... ";
  PK_AXIS2_sf_t basis_set;
  PK_BODY_t primitive;
  double x=1.;
  double y=2.;
  double z=1.;
  PK_ERROR_code_t err=PK_BODY_create_solid_block(x,y,z, NULL, &primitive );
  if (err==PK_ERROR_no_errors) cout << " done." << endl;
  else cout << "err=" << err << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::createSphere(){
  cout << "creating sphere... ";
  PK_AXIS2_sf_t basis_set;
  PK_BODY_t primitive;
  double r=1.;
  PK_ERROR_code_t err=PK_BODY_create_solid_sphere(r, NULL, &primitive );
  if (err==PK_ERROR_no_errors) cout << " done." << endl;
  else cout << "err=" << err << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::createCone(){
  cout << "creating cone... ";
  PK_AXIS2_sf_t basis_set;
  PK_BODY_t primitive;
  double r=1.;
  double h=2.;
  double semiangle = M_PI/6.;
  PK_ERROR_code_t err=PK_BODY_create_solid_cone(r,h,semiangle, NULL, &primitive );
  if (err==PK_ERROR_no_errors) cout << " done." << endl;
  else cout << "err=" << err << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::createTorus(){
  cout << "creating torus... ";
  PK_AXIS2_sf_t basis_set;
  PK_BODY_t primitive;
  double rmin=1.;
  double rmax=2.;
  PK_ERROR_code_t err=PK_BODY_create_solid_torus(rmax,rmin, NULL, &primitive );
  if (err==PK_ERROR_no_errors) cout << " done." << endl;
  else cout << "err=" << err << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::createCylinder(){
  cout << "creating cylinder... ";
  PK_AXIS2_sf_t basis_set;
  PK_BODY_t primitive;
  basis_set.location.coord[0] = 0;
  basis_set.location.coord[1] = 0;
  basis_set.location.coord[2] = 0;
  basis_set.axis.coord[0] = 0;
  basis_set.axis.coord[1] = 1;
  basis_set.axis.coord[2] = 0;
  basis_set.ref_direction.coord[0] = 1;
  basis_set.ref_direction.coord[1] = 0;
  basis_set.ref_direction.coord[2] = 0;
  double radius = 1.;
  double L=1.;
  PK_ERROR_code_t err=PK_BODY_create_solid_cyl( radius, L, &basis_set, &primitive );
  if (err==PK_ERROR_no_errors) cout << " done." << endl;
  else cout << "err=" << err << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::transmit(const string &key){
  int n_parts = 0;
  //  PK_PART_t *parts = NULL;		
  PK_SESSION_ask_parts( &n_parts, &parts );
  cout << "TRANSMIT: n_parts= " << n_parts << endl;

  PK_PART_transmit_o_t transmit_opts;
  PK_PART_transmit_o_m( transmit_opts );
  transmit_opts.transmit_format = PK_transmit_format_text_c;

  err = PK_PART_transmit( n_parts, parts, key.c_str(), &transmit_opts );
  if (err==PK_ERROR_no_errors) cout << "transmitted :)" << endl;
  else
    cout << "transmit errors :(   " << err << endl;
}

//------------------------------------------------------------------------

void ParasolidDataBase::erase_all_parts(){
  int n_parts = 0;
  //PK_PART_t *parts = NULL;		
  PK_SESSION_ask_parts( &n_parts, &parts );
  //  cout << "There are " << n_parts << " parts loaded" << endl;
  //  cout << "deleting..." << endl;
  PK_ENTITY_delete(n_parts, parts);  
  if(n_parts > 0)
    PK_MEMORY_free(parts);
  PK_SESSION_ask_parts( &n_parts, &parts );
  //  cout << "After deletion, there are " << n_parts << " parts loaded" << endl;
}

//------------------------------------------------------------------------

double ParasolidDataBase::get_parasolid_session_precision()const{
  double tol;
  PK_SESSION_ask_precision(&tol);
  return tol;
}

//------------------------------------------------------------------------

