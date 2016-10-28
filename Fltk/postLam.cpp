#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <istream>
#include <cmath>
#include "GModel.h"
#include "postLam.h"

int postLam1(std::string &mname, std::string &pname){

  /* std::string name = GModel::current()->getFileName();
  int lastindex = name.find_last_of(".");
  std::string tpos = name.substr(0, lastindex);
  std::string pfile = tpos + "VIEW" + ".msh";
  std::string mfile = tpos + ".msh";*/
  std::string pfile = pname;
  std::string mfile = mname;
	std::ofstream writepos;
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
	
	for (int i = 0; i < 2*nodes_num; i++)
	delete [] mesh_nodes[i];
      delete [] mesh_nodes;
	  for (int i = 0; i < 4*ele_num; i++)
	delete [] mesh_elens[i];
      delete [] mesh_elens;
    
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
      //writepos << newread << "\n";
      while (iss >> str) tokens.push_back(str);
      dispdata[kj][0] = atof(tokens[0].c_str());
      dispdata[kj][1] = atof(tokens[1].c_str());
      dispdata[kj][2] = atof(tokens[2].c_str());
      dispdata[kj][3] = atof(tokens[3].c_str());
      kj = kj + 1;
      //std::cout << dispdata[k-1][0] << std::endl;
      if (kj == nodes_num) break;
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
    
	
	for (int i = 0; i < 2*nodes_num ; i++)
	delete [] dispdata[i];
      delete [] dispdata;
    // read and regenerate .sn data
    k = 0;
    kk = 0;
    flags1 = 0;
    std::string SSname = mfile + ".sn";
    std::ifstream SSfile(SSname.c_str());
    
    double** SSdata = new double*[4*ele_num];
    int loop[5] = {2, 4, 6, 5, 3};
    std::string plottitle[] = { "E11", "E22", "E33", "2E23", "2E13", "2E12", "S11", "S22", "S33", "S23", "S13", "S12" };
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
    writepos.close();
    return 1;
}

