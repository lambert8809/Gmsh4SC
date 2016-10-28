#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <math.h>
#include "GModel.h"
#include "OpenFile.h"
#include "drawContext.h"
#include "LamReadData.h"
#include <FL/fl_ask.H>
#include <FL/Fl.H>
#include "errorcheck.h"
#include "contextWindow.h"
#include "FlGui.h"


void LamInp::set_nseg(int f){num_seg = f;}
void LamInp::set_nlayer(int f){num_layer = f;}
void LamInp::set_nrep1(int f){num_rep1 = f;}
void LamInp::set_nrep2(int f){num_rep2 = f;}
void LamInp::set_sym(int f){
  if (f == 0)
    sym = false;
  else
    sym = true;
}
int LamInp::get_nseg(){return num_seg;}
int LamInp::get_nlayer(){return num_layer;}
int LamInp::get_nrep1(){return num_rep1;}
int LamInp::get_nrep2(){return num_rep2;}
bool LamInp::get_sym(){return sym;}


int countwords(std::string line){
  std::stringstream  stream(line);
  std::string        oneWord;
  unsigned int       count = 0;
  while(stream >> oneWord) { ++count;}
  return count;
}


void LamInput2(std::string inpName, std::string geoName, int matnum, int flagsBP, int cout3, double &len4sg){
  std::ifstream inputfile(inpName.c_str());
  std::string readline;
  std::string temp1;
  int numrows;
  int count=0;
  std::vector<std::string> dataline;
  std::vector<std::string> dataline2;
  std::vector<std::string> dataline3;
  std::vector<std::vector<double> > rows;
  LamInp data;
  while (getline(inputfile, readline)){
    if (!readline.empty()){
      if (countwords(readline)==1)//read nlayer
	{
	  std::stringstream s(readline);
	  int d; s >> d;
	  data.set_nseg(d);
	  //std::cout << data.get_nseg() << std::endl; 
	  if (data.get_nseg() < 0) return;
	  continue;
	} 
      if (countwords(readline)==4)// read flags n m s k
	{ 
	  std::stringstream s(readline);
	  int d1, d2, d3, d4;
	  s >> d1 >> d2 >> d3 >> d4;
	  data.set_nlayer(d1); data.set_nrep1(d2); data.set_sym(d3); data.set_nrep2(d4);
	  //std::cout << data.get_nlayer() << std::endl;
	  if (data.get_nlayer() <= 0) return;
	  if (data.get_nrep1() <= 0) return;
	  if (data.get_nrep2() <= 0) return;
	  if (d3 != 0 && d3 != 1) return;
	}
      if (countwords(readline)==3)//read layer data
	{
	  dataline.push_back(readline);
	  count++;
	}
    }
    if (count == data.get_nlayer())//add all data of this segment
      {
	for (int i = 0; i < data.get_nrep1(); i++)//consider first repeat
	  for (int j = 0; j < data.get_nlayer(); j++)
	    dataline2.push_back(dataline[j]);
	if (data.get_sym()){  // consider sym
	  int temp = dataline2.size()-1;
	  for (int i = temp; i >= 0; i--)
	    dataline2.push_back(dataline2[i]);
	  temp = dataline2.size()-1;
	  for (int i = 0; i < data.get_nrep2()-1; i++) // consider second repeat
	    for (int j = 0; j < temp; j++)
	      dataline2.push_back(dataline2[j]);
	}
	count = 0;
	for (int i = 0; i < dataline2.size(); i++)
	  dataline3.push_back(dataline2[i]);
	dataline.clear();
	dataline2.clear();
      }      
  }
  inputfile.close();

  for (int i = 0; i < dataline3.size(); i++){
    //std::cout << dataline3[i] << std::endl;
    std::stringstream s(dataline3[i]);
    double d1, d2, d3;
    if (s >> d1 >> d2 >> d3){
      std::vector<double> row;
      row.push_back(d1);
      row.push_back(d2);
      row.push_back(d3);
      rows.push_back(row);}
  }
 
  inputfile.close();

  numrows = dataline3.size();
  std::string t3_name = geoName + ".t3";
  std::ofstream t3_is;
  t3_is.open(t3_name.c_str());
  // calcualte total thickness of laminate
  double tol_thickness;
  for (int i = 0; i < numrows; i++){
    tol_thickness = tol_thickness + rows[i][0];
    //t3_is << tol_thickness  << "\n";
  }
  //std::cout << tol_thickness << std::endl;
  std::vector<double> coor;
  double dt;
  double temp2=0;
  //temp2 = 0-tol_thickness/2;
  //t3_is << tol_thickness << " " << temp2  << "\n";
  coor.push_back(temp2);
  for (int i = 0; i < numrows; i++){
    dt = rows[i][0]/4;
    for (int j = 1; j < 5; j++){
      temp2 = temp2  + dt;
      coor.push_back(temp2);
    }
  }

  // generate element connectivity
  int ele[numrows][5];
  for (int i = 0; i < numrows; i++){
    ele[i][0] = 4*i + 1;
    ele[i][1] = 4*i + 5;
    ele[i][2] = 4*i + 2;
    ele[i][3] = 4*i + 4;
    ele[i][4] = 4*i + 3;
  }

  // generate materials assignment to each layers
  std::vector<std::vector<double> > diff_layers;
  std::vector<double> diff_layer1;
  int layersFlags[numrows];
  diff_layer1.push_back(rows[0][1]);
  diff_layer1.push_back(rows[0][2]);
  diff_layers.push_back(diff_layer1);
  for (int i = 0; i < numrows; i++)
    for (int j = 0; j < diff_layers.size(); j++){
      if (fabs(rows[i][1] - diff_layers[j][0]) < 1.0e-3 && fabs(rows[i][2] - diff_layers[j][1]) < 1.0e-3) break;
      if (j+1 == diff_layers.size()){
	 diff_layer1.clear();
	 diff_layer1.push_back(rows[i][1]);
	 diff_layer1.push_back(rows[i][2]);
	 diff_layers.push_back(diff_layer1);
	}

    }
  for (int i = 0; i < diff_layers.size(); i++)
    for (int j = 0; j < numrows; j++)
      if (fabs(diff_layers[i][0]-rows[j][1]) < 1.0e-3 && fabs(diff_layers[i][1]-rows[j][2]) < 1.0e-3) layersFlags[j] = i + 1;


  if (flagsBP == 2){
    char sep = '/';
    char sep2 = '.';
    std::string t4_name = geoName + ".t4";
    std::ofstream t4_is;
    int lam_index = cout3;  
    std::stringstream convert;
    convert << lam_index;
    std::string index;
    convert >> index;
    std::string Laname = "Laminate(" + index + ") ";
    for (int i = 0; i < numrows; i++){
      if (fabs(rows[0][0]-rows[i][0]) > 1e-5) {
	fl_message("Laminar thickness is constant!");
	return;
      }
    }
    t4_is.open(t4_name.c_str(),std::ofstream::app);
    t4_is << Laname << " " << numrows*rows[0][0] << " " << numrows << "\n";
    for (int i = 0; i < numrows; i++)
      t4_is << (i+1)*rows[0][0] << " " << layersFlags[i] << "\n";
    t4_is << "layerID_" << Laname << "\n";
    for (int i = 0; i < diff_layers.size(); i++)
      t4_is << i+1 << "  " << diff_layers[i][1] << "  " << diff_layers[i][0] << "\n";
    t4_is << "//" << Laname << "\n";
    t4_is.close();
    return;
  }


  if (flagsBP == 3){
    change_boxlay_value(1);
    std::string t4_name = geoName + ".t4";
    std::ofstream t4_is;
    int lam_index = cout3;  
    std::stringstream convert;
    convert << lam_index;
    std::string index;
    convert >> index;
    std::string Laname = "Laminate(" + index + ") ";
    for (int i = 0; i < numrows; i++){
      if (fabs(rows[0][0]-rows[i][0]) > 1e-5) {
	fl_message("Laminar thickness is constant!");
	return;
      }
    }
    Bbeam_para[2*boxlay_flags-2] = numrows*rows[0][0];
    Bbeam_para[2*boxlay_flags-1] = numrows;
    for (int i = 1; i < 2*boxlay_flags-2; i+=2){
      if (Bbeam_para[i] != Bbeam_para[2*boxlay_flags-1]){
	fl_message("Box laminate beam must have same layer numbers!");
	change_boxlay_value(-1);
	change_layname_value(-1);
	return;
      }
    }
    t4_is.open(t4_name.c_str(),std::ofstream::app);
    t4_is << Laname << " " << numrows*rows[0][0] << " " << numrows << "\n";
    for (int i = 0; i < numrows; i++)
      t4_is << (i+1)*rows[0][0] << " " << layersFlags[i] << "\n";
    t4_is << "layerID_" << FlGui::instance()->geoContext13_6->lay_name->value() << "\n";
    for (int i = 0; i < diff_layers.size(); i++)
      t4_is << i+1 << "  " << diff_layers[i][1] << "  " << diff_layers[i][0] << "\n";
    t4_is << "//" << Laname << "\n";
    t4_is.close();
     if (boxlay_flags == 1){
      FlGui::instance()->geoContext13_6->lay_name->value("Left edge of box beam");
      fl_message("up edge of box beam has been generated !");
    }
    else if (boxlay_flags == 2){
      FlGui::instance()->geoContext13_6->lay_name->value("Bottom edge of box beam");
      fl_message("left edge of box beam has been generated !");
    }
    else if (boxlay_flags == 3){
      FlGui::instance()->geoContext13_6->lay_name->value("Right edge of box beam");
      fl_message("Bottom edge of box beam has been generated !");
    }
    else if (boxlay_flags ==4)
      {FlGui::instance()->geoContext13_6->lay_name->value("Up edge of box beam");
	fl_message("box beam layup has been defined");
	FlGui::instance()->geoContext13_6->hide(0);
      }
    return;
  }
  
  if (flagsBP == 4){
    change_Ilay_value(1);
    std::string t4_name = geoName + ".t4";
    std::ofstream t4_is;
    int lam_index = cout3;  
    std::stringstream convert;
    convert << lam_index;
    std::string index;
    convert >> index;
    std::string Laname = "Laminate(" + index + ") ";
    for (int i = 0; i < numrows; i++){
      if (fabs(rows[0][0]-rows[i][0]) > 1e-5) {
	fl_message("Laminar thickness is constant!");
	return;
      }
    }
    t4_is.open(t4_name.c_str(),std::ofstream::app);
    t4_is << Laname << " " << numrows*rows[0][0] << " " << numrows << "\n";
    Ibeam_para[2*Ilay_flags-2] = numrows*rows[0][0];
    Ibeam_para[2*Ilay_flags-1] = numrows;
    for (int i = 0; i < numrows; i++)
      t4_is << (i+1)*rows[0][0] << " " << layersFlags[i] << "\n";
    t4_is << "layerID_" << FlGui::instance()->geoContext13_9->lay_name->value() << "\n";
    for (int i = 0; i < diff_layers.size(); i++)
      t4_is << i+1 << "  " << diff_layers[i][1] << "  " << diff_layers[i][0] << "\n";
    t4_is << "//" << Laname << "\n";
    t4_is.close();
    if (Ilay_flags == 1){
      FlGui::instance()->geoContext13_9->lay_name->value("Up edge of I beam");
      fl_message("Bottom edge of I beam has been generated !");
    }
    else if (Ilay_flags == 2){
      FlGui::instance()->geoContext13_9->lay_name->value("middle edge of I beam");
      fl_message("Up edge of I beam has been generated !");
    }
    else if (Ilay_flags == 3){
      FlGui::instance()->geoContext13_9->lay_name->value("Bottom edge of I beam");
      fl_message("I beam has been generated !");
      FlGui::instance()->geoContext13_9->hide(0);
    }
    return;
  }
  

  t3_is << 1 << " " << coor.size() << " " << numrows << " " << matnum << " " << 0 << " " << diff_layers.size() << "    # nSG nnode nelem nmate nslave nlayer\n\n";

   for (int i = 0; i < coor.size(); i++){
    // std::cout << rows[i][0] << " " << rows[i][1] << " " << rows[i][2] << std::endl;
    t3_is << i+1 << " " << coor[i] << "\n";
  }
   t3_is << "\n\n";

  for (int i = 0; i < numrows; i++)
    t3_is << i+1 << " " << layersFlags[i] << " " << ele[i][0] << " " << ele[i][1] << " " << ele[i][2] << " " << ele[i][3] << " " << ele[i][4] << "\n";
  t3_is << "\n\n";

  for (int i = 0; i < diff_layers.size(); i++)
    t3_is << i+1 << "  " << diff_layers[i][1] << "  " << diff_layers[i][0] << "\n";
  t3_is << "\n\n";


  len4sg=coor.back();

  t3_is.close();

  double visu[numrows][3];
  for (int i = 0; i < numrows; i++){
    visu[i][0] = i+1;
    visu[i][1] = rows[i][0];
    visu[i][2] = layersFlags[i];
  }
  
  std::string lamgeo = geoName + ".msh";
  int lastindex = geoName.find_last_of(".");
  std::string prefix = geoName.substr(0, lastindex);
  std::ofstream wtempmsh;
  double temp3=0;
  wtempmsh.open(lamgeo.c_str());
  wtempmsh << "$MeshFormat\n";
  wtempmsh << "2.2 0 8\n";
  wtempmsh << "$EndMeshFormat\n";
  wtempmsh << "$Nodes\n";
  wtempmsh << numrows+1 << "\n";
  wtempmsh << "1 0 0 0 \n";
  for (int i = 1; i < numrows+1; i++){
    temp3 = temp3 + visu[i-1][1];
    wtempmsh << i+1 << " " << 0 << " " << temp3 << " " << 0 << "\n";
  }
    
  wtempmsh << "$EndNodes\n";
  wtempmsh << "$Elements\n";
  wtempmsh << numrows << "\n";
  for (int i = 0; i < numrows; i++)
    wtempmsh << i+1 << " 1 2 " << visu[i][2] << " " << 2+visu[i][2] << " " << i+1 << " " << i+2 << "\n";
  wtempmsh <<"$EndElements\n";
  wtempmsh.close();
  //std::string lamview = prefix + "View" + ".geo";
  std::ofstream viewfile;
  viewfile.open(geoName.c_str(), std::ofstream::app);
  viewfile << "Merge " << "\"" << lamgeo << "\";\n";
  viewfile << "Mesh.SurfaceFaces=0;\n";
  viewfile << "Mesh.Points=1;\n";
  viewfile << "Mesh.SurfaceEdges=0;\n";
  viewfile << "Mesh.VolumeEdges = 0;\n";
  viewfile << "Mesh.Lines = 1;\n";
  viewfile << "Mesh.LineWidth = 3;\n";
  viewfile << "Mesh.PointSize = 5;\n";
  viewfile << "Mesh.PointType = 1;\n";
  viewfile.close();
  OpenProject(geoName);
  drawContext::global()->draw();

}
