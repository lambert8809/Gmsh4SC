#include <stdio.h>
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#include "string.h"

#include <stdlib.h>

#include <iostream>

#include <vector>

#include "ParasolidDataBase.h"
#include "ParasolidGModelBuilder.h"

#include "callbacks.h"

using namespace std;


int main(int argc, char *argv[]){
  string inputfilename;
  if (argc<=2){
    // WARNING: extension should be xmt_txt on unix, x_t on ntfs stuff ?!?
    cout << "usage: ./testPS filename(without extension)  dim_mesh  mesh_size" << endl;
    return 1;
  }

  inputfilename.assign(argv[1]);
  int dim_mesh = atoi(argv[2]);

  constant_meshsize_data::set_mesh_size((double)(atof(argv[3])));


  // TODO: this needs to be done automatically...
  string schemapath("/home/bernard/devel/gmsh/contrib/Parasolid/interface_parasolid/schema");
  string filepath("/home/bernard/devel/gmsh/contrib/Parasolid/interface_parasolid/");


  // ------------------------------ READING FILE, STORING PK INFO
  ParasolidDataBase db(schemapath);

  // error tags for reading:
  // KO, error 970 (schemas) :
  // KO, error 58 (Key not found)
  

  //  // creating simple bodies and saving to files
  //  db.erase_all_parts();
  //  db.createCylinder();
  //  db.transmit("Cylinder");
  //  db.erase_all_parts();
  //  db.createBlock();
  //  db.transmit("Block");
  //  db.erase_all_parts();
  //  db.createSphere();
  //  db.transmit("Sphere");
  //  db.erase_all_parts();
  //  db.createCone();
  //  db.transmit("Cone");
  //  db.erase_all_parts();
  //  db.createTorus();
  //  db.transmit("Torus");
  //  db.erase_all_parts();
  // return;
  //  //end simple bodies


  db.readFile(filepath,inputfilename.c_str());

  // ------------------------------ CREATING GMODEL
  ParasolidGModelBuilder mb(&db);
  mb.buildGModel();


  // to do a more or less exhaustive test of all entities callbacks before calling gmsh for meshing
  //mb.test();


  // possible to set compound stuff:
  //mb.set_alternative_tag(171,123456);
  //mb.set_alternative_tag(181,123456);


  // possible size fields:
  //mb.setMeshSizeFields();


  // ------------------------------ MESHING
  if (dim_mesh)
    mb.mesh(dim_mesh);


  cout << "main: done :) " << endl;

  return 0;
}












// *********************************************
//             TESTING MESHING  
// *********************************************

// ----------- OK (= no error and mesh looks ok) ---------------
//  db.readFile(filepath,"Work-piece");
//  db.readFile(filepath,"instance_sheet_body");
//  db.readFile(filepath,"instance_prism_tool");
//  db.readFile(filepath,"instance_multi_level");
//  db.readFile(filepath,"instance_h_shape");
//  db.readFile(filepath,"instance_cuboid_tool");
//  db.readFile(filepath,"instance_cuboid_tool2");
//  db.readFile(filepath,"instance_block");
//  db.readFile(filepath,"instance_block_tool");
//  db.readFile(filepath,"3D\ solid-Z-Y\ plane");
//  db.readFile(filepath,"3D\ solid-X-Y\ plane");
//  db.readFile(filepath,"blend3");
//  db.readFile(filepath,"bsurf");
//  db.readFile(filepath,"Cutting-punch");
//  db.readFile(filepath,"Cutting-punch2");
//  db.readFile(filepath,"B2");
//  db.readFile(filepath,"B1");
//  db.readFile(filepath,"Work-piece");
//  db.readFile(filepath,"instance_block_inscribed");
//  db.readFile(filepath,"B3");




// -------------------------------------------------------------
// OK since fin direction in edge_reparamOnFace bug fixed :
// -------------------------------------------------------------
//    IN 2D  IN 2D  IN 2D  IN 2D  IN 2D db.readFile(filepath,"twoplates"); IN 2D  IN 2D  IN 2D  IN 2D 

// -------------------------------------------------------------
// OK since edge/curve direction issue fixed in edge_reparamOnFace :
// -------------------------------------------------------------
//Error   : Unable to recover an edge 5.85167e-11 0.01 && 2.92584e-11 0.01 (28/31)
//Warning : :-( There are 2 intersections in the 1D mesh (curves 30 36)
//Warning : 8-| Gmsh splits those edges and tries again
//Info    : 0 points 0 edges and 0 faces in the initial mesh
//Error   : No tetrahedra in region 18 0
//    db.readFile(filepath,"B4");
//    db.readFile(filepath,"blend1");  // SAUF LE CYLINDER !!!
//    db.readFile(filepath,"blend2");  /// SAUF LE CYLINDER !!!

