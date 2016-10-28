#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <istream>
#include <limits>
#include <cmath>
#include "GModel.h"
#include "CreateFile.h"
#include "GmshDefines.h"
#include "StringUtils.h"
#include "postLam.h"
#include "postswiftcomp.h"


int postswiftcomp(std::string &tfile, std::string &mfile, std::string &pfile){
  std::string mmfile = mfile;
  std::string ppfile = pfile;
  int numnodes = 0;
      int numelems = 0;
      std::string readout;
      //std::string temp = "G:\\00-Purdue_University\\03-Gmsh\\ttest\\postest.geo.t";
      std::ifstream is(tfile.c_str());
      if(is){
      std::string numVertices = "numVertices";
      std::string numElements = "numElements";

      while (getline(is, readout)) {
	std::stringstream iss(readout);
	std::vector<std::string> tokens;
	std::string str;

	// read number of nodes and elements
	if (readout.find(numVertices) != std::string::npos) {
	  while (iss >> str) tokens.push_back(str);
	  std::stringstream convert(tokens[1]);
	  convert >> numnodes;
	}
	else if (readout.find(numElements) != std::string::npos) {
	  while (iss >> str) tokens.push_back(str);
	  std::stringstream convert(tokens[1]);
	  convert >> numelems;
	}
      }
      is.close();}
      
  if (numnodes == 0){
    //std::string geoname = GModel::current()->getFileName();
    //postLam1(geoname);
    if (postLam1(mmfile,ppfile)==1) return 1;

    /* std::ofstream writepos;
    writepos.open(pfile.c_str());
    writepos << "$MeshFormat\n";
    writepos << "2.2 0 8\n";
    writepos << "$EndMeshFormat\n";
    writepos << "$Nodes\n";
  
    // read and generate GEO information from .msh file
    std::ifstream lamfile(mfile.c_str());
    std::string readout;
    int nodes_num;
    int ele_num;
    double length;
    int flags1 = 0;
    double** mesh_nodes;
    int** mesh_elens;
    int k = 0, kk = 0;
  
    while (getline(lamfile,readout)){

      if (flags1 == 1 && readout.find("1") != std::string::npos) flags1 = 2;
      if (flags1 == 3 && readout.find("1") != std::string::npos) flags1 = 4;
    
      if (readout.find("nlayer") != std::string::npos){
	std::stringstream iss(readout);
	std::vector<std::string> tokens;
	std::string str;
	int nlayer;
	while (iss >> str) tokens.push_back(str);
	// std::stringstream convert;
	nlayer = atoi(tokens[5].c_str());
	nodes_num = atoi(tokens[1].c_str());
	ele_num = atoi(tokens[2].c_str());
	//std::cout << nlayer << " " << nodes_num << " " << ele_num << std::endl;
	if (nlayer != 0){
	  mesh_nodes = new double*[2*nodes_num];
	  for (int i = 0; i < 2*nodes_num; ++i)
	    mesh_nodes[i] = new double[4];
	  mesh_elens = new int*[4*ele_num];
	  for (int i = 0; i < 4*ele_num; i++)
	    mesh_elens[i] = new int[9]; 
	  flags1 = 1;
	}       
      }
    
    
      if (flags1 == 2){
	std::stringstream iss(readout);
	std::vector<std::string> tokens;
	std::string str;
	while (iss >> str) tokens.push_back(str);
	mesh_nodes[k][0] = atof(tokens[0].c_str());
	mesh_nodes[k][2] = atof(tokens[1].c_str());
	mesh_nodes[k][1] = 0;
	mesh_nodes[k][3] = 0;
	k = k + 1;
	if (k == nodes_num){ //add length here
	  length = mesh_nodes[nodes_num-1][2]-mesh_nodes[0][2];
	  flags1 = 3;
	  for (int i = 0; i < nodes_num; i++)
	    for (int ii = 0; ii < 4; ii++){
	      if (ii == 1)
		mesh_nodes[i+nodes_num][ii] = mesh_nodes[i][ii]+5*length;
	      else if (ii == 0)
		mesh_nodes[i+nodes_num][ii] = mesh_nodes[i][ii]+nodes_num;
	      else
		mesh_nodes[i+nodes_num][ii] = mesh_nodes[i][ii];
	    }
	}
      }
      

      if (flags1 == 4){
	std::stringstream iss(readout);
	std::vector<std::string> tokens;
	std::string str;
	//std::cout << readout << std::endl;
	while (iss >> str) tokens.push_back(str);
	for (int i = 0; i < 4; i++){
	  mesh_elens[i + 4*kk][0] = 1 + i + 4*kk;
	  mesh_elens[i + 4*kk][1] = 3;
	  mesh_elens[i + 4*kk][2] = 2;
	  mesh_elens[i + 4*kk][3] = atoi(tokens[1].c_str());
	  mesh_elens[i + 4*kk][4] = 10 + atoi(tokens[1].c_str());
	  mesh_elens[i + 4*kk][5] = i + 1 + 4*kk;
	  mesh_elens[i + 4*kk][6] = i + 2 + 4*kk;
	  mesh_elens[i + 4*kk][7] = i + 2 + 4*kk + nodes_num;
	  mesh_elens[i + 4*kk][8] = i + 1 + 4*kk + nodes_num;
	}
	kk = kk + 1;
	if (kk == ele_num) flags1 = 5;			  
      }
    
    }
    lamfile.close();

    // Write GEO information into .msh file(pos)
    writepos << nodes_num *2 << "\n";
    for (int i = 0; i < 2*nodes_num; i++){
      for (int ii = 0; ii < 4; ii++)
	writepos << mesh_nodes[i][ii] << " ";
      writepos << "\n";
    }
    writepos << "$EndNodes\n";
    writepos << "$Elements\n";
    writepos << 4*ele_num << "\n";
    for (int i = 0; i < 4*ele_num; i++){
      for (int ii = 0; ii < 9; ii++)
	writepos << mesh_elens[i][ii] << " ";
      writepos << "\n";
    }
    writepos << "$EndElements\n";

    
    // Finish reading .msh file, read results from .u and .sn file
    // read and regenerate .u data
    int kj = 0;
    
    std::string dispname = mfile + ".u";
    
    std::ifstream dispfile(dispname.c_str());
    std::string newread;
    
    double** dispdata = new double*[2*nodes_num];
    
    for (int i = 0; i < 2*nodes_num; i++)
      dispdata[i] = new double[4];
    
    while (getline(dispfile, newread)){
      std::stringstream iss(newread);
      std::string str;
      std::vector<std::string> tokens;
      writepos << newread << "\n";
      while (iss >> str) tokens.push_back(str);
      dispdata[kj][0] = atof(tokens[0].c_str());
      dispdata[kj][1] = atof(tokens[1].c_str());
      dispdata[kj][2] = atof(tokens[2].c_str());
      dispdata[kj][3] = atof(tokens[3].c_str());
      kj = kj + 1;
      //std::cout << dispdata[k-1][0] << std::endl;
      if (k == nodes_num) break;
    }
    
    dispfile.close();
    
    for (int i = 0; i < nodes_num; i++)
      for (int ii = 0; ii < 4; ii++){
	if (ii == 0) dispdata[i + nodes_num][ii] = dispdata[i][ii] + nodes_num;
	else dispdata[i + nodes_num][ii] = dispdata[i][ii];
      }
     
    writepos << "$NodeData\n";
    writepos << "1\n";
    writepos << "\"U-Magnitude\"\n";
    writepos << "1\n";
    writepos << "0\n";
    writepos << "3\n";
    writepos << "0\n";
    writepos << "1\n";
    writepos << 2*nodes_num << "\n";
    for (int i = 0; i < 2*nodes_num; i++)
      writepos << i+1 << "  " << sqrt(dispdata[i][1] * dispdata[i][1] + dispdata[i][2] * dispdata[i][2] + dispdata[i][3] * dispdata[i][3]) << "\n";
    writepos << "$EndNodeData\n";
    writepos << "$NodeData\n";
    writepos << "1\n";
    writepos << "\"U1\"\n";
    writepos << "1\n";
    writepos << "0\n";
    writepos << "3\n";
    writepos << "0\n";
    writepos << "1\n";
    writepos << 2*nodes_num << "\n";
    for (int i = 0; i < 2*nodes_num; i++)
      writepos << i + 1 << " " << dispdata[i][1] << "\n";
    writepos << "$EndNodeData\n";
    writepos << "$NodeData\n";
    writepos << "1\n";
    writepos << "\"U2\"\n";
    writepos << "1\n";
    writepos << "0\n";
    writepos << "3\n";
    writepos << "0\n";
    writepos << "1\n";
    writepos << 2*nodes_num << "\n";
    for (int i = 0; i < 2*nodes_num; i++)
      writepos << i + 1 << " " << dispdata[i][2] << "\n";
    writepos << "$EndNodeData\n";
    writepos << "$NodeData\n";
    writepos << "1\n";
    writepos << "\"U3\"\n";
    writepos << "1\n";
    writepos << "0\n";
    writepos << "3\n";
    writepos << "0\n";
    writepos << "1\n";
    writepos << 2*nodes_num << "\n";
    for (int i = 0; i < 2*nodes_num; i++)
      writepos << i + 1 << " " << dispdata[i][3] << "\n";
    writepos << "$EndNodeData\n";
    
    // read and regenerate .sn data
    k = 0;
    kk = 0;
    flags1 = 0;
    std::string SSname = mfile + ".sn";
    std::ifstream SSfile(SSname.c_str());
    
    double** SSdata = new double*[4*ele_num];
    int loop[5] = {2, 4, 6, 5, 3};
    std::string plottitle[] = { "E11", "E22", "E33", "E23", "E13", "E12", "S11", "S22", "S33", "S23", "S13", "S12" };
    for (int i = 0; i < 4*ele_num; i++)
      SSdata[i] = new double[6];
    while (getline(SSfile,readout)){
      std::stringstream iss(readout);
      std::vector<std::string> tokens;
      std::string str;
      if (flags1 == 1){
	flags1 = 0;
	k = 0;
      }
      if (k == ele_num) flags1 = 1; 
      if (flags1 == 0){
	while (iss >> str) tokens.push_back(str);
	for (int i = 0; i < 4; i++){
	  SSdata[i + 4*k][0] = i + 1 + 4*k;
	  SSdata[i + 4*k][1] = 4;
	  SSdata[i + 4*k][2] = atof(tokens[loop[i]].c_str());;
	  SSdata[i + 4*k][3] = atof(tokens[loop[i+1]].c_str());
	  SSdata[i + 4*k][4] = SSdata[i + 4*k][3];
	  SSdata[i + 4*k][5] = SSdata[i + 4*k][2];
	}
	k = k + 1;
	if (k == ele_num){
	  writepos << "$ElementNodeData\n";
	  writepos << "1\n";
	  writepos << "\"" << plottitle[kk] << "\"\n";
	  writepos << "1\n";
	  writepos << "0\n";
	  writepos << "3\n";
	  writepos << "0\n";
	  writepos << "1\n";
	  writepos << 4*ele_num << "\n";
	  for (int i = 0; i < 4*ele_num; i++){
	    for (int ii = 0; ii < 6; ii++)
	      writepos << SSdata[i][ii] << " ";
	    writepos << "\n";
	  }
	  writepos << "$EndElementNodeData\n";
	  kk = kk+1;
	}      
      }
      }
      writepos.close();*/
  }


  
  if (numnodes != 0){


      // store data from .u file generated from SwiftComp
      std::string dispfilename = mfile + ".u";
      //std::string dispfile = "G:\\00-Purdue_University\\03-Gmsh\\ttest\\postest.msh.u";
      std::ifstream dis(dispfilename.c_str());
	
      std::string disline;
      // create dynamic 2D array to store displacement data
      double** nodaldis = new double*[numnodes];
      for (int i = 0; i < numnodes; ++i)
		nodaldis[i] = new double[4];
      int j = 0;
      while (getline(dis, disline)) {
	std::stringstream iss(disline);
	std::vector<std::string> tokens;
	std::string str;
	while (iss >> str) tokens.push_back(str);
	nodaldis[j][0] = atof(tokens[0].c_str());
	nodaldis[j][1] = atof(tokens[1].c_str());
	nodaldis[j][2] = atof(tokens[2].c_str());
	nodaldis[j][3] = atof(tokens[3].c_str());
	j = j + 1;
      }
      //std::cin.get();
      dis.close();

      // Prof. Yu, generate displacement results
      std::ofstream writepos;
      writepos.open(pfile.c_str(), std::ofstream::app);
      writepos << "$NodeData\n";
      writepos << "1\n";
      writepos << "\"U-Magnitude\"\n";
      writepos << "1\n";
      writepos << "0\n";
      writepos << "3\n";
      writepos << "0\n";
      writepos << "1\n";
      writepos << numnodes << "\n";
      for (int ind = 0; ind < numnodes; ind++)
	writepos << ind + 1 << " " << sqrt(nodaldis[ind][1] * nodaldis[ind][1] + nodaldis[ind][2] * nodaldis[ind][2] + nodaldis[ind][3] * nodaldis[ind][3]) << "\n";
      writepos << "$EndNodeData\n";
      writepos << "$NodeData\n";
      writepos << "1\n";
      writepos << "\"U1\"\n";
      writepos << "1\n";
      writepos << "0\n";
      writepos << "3\n";
      writepos << "0\n";
      writepos << "1\n";
      writepos << numnodes << "\n";
      for (int ind = 0; ind < numnodes; ind++) writepos << ind + 1 << " " << nodaldis[ind][1] << "\n";
      writepos << "$EndNodeData\n";
      writepos << "$NodeData\n";
      writepos << "1\n";
      writepos << "\"U2\"\n";
      writepos << "1\n";
      writepos << "0\n";
      writepos << "3\n";
      writepos << "0\n";
      writepos << "1\n";
      writepos << numnodes << "\n";
      for (int ind = 0; ind < numnodes; ind++) writepos << ind + 1 << " " << nodaldis[ind][2] << "\n";
      writepos << "$EndNodeData\n";
      writepos << "$NodeData\n";
      writepos << "1\n";
      writepos << "\"U3\"\n";
      writepos << "1\n";
      writepos << "0\n";
      writepos << "3\n";
      writepos << "0\n";
      writepos << "1\n";
      writepos << numnodes << "\n";
      for (int ind = 0; ind < numnodes; ind++) writepos << ind + 1 << " " << nodaldis[ind][3] << "\n";
      writepos << "$EndNodeData\n";
      
      for (int i = 0; i < numnodes ; i++)
	delete [] nodaldis[i];
      delete [] nodaldis;

      // Prof. YU, generate strain and stress data
      // store data from .u file generated from SwiftComp
      std::string elementdata[12][numelems];
      std::string SSfilename = mfile + ".sn";
      std::ifstream ss(SSfilename.c_str());
      std::string ssline;
      std::string plottitle[] = { "E11", "E22", "E33", "2E23", "2E13", "2E12", "S11", "S22", "S33", "S23", "S13", "S12" };
      int inele1 = 0;
      int inele2 = 0;
      while (getline(ss, ssline)) {
	if (ssline.length() != 0) {
	  elementdata[inele1][inele2] = ssline;
	  inele2 = inele2 + 1;
	}
	else {
	  inele1 = inele1 + 1;
	  inele2 = 0;
	}
      }
      for (int i; i < 12; i++){
	writepos << "$ElementNodeData\n";
	writepos << "1\n";
	writepos << "\"" << plottitle[i] << "\"\n";
	writepos << "1\n";
	writepos << "0\n";
	writepos << "3\n";
	writepos << "0\n";
	writepos << "1\n";
	writepos << numelems << "\n";
	for (int j = 0; j < numelems; j++) writepos << elementdata[i][j] << "\n";
	writepos << "$EndElementNodeData\n";
      }

      
      writepos.close();
      

  }
	
  return 1;
}
