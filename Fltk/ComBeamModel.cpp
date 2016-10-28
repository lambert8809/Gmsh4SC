#include "ComBeamModel.h"
#include "contextWindow.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include <limits>
#include <cmath>
#include <vector>
#include <stdlib.h>


void reg_box_beam(double w, double h, double t1, double t2, \
		  double t3, double t4, double matid, std::string geofile){
  std::ofstream writegeo;
  double lc = t1/5;
  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "\n\n";
  writegeo << "//area " << w*t1+w*t3+(h-t1-t3)*t2+(h-t1-t3)*t4 << "\n"; 
  writegeo << "// Create beam section \n";
  writegeo << "Point(1) = {" << -w / 2 << ", " <<  h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(2) = {" << -w / 2 << ", " << -h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(3) = {" <<  w / 2 << ", " << -h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(4) = {" <<  w / 2 << ", " <<  h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(5) = {" << -(w-2*t2)/2 << ", " << (h-2*t1)/2 << ", 0, "<<lc<< "};\n";
  writegeo << "Point(6) = {" << -(w-2*t2)/2 << ", " <<-(h-2*t3)/2 << ", 0, "<<lc<< "};\n";
  writegeo << "Point(7) = {" <<  (w-2*t4)/2 << ", " <<-(h-2*t3)/2 << ", 0, "<<lc<< "};\n";
  writegeo << "Point(8) = {" <<  (w-2*t4)/2 << ", " << (h-2*t1)/2 << ", 0, "<<lc<< "};\n";
  writegeo << "Line(1) = { 1, 2 }; \n";
  writegeo << "Line(2) = { 2, 3 }; \n";
  writegeo << "Line(3) = { 3, 4 }; \n";
  writegeo << "Line(4) = { 4, 1 }; \n";
  writegeo << "Line(5) = { 5, 6 }; \n";
  writegeo << "Line(6) = { 6, 7 }; \n";
  writegeo << "Line(7) = { 7, 8 }; \n";
  writegeo << "Line(8) = { 8, 5 }; \n";
  writegeo << "Line Loop(9) = {4, 1, 2, 3}; \n";
  writegeo << "Line Loop(10) = {8, 5, 6, 7}; \n";
  writegeo << "Plane Surface(11) = {9, 10}; \n";
  writegeo << "Physical Surface(" << matid << ") = {11}; \n";
  writegeo.close();
}

void reg_I_beam(double h, double b1, double b2, double t1, double t2, double t3, double matid, std::string geofile){
  std::ofstream writegeo;
  double lc = t3/4;
  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "\n\n";
  writegeo << "//area " << b1*t1+b2*t2+(h-t1-t2)*t3 << "\n"; 
  writegeo << "// Create beam section \n";
  writegeo << "Point(1) = {" << -b2/2 << ", " <<  h/2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(2) = {" << -b2/2 << ", " <<  h/2-t2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(3) = {" << -t3/2 << ", " <<  h/2-t2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(4) = {" << -t3/2 << ", " << -(h/2-t1) << ", 0, "<< lc << "};\n";
  writegeo << "Point(5) = {" << -b1/2 << ", " << -(h/2-t1) << ", 0, "<<lc<< "};\n";
  writegeo << "Point(6) = {" << -b1/2  << ", " << -h/2 << ", 0, "<<lc<< "};\n";
  writegeo << "Point(7) = {" <<  b1/2  << ", " << -h/2 << ", 0, "<<lc<< "};\n";
  writegeo << "Point(8) = {" <<  b1/2 << ", " << -(h/2-t1) << ", 0, "<<lc<< "};\n";
  writegeo << "Point(9) = {" <<  t3/2 << ", " << -(h/2-t1) << ", 0, "<< lc << "};\n";
  writegeo << "Point(10) = {" <<  t3/2 << ", " <<  h/2-t2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(11) = {" <<  b2/2 << ", " <<  h/2-t2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(12) = {" <<  b2/2 << ", " <<  h/2 << ", 0, "<< lc << "};\n";
  writegeo << "Line(1) = { 1, 2 }; \n";
  writegeo << "Line(2) = { 2, 3 }; \n";
  writegeo << "Line(3) = { 3, 4 }; \n";
  writegeo << "Line(4) = { 4, 5 }; \n";
  writegeo << "Line(5) = { 5, 6 }; \n";
  writegeo << "Line(6) = { 6, 7 }; \n";
  writegeo << "Line(7) = { 7, 8 }; \n";
  writegeo << "Line(8) = { 8, 9 }; \n";
  writegeo << "Line(9) = { 9, 10 }; \n";
  writegeo << "Line(10) = { 10, 11 }; \n";
  writegeo << "Line(11) = { 11, 12 }; \n";
  writegeo << "Line(12) = { 12, 1 }; \n";
  writegeo << "Line Loop(13) = {12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; \n";
  writegeo << "Plane Surface(14) = {13}; \n";
  writegeo << "Physical Surface(" << matid << ") = {14}; \n";
  writegeo.close();
}

void reg_rec_beam(double w, double h, double matid, std::string geofile){
  std::ofstream writegeo;
  double lc = ((w < h)? w : h)/16;
  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "\n\n";
  writegeo << "// Create beam section \n";
  writegeo << "Point(1) = {" << -w / 2 << ", " <<  h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(2) = {" << -w / 2 << ", " << -h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(3) = {" <<  w / 2 << ", " << -h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Point(4) = {" <<  w / 2 << ", " <<  h / 2 << ", 0, "<< lc << "};\n";
  writegeo << "Line(1) = { 1, 2 }; \n";
  writegeo << "Line(2) = { 2, 3 }; \n";
  writegeo << "Line(3) = { 3, 4 }; \n";
  writegeo << "Line(4) = { 4, 1 }; \n";
  writegeo << "Line Loop(5) = {4, 1, 2, 3}; \n";
  writegeo << "Plane Surface(6) = {5}; \n";
  writegeo << "Physical Surface(" << matid << ") = {6}; \n";
  writegeo.close();
}



void reg_cir_beam(double r, double matid, std::string geofile){
  std::ofstream writegeo;
  double lc = r/10;
  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "\n\n";
  writegeo << "//area " << r*r*3.1415926 << "\n"; 
  writegeo << "// Create beam section \n";
  writegeo << "Point(1) = {" <<  0 << ", " <<  0 << ", 0, "<< lc << "};\n";
  writegeo << "Point(2) = {" << -r << ", " <<  0 << ", 0, "<< lc << "};\n";
  writegeo << "Point(3) = {" <<  0 << ", " << -r << ", 0, "<< lc << "};\n";
  writegeo << "Point(4) = {" <<  r << ", " <<  0 << ", 0, "<< lc << "};\n";
  writegeo << "Point(5) = {" <<  0 << ", " <<  r << ", 0, "<<lc<< "};\n";
  writegeo << "Circle(1) = {2, 1, 3 }; \n";
  writegeo << "Circle(2) = {3, 1, 4 }; \n";
  writegeo << "Circle(3) = {4, 1, 5 }; \n";
  writegeo << "Circle(4) = {5, 1, 2 }; \n";
  writegeo << "Line Loop(5) = {4, 1, 2, 3}; \n";
  writegeo << "Plane Surface(6) = {5}; \n";
  writegeo << "Physical Surface(" << matid << ") = {6}; \n";
  writegeo.close();

}

void reg_pipe_beam(double r, double t, double matid, std::string geofile){
  std::ofstream writegeo;
  double lc = t/4;
  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "\n\n";
  writegeo << "//area " << r*r*3.1415926-(r-t)*(r-t)*3.1415926 << "\n"; 
  writegeo << "//Create beam section \n";
  writegeo << "Point(1) = {" <<  0 << ", " <<  0 << ", 0, "<< lc << "};\n";
  writegeo << "Point(2) = {" << -r << ", " <<  0 << ", 0, "<< lc << "};\n";
  writegeo << "Point(3) = {" <<  0 << ", " << -r << ", 0, "<< lc << "};\n";
  writegeo << "Point(4) = {" <<  r << ", " <<  0 << ", 0, "<< lc << "};\n";
  writegeo << "Point(5) = {" <<  0 << ", " <<  r << ", 0, "<<lc<< "};\n";
  writegeo << "Point(6) = {" <<  -r+t << ", " <<  0 << ", 0, "<<lc<< "};\n";
  writegeo << "Point(7) = {" <<  0 << ", " <<  -r+t << ", 0, "<<lc<< "};\n";
  writegeo << "Point(8) = {" <<  r-t << ", " << 0 << ", 0, "<<lc<< "};\n";
  writegeo << "Point(9) = {" <<  0 << ", " <<  r-t << ", 0, "<<lc<< "};\n";
  writegeo << "Circle(1) = {2, 1, 3 }; \n";
  writegeo << "Circle(2) = {3, 1, 4 }; \n";
  writegeo << "Circle(3) = {4, 1, 5 }; \n";
  writegeo << "Circle(4) = {5, 1, 2 }; \n";
  writegeo << "Circle(5) = {6, 1, 7 }; \n";
  writegeo << "Circle(6) = {7, 1, 8 }; \n";
  writegeo << "Circle(7) = {8, 1, 9 }; \n";
  writegeo << "Circle(8) = {9, 1, 6 }; \n";
  writegeo << "Line Loop(9) = {4, 1, 2, 3}; \n";
  writegeo << "Line Loop(10) = {8, 5, 6, 7}; \n";
  writegeo << "Plane Surface(11) = {9, 10}; \n";
  writegeo << "Physical Surface(" << matid << ") = {11}; \n";
  writegeo.close();

}


std::string convert2(int in){
  std::stringstream convert1;
  convert1 << in;
  std::string index;
  convert1 >> index;
  return index;
}

void comp_rec_beam(double w, std::string geofile, int cout2){
  std::ofstream writegeo;
  double lc = w/8;
  std::string t4file = geofile + ".t4";
  int lam_index = cout2;  
  std::stringstream convert;
  convert << lam_index;
  std::string index;
  convert >> index;    
  std::string name = "Laminate(" + index + ") ";
  std::string layer_id = "layerID_" + name;
  double length;
  int numlayrs;
  std::ifstream is(t4file.c_str());
  std::string readout;
  std::string temp;
  int flags1 = 0;
  std::string endflags = "//" + name;
  double node;
  int layerID;
  std::vector<double> nodes;
  nodes.push_back(0);
  std::vector<int> layerIDs;
  std::vector<std::string> nlayer2;
  std::string testss;
  while (getline(is, readout)){
    if (readout.find(endflags) != std::string::npos) break;
    if (flags1 == 2) {
      nlayer2.push_back(readout);
      testss = readout;
    }
    
    if (readout.find(layer_id) != std::string::npos) flags1 = 2;
    
    if (flags1 == 1){
      std::istringstream first(readout);
      first >> node >> layerID;
      nodes.push_back(node);
      layerIDs.push_back(layerID);
    }    
    if (readout.find(name) != std::string::npos && readout.find("layerID") == std::string::npos\
	&& readout.find("//") == std::string::npos){
      std::istringstream first(readout);
      first >> temp >> length >> numlayrs;
      flags1 = 1;
    }
  }
  is.close();

  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "\n\n";
  writegeo << "// Create beam section \n";
  writegeo << "//" << temp << " " << length << " " << name << " " << numlayrs <<"\n";
  // create nodes
  for (int i = 0; i < nodes.size(); i++)
    writegeo << "Point(" << i+1 << ") = {" << -w/2 << ", " << -length/2 + nodes[i] << ", 0, "<< lc << "};\n";
  for (int i = nodes.size(); i < 2*nodes.size(); i++)
    writegeo << "Point(" << i+1 << ") = {" <<  w/2 << ", " << -length/2 + nodes[i-nodes.size()] << ", 0, "<< lc << "};\n";
  //create lines
  writegeo << "Line(1) = { 1, "<< nodes.size()+1 << " };\n";
  for (int i = 1; i < nodes.size(); i++){
    writegeo << "Line(" << 2+(i-1)*3 << ") = { " << nodes.size()+i << ", " << nodes.size()+i+1 << " };\n";
    writegeo << "Line(" << 3+(i-1)*3 << ") = { " << nodes.size()+i+1 << ", " << i+1 << " };\n";
    writegeo << "Line(" << 4+(i-1)*3 << ") = { " << i+1 <<", " << i << " };\n";
  }
  // create line_loops
  int loop_id = 5 + (nodes.size()-2)*3;
  writegeo << "Line Loop(" << loop_id << ") = {1, 2, 3, 4}; \n";
  for (int i = 1; i < nodes.size()-1; i++)
    writegeo << "Line Loop(" << loop_id+i << ") = {" << -(3+(i-1)*3) << ", " << 5+(i-1)*3 << ", " << 6+(i-1)*3 << ", " << 7+(i-1)*3 << "}; \n";
  int Plane_id = loop_id + nodes.size();
  for (int i = 0; i < nodes.size()-1; i++)
    writegeo << "Plane Surface(" << Plane_id+i << ") = {" << loop_id+i << "};\n";
  //create Physical plane

  std::string phys_s;
  for (int i = 0; i < nlayer2.size(); i++){
    phys_s = "Physical Surface(" + convert2(i+1) + ") = {";
    for (int j = 0; j < layerIDs.size(); j++){
      if (i+1 == layerIDs[j]) {
	phys_s = phys_s + convert2(Plane_id+j) + ", ";
      }
    }
    writegeo << phys_s.substr(0, phys_s.length()-2) << "};\n";
  }

  // create structuted mesh
  writegeo << "\n";
  for (int i = 0; i < nodes.size()-1; i++)
    writegeo << "Transfinite Surface {" << Plane_id + i << "}; \n";
    
  
  
  // pass lay-id information
  writegeo << "// nlayers " << nlayer2.size() << "\n";
  for (int i = 0; i < nlayer2.size(); i++)
    writegeo << "// " << nlayer2[i] << "\n";
  writegeo << "// layers_end\n";
  writegeo.close();

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create laminate I beam section
//
//
////////////////////////////////////////////////
// generate geomoetry for bottom and up walls 
int lam(double nodes[][2], int n_1st, int nlayers, double inter_info[], int inter_n, \
	std::string geofile, std::vector<std::vector<int> > &v, int walls[], int index, \
	int nid, std::vector<int> &il, std::vector<std::string> &suf){
  int num_n = 2*(nlayers+1);
  double lo_n[num_n][2];
  //int index = 1;
  std::vector<int> line_id;
  std::ofstream wgeo;
  wgeo.open(geofile.c_str(),std::ofstream::app);
  for (int i = 0; i < num_n; i++){
    lo_n[i][0] = nodes[n_1st+i][0];
    lo_n[i][1] = nodes[n_1st+i][1];
    //std::cout << lo_n[i][0] << " " << lo_n[i][1] << std::endl;
  }
  line_id.push_back(index);
  wgeo << "Line(" << index++ << ") = { " << n_1st+1+nlayers+1 << ", " << inter_info[0] << " };\n";
  
  for (int i = 0; i < inter_n-1;i++){
    line_id.push_back(index);
    il.push_back(index);
    wgeo << "Line(" << index++ << ") = { " << inter_info[i] << ", " << inter_info[i+1] << " };\n";
    
  }
  line_id.push_back(index);
  wgeo << "Line(" << index << ") = { " << inter_info[inter_n-1] << ", " << n_1st+1 << " };\n";
  
  for (int i = 0; i < nlayers; i++){
    wgeo << "Line(" << index+3*i+1 << ") = { " << n_1st+1+i << ", " << n_1st+1+i+1 << " };\n";
    line_id.push_back(index+3*i+1);
    wgeo << "Line(" << index+3*i+2 << ") = { " << n_1st+1+i+1 << ", " << n_1st+1+i+1+nlayers+1 << " };\n";
    line_id.push_back(index+3*i+2);
    wgeo << "Line(" << index+3*i+3 << ") = { " << n_1st+1+i+1+nlayers+1 << ", " << n_1st+1+i+1+nlayers \
	 << " };\n";
    line_id.push_back(index+3*i+3);    
  }
  
  //Line loop
  int neg;
  index += 3*nlayers+1; 
  for (int i = 0; i < nlayers; i++){
    if (i == 0){
      wgeo << "Line Loop(" << index+i << ") = {";
      for (int j = 0; j < 2+inter_n-1; j++)
	wgeo << line_id[j] << ", ";
      wgeo << line_id[inter_n+1] << ", " << line_id[inter_n+2] << ", " << line_id[inter_n+3] <<" };\n";
      neg = inter_n+2;
    }
    else {
      wgeo << "Line Loop(" << index+i << ") = {" << -line_id[neg] << ", " << line_id[neg+2] << ", " << \
	line_id[neg+3] << ", " << line_id[neg+4] << " };\n";
      neg+= 3;
    }
  }
  // Plane Surface
  std::string mesh;
  for (int i = 0; i < nlayers; i++){
    wgeo << "Plane Surface(" << index+nlayers+i << ") = {" << index+i << "};\n";
    if (i==0)
      mesh = "Transfinite Surface {" + convert2(index+nlayers+i) +"} = {"+ convert2(n_1st+1)+ \
	"," + convert2(n_1st+2) + "," + convert2(n_1st+1+nlayers+1+1) +\
	"," + convert2(n_1st+1+nlayers+1) + "};";
    else
      mesh = "Transfinite Surface {" + convert2(index+nlayers+i) + "};";
      suf.push_back(mesh);
  }

  index+=nlayers;
  //create Physical plane
  std::string phys_s;
  for (int i = 0; i < v.size(); i++){
    phys_s = "Physical Surface(" + convert2(v[i][0]) + ") = {";
    for (int j = 0; j < nlayers; j++){
      if (i+1 == walls[j]-nid) {
	phys_s = phys_s + convert2(index+j) + ", ";
      }
    }
    wgeo << phys_s.substr(0, phys_s.length()-2) << "};\n";
    }
  
  wgeo.close();
  index+=nlayers;
  return index;
}



/////////////////////////////////////////
// generate geomoetry for middle walls 
void m_lam(std::vector<int> &inter_l, std::string geofile, double interB[], double interU[], int nlayers,\
	   int index, std::vector<std::vector<int> > &v, int walls[], int nid, std::vector<std::string> &suf){
  std::ofstream wgeo;
  wgeo.open(geofile.c_str(),std::ofstream::app);
  //line
  for (int i = 0; i < nlayers+1; i++){
    wgeo << "Line(" << index++ << ") = { " << interU[i] << ", " << interB[nlayers-i] << " };\n";
  }
  // line loop
  for (int i = 0; i < nlayers; i++)
    wgeo << "Line Loop(" << index+i << ") = {" << index-nlayers-1+i << ", " << -inter_l[nlayers-1-i] \
	 << ", " << -(index-nlayers+i) << ", " << -inter_l[nlayers+i] << " };\n";
  // Plane Surface
  std::string mesh;
  for (int i = 0; i < nlayers; i++){
    wgeo << "Plane Surface(" << index+nlayers+i << ") = {" << index+i << "};\n";
    mesh = "Transfinite Surface {" + convert2(index+nlayers+i) + "};";
    suf.push_back(mesh);
  }

  index+=nlayers;
  //create Physical plane
  std::string phys_s;
  for (int i = 0; i < v.size(); i++){
    phys_s = "Physical Surface(" + convert2(v[i][0]) + ") = {";
    for (int j = 0; j < nlayers; j++){
      if (i+1 == walls[j]-nid) {
	phys_s = phys_s + convert2(index+j) + ", ";
      }
    }
    wgeo << phys_s.substr(0, phys_s.length()-2) << "};\n";
    }


  // create structuted mesh
  wgeo << "\n";
  for (int i = 0; i < suf.size(); i++)
    wgeo << suf[i] << "\n";
  
  wgeo.close();

}



/////////////////////////
// regenerate layer_id 
void layerIDS(std::vector<std::vector<int> > &bot, std::vector<std::vector<int> > &up, \
	      std::vector<std::vector<int> > &mid, std::string geofile){
  std::vector<std::vector<int> > newIDs;
  std::vector<int> final_id;
  std::vector<int> wall_id;
  int total_IDs = bot.size();
  int flags=0;

  for (int i = 0; i < bot.size(); i++){
    newIDs.push_back(bot[i]);
    final_id.push_back(bot[i][0]);
    wall_id.push_back(1);
  }

  for (int i = 0; i < up.size(); i++){
    wall_id.push_back(2);
    for (int j = 0; j < newIDs.size(); j++){
      if (up[i][1] == newIDs[j][1] && up[i][2] == newIDs[j][2]){
	final_id.push_back(newIDs[i][0]);
	break;
      }
      if (j == newIDs.size()-1){
	total_IDs+=1;
	up[i][0]= total_IDs;
	newIDs.push_back(up[i]);
	final_id.push_back(total_IDs);
	break;
      }      
    }    
  }

   for (int i = 0; i < mid.size(); i++){
     wall_id.push_back(3);
    for (int j = 0; j < newIDs.size(); j++){
      if (mid[i][1] == newIDs[j][1] && mid[i][2] == newIDs[j][2]){
	final_id.push_back(newIDs[i][0]);
	break;
      }
      if (j == newIDs.size()-1){
	total_IDs+=1;
	mid[i][0]= total_IDs;
	newIDs.push_back(mid[i]);
	final_id.push_back(total_IDs);
	break;
      }  
    }    
  }

   
  std::ofstream wgeo;
  wgeo.open(geofile.c_str(),std::ofstream::app);
  wgeo << "// nlayers " << newIDs.size() << "\n";
  for (int i = 0; i < newIDs.size(); i++)
    wgeo << "// " << newIDs[i][0] << " " << newIDs[i][1] << " " << newIDs[i][2] <<  "\n";
  wgeo << "// layers_end\n\n";

  wgeo << "// Information for element coordinates\n";
  for (int i = 0; i < final_id.size(); i++)
    wgeo << "//EC " << final_id[i] << " " << wall_id[i] << "\n";
  wgeo << "//End infor\n";
    
  wgeo.close();

}

void comp_I_beam(double h, double b1, double b2, std::string geofile){
  std::ofstream writegeo;
  passinfo Ib;
  double layer_b = Ibeam_para[0], layer_u = Ibeam_para[2], layer_m = Ibeam_para[4];
  int n_layer_b = int(Ibeam_para[1]), n_layer_u = int(Ibeam_para[3]), n_layer_m = int(Ibeam_para[5]);
  double lc = layer_m/n_layer_m;
  int up_edge[n_layer_u];
  int mid_edge[n_layer_m];
  int bot_edge[n_layer_b];
  std::vector<std::vector<int> > up_ID;
  std::vector<std::vector<int> > mid_ID;
  std::vector<std::vector<int> > bot_ID;
  std::string filename = geofile + ".t4";;
  std::ifstream data(filename.c_str());
  std::string readout;
  int flagsI=0,count=0;
  double temp=0;
  int add_ID=0;
  std::vector<std::string> surface;
   while (getline(data,readout)){
    // Prof. Yu, read data for bottom_edge
    if (readout.find("//Laminate(1)") != std::string::npos) flagsI = 0;
    if (flagsI == 4) {
      std::stringstream s(readout);
      int i1, i2, i3;
      if (s >> i1 >> i2 >> i3){
	std::vector<int> ids;
	ids.push_back(i1);
	ids.push_back(i2);
	ids.push_back(i3);
	bot_ID.push_back(ids);
      }
    }
    if (readout.find("layerID_Bottom") != std::string::npos) {flagsI = 4; count = 0;}
    if (flagsI == 1){
      std::istringstream first(readout);
      first >> temp >> bot_edge[count];    
      count++;
    }
    if (readout.find("Laminate(1)") != std::string::npos && readout.find("layerID") == std::string::npos \
	&& readout.find("//") == std::string::npos)
      flagsI = 1;
    
    // Prof. Yu, read data for up_edge
    if (readout.find("//Laminate(2)") != std::string::npos) flagsI = 0;
    if (flagsI == 5){
      std::stringstream s(readout);
      int i1, i2, i3;
      if (s >> i1 >> i2 >> i3){
	std::vector<int> ids;
	ids.push_back(i1+add_ID);
	ids.push_back(i2);
	ids.push_back(i3);
	up_ID.push_back(ids);
      }
    }
    if (readout.find("layerID_Up") != std::string::npos) {flagsI = 5; count = 0;}
    if (flagsI == 2){
      std::istringstream first(readout);
      first >> temp >> up_edge[count];
      up_edge[count]+=add_ID;
      count++;
    }
    if (readout.find("Laminate(2)") != std::string::npos && readout.find("layerID") == std::string::npos \
	&& readout.find("//") == std::string::npos){
      flagsI = 2;
      add_ID += bot_ID.size();
    }
    //Prof. Yu, read data for middle_edge
    if (readout.find("//Laminate(3)") != std::string::npos) flagsI = 0;
    if (flagsI == 6){
      std::stringstream s(readout);
      int i1, i2, i3;
      if (s >> i1 >> i2 >> i3){
	std::vector<int> ids;
	ids.push_back(i1+add_ID);
	ids.push_back(i2);
	ids.push_back(i3);
	mid_ID.push_back(ids);
      }
    }
    if (readout.find("layerID_middle") != std::string::npos) {flagsI = 6; count = 0;}
    if (flagsI == 3){
      std::istringstream first(readout);
      first >> temp >> mid_edge[count];
      mid_edge[count]+=add_ID;
      count++;
    }
    if (readout.find("Laminate(3)") != std::string::npos && readout.find("layerID") == std::string::npos \
	&& readout.find("//") == std::string::npos){
      flagsI = 3;
      add_ID += up_ID.size(); 
    } 
  }
  data.close();
  //for (int i = 0; i < 4; i++)
  //std::cout << bot_edge[i] << " " << up_edge[i] << " " << mid_edge[i] << std::endl;

  
  // Generate all nodes
  int nnodes = 2*(n_layer_b+1)+2*(n_layer_u+1)+2*(n_layer_m+1);
  double nodes[nnodes][2];
  double delt_t1 = layer_b/n_layer_b;
  double delt_t2 = layer_u/n_layer_u;
  double delt_t3 = layer_m/n_layer_m;
  double inter_bm[n_layer_m+1];
  double inter_um[n_layer_m+1];
  int temp_id;
  // nodes in bottom wall
  nodes[0][0] = -b1/2;  nodes[0][1] = -h/2+layer_b;
  for (int i = 1; i < n_layer_b+1; i++){
    nodes[i][0]=nodes[0][0];
    nodes[i][1]=nodes[i-1][1]-delt_t1; 
  }
  nodes[n_layer_b][1]=-h/2;
  temp_id=n_layer_b+1;
  for (int i = 0; i < n_layer_b+1; i++){
    nodes[temp_id+i][0]=b1/2;
    nodes[temp_id+i][1]=nodes[i][1];
  }
  temp_id+=n_layer_b+1;
  // nodes in up wall
  nodes[temp_id][0] = b2/2;  nodes[temp_id][1]=h/2-layer_u;
  for (int i = 1; i < n_layer_u+1; i++){
    nodes[temp_id+i][0]=nodes[temp_id][0];
    nodes[temp_id+i][1]=nodes[temp_id+i-1][1]+delt_t2; 
  }
  nodes[temp_id+n_layer_u][1]=h/2;
  temp_id+=n_layer_u+1;
  for (int i = 0; i < n_layer_u+1; i++){
    nodes[temp_id+i][0]=-b2/2;
    nodes[temp_id+i][1]=nodes[temp_id-n_layer_u-1+i][1];
  }
  temp_id+=n_layer_u+1;
  // nodes in middle wal
  nodes[temp_id][0] = -layer_m/2;  nodes[temp_id][1]=h/2-layer_u;
  inter_um[0] = temp_id+1; 
  for (int i = 1; i < n_layer_m+1; i++){
    nodes[temp_id+i][0]=nodes[temp_id+i-1][0]+delt_t3;
    nodes[temp_id+i][1]=h/2-layer_u;
    inter_um[i] = temp_id+i+1;
  }
  nodes[temp_id+n_layer_m][0]=layer_m/2;
  temp_id+=n_layer_m+1;
  for (int i = 0; i < n_layer_m+1; i++){
    nodes[temp_id+i][0]=nodes[temp_id-n_layer_m-1+i][0];
    nodes[temp_id+i][1]=-h/2+layer_b;
    inter_bm[n_layer_m-i] = temp_id+i+1;  
  }
  temp_id+=n_layer_m+1;
  

  
  
  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "//Composites I beam \n";
  writegeo << "//Create beam section \n";
  
  //create nodes
  for (int i = 0; i < nnodes; i++)
    writegeo << "Point(" << i+1 << ") = {" << nodes[i][0] << ", " << nodes[i][1] << ", 0, " << lc << "};\n";
  writegeo.close();

  int ninit_ids=0;
  int index=1;
  int nid=0;
  std::vector<int> inter_line;
  ////////////////////////////////////////////////////////////////////////////////////
  // nodes--nodes coordinates,                      ninit_ids--first node in this lam
  // n_layer_b--number of layers in this lam        inter_bm--interface nodes labels
  // n_layer_m+1--number of nodes in interface      Ioutput--output file name
  // bot_IDs--layer_IDS for bottom wall             bot_edge--layer up in bottom wall
  // index--index for line/line loop/plane surface  nid--previous different layers
  // inter_line--lines in interface
  index = lam(nodes, ninit_ids, n_layer_b, inter_bm, n_layer_m+1, geofile, bot_ID, bot_edge,\
	      index, nid, inter_line, surface);
  ninit_ids=(n_layer_b+1)*2;
  nid=bot_ID.size();
  index = lam(nodes, ninit_ids, n_layer_u, inter_um, n_layer_m+1, geofile, up_ID, up_edge,\
	      index, nid, inter_line, surface);
  nid+=up_ID.size();
  m_lam(inter_line, geofile, inter_bm, inter_um, n_layer_m, index, mid_ID, mid_edge, nid, surface);
  layerIDS(bot_ID, up_ID, mid_ID, geofile);
}

//
// I beam section end
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create laminate box beam section
//
//
int first_wall(int init_n, int num_n, std::vector<int> &Iline, int geoID, std::string geofile,\
	       std::vector<std::vector<int> > &v, int walls[],std::vector<int> &Fl, \
	       std::vector<std::string> &surf, std::vector<int> &meshline);

int LB_wall(int init_n, int num_n, std::vector<int> &Iline, int geoID, std::string geofile,\
	    std::vector<std::vector<int> > &v, int walls[],int nid, std::vector<std::string> &surf,\
	    std::vector<int> &meshline);

int last_wall(int init_n, int num_n, std::vector<int> &Iline, int geoID, std::string geofile,\
	      std::vector<std::vector<int> > &v, int walls[],int nid, std::vector<int> &Fl,\
	      std::vector<std::string> &surf, std::vector<int> &meshline, int intev);

void BlayerIDS(std::vector<std::vector<int> > &up, std::vector<std::vector<int> > &left, \
	      std::vector<std::vector<int> > &bot, std::vector<std::vector<int> > &right, std::string geofile);


void comp_box_beam(double w, double h, std::string geofile){
  std::ofstream writegeo;
  double layer_t1=Bbeam_para[0], layer_t2=Bbeam_para[2], layer_t3=Bbeam_para[4], layer_t4=Bbeam_para[6];
  int nlayers = int(Bbeam_para[1]);
  double lc = layer_t1/nlayers;
  int intev = int(w / lc);
  int up_edge[nlayers];
  int left_edge[nlayers];
  int bot_edge[nlayers];
  int right_edge[nlayers];
  std::vector<std::vector<int> > up_ID;
  std::vector<std::vector<int> > left_ID;
  std::vector<std::vector<int> > bot_ID;
  std::vector<std::vector<int> > right_ID;
  std::string filename = geofile + ".t4";;
  std::ifstream data(filename.c_str());
  std::string readout;
  int num_layer;
  double temp=0;
  int lnum_id  = 0;
  int tempf=0;
  int flagsBox=0;
  int count = 0;
  int add_ID=0;
  while (getline(data,readout)){
    // Prof. Yu, read data for up_edge
    if (readout.find("//Laminate(1)") != std::string::npos) flagsBox = 0;
    if (flagsBox == 5) {
      std::stringstream s(readout);
      int i1, i2, i3;
      if (s >> i1 >> i2 >> i3){
	std::vector<int> ids;
	ids.push_back(i1);
	ids.push_back(i2);
	ids.push_back(i3);
	up_ID.push_back(ids);
      }
    }
    if (readout.find("layerID_Up") != std::string::npos) {flagsBox = 5; count = 0;}
    if (flagsBox == 1){
      std::istringstream first(readout);
      first >> temp >> up_edge[count];    
      count++;
    }
    if (readout.find("Laminate(1)") != std::string::npos && readout.find("layerID") == std::string::npos \
	&& readout.find("//") == std::string::npos)
      flagsBox = 1;

    // Prof. Yu, read data for left_edge
    if (readout.find("//Laminate(2)") != std::string::npos) flagsBox = 0;
    if (flagsBox == 6) {
      std::stringstream s(readout);
      int i1, i2, i3;
      if (s >> i1 >> i2 >> i3){
	std::vector<int> ids;
	ids.push_back(i1+add_ID);
	ids.push_back(i2);
	ids.push_back(i3);
	left_ID.push_back(ids);
      }
    }
    if (readout.find("layerID_Left") != std::string::npos) {flagsBox = 6; count = 0;}
    if (flagsBox == 2){      
      std::istringstream first(readout);
      first >> temp >> left_edge[count];
      left_edge[count]+=add_ID;
      count++;
    }
    if (readout.find("Laminate(2)") != std::string::npos && readout.find("layerID") == std::string::npos \
	&& readout.find("//") == std::string::npos){
      flagsBox = 2;
      add_ID+=up_ID.size();
    }
    
    //Prof. Yu, read data for bottom_edge
    if (readout.find("//Laminate(3)") != std::string::npos) flagsBox = 0;
    if (flagsBox == 7){
      std::stringstream s(readout);
      int i1, i2, i3;
      if (s >> i1 >> i2 >> i3){
	std::vector<int> ids;
	ids.push_back(i1+add_ID);
	ids.push_back(i2);
	ids.push_back(i3);
	bot_ID.push_back(ids);
      }
    }
    if (readout.find("layerID_Bottom") != std::string::npos) {flagsBox = 7; count = 0;}
    if (flagsBox == 3){      
      std::istringstream first(readout);
      first >> temp >> bot_edge[count];
      bot_edge[count]+=add_ID;
      count++;
    }
    if (readout.find("Laminate(3)") != std::string::npos && readout.find("layerID") == std::string::npos \
	&& readout.find("//") == std::string::npos){
      flagsBox = 3;
      add_ID+=left_ID.size();
    }
    
    //Prof. Yu, read data for right_edge 
    if (readout.find("//Laminate(4)") != std::string::npos) break;
    if (flagsBox == 8) {
      std::stringstream s(readout);
      int i1, i2, i3;
      if (s >> i1 >> i2 >> i3){
	std::vector<int> ids;
	ids.push_back(i1+add_ID);
	ids.push_back(i2);
	ids.push_back(i3);
	right_ID.push_back(ids);
      }
    }
    if (readout.find("layerID_Right") != std::string::npos) {flagsBox = 8; count = 0;}
    if (flagsBox == 4){      
      std::istringstream first(readout);
      first >> temp >> right_edge[count];
      right_edge[count]+=add_ID;
      count++;
    }
    if (readout.find("Laminate(4)") != std::string::npos && readout.find("layerID") == std::string::npos \
	&& readout.find("//") == std::string::npos){
      flagsBox = 4;
      add_ID+=bot_ID.size();
    }    
  }
  data.close();
   


  double nodes[(nlayers+1)*4][2];
  int nodesID = 0;
  double delt_x = layer_t4/nlayers;
  double delt_y = layer_t1/nlayers;
  // first line nodes
  for (int i = 0; i < nlayers+1; i++){
    nodes[i][0] = w/2-layer_t4+i*delt_x;
    nodes[i][1] = h/2-layer_t1+i*delt_y;
  }
  // second line nodes
  nodesID+=nlayers+1;
  delt_x = layer_t2/nlayers;
  delt_y = layer_t1/nlayers;
  for (int i = 0; i < nlayers+1; i++){
    nodes[i+nodesID][0] = -w/2+layer_t2-i*delt_x;
    nodes[i+nodesID][1] = h/2-layer_t1+i*delt_y;  
  }
  // third second line nodes
  nodesID+=nlayers+1;
  delt_x = layer_t2/nlayers;
  delt_y = layer_t3/nlayers;
  for (int i = 0; i < nlayers+1; i++){
    nodes[i+nodesID][0] = -w/2+layer_t2-i*delt_x;
    nodes[i+nodesID][1] = -h/2+layer_t3-i*delt_y;  
  }
  // fourth line nodes
  nodesID+=nlayers+1;
  delt_x = layer_t4/nlayers;
  delt_y = layer_t3/nlayers;
  for (int i = 0; i < nlayers+1; i++){
    nodes[i+nodesID][0] =  w/2-layer_t4+i*delt_x;
    nodes[i+nodesID][1] = -h/2+layer_t3-i*delt_y;  
  }
  nodesID+=nlayers+1;
  for (int i = 0; i < (nlayers+1)*4; i++)
    std::cout << nodes[i][0] << " " << nodes[i][1] << std::endl;

  writegeo.open(geofile.c_str(),std::ofstream::app);
  writegeo << "//Composites box beam \n";
  writegeo << "//Create beam section \n";
  //create nodes
  for (int i = 0; i < nodesID; i++)
    writegeo << "Point(" << i+1 << ") = {" << nodes[i][0] << ", " << nodes[i][1] << ", 0, " << lc << "};\n";
  writegeo.close();

  std::vector<int> B_inter_info;
  std::vector<int> first_line;
  std::vector<std::string> surf;
  std::vector<int> meshline;
  int geoID=0;
  int init_n=1;
  int nid=0;
  geoID=first_wall(init_n, nlayers, B_inter_info, geoID, geofile, up_ID, up_edge, first_line,surf,meshline);
  init_n+=nlayers+1;
  nid+=up_ID.size();
  geoID=LB_wall(init_n, nlayers, B_inter_info, geoID, geofile, left_ID, left_edge,nid, surf, meshline);
  init_n+=nlayers+1;
  nid+=left_ID.size();
  geoID=LB_wall(init_n, nlayers, B_inter_info, geoID, geofile, bot_ID, bot_edge,nid,surf, meshline);
  init_n+=nlayers+1;
  nid+=bot_ID.size();
  geoID=last_wall(init_n, nlayers, B_inter_info, geoID, geofile, right_ID, right_edge,nid, first_line,\
		  surf, meshline, intev);
  BlayerIDS(up_ID, left_ID, bot_ID, right_ID, geofile);
  
}


int first_wall(int init_n, int num_n, std::vector<int> &Iline, int geoID, std::string geofile,\
	       std::vector<std::vector<int> > &v, int walls[], std::vector<int> &Fl, \
	       std::vector<std::string> &surf, std::vector<int> &meshline){
  std::ofstream wgeo;
  wgeo.open(geofile.c_str(),std::ofstream::app);
  wgeo << "Line(" << 1 << ") = { " << init_n + num_n+1 << ", " << init_n << " };\n";
  meshline.push_back(1);
  for (int i = 0; i < num_n; i++){
    wgeo << "Line(" << 3*i+2 << ") = { " << init_n+i  << ", " << init_n+1+i << " };\n";
    wgeo << "Line(" << 3*i+3 << ") = { " << init_n+1+i << ", " << init_n+num_n+2+i << " };\n";
    meshline.push_back(3*i+3);
    wgeo << "Line(" << 3*i+4 << ") = { " << init_n + num_n+2+i << ", " << init_n+num_n+1+i << " };\n";
    Iline.push_back(3*i+4);
    Fl.push_back(3*i+2);
  }
  geoID += 3*num_n+1+1;
  wgeo << "Line Loop(" << geoID <<  ") = {" << 1 << ", " << 2 << ", " << 3 << ", " << 4 << " };\n";
  for (int i = 1; i < num_n; i++)
    wgeo << "Line Loop(" << geoID+i <<  ") = {" << -3*i << ", " << 3*i+2 << ", " << 3*i+3\
	 << ", " << 3*i+4 << " };\n";
  geoID+=num_n;
  // Plane Surface
  std::string mesh; 
  for (int i = 0; i < num_n; i++){
    wgeo << "Plane Surface(" << geoID+i << ") = {" << geoID-num_n+i << "};\n";
    mesh = "Transfinite Surface {" + convert2(geoID+i) + "};";
    surf.push_back(mesh);
  }
  
  //create Physical plane
  std::string phys_s;
  for (int i = 0; i < v.size(); i++){
    phys_s = "Physical Surface(" + convert2(v[i][0]) + ") = {";
    for (int j = 0; j < num_n; j++){
      if (i+1 == walls[j]) {
	phys_s = phys_s + convert2(geoID+j) + ", ";
      }
    }
    wgeo << phys_s.substr(0, phys_s.length()-2) << "};\n";
    }
  wgeo.close();
  geoID+=num_n;  
  return geoID;
}


int LB_wall(int init_n, int num_n, std::vector<int> &Iline, int geoID, std::string geofile,\
	    std::vector<std::vector<int> > &v, int walls[],int nid, std::vector<std::string> &surf,\
	    std::vector<int> &meshline){
  std::vector<int> Iline2;
  for (int i = 0; i < Iline.size(); i++)
    Iline2.push_back(Iline[i]);
  Iline.clear();
  std::ofstream wgeo;
  wgeo.open(geofile.c_str(),std::ofstream::app);
  int init_line = geoID;
  wgeo << "Line(" << geoID << ") = { " << init_n + num_n+1 << ", " << init_n << " };\n";
  meshline.push_back(geoID);
  for (int i = 0; i < num_n; i++){
    //wgeo << "Line(" << 3*i+2+geoID << ") = { " << init_n+i  << ", " << init_n+1+i << " };\n";
    wgeo << "Line(" << 2*i+1+geoID << ") = { " << init_n+1+i << ", " << init_n+num_n+2+i << " };\n";
    meshline.push_back(2*i+1+geoID);
    wgeo << "Line(" << 2*i+2+geoID << ") = { " << init_n + num_n+2+i << ", " << init_n+num_n+1+i << " };\n";
    Iline.push_back(2*i+2+geoID);
  }
  geoID += 2*num_n+1;
  wgeo << "Line Loop(" << geoID <<  ") = {" << init_line << ", " << -Iline2[0] << ", "\
       << init_line+1 << ", " << init_line+2 << " };\n";
  for (int i = 1; i < num_n; i++)
    wgeo << "Line Loop(" << geoID+i <<  ") = {" << -(init_line+2*i-1) << ", " << -Iline2[i]\
	 << ", " << init_line+2*i-1+2 << ", " << init_line+2*i-1+3 << " };\n";
  geoID+=num_n;

  // Plane Surface
  std::string mesh; 
  for (int i = 0; i < num_n; i++){
    wgeo << "Plane Surface(" << geoID+i << ") = {" << geoID-num_n+i << "};\n";
    mesh = "Transfinite Surface {" + convert2(geoID+i) + "};";
    surf.push_back(mesh);
  }
  
  //create Physical plane
  std::string phys_s;
  for (int i = 0; i < v.size(); i++){
    phys_s = "Physical Surface(" + convert2(v[i][0]) + ") = {";
    for (int j = 0; j < num_n; j++){
      if (i+1 == walls[j]-nid) {
	phys_s = phys_s + convert2(geoID+j) + ", ";
      }
    }
    wgeo << phys_s.substr(0, phys_s.length()-2) << "};\n";
    }
  wgeo.close();
  geoID+=num_n;  
  return geoID;
}

int last_wall(int init_n, int num_n, std::vector<int> &Iline, int geoID, std::string geofile,\
	      std::vector<std::vector<int> > &v, int walls[],int nid, std::vector<int> &Fl, \
	      std::vector<std::string> &surf, std::vector<int> &meshline, int intev){
  std::ofstream wgeo;
  wgeo.open(geofile.c_str(),std::ofstream::app);
  int init_line = geoID;
  for (int i = 0; i < num_n+1; i++){
    wgeo << "Line(" << geoID+i << ") = { " << init_n+i << ", " <<1+i << " };\n";
    meshline.push_back(geoID+i);
  }
  int Mline = geoID;
  geoID+=num_n+1;
  for (int i = 0; i < num_n; i++){
    wgeo << "Line Loop(" << geoID+i <<  ") = {" << -Fl[i] << ", " << -(Mline+i) << ", " << -Iline[i]\
	 << ", " << Mline+i+1 << " };\n";
  }
  geoID+=num_n;
  // Plane Surface
  std::string mesh; 
  for (int i = 0; i < num_n; i++){
    wgeo << "Plane Surface(" << geoID+i << ") = {" << geoID-num_n+i << "};\n";
    mesh = "Transfinite Surface {" + convert2(geoID+i) + "};";
    surf.push_back(mesh);
  }
  
  //create Physical plane
  std::string phys_s;
  for (int i = 0; i < v.size(); i++){
    phys_s = "Physical Surface(" + convert2(v[i][0]) + ") = {";
    for (int j = 0; j < num_n; j++){
      if (i+1 == walls[j]-nid) {
	phys_s = phys_s + convert2(geoID+j) + ", ";
      }
    }
    wgeo << phys_s.substr(0, phys_s.length()-2) << "};\n";
  }
  // create structuted mesh
  wgeo << "\n";
  wgeo << "Transfinite Line {" << meshline[0]; 
  for (int i = 0; i < meshline.size(); i++)
    wgeo << ", " << meshline[i];
  wgeo << "} = " << intev << " Using Progression 1;\n";
  wgeo << "\n";
  
  for (int i = 0; i < surf.size(); i++)
    wgeo << surf[i] << "\n";

  wgeo.close();
  
  geoID+=num_n;  
  return geoID;
}


/////////////////////////
// regenerate layer_id 
void BlayerIDS(std::vector<std::vector<int> > &up, std::vector<std::vector<int> > &left, \
	      std::vector<std::vector<int> > &bot, std::vector<std::vector<int> > &right, std::string geofile){
  std::vector<std::vector<int> > newIDs;
  std::vector<int> final_id;
  std::vector<int> wall_id;
  int total_IDs = bot.size();
  int flags=0;

  for (int i = 0; i < up.size(); i++){
    newIDs.push_back(up[i]);
    final_id.push_back(up[i][0]);
    wall_id.push_back(1);
    // std::cout << newIDs[i][0] << newIDs[i][1] << newIDs[i][2] << std::endl;
  }

  for (int i = 0; i < left.size(); i++){
    wall_id.push_back(2);
    for (int j = 0; j < newIDs.size(); j++){
      if (left[i][1] == newIDs[j][1] && left[i][2] == newIDs[j][2]){
	final_id.push_back(newIDs[j][0]);
	break;
      }
      if (j == newIDs.size()-1){
	total_IDs+=1;
	left[i][0]= total_IDs;
	newIDs.push_back(left[i]);
	final_id.push_back(total_IDs);
	break;
      }      
    }    
  }

   for (int i = 0; i < bot.size(); i++){
     wall_id.push_back(3);
    for (int j = 0; j < newIDs.size(); j++){
      if (bot[i][1] == newIDs[j][1] && bot[i][2] == newIDs[j][2]){
	final_id.push_back(newIDs[j][0]);
	break;
      }
      if (j == newIDs.size()-1){
	total_IDs+=1;
	bot[i][0]= total_IDs;
	newIDs.push_back(bot[i]);
	final_id.push_back(total_IDs);
	break;
      }  
    }    
  }

   for (int i = 0; i < right.size(); i++){
     wall_id.push_back(4);
    for (int j = 0; j < newIDs.size(); j++){
      if (right[i][1] == newIDs[j][1] && right[i][2] == newIDs[j][2]){
	final_id.push_back(newIDs[j][0]);
	break;
      }
      if (j == newIDs.size()-1){
	total_IDs+=1;
	right[i][0]= total_IDs;
	newIDs.push_back(right[i]);
	final_id.push_back(total_IDs);
	break;
      }  
    }    
   }

   std::ofstream wgeo;
   wgeo.open(geofile.c_str(),std::ofstream::app);
   wgeo << "// nlayers " << newIDs.size() << "\n";
   for (int i = 0; i < newIDs.size(); i++)
     wgeo << "// " << newIDs[i][0] << " " << newIDs[i][1] << " " << newIDs[i][2] <<  "\n";
   wgeo << "// layers_end\n\n";

   wgeo << "// Information for element coordinates\n";
   for (int i = 0; i < final_id.size(); i++)
     wgeo << "//EC " << final_id[i] << " " << wall_id[i] << "\n";
   wgeo << "//End infor\n";
    
   wgeo.close();
    
}
//
// box beam section end
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