//Error   : Unable to recover an edge 1.69735 1.20627 && 0.102338 1.20627 (0/16)
//Error   : Unable to recover an edge -0.497351 1.00127 && -0.497351 0.505433 (0/5)
//Error   : Unable to recover an edge -0.497351 1.10627 && -0.497351 -0.393734 (15/15)
//    db.readFile(filepath,"test-sim-Erwan-Combine");
//                          AVEC *size = 0.02;, c'est un peu cossu :)

// -------------------------------------------------------------
// OK since periodic issue fixed :
// -------------------------------------------------------------

//Warning : :-( There are 4 intersections in the 1D mesh (curves 25 32 25 46)
//Warning : 8-| Gmsh splits those edges and tries again
//Jettisoning redundant points.
//Info    : 0 points 0 edges and 0 faces in the initial mesh
//Error   : No tetrahedra in region 21 0
//    db.readFile(filepath,"Hole\ CAD\ model");
//db.readFile(filepath,"RVE4_RVE1_Phase1");








// ----------- KO ---------------


// CURIEUX: PASSE OK, EN 2d/3d, MAIS AFFICHE:
//  Error   : GenericFace::ERROR from FaceXYZFromUV !
//db.readFile(filepath,"RVE4_RVE1_Phase1");// SPHERES !!!!!



//Error   : GenericFace::ERROR from FaceUVFromXYZ ! 
// CRASH LE PC, MEM SWAP AVEC SIZE=0.1, SEGFAULT AVEC 0.125 !!???????
//  db.readFile(filepath,"TRVx_b2");





// BOXON BOXON BOXON !!!!!!!!
//Warning : Treating face 5763
//Warning : :-( There are 2 intersections in the 1D mesh (curves 7019 7030), face 5763
//Warning : 8-| Gmsh splits those edges and tries again
//Error   : GenericFace::ERROR from FaceUVFromXYZ ! 
//
//MVertex (3.70327,-0.287295,1.13844)
//coucou v on dim 1
//   getParameter -> 49.5434
//edge_reparamOnFace:: Debug : reversing parameter, fin_is_positive=no dir=1
//error from PK_FIN_find_surf_parameters : 120
//edge bounds :0 65.978   fin bounds = 0  1     param = 49.5434 param_to_use -48.5434
//edge_reparamOnFace::PK_FIN_find_surf_parameters error = 120 , given parameter coord is out of range  
//GenericEdge::ERROR from EdgeReparamOnFace ! Edge Native id 109373
//reparamOnFace, param (0,0)
//returning true
//
//MVertex (3.71574,-0.314919,1.12607)
//coucou v on dim 0
//coucou 2
//PK_ERROR_not_on_surface
//reparamOnFace, param (13.8284,3.49907e-05)
//returning true
//
//Warning : Treating face 5763
//Warning : :-) Gmsh was able to recover all edges after 7 iterations
//Error   : GenericFace::ERROR from FaceUVFromXYZ ! 
//returning true
//Debug   : Delaunization of the initial mesh done (0 swaps)
//Debug   :      39 points created -- Worst tri radius is 1171.942
//Debug   : Point 10.9748 0.00623589 cannot be inserted because 1
//Debug   : Point 14.7181 0.315803 cannot be inserted because 1
//Debug   : Point 10.9431 0.0053515 cannot be inserted because 1
//Debug   : Point 14.7181 0.320502 cannot be inserted because 1
//Debug   : Point 14.719 0.313278 cannot be inserted because 1
//Debug   : Point 14.6976 0.33995 cannot be inserted because 1
//Debug   : Point 14.7183 0.308583 cannot be inserted because 1
//Debug   : Point 14.7183 0.300861 cannot be inserted because 1
//Debug   : Point 14.4506 0.0114194 cannot be inserted because 1
//Debug   : Point 14.7181 0.321306 cannot be inserted because 1
//Erreur de segmentation
//    db.readFile(filepath,"work_Syusei");












//Warning : GenericEdge::geomType:: unknown type from callback:
//Error   : Unable to recover an edge 0.0475703 -0.0232957 && 0.0475703 -0.0232957 (34/38)
//face bounds u:0.812732 1.5708
//face bounds v:-0.01 1.21514e-13
//uv = 2.13943 -0.952663
//face_XYZFromUV::PK_SURF_eval error = 120 , given uv coords are out of range  
//Error   : GenericFace::ERROR from FaceXYZFromUV ! 
//Delaunizing vertices...
//Warning:  Point 133 is replaced by point 135.
//  Avoid creating a very short edge (len = 0) (< 3.58039e-08).
//  You may try a smaller tolerance (-T) (current is 1e-08)
//  or use the option -M0/1 to avoid such replacement.
//The dihedral angle between them is 4.13353e-05 degree.
//Hint:  You may use -p/# to decrease the dihedral angle  tolerance 0.1 (degree).
//Error   : Self intersecting surface mesh, computing intersections (this could take a while)
//Info    : 0 points 0 edges and 0 faces in the initial mesh
//Error   : No tetrahedra in region 487 0
//Info    : 0 points 0 edges and 0 faces in the initial mesh
//Error   : No tetrahedra in region 488 0
//    db.readFile(filepath,"United131798_part\(131798\)");







