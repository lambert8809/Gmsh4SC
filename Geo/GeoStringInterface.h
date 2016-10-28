// Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#ifndef _GEO_STRING_INTERFACE_H_
#define _GEO_STRING_INTERFACE_H_

#include <string>
#include <vector>
#include "ListUtils.h"

void coherence(std::string fileName);
void delet(List_T *list, std::string fileName, std::string what);
void add_infile(std::string text, std::string fileName, bool deleted_something=false);
void add_charlength(List_T *list, std::string fileName, std::string lc);
void add_recosurf(List_T *list, std::string fileName);
void add_trsfline(std::vector<int> &l, std::string fileName, std::string type,
                  std::string typearg, std::string pts);
void add_trsfsurf(std::vector<int> &l, std::string fileName, std::string dir);
void add_trsfvol(std::vector<int> &l, std::string fileName);
void add_embedded(std::string what, std::vector<int> &l, std::string fileName);

void add_param(std::string num, std::string e1, std::string e2, std::string e3,
	       std::string g1, std::string g2, std::string g3,
	       std::string v1, std::string v2, std::string v3,
	       std::string rho, std::string ti,
	       std::string alpha1, std::string alpha2,std::string alpha3,std::string ce,
	       std::string name, std::string fileName);
void add_param1(std::string num, std::string e, std::string v,
		std::string rho, std::string ti, std::string alpha, std::string ce,
		std::string name, std::string fileName);
//void add_matname(std::string num, std::string name, std::string fileName);
void add_param2(std::string num, std::string c11, std::string c12, std::string c13, std::string c14, std::string c15, std::string c16,
		std::string c22, std::string c23, std::string c24, std::string c25, std::string c26,
		std::string c33, std::string c34, std::string c35, std::string c36,
		std::string c44, std::string c45, std::string c46,
		std::string c55, std::string c56,
		std::string c66,
		std::string rho, std::string ti,
		std::string alpha1, std::string alpha2,std::string alpha3,
		std::string alpha4, std::string alpha5,std::string alpha6,std::string ce,
		std::string name,std::string fileName);

/* add conductivity function */
void add_conduc1(std::string num, std::string name,
		 std::string rho, std::string ti, std::string ck,
		 std::string fileName);
void add_conduc2(std::string num, std::string name,
		 std::string rho, std::string ti,
		 std::string ck11,std::string ck22,std::string ck33,
		 std::string fileName);
void add_conduc3(std::string num, std::string name,
		 std::string rho, std::string ti,
		 std::string ck11,std::string ck12,std::string ck13,
		 std::string ck22,std::string ck23,std::string ck33,
		 std::string fileName);

void add_Model1(std::string SG2model, std::string volumef, std::string volumeI, std::string mat1, std::string mat2, std::string mat3, std::string fileName); // Prof. Yu, add 2D common SG
void add_Model2(std::string SG3model, std::string volumef, std::string mat1, std::string mat2, std::string fileName); // Prof. Yu, add 3D common SG

void add_flags1(std::string analysis, std::string elem, std::string trans, std::string temp, 
					 std::string fileName);
void add_flags2(std::string analysis, std::string elem, std::string trans, std::string temp,  
				std::string Bmodel, std::string curvatures1, std::string curvatures2, std::string curvatures3, std::string oblique1,
				std::string oblique2, std::string fileName); // Prof. Yu, add beam function
void add_flags3(std::string analysis, std::string elem, std::string trans, std::string temp, 
				std::string Pmodel, std::string curvatures1, std::string curvatures2, std::string fileName); // Prof. Yu, add shell function
void add_flags4(std::string analysis, std::string elem, std::string trans, std::string temp, 
				std::string Pmodel, std::string fileName); // Prof. Yu, add plate function
				
void add_dehomoSolid1(std::string v1, std::string v2, std::string v3, 
	            std::string C11, std::string C12, std::string C13, 
				std::string C21, std::string C22, std::string C23,
				std::string C31, std::string C32, std::string C33,
				std::string e1, std::string e2, std::string e3, std::string e4, std::string e5, std::string e6, std::string fileName);
void add_dehomoBeam1(std::string v1, std::string v2, std::string v3,
	std::string C11, std::string C12, std::string C13,
	std::string C21, std::string C22, std::string C23,
	std::string C31, std::string C32, std::string C33,
	std::string e11, std::string k11, std::string k12, std::string k13, std::string fileName);
void add_dehomoSP1(std::string v1, std::string v2, std::string v3,
	std::string C11, std::string C12, std::string C13,
	std::string C21, std::string C22, std::string C23,
	std::string C31, std::string C32, std::string C33,
	std::string e1, std::string e2, std::string e3, std::string e4, std::string e5, std::string e6, std::string fileName);
void add_periodic_line(List_T *list, std::string filrName);
void add_periodic_surface(List_T *list, std::string fileName);


/*void add_param(std::string par, std::string value, std::string label,
               std::string path, std::string fileName);*/
void add_point(std::string fileName, std::string x, std::string y, std::string z,
               std::string lc);
void add_multline(std::string type, std::vector<int> &p, std::string fileName);
void add_circ(int p1, int p2, int p3, std::string fileName);
void add_ell(int p1, int p2, int p3, int p4, std::string fileName);
void add_field_option(int field_id, std::string option_name, std::string option_value,
                      std::string fileName);
void add_field(int field_id, std::string type_name, std::string fileName);
void delete_field(int field_id, std::string fileName);
void set_background_field(int field_id,std::string fileName);
void add_lineloop(List_T *list, std::string fileName, int *numloop);
void add_surf(std::string type, List_T *list, std::string fileName);
void add_surfloop(List_T *list, std::string fileName, int *numvol);
void add_vol(List_T *list, std::string fileName);
void add_physical(std::string type, List_T *list, std::string fileName, std::string num); // Prof. Yu
void add_compound(std::string type, List_T *list, std::string fileName);
void translate(int add, List_T *list, std::string fileName, std::string what,
               std::string tx, std::string ty, std::string tz);
void rotate(int add, List_T *list, std::string fileName, std::string what,
            std::string ax, std::string ay, std::string az,
            std::string px, std::string py, std::string pz, std::string angle);
void dilate(int add, List_T *list, std::string fileName, std::string what,
            std::string dx, std::string dy, std::string dz, std::string df);
void symmetry(int add, List_T *list, std::string fileName, std::string what,
              std::string sa, std::string sb, std::string sc, std::string sd);
void extrude(List_T *list, std::string fileName, std::string what, std::string tx,
             std::string ty, std::string tz);
void protude(List_T *list, std::string fileName, std::string what,
             std::string ax, std::string ay, std::string az,
             std::string px, std::string py, std::string pz, std::string angle);
void split_edge(int edge_id, List_T *vertices, std::string fileName);

#endif