//Warning : Treating face 2713
//Error   : GenericEdge::ERROR from EdgeReparamOnFace ! Edge Native id 28259
//Warning : Treating face 2714
//Error   : Unable to recover an edge -1.61873 0.270748 -0.0035 && -1.61873 0.341748 -0.0035 (0/2)
//Error   : GenericEdge::ERROR from EdgeReparamOnFace ! Edge Native id 28190
//Warning : Treating face 2715
//MVertex (-1.30996,0.358578,-0.037)
//coucou v on dim 1
//   getParameter -> -121.67
//edge_reparamOnFace:: Debug : reversing parameter, fin_is_positive=no dir=1
//error from PK_FIN_find_surf_parameters : 120
//edge bounds :-211.939 -31.4011   fin bounds = -90.2689  90.2689     param = -121.67 param_to_use 121.67
//edge_reparamOnFace::PK_FIN_find_surf_parameters error = 120 , given parameter coord is out of range
//Error   : GenericEdge::ERROR from EdgeReparamOnFace ! Edge Native id 28190
//Debug   : Delaunization of the initial mesh done (1 swaps)
//Debug   :      21 points created -- Worst tri radius is 312427908267292.312
//Debug   : Point 0.0203402 -2.2915 cannot be inserted because 1
//Erreur de segmentation
//    db.readFile(filepath,"Imprinted1_part\(255902\)");



//  face parbounds = [0,0.281927] [-0.170298,-0.169998]
//MVertex (-0.621457,0.18,-0.1677)
//coucou v on dim 0
//coucou 2
//PK_ERROR_not_on_surface
//reparamOnFace, param (0.281927,-0.169998)
//returning true
//MVertex (-0.640583,0.0909017,-0.1677)
//coucou v on dim 1
//   getParameter -> 0.135104
//edge_reparamOnFace:: Debug : reversing parameter, fin_is_positive=no dir=1
//error from PK_FIN_find_surf_parameters : 120
//edge bounds :0 0.270208   fin bounds = 0.729791  1     param = 0.135104 param_to_use 1.59469
//edge_reparamOnFace::PK_FIN_find_surf_parameters error = 120 , given parameter coord is out of range  
//GenericEdge::ERROR from EdgeReparamOnFace ! Edge Native id 15392
//Error   : GenericFace::ERROR from FaceUVFromXYZ ! 
//Error   : GenericEdge::ERROR from EdgeReparamOnFace ! Edge Native id 15392
//Erreur de segmentation
//    db.readFile(filepath,"Stator_part\(43\)");




// BOXON TOTAL !!!!!!!!
//db.readFile(filepath,"fmdAllMergedBut2");




//Error   : Unable to recover an edge 0.0547786 0.00493016 && 0.0547786 -0.00493016 (17/34)
//Error   : Unable to recover an edge 0.0147219 -0.00946121 && 0.0175 0 (10/10)
//    db.readFile(filepath,"1.120.15\ B");  //// 2 CYLINDRES !!!!!!!








//Error   : GenericFace::ERROR from FaceXYZFromUV ! 
//(because asking for uv coord out of range ! )
//Error   : Unable to recover an edge 0.0060325 0 && 1.64432e-17 -0.0060325 (0/3)
//Warning : :-( There are 2 intersections in the 1D mesh (curves 120 117)
//Warning : 8-| Gmsh splits those edges and tries again
//    db.readFile(filepath,"Morse\ cone");// CYLINDRE ISSUE








//  Error   : Unable to recover an edge -0.00795619 0.017681 0.084925 && -0.0112517 0.0256372 0.084925 (3/7)
//    db.readFile(filepath,"blend1");  /// CYLINDER !!!
//    db.readFile(filepath,"blend2");  /// CYLINDER !!!


//Warning : :-( There are 2 intersections in the 1D mesh (curves 236 235)
//Warning : 8-| Gmsh splits those edges and tries again
//Error   : Unable to recover an edge -0.025 0.0015 && -0.00833333 0.0015 (0/2)
//Info    : 0 points 0 edges and 0 faces in the initial mesh
//    db.readFile(filepath,"fan");  /// CYLINDER ??????????





// OK in 2D, STILL NEED TO FIND WHY WEIRD 1D POINTS ARE ADDED... !!!???
// in 3D : 
//  Error   : Cannot build pyramids on non manifold faces
//  Error   : Cannot build pyramids on non manifold faces
//    db.readFile(filepath,"twoplates");








// ++++ Error:  The point set is trivial.
// Error   : Surface mesh is wrong, cannot do the 3D mesh
// db.readFile(filepath,"instance_solid_cyl");
//  db.readFile(filepath,"instance_solid_cyl2");

