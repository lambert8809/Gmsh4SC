// Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#include <FL/Fl_Tabs.H>
#include <FL/Fl_Return_Button.H>
#include "FlGui.h"
#include "drawContext.h"
#include "contextWindow.h"
#include "paletteWindow.h"
#include "GModel.h"
#include "GeoStringInterface.h"
#include "OpenFile.h"
#include "Context.h"

#include "CreateFile.h"
#include <fileDialogs.h>
#include "OS.h"
#include "GmshDefines.h"
#include <FL/fl_ask.H>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "chooseswift.h"              //Prof.Wenbin Yu
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "Options.h"
//Prof. Yu
#include "AddMatName.h"
#include <FL/Fl_File_Chooser.H>
#include "LamReadData.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include "ComBeamModel.h"
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Output.H>
#include "errorcheck.h"
#include "importSC.h"

double len4SG=0;

void msh4_1dsg(std::string name, std::string t3name, int sg_flags);

static void add_mat_id(std::string fileName){
  std::ifstream geofile(fileName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::vector<std::string> mindex;
  std::vector<int> intmindex;
  std::string minput;
  int matflag = 0;

  while (getline(geofile, readoutline)){
    if (readoutline.find(point) != std::string::npos){
      size_t pos = readoutline.find(point);
      readoutline.erase(0, pos + 16);
      std::istringstream iss(readoutline);
      iss >> minput;
      mindex.push_back(minput);
    }
  }
  geofile.close();
  for (int i = 0; i < mindex.size(); i++){
    int num = atoi(mindex[i].c_str());
    intmindex.push_back(num);
  }
  int matid = *std::max_element(intmindex.begin(),intmindex.end());

  matid = matid + 1;
  std::ostringstream ss;
  ss << matid;
  std::string mmatid;
  mmatid = ss.str();
  FlGui::instance()->geoContext1->input[0]->value(mmatid.c_str());
  FlGui::instance()->geoContext1->input[39]->value(mmatid.c_str());
  FlGui::instance()->geoContext1->input[41]->value(mmatid.c_str());
  FlGui::instance()->geoContext21->input[0]->value(mmatid.c_str());
  FlGui::instance()->geoContext21->input[5]->value(mmatid.c_str());
  FlGui::instance()->geoContext21->input[12]->value(mmatid.c_str());
  
  
  std::string autoname = "MAT" + mmatid;
  FlGui::instance()->geoContext1->input[40]->value(autoname.c_str());
  FlGui::instance()->geoContext1->input[42]->value(autoname.c_str());
  FlGui::instance()->geoContext1->input[43]->value(autoname.c_str());
  FlGui::instance()->geoContext21->input[1]->value(autoname.c_str());
  FlGui::instance()->geoContext21->input[6]->value(autoname.c_str());
  FlGui::instance()->geoContext21->input[13]->value(autoname.c_str());
}

std::vector<std::string> chec_matname;

static void define_conductivity1(Fl_Widget *w, void *data){
  for (int i = 0; i < chec_matname.size(); i++)
    if (chec_matname[i] == FlGui::instance()->geoContext21->input[0]->value()){
      fl_message("Please input a different material name!");
      return;
    }
  chec_matname.push_back(FlGui::instance()->geoContext21->input[0]->value());
  
  add_conduc1(FlGui::instance()->geoContext21->input[0]->value(),         
	     FlGui::instance()->geoContext21->input[1]->value(),
	     FlGui::instance()->geoContext21->input[2]->value(),
	     FlGui::instance()->geoContext21->input[3]->value(),
	     FlGui::instance()->geoContext21->input[4]->value(),
	     GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();
  AddMatName(GModel::current()->getFileName());
  add_mat_id(GModel::current()->getFileName());
  FlGui::instance()->geoContext21->input[2]->value("0");
  FlGui::instance()->geoContext21->input[3]->value("0");
  FlGui::instance()->geoContext21->input[4]->value("0");
}

static void define_conductivity2(Fl_Widget *w, void *data){
  for (int i = 0; i < chec_matname.size(); i++)
    if (chec_matname[i] == FlGui::instance()->geoContext21->input[5]->value()){
      fl_message("Please input a different material name!");
      return;
    }
  chec_matname.push_back(FlGui::instance()->geoContext21->input[5]->value());
  
  add_conduc2(FlGui::instance()->geoContext21->input[5]->value(),         
	      FlGui::instance()->geoContext21->input[6]->value(),
	      FlGui::instance()->geoContext21->input[7]->value(),
	      FlGui::instance()->geoContext21->input[8]->value(),
	      FlGui::instance()->geoContext21->input[9]->value(),
	      FlGui::instance()->geoContext21->input[10]->value(),
	      FlGui::instance()->geoContext21->input[11]->value(),
	     GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();
  AddMatName(GModel::current()->getFileName());
  add_mat_id(GModel::current()->getFileName());
  FlGui::instance()->geoContext21->input[7]->value("0");
  FlGui::instance()->geoContext21->input[8]->value("0");
  FlGui::instance()->geoContext21->input[9]->value("0");
  FlGui::instance()->geoContext21->input[10]->value("0");
  FlGui::instance()->geoContext21->input[11]->value("0");
}

static void define_conductivity3(Fl_Widget *w, void *data){
  for (int i = 0; i < chec_matname.size(); i++)
    if (chec_matname[i] == FlGui::instance()->geoContext21->input[12]->value()){
      fl_message("Please input a different material name!");
      return;
    }
  chec_matname.push_back(FlGui::instance()->geoContext21->input[12]->value());
  
  add_conduc3(FlGui::instance()->geoContext21->input[12]->value(),         
	      FlGui::instance()->geoContext21->input[13]->value(),
	      FlGui::instance()->geoContext21->input[14]->value(),
	      FlGui::instance()->geoContext21->input[15]->value(),
	      FlGui::instance()->geoContext21->input[16]->value(),
	      FlGui::instance()->geoContext21->input[17]->value(),
	      FlGui::instance()->geoContext21->input[18]->value(),
	      FlGui::instance()->geoContext21->input[19]->value(),
	      FlGui::instance()->geoContext21->input[20]->value(),
	      FlGui::instance()->geoContext21->input[21]->value(),
	     GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();
  AddMatName(GModel::current()->getFileName());
  add_mat_id(GModel::current()->getFileName());
  FlGui::instance()->geoContext21->input[16]->value("0");
  FlGui::instance()->geoContext21->input[17]->value("0");
  FlGui::instance()->geoContext21->input[18]->value("0");
  FlGui::instance()->geoContext21->input[19]->value("0");
  FlGui::instance()->geoContext21->input[20]->value("0");
  FlGui::instance()->geoContext21->input[21]->value("0");
}

static void con_geometry_define_parameter_cb1(Fl_Widget *w, void *data)       //Add orth material
{
  for (int i = 0; i < chec_matname.size(); i++)
    if (chec_matname[i] == FlGui::instance()->geoContext1->input[42]->value()){
      fl_message("Please input a different material name!");
      return;
    }
  chec_matname.push_back(FlGui::instance()->geoContext1->input[42]->value());
  add_param(FlGui::instance()->geoContext1->input[0]->value(),         //Prof. Wenbin Yu
            FlGui::instance()->geoContext1->input[1]->value(),
            FlGui::instance()->geoContext1->input[24]->value(),
            FlGui::instance()->geoContext1->input[25]->value(),
	    //Prof. Wenbin Yu
	    FlGui::instance()->geoContext1->input[26]->value(),
	    FlGui::instance()->geoContext1->input[27]->value(),
	    FlGui::instance()->geoContext1->input[28]->value(),
	    FlGui::instance()->geoContext1->input[29]->value(),
	    FlGui::instance()->geoContext1->input[30]->value(),
	    FlGui::instance()->geoContext1->input[31]->value(),
	    FlGui::instance()->geoContext1->input[32]->value(),
	    FlGui::instance()->geoContext1->input[33]->value(),
	    FlGui::instance()->geoContext1->input[47]->value(),
	    FlGui::instance()->geoContext1->input[48]->value(),
	    FlGui::instance()->geoContext1->input[49]->value(),
	    FlGui::instance()->geoContext1->input[50]->value(),
	    FlGui::instance()->geoContext1->input[42]->value(),
	    //Prof. Wenbin Yu
            GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();

 
  //FlGui::instance()->geoContext1->input[0]->value(add_mat_id());
  //add_matname(FlGui::instance()->geoContext1->input[0]->value(),
	     // FlGui::instance()->geoContext1->input[42]->value(),
	      //GModel::current()->getFileName());
   AddMatName(GModel::current()->getFileName());
   add_mat_id(GModel::current()->getFileName());
   FlGui::instance()->geoContext1->input[1]->value("0");
   FlGui::instance()->geoContext1->input[24]->value("0");
   FlGui::instance()->geoContext1->input[25]->value("0");
   FlGui::instance()->geoContext1->input[26]->value("0");
   FlGui::instance()->geoContext1->input[27]->value("0");
   FlGui::instance()->geoContext1->input[28]->value("0");
   FlGui::instance()->geoContext1->input[29]->value("0");
   FlGui::instance()->geoContext1->input[30]->value("0");
   FlGui::instance()->geoContext1->input[31]->value("0");
   FlGui::instance()->geoContext1->input[32]->value("0");
   FlGui::instance()->geoContext1->input[33]->value("0");
   FlGui::instance()->geoContext1->input[47]->value("0");
   FlGui::instance()->geoContext1->input[48]->value("0");
   FlGui::instance()->geoContext1->input[49]->value("0");
   FlGui::instance()->geoContext1->input[50]->value("0");

}
//Prof. Wenbin Yu
static void con_geometry_define_parameter_cb2(Fl_Widget *w, void *data)   //add iso material
{
  for (int i = 0; i < chec_matname.size(); i++)
    if (chec_matname[i] == FlGui::instance()->geoContext1->input[40]->value()){
      fl_message("Please input a different material name!");
      return;
    }
  chec_matname.push_back(FlGui::instance()->geoContext1->input[40]->value());
  add_param1(FlGui::instance()->geoContext1->input[39]->value(),
	     FlGui::instance()->geoContext1->input[34]->value(),
             FlGui::instance()->geoContext1->input[35]->value(),
             FlGui::instance()->geoContext1->input[36]->value(),
	     FlGui::instance()->geoContext1->input[37]->value(),
	     FlGui::instance()->geoContext1->input[45]->value(),
	     FlGui::instance()->geoContext1->input[46]->value(),
	     FlGui::instance()->geoContext1->input[40]->value(),
             GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();



  //matname.push_back(FlGui::instance()->geoContext1->input[40]->value());

  //add_matname(FlGui::instance()->geoContext1->input[39]->value(),
	      //FlGui::instance()->geoContext1->input[40]->value(),
	      //GModel::current()->getFileName());



  AddMatName(GModel::current()->getFileName());
  add_mat_id(GModel::current()->getFileName());

  FlGui::instance()->geoContext1->input[34]->value("0");
  FlGui::instance()->geoContext1->input[35]->value("0");
  FlGui::instance()->geoContext1->input[36]->value("0");
  FlGui::instance()->geoContext1->input[37]->value("0");
  FlGui::instance()->geoContext1->input[45]->value("0");
  FlGui::instance()->geoContext1->input[46]->value("0");

}
static void con_geometry_define_parameter_cb3(Fl_Widget *w, void *data)   //add aniso material
{
  for (int i = 0; i < chec_matname.size(); i++)
    if (chec_matname[i] == FlGui::instance()->geoContext1->input[43]->value()){
      fl_message("Please input a different material name!");
      return;
    }
  chec_matname.push_back(FlGui::instance()->geoContext1->input[43]->value());
  add_param2(FlGui::instance()->geoContext1->input[41]->value(),
	     FlGui::instance()->geoContext1->input[2]->value(),
             FlGui::instance()->geoContext1->input[3]->value(),
             FlGui::instance()->geoContext1->input[4]->value(),
	     FlGui::instance()->geoContext1->input[5]->value(),
	     FlGui::instance()->geoContext1->input[6]->value(),
	     FlGui::instance()->geoContext1->input[7]->value(),
	     FlGui::instance()->geoContext1->input[8]->value(),
	     FlGui::instance()->geoContext1->input[9]->value(),
	     FlGui::instance()->geoContext1->input[10]->value(),
	     FlGui::instance()->geoContext1->input[11]->value(),
	     FlGui::instance()->geoContext1->input[12]->value(),
	     FlGui::instance()->geoContext1->input[13]->value(),
	     FlGui::instance()->geoContext1->input[14]->value(),
	     FlGui::instance()->geoContext1->input[15]->value(),
	     FlGui::instance()->geoContext1->input[16]->value(),
	     FlGui::instance()->geoContext1->input[17]->value(),
	     FlGui::instance()->geoContext1->input[18]->value(),
	     FlGui::instance()->geoContext1->input[19]->value(),
	     FlGui::instance()->geoContext1->input[20]->value(),
	     FlGui::instance()->geoContext1->input[21]->value(),
	     FlGui::instance()->geoContext1->input[22]->value(),
	     FlGui::instance()->geoContext1->input[23]->value(),
	     FlGui::instance()->geoContext1->input[38]->value(),
	     FlGui::instance()->geoContext1->input[51]->value(),
	     FlGui::instance()->geoContext1->input[52]->value(),
	     FlGui::instance()->geoContext1->input[53]->value(),
	     FlGui::instance()->geoContext1->input[54]->value(),
	     FlGui::instance()->geoContext1->input[55]->value(),
	     FlGui::instance()->geoContext1->input[56]->value(),
	     FlGui::instance()->geoContext1->input[57]->value(),
	     FlGui::instance()->geoContext1->input[43]->value(),
             GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();


  //FlGui::instance()->geoContext1->input[40]->value(add_mat_id());
  //add_matname(FlGui::instance()->geoContext1->input[41]->value(),
	      //FlGui::instance()->geoContext1->input[43]->value(),
	     // GModel::current()->getFileName());
  AddMatName(GModel::current()->getFileName());
  add_mat_id(GModel::current()->getFileName());

  FlGui::instance()->geoContext1->input[2]->value("0");
  FlGui::instance()->geoContext1->input[3]->value("0");
  FlGui::instance()->geoContext1->input[4]->value("0");
  FlGui::instance()->geoContext1->input[5]->value("0");
  FlGui::instance()->geoContext1->input[6]->value("0");
  FlGui::instance()->geoContext1->input[7]->value("0");
  FlGui::instance()->geoContext1->input[8]->value("0");
  FlGui::instance()->geoContext1->input[9]->value("0");
  FlGui::instance()->geoContext1->input[10]->value("0");
  FlGui::instance()->geoContext1->input[11]->value("0");
  FlGui::instance()->geoContext1->input[12]->value("0");
  FlGui::instance()->geoContext1->input[13]->value("0");
  FlGui::instance()->geoContext1->input[14]->value("0");
  FlGui::instance()->geoContext1->input[15]->value("0");
  FlGui::instance()->geoContext1->input[16]->value("0");
  FlGui::instance()->geoContext1->input[17]->value("0");
  FlGui::instance()->geoContext1->input[18]->value("0");
  FlGui::instance()->geoContext1->input[19]->value("0");
  FlGui::instance()->geoContext1->input[20]->value("0");
  FlGui::instance()->geoContext1->input[21]->value("0");
  FlGui::instance()->geoContext1->input[22]->value("0");
  FlGui::instance()->geoContext1->input[23]->value("0");
  FlGui::instance()->geoContext1->input[38]->value("0");
  FlGui::instance()->geoContext1->input[51]->value("0");
  FlGui::instance()->geoContext1->input[52]->value("0");
  FlGui::instance()->geoContext1->input[53]->value("0");
  FlGui::instance()->geoContext1->input[54]->value("0");
  FlGui::instance()->geoContext1->input[55]->value("0");
  FlGui::instance()->geoContext1->input[56]->value("0");
  FlGui::instance()->geoContext1->input[57]->value("0");
}


static void con_geometry_define_parameter_cb5(Fl_Widget *w, void *data)   //add flags
{
  std::string temp= GModel::current()->getFileName();
  
  if (temp.length()>8){
    if (temp.find("untitled")!=std::string::npos){
      fl_message("Please save the model before saving the SC file!");
      return;
    }
  }
	
  if(temp.find(".sc")!=std::string::npos){
    fl_message("Don't need to save import file, please directly run it!");
    return;
  }

  add_flags1(FlGui::instance()->geoContext10->choice[0]->text(),
	  FlGui::instance()->geoContext10->choice[1]->text(),
	  FlGui::instance()->geoContext10->choice[2]->text(),
	  FlGui::instance()->geoContext10->choice[3]->text(),
	  //FlGui::instance()->geoContext10->input[0]->value(),
	  GModel::current()->getFileName());

  FlGui::instance()->resetVisibility();
  std::string name = CTX::instance()->outputFileName;
  if (name.empty()){
	  if (CTX::instance()->mesh.fileFormat == FORMAT_AUTO)
		  name = GetDefaultFileName(FORMAT_MSH);
	  else
		  name = GetDefaultFileName(CTX::instance()->mesh.fileFormat);
  }
  if (CTX::instance()->confirmOverwrite) {
	  if (!StatFile(name))
		  if (!fl_choice("File '%s' already exists.\n\nDo you want to replace it?",
			  "Cancel", "Replace", 0, name.c_str()))
			  return;
  }

  Fl_Window *window = new Fl_Window(480, 320, 360, 120, "Please Wait");
  Fl_Box *box = new Fl_Box(20, 10, 300, 100, "Preparing input file...");
  box->box(FL_FLAT_BOX);
  box->labelfont(FL_BOLD);
  box->labelsize(18);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show();
  std::string tt3_name = GModel::current()->getFileName() + ".t3";
  std::ifstream t3file(tt3_name.c_str());
  if (!t3file)
    CreateOutputFile(name, CTX::instance()->mesh.fileFormat);
  else
    msh4_1dsg(name,tt3_name,1);
  window->hide();
  //FlGui::instance()->geoContext4->hide(0);    //wenbin yu, when user hits add, close window
}

static void con_geometry_define_parameter_cb6(Fl_Widget *w, void *data)   // Prof. Yu, add flags2
{
  std::string temp= GModel::current()->getFileName();

  if (temp.length()>8){
    if (temp.find("untitled")!=std::string::npos){
      fl_message("Please save the model before saving the SC file!");
      return;
    }
  }
  
  if(temp.find(".sc")!=std::string::npos){
    fl_message("Don't need to save import file, please directly run it!");
    return;
  }
  std::ofstream add_b_flag;
  add_b_flag.open(temp.c_str(),std::ofstream::app);
  add_b_flag << "\n//beam section\n";
  add_b_flag.close();
  

  add_flags2(FlGui::instance()->geoContext8->choice[8]->text(),
	     FlGui::instance()->geoContext8->choice[9]->text(),
	     FlGui::instance()->geoContext8->choice[10]->text(),
	     FlGui::instance()->geoContext8->choice[11]->text(),
	     FlGui::instance()->geoContext8->choice[5]->text(),
	     FlGui::instance()->geoContext8->input[1]->value(),
	     FlGui::instance()->geoContext8->input[2]->value(),
	     FlGui::instance()->geoContext8->input[3]->value(),
	     FlGui::instance()->geoContext8->input[4]->value(),
	     FlGui::instance()->geoContext8->input[5]->value(),
	     GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();
  std::string name = CTX::instance()->outputFileName;
  if (name.empty()){
    if (CTX::instance()->mesh.fileFormat == FORMAT_AUTO)
      name = GetDefaultFileName(FORMAT_MSH);
    else
      name = GetDefaultFileName(CTX::instance()->mesh.fileFormat);
  }
  if (CTX::instance()->confirmOverwrite) {
    if (!StatFile(name))
      if (!fl_choice("File '%s' already exists.\n\nDo you want to replace it?",
		     "Cancel", "Replace", 0, name.c_str()))
	return;
  }
  Fl_Window *window = new Fl_Window(480, 320, 360, 120, "Please Wait");
  Fl_Box *box = new Fl_Box(20, 10, 300, 100, "Preparing input file...");
  box->box(FL_FLAT_BOX);
  box->labelfont(FL_BOLD);
  box->labelsize(18);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show();
  CreateOutputFile(name, CTX::instance()->mesh.fileFormat);
  window->hide();
  //FlGui::instance()->geoContext4->hide(0);    //wenbin yu, when user hits add, close window
}

static void con_geometry_define_parameter_cb7(Fl_Widget *w, void *data)   // Prof. Yu,add flags3
{
  std::string temp= GModel::current()->getFileName();
  
  if (temp.length()>8){
    if (temp.find("untitled")!=std::string::npos){
      fl_message("Please save the model before saving the SC file!");
      return;
    }
  }
  
  if(temp.find(".sc")!=std::string::npos){
    fl_message("Don't need to save import file, please directly run it!");
    return;
  }

  add_flags3(FlGui::instance()->geoContext9->choice[13]->text(),
	     FlGui::instance()->geoContext9->choice[14]->text(),
	     FlGui::instance()->geoContext9->choice[15]->text(),
	     FlGui::instance()->geoContext9->choice[16]->text(),
	     FlGui::instance()->geoContext9->choice[6]->text(),
	     FlGui::instance()->geoContext9->input[6]->value(),
	     FlGui::instance()->geoContext9->input[7]->value(),
	     GModel::current()->getFileName());

  FlGui::instance()->resetVisibility();
  std::string name = CTX::instance()->outputFileName;
  if (name.empty()){
    if (CTX::instance()->mesh.fileFormat == FORMAT_AUTO)
      name = GetDefaultFileName(FORMAT_MSH);
    else
      name = GetDefaultFileName(CTX::instance()->mesh.fileFormat);
  }
  if (CTX::instance()->confirmOverwrite) {
    if (!StatFile(name))
      if (!fl_choice("File '%s' already exists.\n\nDo you want to replace it?",
		     "Cancel", "Replace", 0, name.c_str()))
	return;
  }

  Fl_Window *window = new Fl_Window(480, 320, 360, 120, "Please Wait");
  Fl_Box *box = new Fl_Box(20, 10, 300, 100, "Preparing input file...");
  box->box(FL_FLAT_BOX);
  box->labelfont(FL_BOLD);
  box->labelsize(18);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show();

  std::string tt3_name = GModel::current()->getFileName() + ".t3";
  std::ifstream t3file(tt3_name.c_str());
  if (!t3file)
    CreateOutputFile(name, CTX::instance()->mesh.fileFormat);
  else
    msh4_1dsg(name,tt3_name,0);
  window->hide();
	   // FlGui::instance()->geoContext4->hide(0);    //wenbin yu, when user hits add, close window
}



static void con_geometry_define_parameter_cb8(Fl_Widget *w, void *data)   // Prof. Yu,add flags3
{
  std::string temp= GModel::current()->getFileName();
  
  if (temp.length()>8){
    if (temp.find("untitled")!=std::string::npos){
      fl_message("Please save the model before saving the SC file!");
      return;
    }
  }
  
  if(temp.find(".sc")!=std::string::npos){
    fl_message("Don't need to save import file, please directly run it!");
    return;
  }

  add_flags4(FlGui::instance()->geoContext9->choice[18]->text(),
	     FlGui::instance()->geoContext9->choice[19]->text(),
	     FlGui::instance()->geoContext9->choice[20]->text(),
	     FlGui::instance()->geoContext9->choice[21]->text(),
	     FlGui::instance()->geoContext9->choice[7]->text(),
	     GModel::current()->getFileName());
  
  FlGui::instance()->resetVisibility();
  std::string name = CTX::instance()->outputFileName;
  if (name.empty()){
    if (CTX::instance()->mesh.fileFormat == FORMAT_AUTO)
      name = GetDefaultFileName(FORMAT_MSH);
    else
      name = GetDefaultFileName(CTX::instance()->mesh.fileFormat);
  }
  if (CTX::instance()->confirmOverwrite) {
    if (!StatFile(name))
      if (!fl_choice("File '%s' already exists.\n\nDo you want to replace it?",
		     "Cancel", "Replace", 0, name.c_str()))
	return;
  }
  
  Fl_Window *window = new Fl_Window(480, 320, 360, 120, "Please Wait");
  Fl_Box *box = new Fl_Box(20, 10, 300, 100, "Preparing input file...");
  box->box(FL_FLAT_BOX);
  box->labelfont(FL_BOLD);
  box->labelsize(18);
  box->labeltype(FL_SHADOW_LABEL);
  window->end();
  window->show();
  std::string tt3_name = GModel::current()->getFileName() + ".t3";
  std::ifstream t3file(tt3_name.c_str());
  if (!t3file)
    CreateOutputFile(name, CTX::instance()->mesh.fileFormat);
  else
    msh4_1dsg(name,tt3_name,0);
  window->hide();
  // FlGui::instance()->geoContext4->hide(0);    //wenbin yu, when user hits add, close window
}
//Prof. Wenbin Yu


static void vamuch_choose_executable_cb2(Fl_Widget *w, void *data)  // Prof. Yu, dehomogization for solid elasticity
{
  
  add_dehomoSolid1(FlGui::instance()->geoContext5->input[0]->value(),
		   FlGui::instance()->geoContext5->input[1]->value(),
		   FlGui::instance()->geoContext5->input[2]->value(),
		   FlGui::instance()->geoContext5->input[3]->value(),
		   FlGui::instance()->geoContext5->input[4]->value(),
		   FlGui::instance()->geoContext5->input[5]->value(),
		   FlGui::instance()->geoContext5->input[6]->value(),
		   FlGui::instance()->geoContext5->input[7]->value(),
		   FlGui::instance()->geoContext5->input[8]->value(),
		   FlGui::instance()->geoContext5->input[9]->value(),
		   FlGui::instance()->geoContext5->input[10]->value(),
		   FlGui::instance()->geoContext5->input[11]->value(),
		   FlGui::instance()->geoContext5->input[12]->value(),
		   FlGui::instance()->geoContext5->input[13]->value(),
		   FlGui::instance()->geoContext5->input[14]->value(),
		   FlGui::instance()->geoContext5->input[15]->value(),
		   FlGui::instance()->geoContext5->input[16]->value(),
		   FlGui::instance()->geoContext5->input[17]->value(),
		   GModel::current()->getFileName());
	FlGui::instance()->resetVisibility();

	//FlGui::instance()->geoContext5->hide(0);
}

static void vamuch_choose_executable_cb3(Fl_Widget *w, void *data)  // Prof. Yu, dehomogization for beam elasticity
{
	add_dehomoBeam1(FlGui::instance()->geoContext11->input[0]->value(),
		FlGui::instance()->geoContext11->input[1]->value(),
		FlGui::instance()->geoContext11->input[2]->value(),
		FlGui::instance()->geoContext11->input[3]->value(),
		FlGui::instance()->geoContext11->input[4]->value(),
		FlGui::instance()->geoContext11->input[5]->value(),
		FlGui::instance()->geoContext11->input[6]->value(),
		FlGui::instance()->geoContext11->input[7]->value(),
		FlGui::instance()->geoContext11->input[8]->value(),
		FlGui::instance()->geoContext11->input[9]->value(),
		FlGui::instance()->geoContext11->input[10]->value(),
		FlGui::instance()->geoContext11->input[11]->value(),
		FlGui::instance()->geoContext11->input[12]->value(),
		FlGui::instance()->geoContext11->input[13]->value(),
		FlGui::instance()->geoContext11->input[14]->value(),
		FlGui::instance()->geoContext11->input[15]->value(),
		GModel::current()->getFileName());
	FlGui::instance()->resetVisibility();

	//FlGui::instance()->geoContext5->hide(0);
}

static void vamuch_choose_executable_cb4(Fl_Widget *w, void *data)  // Prof. Yu, dehomogization for shell/plate elasticity
{
	add_dehomoSP1(FlGui::instance()->geoContext12->input[0]->value(),
		FlGui::instance()->geoContext12->input[1]->value(),
		FlGui::instance()->geoContext12->input[2]->value(),
		FlGui::instance()->geoContext12->input[3]->value(),
		FlGui::instance()->geoContext12->input[4]->value(),
		FlGui::instance()->geoContext12->input[5]->value(),
		FlGui::instance()->geoContext12->input[6]->value(),
		FlGui::instance()->geoContext12->input[7]->value(),
		FlGui::instance()->geoContext12->input[8]->value(),
		FlGui::instance()->geoContext12->input[9]->value(),
		FlGui::instance()->geoContext12->input[10]->value(),
		FlGui::instance()->geoContext12->input[11]->value(),
		FlGui::instance()->geoContext12->input[12]->value(),
		FlGui::instance()->geoContext12->input[13]->value(),
		FlGui::instance()->geoContext12->input[14]->value(),
		FlGui::instance()->geoContext12->input[15]->value(),
		FlGui::instance()->geoContext12->input[16]->value(),
		FlGui::instance()->geoContext12->input[17]->value(),
		GModel::current()->getFileName());
	FlGui::instance()->resetVisibility();

	//FlGui::instance()->geoContext5->hide(0);
}




// Prof. Yu, add exit button
static void con_exit_cb(Fl_Widget *w, void *data)
{
  FlGui::instance()->geoContext1->hide(0);
  FlGui::instance()->geoContext14P->hide(0);
  FlGui::instance()->geoContext13_2->hide(0);
  FlGui::instance()->geoContext13_3->hide(0);
  FlGui::instance()->geoContext13_5->hide(0);
  FlGui::instance()->geoContext13_8->hide(0);
  FlGui::instance()->geoContext21->hide(0);
}


void show_plot(string geofile, string mshfile){
  ofstream geoout;
  geoout.open(geofile.c_str());
  geoout <<  "Merge " << "\"" << mshfile << "\";\n";
  geoout << "Mesh.SurfaceFaces=0;\n" << "Mesh.Points=0;\n";
  geoout << "Mesh.SurfaceEdges=0;\n" << "Mesh.VolumeEdges = 0;\n";
  geoout << "View[0].Visible=1;\n";
  for (int i = 1; i < 16; i++) geoout << "View[" << i << "].Visible=0;\n";
  geoout.close();
  OpenProject(geofile);
  drawContext::global()->draw();  
}


// Prof. Yu, add run swiftcomp homogenization\dehomogenization function
void vamuch_choose_executable_cb(Fl_Widget *w, void *data)
{
  FlGui::instance()->geoContext8->hide(0);
  FlGui::instance()->geoContext9->hide(0);
  FlGui::instance()->geoContext10->hide(0);
  FlGui::instance()->geoContext5->hide(0);
  FlGui::instance()->geoContext11->hide(0);
  FlGui::instance()->geoContext12->hide(0);
  
  std::string str((const char*)data);
  std::string temp= GModel::current()->getFileName(); 
  if(temp.find(".sc")!=std::string::npos){
    std::string scfile=temp.substr(0,temp.length()-4);
    std::string mfile=scfile+".msh";
    if(str=="homo1") run_homo(1,scfile,1);
    else if (str=="homo2") run_homo(2,scfile,1);
    else if (str=="homo3") run_homo(3,scfile,1);
    else if (str=="dehomo1") {run_homo(1,scfile,2); ImportSC test1(scfile,mfile,1); show_plot(temp,mfile);}
    else if (str=="dehomo2") {run_homo(2,scfile,2); ImportSC test1(scfile,mfile,2); show_plot(temp,mfile);}
    else if (str=="dehomo3") {run_homo(3,scfile,2); ImportSC test1(scfile,mfile,3); show_plot(temp,mfile);}
    else return;

    return;
  }

  
  if (str=="homo1" || str=="homo2" || str=="homo3") str="homo";
  if (str=="dehomo1" || str=="dehomo2" || str=="dehomo3") str="dehomo";
  if (str == "homo"){
    Msg::StatusBar(true, "Loading SwiftComp for homogenization...");
    choose_swiftcomp_executable(str);
  }
  if (str == "dehomo"){
    Msg::StatusBar(true, "Loading SwiftComp for dehomogenization...");
    choose_swiftcomp_executable(str);
  }
}


//extern int period_flags;
//Prof. Yu
static void con_geometry_comSG_parameter_cb1(Fl_Widget *w, void *data)
{
  
  change_com_value(1);
  change_period_value(1);
  add_Model1(FlGui::instance()->geoContext7_1->choice[0]->text(),
	     FlGui::instance()->geoContext7_1->input[1]->value(),
	     FlGui::instance()->geoContext7_1->input[2]->value(),
	     FlGui::instance()->geoContext7_1->choice[5]->text(),
	     FlGui::instance()->geoContext7_1->choice[6]->text(),
	     FlGui::instance()->geoContext7_1->choice[7]->text(),
	     GModel::current()->getFileName());
  FlGui::instance()->resetVisibility();
  FlGui::instance()->geoContext7->hide(0);
}

static void con_geometry_comSG_parameter_cb2(Fl_Widget *w, void *data)
{
  change_com_value(1);
  change_period_value(1);
	add_Model2(FlGui::instance()->geoContext7->choice[1]->text(),
		//FlGui::instance()->geoContext7->input[5]->value(),
		//FlGui::instance()->geoContext7->input[6]->value(),
		//FlGui::instance()->geoContext7->input[7]->value(),
		FlGui::instance()->geoContext7->input[8]->value(),
		FlGui::instance()->geoContext7->choice[8]->text(),
		FlGui::instance()->geoContext7->choice[9]->text(),
		GModel::current()->getFileName());
	FlGui::instance()->resetVisibility();
	FlGui::instance()->geoContext7->hide(0);
}


static void con_geometry_comSG_PS(Fl_Widget *w, void *data){
  FlGui::instance()->geoContext14P->hide(0);
  
  std::string str((const char*)data);
  if (str == "fast"){
    FlGui::instance()->geoContext14->show(0);
  }
  
  if (str == "advanced"){
    FlGui::instance()->geoContext14_1->show(0);
  }  

}

static void pop_com_define(Fl_Widget *w, void *data){
  std::string str((const char*)data);
  if (str == "define")
    FlGui::instance()->geoContext13_1->show(0);
  if (str == "define2")
    FlGui::instance()->geoContext13_4->show(0);
  if (str == "define_I")
    FlGui::instance()->geoContext13_7->show(0);
  //if (str == "assign")
  // FlGui::instance()->geoContext13_4->show(0);
}

static void con_geometry_comSG_Beam(Fl_Widget *w, void *data){
  FlGui::instance()->geoContext13_1->hide(0);
  FlGui::instance()->geoContext13_4->hide(0);
  FlGui::instance()->geoContext13_7->hide(0);
  
  std::string str((const char*)data);
  if (str == "fast"){
    FlGui::instance()->geoContext13_2->show(0);
  }
  if (str == "fast2"){
    FlGui::instance()->geoContext13_5->show(0);
  }
  if (str == "fast_I"){
    FlGui::instance()->geoContext13_8->show(0);
  }
  if (str == "advanced"){
    FlGui::instance()->geoContext13_3->show(0);
  }
  if (str == "advanced_I"){
    FlGui::instance()->geoContext13_9->show(0);
  }
  if (str == "advanced_B"){
    FlGui::instance()->geoContext13_6->show(0);
  } 

}


// visualize laminate model
static void conSG_Lam_visual(double **V_layers, int numlayers){
  std::string fileName = GModel::current()->getFileName();
  std::string lamgeo = fileName + ".msh";
  //std::string prefix = fileName.substr(0, fileName.length() - 4);
  std::ofstream wtempmsh;
  double temp;
  wtempmsh.open(lamgeo.c_str());
  wtempmsh << "$MeshFormat\n";
  wtempmsh << "2.2 0 8\n";
  wtempmsh << "$EndMeshFormat\n";
  wtempmsh << "$Nodes\n";
  wtempmsh << numlayers+1 << "\n";
  wtempmsh << "1 0 0 0 \n";
  for (int i = 1; i < numlayers+1; i++){
    temp = temp + V_layers[i-1][1];
    wtempmsh << i+1 << " " << 0 << " " << temp << " " << 0 << "\n";
  }
    
  wtempmsh << "$EndNodes\n";
  wtempmsh << "$Elements\n";
  wtempmsh << numlayers << "\n";
  for (int i = 0; i < numlayers; i++)
    wtempmsh << i+1 << " 1 2 " << V_layers[i][2] << " " << 2+V_layers[i][2] << " " << i+1 << " " << i+2 << "\n";
  wtempmsh <<"$EndElements\n";
  wtempmsh.close();
  //std::string lamview = prefix + "View" + ".geo";
  std::ofstream viewfile;
  viewfile.open(fileName.c_str(), std::ofstream::app);
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
  OpenProject(fileName);
  drawContext::global()->draw();
}

//define Ibeam array to pass laminate information
double Ibeam_para[6];
double Bbeam_para[8];

static void con_geometry_comSG_lam(Fl_Widget *w, void *data){  
  int beam = 0;
  std::string str((const char*)data);
  if (str == "rectangular") {
    beam = 1;
  } 
  if (str == "box") {
    beam = 2;
    change_boxlay_value(1);
  }
  if (str == "I") {
    beam = 3;
    change_Ilay_value(1);
  }
  std::string file_name = GModel::current()->getFileName();
  
    
  //Prof. Yu take layup parameter
  int flags_end = 0;
  int flags_sym = 0;
  int flags_n = 0;
  double tol_thick = 0;
  std::string layup = "";
  if (beam == 1)
    layup = FlGui::instance()->geoContext13_2->input[0]->value();
  else if (beam ==2)
    layup = FlGui::instance()->geoContext13_5->input[0]->value();
  else if (beam == 3)
    layup = FlGui::instance()->geoContext13_8->input[0]->value();
  else
    layup = FlGui::instance()->geoContext14->input[0]->value();
  if (layup.find("s") != std::string:: npos || layup.find("S") != std::string:: npos) flags_sym = 1;
  std::string temp = layup;
  size_t pos = temp.find("]");
  std::string check_end = temp.erase(0,pos+1);
  if (!check_end.empty()) flags_end = 1;
  for (int i = 0; i < layup.length(); i++){
    if (layup[i] == '/' || layup[i] == '[' || layup[i] == ']') layup[i] = ' ';
  }
  std::vector<std::string> all_layer;
  std::stringstream tran_ss(layup);
  //std::string temp;
  while (tran_ss >> temp)
    all_layer.push_back(temp);
  if (flags_end == 1 && all_layer.back() != "s" && all_layer.back() != "S") flags_n = 1;
  int lay_num = 0;
  std::string checkS = "";
  if (flags_n == 1){
    std::istringstream last_ss(all_layer.back());
    last_ss >> lay_num >> checkS;
    if (checkS != "" && checkS != "s" && checkS != "S"){
      fl_message("Wrong input parameters!");
      return;
    } 
  }
  
  //Prof. Yu, generate coordinates and layers
  std::string thick;
  if (beam == 1)
    thick = FlGui::instance()->geoContext13_2->input[1]->value();
  else if (beam ==2)
    thick = FlGui::instance()->geoContext13_5->input[1]->value();
  else if (beam ==3)
    thick = FlGui::instance()->geoContext13_8->input[1]->value();
  else
    thick = FlGui::instance()->geoContext14->input[1]->value();
  double thickness = atof(thick.c_str());
  double dt = thickness / 4;
  int elenum = 0;
  std::vector<std::string> layers;

  // if lamniate made up by even plies, calculate total thickness, number of plies
  // and laminate sequences
    // Case1: No repeated plies and symmetric
  if (flags_end == 0){
    tol_thick = all_layer.size()*thickness;
    elenum = tol_thick / thickness;
    for (int i = 0; i < elenum; i++)
      layers.push_back(all_layer[i]);
  }
  // Case2: Only symmetric
  if (flags_end == 1 && lay_num == 0 && flags_sym == 1){
    tol_thick = (all_layer.size()-1)*thickness * 2;
    elenum = tol_thick / thickness;
    for (int i = 0; i < elenum/2; i++)
      {
	layers.push_back(all_layer[i]);
      }
    for (int i = 0; i < elenum/2; i++)
      {
	layers.push_back(all_layer[elenum/2-i-1]);
      }
  }
    // Case3: Only repeated plies
    if (flags_end == 1 && lay_num != 0 && flags_sym == 0){
      tol_thick = (all_layer.size()-1) * lay_num * thickness;
      elenum = tol_thick / thickness;
      int kl = 0;
      while (kl < lay_num){
	for (int i = 0; i < elenum/lay_num; i++)
	  layers.push_back(all_layer[i]);
	kl = kl + 1;
      }
    }
    // Case4: Repeated and symmetric plies
    if (flags_end == 1 && lay_num != 0 && flags_sym == 1){
      tol_thick = (all_layer.size()-1) * lay_num * thickness * 2;
      elenum = tol_thick / thickness;
      int kl = 0;
      while (kl < lay_num){
	for (int i = 0; i < elenum/lay_num/2; i++)
	  layers.push_back(all_layer[i]);
	kl = kl + 1;
      }
      for (int i = 0; i < elenum / 2; i++)
	layers.push_back(layers[elenum/2-i-1]);
    }

    // if lamniate made up by odd plies
    /*
  if (readEO == "Odd plies" && flags_sym == 1){
    tol_thick = tol_thick - thickness;
    elenum = elenum - 1;
    for (int i = (elenum-1)/2; i < elenum; i++) layers[i] = layers[i+1];
    }*/

   // Read material properties
  std::string mname;
  if (beam == 1)
    mname = FlGui::instance()->geoContext13_2->choice[0]->text();
  else if (beam == 2)
    mname = FlGui::instance()->geoContext13_5->choice[0]->text();
  else if (beam == 3)
    mname = FlGui::instance()->geoContext13_8->choice[0]->text();
  else
    mname = FlGui::instance()->geoContext14->choice[0]->text();
  std::string idtemp;
  std::istringstream rmatid(mname);
  rmatid >> idtemp;

  
  double init_coor = -tol_thick / 2;
  std::vector<double> coor;
  int t = 0;
  while (t * dt < tol_thick){
    coor.push_back(-tol_thick/2 + t*dt);
    t++;
  }
  coor.push_back(tol_thick/2);

  // generate elements
  std::vector<std::string> nlayers;
  int layerFlags[elenum];
  nlayers.push_back(all_layer[0]);
  int tempn = all_layer.size();
  if (flags_end != 0) tempn = tempn - 1;
  for (int i = 0; i < tempn; i++)
    for (int j = 0; j < nlayers.size(); j++){
      if (all_layer[i] == nlayers[j]) break;
      if (j+1 == nlayers.size()) nlayers.push_back(all_layer[i]);
    }
  for (int i = 0; i < nlayers.size(); i++)
    for (int j = 0; j < layers.size(); j++)
      if (nlayers[i] == layers[j]) layerFlags[j] = i+1;

  int ele[elenum][5];
  for (int i = 0; i < elenum; i++){
    ele[i][0] = 4*i + 1;
    ele[i][1] = 4*i + 5;
    ele[i][2] = 4*i + 2;
    ele[i][3] = 4*i + 4;
    ele[i][4] = 4*i + 3;
  }

  
  std::string t4_name = file_name + ".t4";
  
  std::ofstream t4_is;
  if (beam != 0){
    change_layname_value(1);
    int lam_index = layname_flags;  
    std::stringstream convert;
    convert << lam_index;
    std::string index;
    convert >> index;
    //std::string Laname = "Laminate(" + index + "):" + beamflags;
    std::string Laname = "Laminate(" + index + ") ";
    t4_is.open(t4_name.c_str(),std::ofstream::app);
    if (beam == 2){
      Bbeam_para[2*boxlay_flags-2] = elenum*thickness;
      Bbeam_para[2*boxlay_flags-1] = elenum;
      for (int i = 1; i < 2*boxlay_flags-2; i+=2){
	if (Bbeam_para[i] != Bbeam_para[2*boxlay_flags-1]){
	  fl_message("Box laminate beam must have same layer numbers!");
	  change_boxlay_value(-1);
	  change_layname_value(-1);
	  return;
	}
      }
    }
    t4_is << Laname << " " << elenum*thickness << " " << elenum <<"\n";
    if (beam == 3){
      Ibeam_para[2*Ilay_flags-2] = elenum*thickness;
      Ibeam_para[2*Ilay_flags-1] = elenum;
    }
    
    for (int i = 0; i < elenum; i++)
      t4_is << (i+1)*thickness << " " << layerFlags[i] << "\n";
    if (beam == 1)
      t4_is << "layerID_" << Laname << "\n";
    if (beam ==2)
      t4_is << "layerID_" << FlGui::instance()->geoContext13_5->lay_name->value() << "\n";
    if (beam ==3)
      t4_is << "layerID_" << FlGui::instance()->geoContext13_8->lay_name->value() << "\n";
    for (int i = 0; i < nlayers.size(); i++)
      t4_is << i+1 << " " << idtemp << " " << nlayers[i] << "\n";
    t4_is << "//" << Laname << "\n";
    t4_is.close();

    if (Ilay_flags == 1){
      FlGui::instance()->geoContext13_8->lay_name->value("Up edge of I beam");
      fl_message("Bottom edge of I beam has been generated !");
    }
    else if (Ilay_flags == 2){
      FlGui::instance()->geoContext13_8->lay_name->value("middle edge of I beam");
      fl_message("Up edge of I beam has been generated !");
    }
    else if (Ilay_flags == 3){
      FlGui::instance()->geoContext13_8->lay_name->value("Bottom edge of I beam");
      fl_message("I beam has been generated !");
      FlGui::instance()->geoContext13_8->hide(0);
    }

    
    //FlGui::instance()->geoContext13_2->input[2]->value("");
    if (boxlay_flags == 1){
      FlGui::instance()->geoContext13_5->lay_name->value("Left edge of box beam");
      fl_message("up edge of box beam has been generated !");
    }
    else if (boxlay_flags == 2){
      FlGui::instance()->geoContext13_5->lay_name->value("Bottom edge of box beam");
      fl_message("left edge of box beam has been generated !");
    }
    else if (boxlay_flags == 3){
      FlGui::instance()->geoContext13_5->lay_name->value("Right edge of box beam");
      fl_message("Bottom edge of box beam has been generated !");
    }
    else if (boxlay_flags ==4)
      {FlGui::instance()->geoContext13_5->lay_name->value("Up edge of box beam");
	fl_message("box beam layup has been defined");
	FlGui::instance()->geoContext13_5->hide(0);
      }
    if (beam == 1){
      fl_message("Laminate beam has been generated !");
      FlGui::instance()->geoContext13_2->hide(0);
    }
    beam = 0;
    return;
  }
  
  len4SG = tol_thick;
  std::string t3_name = file_name + ".t3";
  std::ofstream t3_is;
  t3_is.open(t3_name.c_str());
  //for (int i = 0; i < all_layer.size(); i++)
  //t3_is << all_layer[i] << "\n";
  t3_is << 1 << " " << coor.size() << " " << elenum << " " << 1 << " " << 0 << " " << nlayers.size() << "    # nSG nnode nelem nmate nslave nlayer\n\n";

  for (int i = 0; i < coor.size(); i++)
    t3_is << i+1 << " " << coor[i] << "\n";
  t3_is << "\n\n";
  for (int i = 0; i < elenum; i++)
    t3_is << i+1 << " " <<  layerFlags[i] << " " << ele[i][0] << " " << ele[i][1] << " " << ele[i][2] << " " << ele[i][3] << " " << ele[i][4] << "\n";
  t3_is << "\n\n";
  //for (int i = 0; i < nlayers.size(); i++)
  //t3_is << nlayers[i] << "\n";
  //for (int i = 0; i < elenum; i++)
  //t3_is << layers[i] << "\n";
  //for (int i = 0; i < elenum; i++)
  //t3_is << layerFlags[i] << "\n";

 
  for (int i = 0; i < nlayers.size(); i++)
    t3_is << i+1 << " " << idtemp << " " << nlayers[i] << "\n";
  t3_is << "\n\n";

  t3_is.close();

  double **visu = 0;
  visu = new double *[elenum];
  for (int i = 0; i < elenum; i++)
    visu[i] = new double[3];
  for (int i = 0; i <elenum; i++){
    visu[i][0] = i+1;
    visu[i][1] = thickness;
    visu[i][2] = layerFlags[i];
  }
   
  conSG_Lam_visual(visu, elenum); 
  for (int i = 0; i < elenum; i++)
    delete [] visu[i];
  delete [] visu;

    
  fl_message("Laminate input file for SwiftComp has been generated !");
    FlGui::instance()->geoContext14->hide(0);
}



// Prof. Yu, add advanced laminate function
static void con_geometry_comSG_lam2(Fl_Widget *w, void *data){
  int beam = 0;
  //std::string beamflags = FlGui::instance()->geoContext13_-3geoContext13_3>input[16]->value();
  //BLname.set_name(beamflags);
  double inputData[8][3];
  std::string temp1, temp2, temp3;
  int k=0;
  std::string str((const char*)data);
  if (str == "Rec") {
    beam = 1;
  }
  if (str == "Ibeam"){
    beam = 3;
    change_Ilay_value(1);
  }
  if (str == "box") {
    beam = 2;
    change_boxlay_value(1);
  }
  
  if (beam == 0){
    k = 0;
    for (int i = 0; i < 8; i++){
      temp1 = FlGui::instance()->geoContext14_1->input[2*i]->value();
      temp2 = FlGui::instance()->geoContext14_1->input[2*i+1]->value();
      temp3 = FlGui::instance()->geoContext14_1->choice[i]->text();
      if (temp1 != "" && temp2 != "" && temp3 == "Select material:") fl_message("Please select material-id !");
      if (temp1 == "" || temp2 == "" || temp3 == "") break;
      std::istringstream iss(temp3);
      iss >> temp3;
      inputData[i][0] = atof(temp1.c_str());
      inputData[i][1] = atof(temp2.c_str());
      inputData[i][2] = atof(temp3.c_str());
      k = i+1;
    }
  }
  if (beam == 1){
    k = 0;
    for (int i = 0; i < 8; i++){
      temp1 = FlGui::instance()->geoContext13_3->input[2*i]->value();
      temp2 = FlGui::instance()->geoContext13_3->input[2*i+1]->value();
      temp3 = FlGui::instance()->geoContext13_3->choice[i]->text();
      if (temp1 != "" && temp2 != "" && temp3 == "Select material:") fl_message("Please select material-id !");
      if (temp1 == "" || temp2 == "" || temp3 == "") break;
      std::istringstream iss(temp3);
      iss >> temp3;
      inputData[i][0] = atof(temp1.c_str());
      inputData[i][1] = atof(temp2.c_str());
      inputData[i][2] = atof(temp3.c_str());
      k = i+1;
    }
  }
  if (beam == 2){
    k = 0;
    for (int i = 0; i < 8; i++){
      temp1 = FlGui::instance()->geoContext13_6->input[2*i]->value();
      temp2 = FlGui::instance()->geoContext13_6->input[2*i+1]->value();
      temp3 = FlGui::instance()->geoContext13_6->choice[i]->text();
      if (temp1 != "" && temp2 != "" && temp3 == "Select material:") fl_message("Please select material-id !");
      if (temp1 == "" || temp2 == "" || temp3 == "") break;
      std::istringstream iss(temp3);
      iss >> temp3;
      inputData[i][0] = atof(temp1.c_str());
      inputData[i][1] = atof(temp2.c_str());
      inputData[i][2] = atof(temp3.c_str());
      k = i+1;
    }
  }
  if (beam == 3){
    k = 0;
    for (int i = 0; i < 8; i++){
      temp1 = FlGui::instance()->geoContext13_9->input[2*i]->value();
      temp2 = FlGui::instance()->geoContext13_9->input[2*i+1]->value();
      temp3 = FlGui::instance()->geoContext13_9->choice[i]->text();
      if (temp1 != "" && temp2 != "" && temp3 == "Select material:") fl_message("Please select material-id !");
      if (temp1 == "" || temp2 == "" || temp3 == "") break;
      std::istringstream iss(temp3);
      iss >> temp3;
      inputData[i][0] = atof(temp1.c_str());
      inputData[i][1] = atof(temp2.c_str());
      inputData[i][2] = atof(temp3.c_str());
      k = i+1;
    }
  }
  
  // calcualte total thickness of laminate
  double tol_thickness = 0;
  for (int i = 0; i < k; i++)
    tol_thickness = tol_thickness + inputData[i][0];
  //std::cout << tol_thickness << std::endl;
  std::vector<double> coor1;
  double dt;
  double temp4 = - tol_thickness / 2;
  coor1.push_back(-tol_thickness/2);
  for (int i = 0; i < k; i++){
    dt = inputData[i][0]/4;
    for (int j = 1; j < 5; j++){
      temp4 = temp4  + dt;
      coor1.push_back(temp4);
    }
  }

   // generate element connectivity
  int ele[k][5];
  for (int i = 0; i < k; i++){
    ele[i][0] = 4*i + 1;
    ele[i][1] = 4*i + 5;
    ele[i][2] = 4*i + 2;
    ele[i][3] = 4*i + 4;
    ele[i][4] = 4*i + 3;
  }

// generate materials assignment to each layers
  std::vector<std::vector<double> > diff_layers;
  std::vector<double> diff_layer1;
  int layersFlags[k];
  diff_layer1.push_back(inputData[0][1]);
  diff_layer1.push_back(inputData[0][2]);
  diff_layers.push_back(diff_layer1);
  for (int i = 0; i < k; i++)
    for (int j = 0; j < diff_layers.size(); j++){
      if (fabs(inputData[i][1] - diff_layers[j][0]) < 1.0e-3 && fabs(inputData[i][2] - diff_layers[j][1]) < 1.0e-3) break;
      if (j+1 == diff_layers.size()){
	 diff_layer1.clear();
	 diff_layer1.push_back(inputData[i][1]);
	 diff_layer1.push_back(inputData[i][2]);
	 diff_layers.push_back(diff_layer1);
	}

    }
  for (int i = 0; i < diff_layers.size(); i++)
    for (int j = 0; j < k; j++)
      if (fabs(diff_layers[i][0]-inputData[j][1]) < 1.0e-3 && fabs(diff_layers[i][1]-inputData[j][2]) < 1.0e-3) layersFlags[j] = i + 1;


  std::string file_name = GModel::current()->getFileName();
  std::string t4_name = file_name + ".t4";
  
  std::ofstream t4_is;
  if (beam != 0){
    change_layname_value(1);
    int lam_index = layname_flags;  
    std::stringstream convert;
    convert << lam_index;
    std::string index;
    convert >> index;
    std::string Laname = "Laminate(" + index + ") ";
    for (int i = 0; i < k; i++){
      if (fabs(inputData[0][0]-inputData[i][0]) > 1e-5) {
	fl_message("Laminar thickness is constant!");
	return;
      }
    }
    if (beam == 2){
      Bbeam_para[2*boxlay_flags-2] = k*inputData[0][0];
      Bbeam_para[2*boxlay_flags-1] = k;
      for (int i = 1; i < 2*boxlay_flags-2; i+=2){
	if (Bbeam_para[i] != Bbeam_para[2*boxlay_flags-1]){
	  fl_message("Box laminate beam must have same layer numbers!");
	  change_boxlay_value(-1);
	  change_layname_value(-1);
	  return;
	}
      }
    }
    t4_is.open(t4_name.c_str(),std::ofstream::app);
    t4_is << Laname << " " << k*inputData[0][0] << " " << k << "\n";
    if (beam == 3){
      Ibeam_para[2*Ilay_flags-2] = k*inputData[0][0];
      Ibeam_para[2*Ilay_flags-1] = k;
    }
    for (int i = 0; i < k; i++)
      t4_is << (i+1)*inputData[0][0] << " " << layersFlags[i] << "\n";
    if (beam == 1)
      t4_is << "layerID_" << Laname << "\n";
    if (beam == 2)
      t4_is << "layerID_" << FlGui::instance()->geoContext13_6->lay_name->value() << "\n";
    if (beam == 3)
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
    beam = 0;
    //FlGui::instance()->geoContext13_3->input[16]->value("");
    return;
  }



  
  std::ifstream geofile(file_name.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string endread = "{};";
  int setflags = 0;
  int matnum = 0;
  std::vector<std::string> matread;
  while (getline(geofile, readoutline)) {
    if (readoutline.find(point) != std::string::npos){
      size_t pos = readoutline.find(point);
      readoutline.erase(0, pos + 16);
      setflags = 1;
      matnum++;
    }
    if (readoutline.find(endread) != std::string::npos){
      setflags = 0;
      matread.push_back("");
    } 
    if (setflags == 1) matread.push_back(readoutline);
  }
  geofile.close();

  
  len4SG = tol_thickness;
  std::string t3_name = file_name + ".t3";
  std::ofstream t3_is;
  t3_is.open(t3_name.c_str());
 
  t3_is << 1 << " " << coor1.size() << " " << k << " " << matnum << " " << 0 << " " << diff_layers.size() << "    # nSG nnode nelem nmate nslave nlayer\n\n";

   for (int i = 0; i < coor1.size(); i++){
    t3_is << i+1 << " " << coor1[i] << "\n";
  }
   t3_is << "\n\n";

  for (int i = 0; i < k; i++)
    t3_is << i+1 << " " << layersFlags[i] << " " << ele[i][0] << " " << ele[i][1] << " " << ele[i][2] << " " << ele[i][3] << " " << ele[i][4] << "\n";
  t3_is << "\n\n";

  for (int i = 0; i < diff_layers.size(); i++)
    t3_is << i+1 << "  " << diff_layers[i][1] << "  " << diff_layers[i][0] << "\n";
  t3_is << "\n\n";
  /*
  for (int i = 0; i < matread.size(); i++){
    if (matread[i] == "")
      break;
    else
      t3_is << matread[i] << "\n";
  }
  
  
  t3_is << "\n\n";
  t3_is << tol_thickness << "\n";*/

  t3_is.close();

  double **visu = 0;
  visu = new double *[k];
  for (int i = 0; i < k; i++)
    visu[i] = new double[3];
  for (int i = 0; i < k; i++){
    visu[i][0] = i+1;
    visu[i][1] = inputData[i][0];
    visu[i][2] = layersFlags[i];
  }
   
  conSG_Lam_visual(visu, k); 
  for (int i = 0; i < k; i++)
    delete [] visu[i];
  delete [] visu;
  
  fl_message("Laminate input file for SwiftComp has been generated !");
   FlGui::instance()->geoContext14_1->hide(0);
  
}


static void comSG_lam_upload(Fl_Widget* w, void* data){
  FlGui::instance()->geoContext13_1->hide(0);
  Fl_File_Chooser chooser(".",                        // directory
                            "*",                        // filter
                            Fl_File_Chooser::MULTI,     // chooser type
                            "Title Of Chooser");        // title
    chooser.show();

    // Block until user picks something.
    //     (The other way to do this is to use a callback())
    //
    while(chooser.shown())
        { Fl::wait(); }

    // User hit cancel?
    if ( chooser.value() == NULL )
        { fprintf(stderr, "(User hit 'Cancel')\n"); return; }
    std::string fileName = GModel::current()->getFileName();
    std::ifstream geofile(fileName.c_str());
    std::string readoutline;
    std::string point = "Physical Point(\"";
    std::vector<std::string> mindex;
    std::string minput;
    while (getline(geofile, readoutline)){
      if (readoutline.find(point) != std::string::npos){
	size_t pos = readoutline.find(point);
        readoutline.erase(0, pos + 16);
        std::istringstream iss(readoutline);
        iss >> minput;
        mindex.push_back(minput);
      }
    }
    geofile.close();
    std::string inpName = chooser.value();
    char sep = '/';
    char sep2 = '.';
    size_t pos = inpName.rfind(sep, inpName.length());
    std::string beamflags = inpName.substr(pos+1, inpName.length()-pos);
    size_t pos2 = beamflags.rfind(sep2, beamflags.length());
    beamflags = beamflags.erase(pos2, beamflags.length()-pos2);
    //BLname.set_name(beamflags);
    int matnum = mindex.size();
    int BOP;
    std::string str((const char*)data);
    if (str == "plate") BOP = 1;        
    if (str == "Rbeam") BOP = 2;
    if (str == "Bbeam") BOP = 3;
    if (str == "Ibeam") BOP = 4;
    change_layname_value(1);
    LamInput2(chooser.value(), fileName, matnum, BOP, layname_flags,len4SG);
    if (BOP ==1)
      fl_message("Laminate input file for SwiftComp has been generated !");
}


// Prof. Yu, add common beam cross section
static void comSG_Beam_Reg(Fl_Widget* w, void* data){
  std::string str((const char*)data);
  if (str == "box"){
    double w,h,matid;
    double t1,t2,t3,t4;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[0]->value();
    w = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[1]->value();
    h = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[2]->value();
    t1 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[20]->value();
    t2 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[21]->value();
    t3 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[22]->value();
    t4 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->choice[0]->text();
    std::istringstream iss(temp);
    iss >> temp;
    matid = atof(temp.c_str());
    if (matid == 0) {
      fl_message("Please select material-id!");
      return;
    }
    reg_box_beam(w,h,t1,t2,t3,t4,matid,GModel::current()->getFileName());
  }
  
  if (str == "I"){
    double h,b1,b2,t1,t2,t3,matid;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[3]->value();
    h = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[4]->value();
    b1 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[5]->value();
    b2 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[6]->value();
    t1 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[7]->value();
    t2 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[8]->value();
    t3 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->choice[1]->text();
    std::istringstream iss(temp);
    iss >> temp;
    matid = atof(temp.c_str());
    if (matid == 0) {
      fl_message("Please select material-id!");
      return;
    }
    reg_I_beam(h,b1,b2,t1,t2,t3,matid,GModel::current()->getFileName());
  }

  if (str == "rec"){
    double w,h,matid;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[9]->value();
    w = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[10]->value();
    h = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->choice[2]->text();
    std::istringstream iss(temp);
    iss >> temp;
    matid = atof(temp.c_str());
    if (matid == 0) {
      fl_message("Please select material-id!");
      return;
    }
    reg_rec_beam(w,h,matid,GModel::current()->getFileName());
  }

  if (str == "Cir"){
    double r,matid;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[15]->value();
    r = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->choice[3]->text();
    std::istringstream iss(temp);
    iss >> temp;
    matid = atof(temp.c_str());
    if (matid == 0) {
      fl_message("Please select material-id!");
      return;
    }
    reg_cir_beam(r,matid,GModel::current()->getFileName());
  }

  if (str == "pipe"){
    double r,t,matid;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[16]->value();
    r = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[17]->value();
    t = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->choice[4]->text();
    std::istringstream iss(temp);
    iss >> temp;
    matid = atof(temp.c_str());
    if (matid == 0) {
      fl_message("Please select material-id!");
      return;
    }
    reg_pipe_beam(r,t,matid,GModel::current()->getFileName());
  }
  
  if (str == "Crec"){
    double w,h;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[14]->value();
    w = atof(temp.c_str());   
    comp_rec_beam(w, GModel::current()->getFileName(),layname_flags);
  }

  if (str == "Cbox"){
    double w, h;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[18]->value();
    w = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[19]->value();
    h = atof(temp.c_str()); 
    comp_box_beam(w,h, GModel::current()->getFileName());
  }
  
  if (str == "C_I"){
    double h,b1,b2;
    std::string temp;
    temp = FlGui::instance()->geoContext13->input[23]->value();
    h = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[24]->value();
    b1 = atof(temp.c_str());
    temp = FlGui::instance()->geoContext13->input[25]->value();
    b2 = atof(temp.c_str());   
    comp_I_beam(h,b1,b2, GModel::current()->getFileName());
  }

  
  FlGui::instance()->resetVisibility();
  FlGui::instance()->geoContext13->hide(0);
  OpenProject(GModel::current()->getFileName());
  drawContext::global()->draw();
  Msg::StatusBar(true, "Done generating beam section!");

}






//Prof. Yu

static void con_geometry_define_point_cb(Fl_Widget *w, void *data)
{
  add_point(GModel::current()->getFileName(),
            FlGui::instance()->geoContext->input[2]->value(),
            FlGui::instance()->geoContext->input[3]->value(),
            FlGui::instance()->geoContext->input[4]->value(),
            FlGui::instance()->geoContext->input[5]->value());
  FlGui::instance()->resetVisibility();
  GModel::current()->setSelection(0);
  SetBoundingBox();
  drawContext::global()->draw();
}

static void con_geometry_snap_cb(Fl_Widget *w, void *data)
{
  CTX::instance()->geom.snap[0] = FlGui::instance()->geoContext->value[0]->value();
  CTX::instance()->geom.snap[1] = FlGui::instance()->geoContext->value[1]->value();
  CTX::instance()->geom.snap[2] = FlGui::instance()->geoContext->value[2]->value();
}

geometryContextWindow::geometryContextWindow(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 31 * FL_NORMAL_SIZE;
  int height = 4 * WB + 8 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
                          "Contextual Geometry Definitions");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    // 0: Parameter
    /*{
      group[0] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Parameter");
      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW, BH, "Name");
      input[0]->value("lc");
      input[1] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW, BH, "Value");
      input[1]->value("0.1");
      input[24] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW, BH, "Label");
      input[24]->value("");
      input[25] = new Fl_Input(2 * WB, 2 * WB + 4 * BH, IW, BH, "Path");
      input[25]->value("Parameters");
      for(int i = 0; i < 2; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for(int i = 24; i < 26; i++) input[i]->align(FL_ALIGN_RIGHT);
      {
        Fl_Return_Button *o = new Fl_Return_Button
          (width - BB - 2 * WB, 2 * WB + 7 * BH, BB, BH, "Add");
        o->callback(con_geometry_define_parameter_cb);
      }
      group[0]->end();
    }*/
    // 1: Point  // Prof. YU
    {
      group[0] = new Fl_Group //Prof. Wenbin Yu
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Point");
      input[2] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW, BH, "X coordinate");
      input[2]->value("0");
      input[3] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW, BH, "Y coordinate");
      input[3]->value("0");
      input[4] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW, BH, "Z coordinate");
      input[4]->value("0");
      input[5] = new Fl_Input(2 * WB, 2 * WB + 4 * BH, IW, BH, "Prescribed mesh element size at point");
      input[5]->value("1.0");
      for(int i = 2; i < 6; i++) {
        input[i]->align(FL_ALIGN_RIGHT);
      }
      value[0] = new Fl_Value_Input(2 * WB, 2 * WB + 5 * BH, IW/3, BH);
      value[1] = new Fl_Value_Input(2 * WB + IW/3, 2 * WB + 5 * BH, IW/3, BH);
      value[2] = new Fl_Value_Input(2 * WB + 2*IW/3, 2 * WB + 5 * BH, IW/3, BH,
                                    "Snapping grid spacing");
      for(int i = 0; i < 3; i++) {
        value[i]->align(FL_ALIGN_RIGHT);
        value[i]->callback(con_geometry_snap_cb);
      }
      {
        Fl_Return_Button *o = new Fl_Return_Button
          (width - BB - 2 * WB, 2 * WB + 7 * BH, BB, BH, "Add");
        o->callback(con_geometry_define_point_cb);
      }
      group[0]->end();
    }
    // 2: Translation
    {
      group[1] = new Fl_Group            // Prof. Yu
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Translation");
      input[6] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW, BH, "X component");
      input[6]->value("0");
      input[7] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW, BH, "Y component");
      input[7]->value("0");
      input[8] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW, BH, "Z component");
      input[8]->value("1");
      for(int i = 6; i < 9; i++) {
        input[i]->align(FL_ALIGN_RIGHT);
      }
      group[1]->end();
    }
    // 3: Rotation
    {
      group[2] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Rotation");
      input[9] = new Fl_Input
        (2 * WB, 2 * WB + 1 * BH, IW, BH, "X coordinate of an axis point");
      input[9]->value("0");
      input[10] = new Fl_Input
        (2 * WB, 2 * WB + 2 * BH, IW, BH, "Y coordinate of an axis point");
      input[10]->value("0");
      input[11] = new Fl_Input
        (2 * WB, 2 * WB + 3 * BH, IW, BH, "Z coordinate of an axis point");
      input[11]->value("0");
      input[12] = new Fl_Input
        (2 * WB, 2 * WB + 4 * BH, IW, BH, "X component of axis direction");
      input[12]->value("0");
      input[13] = new Fl_Input
        (2 * WB, 2 * WB + 5 * BH, IW, BH, "Y component of axis direction");
      input[13]->value("1");
      input[14] = new Fl_Input
        (2 * WB, 2 * WB + 6 * BH, IW, BH, "Z component of axis direction");
      input[14]->value("0");
      input[15] = new Fl_Input
        (2 * WB, 2 * WB + 7 * BH, IW, BH, "Angle in radians");
      input[15]->value("Pi/4");
      for(int i = 9; i < 16; i++) {
        input[i]->align(FL_ALIGN_RIGHT);
      }
      group[2]->end();
    }
    // 4: Scale
    {
      group[3] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Scale");
      input[16] = new Fl_Input
        (2 * WB, 2 * WB + 1 * BH, IW, BH, "X component of direction");
      input[16]->value("0");
      input[17] = new Fl_Input
        (2 * WB, 2 * WB + 2 * BH, IW, BH, "Y component of direction");
      input[17]->value("0");
      input[18] = new Fl_Input
        (2 * WB, 2 * WB + 3 * BH, IW, BH, "Z component of direction");
      input[18]->value("0");
      input[19] = new Fl_Input
        (2 * WB, 2 * WB + 4 * BH, IW, BH, "Factor");
      input[19]->value("0.5");
      for(int i = 16; i < 20; i++) {
        input[i]->align(FL_ALIGN_RIGHT);
      }
      group[3]->end();
    }
    // 5: Symmetry
    {
      group[4] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Symmetry");
      input[20] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW, BH, "A");
      input[20]->value("1");
      input[21] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW, BH, "B");
      input[21]->value("0");
      input[22] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW, BH, "C");
      input[22]->value("0");
      input[23] = new Fl_Input(2 * WB, 2 * WB + 4 * BH, IW, BH, "D");
      input[23]->value("1");
      for(int i = 20; i < 24; i++) {
        input[i]->align(FL_ALIGN_RIGHT);
      }
      group[4]->end();
    }
    o->end();
  }

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow::show(int pane)
{
  for(int i = 0; i < 5; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}


//Prof. Wenbin Yu
geometryContextWindow1::geometryContextWindow1(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 70 * FL_NORMAL_SIZE;
  int height = 4 * WB + 12 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
                          "Material Properties");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);


    //Prof. Wenbin Yu
    // 1: Add Isotropic Material                               //Prof. Wenbin Yu
    {
      //group[0] = new Fl_Group                                                  //Prof. Wenbin Yu
      group[0] = new Fl_Group                                              //Prof. Wenbin Yu
        //(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Parameter");           //Prof. Wenbin Yu
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Isotropic");          //Prof. Wenbin Yu

	  //Prof. Wenbin Yu
      input[39] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW/2, BH, "Material ID number");
      input[39]->value("1");
      input[40] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW,  BH, "Material Name");
      input[40]->value("MAT1");
      input[34] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW/2, BH, "E");
      input[34]->value("0");
      input[35] = new Fl_Input(2 * WB + IW, 2 * WB + 2 * BH, IW/2, BH, "v");
      input[35]->value("0");

      input[36] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW/2, BH, "rho");
      input[36]->value("0");
      input[37] = new Fl_Input(2 * WB + IW, 2 * WB + 3 * BH, IW/2, BH, "Ti");
      input[37]->value("0");

      //Prof Yu add thermal parameters
      input[45] = new Fl_Input(2 * WB, 2 * WB + 5 * BH, IW/2, BH, "alpha");
      input[45]->value("0");
      input[46] = new Fl_Input(2 * WB + IW, 2 * WB + 5 * BH, IW/2, BH, "Ce");
      input[46]->value("0");

      //Prof. Wenbin Yu
      for(int i = 45; i < 47; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for(int i = 39; i < 41; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for(int i = 34; i < 38; i++)   input[i]->align(FL_ALIGN_RIGHT);

      {
        Fl_Return_Button *o = new Fl_Return_Button
          (width - 2 * BB - 5 * WB, 2 * WB + 11 * BH, BB, BH, "Add");    //Prof. Wenbin Yu
        o->callback(con_geometry_define_parameter_cb2);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }
      //group[0]->end();              //Prof. Wenbin Yu
	  group[0]->end();                //Prof. Wenbin Yu
    }

    // 2: Add Orthotropic Material                                         //Prof. Wenbin Yu
    {
      group[1] = new Fl_Group                                               //Prof. Wenbin Yu
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Orthotropic");        //Prof. Wenbin Yu


      //Prof. Wenbin Yu
      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW / 2, BH, "Material ID number");
      input[0]->value("1");
      input[42] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW, BH, "Material Name");
      input[42]->value("MAT1");
      input[1] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW / 2, BH, "E1");
      input[1]->value("0");
      input[24] = new Fl_Input(2 * WB + IW, 2 * WB + 2 * BH, IW / 2, BH, "E2");
      input[24]->value("0");
      input[25] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 2 * BH, IW / 2, BH, "E3");
      input[25]->value("0");
      input[26] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW / 2, BH, "G12");
      input[26]->value("0");
      input[27] = new Fl_Input(2 * WB + IW, 2 * WB + 3 * BH, IW / 2, BH, "G13");
      input[27]->value("0");
      input[28] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 3 * BH, IW / 2, BH, "G23");
      input[28]->value("0");
      input[29] = new Fl_Input(2 * WB, 2 * WB + 4 * BH, IW / 2, BH, "v12");
      input[29]->value("0");
      input[30] = new Fl_Input(2 * WB + IW, 2 * WB + 4 * BH, IW / 2, BH, "v13");
      input[30]->value("0");
      input[31] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 4 * BH, IW / 2, BH, "v23");
      input[31]->value("0");
      input[32] = new Fl_Input(2 * WB, 2 * WB + 5 * BH, IW / 2, BH, "rho");
      input[32]->value("0");
      input[33] = new Fl_Input(2 * WB + IW, 2 * WB + 5 * BH, IW / 2, BH, "Ti");
      input[33]->value("0");
      
      input[47] = new Fl_Input(2 * WB, 2 * WB + 7 * BH, IW/2, BH, "alpha11");
      input[47]->value("0");
      input[48] = new Fl_Input(2 * WB + IW, 2 * WB + 7 * BH, IW/2, BH, "alpha22");
      input[48]->value("0");
      input[49] = new Fl_Input(2 * WB + 2*IW, 2 * WB + 7 * BH, IW/2, BH, "alpha33");
      input[49]->value("0");
      input[50] = new Fl_Input(2 * WB + 3*IW, 2 * WB + 7 * BH, IW/2, BH, "Ce");
      input[50]->value("0");

      for (int i = 47; i < 51; i++)   input[i]->align(FL_ALIGN_RIGHT);
      //Prof. Wenbin Yu
      for (int i = 0; i < 2; i++)   input[i]->align(FL_ALIGN_RIGHT);
      input[42]->align(FL_ALIGN_RIGHT);
      //for(int i = 24; i < 26; i++) input[i]->align(FL_ALIGN_RIGHT);   //Prof. Wenbin Yu
      for (int i = 24; i < 34; i++) input[i]->align(FL_ALIGN_RIGHT);    //Prof. Wenbin Yu
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 2 * WB + 11 * BH, BB, BH, "Add");    //Prof. Wenbin Yu
	o->callback(con_geometry_define_parameter_cb1);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }

      //group[0]->end();              //Prof. Wenbin Yu
      group[1]->end();                //Prof. Wenbin Yu
    }
    //Prof. Wenbin Yu
    // 3: Add Anisotropic Material                                 //Prof. Wenbin Yu
    {
	  group[2] = new Fl_Group                     //Prof. Wenbin Yu
        //(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Parameter");       //Prof. Wenbin Yu
	    (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Anisotropic");       //Prof. Wenbin Yu

	  //Prof. Wenbin Yu
	  input[41] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW/2, BH, "Material ID number");
      input[41]->value("1");
      input[43] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW, BH, "Material Name");
      input[43]->value("MAT1");
      input[2] = new Fl_Input(2 * WB + IW/2-IW/2, 2 * WB + 2 * BH, IW/2, BH, "C11");
      input[2]->value("0");
      input[3] = new Fl_Input(2 * WB + IW*3/2-IW/2, 2 * WB + 2 * BH, IW/2, BH, "C12");
      input[3]->value("0");
      input[4] = new Fl_Input(2 * WB + IW*5/2-IW/2, 2 * WB + 2 * BH, IW/2, BH, "C13");
      input[4]->value("0");
      input[5] = new Fl_Input(2 * WB + IW*7/2-IW/2, 2 * WB + 2 * BH, IW/2, BH, "C14");
      input[5]->value("0");
      input[6] = new Fl_Input(2 * WB + IW*9/2-IW/2, 2 * WB + 2 * BH, IW/2, BH, "C15");
      input[6]->value("0");
      input[7] = new Fl_Input(2 * WB + IW*11/2-IW/2, 2 * WB + 2 * BH, IW/2, BH, "C16");
      input[7]->value("0");

      input[8] = new Fl_Input(2 * WB + IW*3/2-IW/2, 2 * WB + 3 * BH, IW/2, BH, "C22");
      input[8]->value("0");
      input[9] = new Fl_Input(2 * WB + IW*5/2-IW/2, 2 * WB + 3 * BH, IW/2, BH, "C23");
      input[9]->value("0");
      input[10] = new Fl_Input(2 * WB + IW*7/2-IW/2, 2 * WB + 3 * BH, IW/2, BH, "C24");
      input[10]->value("0");
      input[11] = new Fl_Input(2 * WB + IW*9/2-IW/2, 2 * WB + 3 * BH, IW/2, BH, "C25");
      input[11]->value("0");
      input[12] = new Fl_Input(2 * WB + IW*11/2-IW/2, 2 * WB + 3 * BH, IW/2, BH, "C26");
      input[12]->value("0");

      input[13] = new Fl_Input(2 * WB + IW*5/2-IW/2, 2 * WB + 4 * BH, IW/2, BH, "C33");
      input[13]->value("0");
      input[14] = new Fl_Input(2 * WB + IW*7/2-IW/2, 2 * WB + 4 * BH, IW/2, BH, "C34");
      input[14]->value("0");
      input[15] = new Fl_Input(2 * WB + IW*9/2-IW/2, 2 * WB + 4 * BH, IW/2, BH, "C35");
      input[15]->value("0");
      input[16] = new Fl_Input(2 * WB + IW*11/2-IW/2, 2 * WB + 4 * BH, IW/2, BH, "C36");
      input[16]->value("0");

      input[17] = new Fl_Input(2 * WB + IW*7/2-IW/2, 2 * WB + 5 * BH, IW/2, BH, "C44");
      input[17]->value("0");
      input[18] = new Fl_Input(2 * WB + IW*9/2-IW/2, 2 * WB + 5 * BH, IW/2, BH, "C45");
      input[18]->value("0");
      input[19] = new Fl_Input(2 * WB + IW*11/2-IW/2, 2 * WB + 5 * BH, IW/2, BH, "C46");
      input[19]->value("0");

      input[20] = new Fl_Input(2 * WB + IW*9/2-IW/2, 2 * WB +  6 * BH, IW/2, BH, "C55");
      input[20]->value("0");
      input[21] = new Fl_Input(2 * WB + IW*11/2-IW/2, 2 * WB + 6 * BH, IW/2, BH, "C56");
      input[21]->value("0");

      input[22] = new Fl_Input(2 * WB + IW*11/2-IW/2, 2 * WB + 7 * BH, IW/2, BH, "C66");
      input[22]->value("0");

      input[23] = new Fl_Input(2 * WB + IW/2-IW/2, 2 * WB + 8 * BH, IW/2, BH, "rho");
      input[23]->value("0");
      input[38] = new Fl_Input(2 * WB + IW*3/2-IW/2, 2 * WB + 8 * BH, IW/2, BH, "Ti");
      input[38]->value("0");

      input[51] = new Fl_Input(2 * WB, 2 * WB + 9 * BH, IW/2, BH, "alpha11");
      input[51]->value("0");
      input[52] = new Fl_Input(2 * WB + IW, 2 * WB + 9 * BH, IW/2, BH, "alpha22");
      input[52]->value("0");
      input[53] = new Fl_Input(2 * WB + 2*IW, 2 * WB + 9 * BH, IW/2, BH, "alpha33");
      input[53]->value("0");
      input[54] = new Fl_Input(2 * WB + 3*IW, 2 * WB + 9 * BH, IW/2, BH, "2alpha23");
      input[54]->value("0");
      input[55] = new Fl_Input(2 * WB + 4*IW, 2 * WB + 9 * BH, IW/2, BH, "2alpha13");
      input[55]->value("0");
      input[56] = new Fl_Input(2 * WB + 5*IW, 2 * WB + 9 * BH, IW/2, BH, "2alpha12");
      input[56]->value("0");
      input[57] = new Fl_Input(2 * WB + 6*IW, 2 * WB + 9 * BH, IW/2, BH, "Ce");
      input[57]->value("0");

      //Prof. Wenbin Yu
      for(int i = 51; i < 58; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for(int i = 41; i < 42; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for(int i = 2; i < 24; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for(int i = 38; i < 39; i++)   input[i]->align(FL_ALIGN_RIGHT);
      input[43]->align(FL_ALIGN_RIGHT);
      {
        Fl_Return_Button *o = new Fl_Return_Button
          (width - 2 * BB - 5 * WB, 2 * WB + 11 * BH, BB, BH, "Add");    //Prof. Wenbin Yu
        o->callback(con_geometry_define_parameter_cb3);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }
      //group[0]->end();              //Prof. Wenbin Yu
      group[2]->end();                //Prof. Wenbin Yu
    }
	//Prof. Wenbin Yu
    o->end();
  }

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow1::show(int pane)
{
  for(int i = 0; i < 3; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}
void geometryContextWindow1::hide(int pane)
{

  win->hide();
}


geometryContextWindow2::geometryContextWindow2(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 30 * FL_NORMAL_SIZE;
  int height = 4 * WB + 4 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
                          "Materilization");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    {
      group[0] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Add");
      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW, BH, "Material ID number");
      input[0]->value("1");
      input[0]->align(FL_ALIGN_RIGHT);
      group[0]->end();
    }
    o->end();
  }

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow2::show(int pane)
{
  for(int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

// prof. wenbin yu, when user hit q, then close window at the same time
void geometryContextWindow2::hide(int pane)
{

	win->hide();
}


// Prof. Yu, add common SG
// Prof. Yu, common SG for solid model
geometryContextWindow7::geometryContextWindow7(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Common SG");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    /*
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "2D SG");


      static Fl_Menu_Item  SG2D_model[] = {
	{ "Select type of models:", 0, 0, 0 },
	{ "Square Pack Microstructure", 0, 0, 0 },
	{ "Hexagonal Pack Microstructure", 0, 0, 0 },
	{ 0 }
      };

      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 1 * BH, IW * 2.5, BH, "Type of models");
      choice[0]->menu(SG2D_model);
      choice[0]->align(FL_ALIGN_RIGHT);
      input[1] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW * 2.5, BH, "Volume fraction of fiber");
      input[1]->value("0.4");
      input[2] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW * 2.5, BH, "Volume fraction of interphase (if any)");
      input[2]->value("0");
      choice[5] = new Fl_Choice(2 * WB, 2 * WB + 4* BH, IW * 2.5, BH, "Fiber material");
      //choice[5]->menu(Matname);
      choice[6] = new Fl_Choice(2 * WB, 2 * WB + 5 * BH, IW * 2.5, BH, "matrix material");
      //choice[6]->menu(Matname);
      choice[7] = new Fl_Choice(2 * WB, 2 * WB + 6 * BH, IW * 2.5, BH, "Interphase material (if any)");
      //choice[7]->menu(Matname);
      for (int i = 1; i < 3; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for (int i = 5; i < 8; i++)   choice[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_parameter_cb1);
      }

      group[0]->end();
      }*/

    // Prof. Yu, 3D common SG
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "3D SG");

      static Fl_Menu_Item SG3D_model[] = {
	{ "Select type of models:", 0, 0, 0 },
	{ "Spherical Inclusions Microstructure", 0, 0, 0 },
	{ 0 }
      };

      choice[1] = new Fl_Choice(2 * WB, 2 * WB + 1 * BH, IW * 2.5, BH, "Type of models");
      choice[1]->menu(SG3D_model);
      choice[1]->align(FL_ALIGN_RIGHT);
      input[8] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW * 2.5, BH, "Volume fraction");
      input[8]->value("0.4");
      choice[8] = new Fl_Choice(2 * WB, 2 * WB + 3 * BH, IW * 2.5, BH, "Inclusion material");
      choice[9] = new Fl_Choice(2 * WB, 2 * WB + 4 * BH, IW * 2.5, BH, "Matrix material");
      for (int i = 8; i < 9; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for (int i = 8; i < 10; i++)   choice[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_parameter_cb2);
      }

      group[0]->end();
    }

    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow7::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow7::hide(int pane)
{

	win->hide();
}



geometryContextWindow7_1::geometryContextWindow7_1(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Common SG");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);

    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "2D SG");


      static Fl_Menu_Item  SG2D_model[] = {
	{ "Select type of models:", 0, 0, 0 },
	{ "Square Pack Microstructure", 0, 0, 0 },
	{ "Hexagonal Pack Microstructure", 0, 0, 0 },
	{ 0 }
      };

      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 1 * BH, IW * 2.5, BH, "Type of models");
      choice[0]->menu(SG2D_model);
      choice[0]->align(FL_ALIGN_RIGHT);
      input[1] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW * 2.5, BH, "Volume fraction of fiber");
      input[1]->value("0.4");
      input[2] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW * 2.5, BH, "Volume fraction of interphase (if any)");
      input[2]->value("0");
      choice[5] = new Fl_Choice(2 * WB, 2 * WB + 4* BH, IW * 2.5, BH, "Fiber material");
      //choice[5]->menu(Matname);
      choice[6] = new Fl_Choice(2 * WB, 2 * WB + 5 * BH, IW * 2.5, BH, "matrix material");
      //choice[6]->menu(Matname);
      choice[7] = new Fl_Choice(2 * WB, 2 * WB + 6 * BH, IW * 2.5, BH, "Interphase material (if any)");
      //choice[7]->menu(Matname);
      for (int i = 1; i < 3; i++)   input[i]->align(FL_ALIGN_RIGHT);
      for (int i = 5; i < 8; i++)   choice[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_parameter_cb1);
      }

      group[0]->end();
    }


    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow7_1::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow7_1::hide(int pane)
{

	win->hide();
}



//Prof. Yu, common model for beam
void SelectGroup_CB(Fl_Widget*, void*) {
  if (FlGui::instance()->geoContext13->bro->value() == 1){
    FlGui::instance()->geoContext13->group[1]->hide();
    FlGui::instance()->geoContext13->group[2]->hide();
    FlGui::instance()->geoContext13->group[3]->hide();
    FlGui::instance()->geoContext13->group[4]->hide();
    FlGui::instance()->geoContext13->group[0]->show();
  }
  if (FlGui::instance()->geoContext13->bro->value() == 2){
    FlGui::instance()->geoContext13->group[0]->hide();
    FlGui::instance()->geoContext13->group[2]->hide();
    FlGui::instance()->geoContext13->group[3]->hide();
    FlGui::instance()->geoContext13->group[4]->hide();
    FlGui::instance()->geoContext13->group[1]->show();
  }
  if (FlGui::instance()->geoContext13->bro->value() == 3){
    FlGui::instance()->geoContext13->group[1]->hide();
    FlGui::instance()->geoContext13->group[0]->hide();
    FlGui::instance()->geoContext13->group[3]->hide();
    FlGui::instance()->geoContext13->group[4]->hide();
    FlGui::instance()->geoContext13->group[2]->show();
  }
  if (FlGui::instance()->geoContext13->bro->value() == 4){
    FlGui::instance()->geoContext13->group[1]->hide();
    FlGui::instance()->geoContext13->group[0]->hide();
    FlGui::instance()->geoContext13->group[2]->hide();
    FlGui::instance()->geoContext13->group[4]->hide();
    FlGui::instance()->geoContext13->group[3]->show();
  }
  if (FlGui::instance()->geoContext13->bro->value() == 5){
    FlGui::instance()->geoContext13->group[1]->hide();
    FlGui::instance()->geoContext13->group[0]->hide();
    FlGui::instance()->geoContext13->group[2]->hide();
    FlGui::instance()->geoContext13->group[3]->hide();
    FlGui::instance()->geoContext13->group[4]->show();
  } 


}


geometryContextWindow13::geometryContextWindow13(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 36 * FL_NORMAL_SIZE;
  int height = 4 * WB + 15 * BH;
  int L = 7 * FL_NORMAL_SIZE;
  int BW = width - 4 * WB;
  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,"Beam Section");
  
  win->box(GMSH_WINDOW_BOX);
  bro = new Fl_Hold_Browser(0,0,L, height);
  bro->box(GMSH_SIMPLE_RIGHT_BOX);
  bro->has_scrollbar(Fl_Browser_::VERTICAL);
  bro->add("Rectangular");
  bro->add("I");
  bro->add("Box");
  bro->add("Circle");
  bro->add("Pipe");
  bro->callback(SelectGroup_CB);
  bro->value(1);
  width = 32 * FL_NORMAL_SIZE;

  group[0] = new Fl_Group(L,0, width, height,"Shape: Rectangular");
  {
    Fl_Tabs *o = new Fl_Tabs(L + WB, WB, width - 10*WB, height - 2 * WB);
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Isotropic");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, 1.1*IW, BH, "Shape: Rectangular");
	box1 -> box(FL_NO_BOX);
	input[9] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH,"Width");
	input[9]-> value("");
	input[10] = new Fl_Input(L + 2*WB, 2*WB + 3*BH+0.4*BH, 1.5*BB, BH,"Height");
	input[10]-> value("");
	for (int i = 9; i < 11; i++) input[i]->align(FL_ALIGN_RIGHT);
	choice[2] = new Fl_Choice(L+2*WB, 2*WB+4*BH+0.6*BH, 1.5*BB, BH,"Material-id");
	choice[2]->align(FL_ALIGN_RIGHT);
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg,(void*)"rec");
	}
      }
      o->end();
    }
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Composites");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, 1.1*IW, BH, "Shape: Rectangular");
	box1 -> box(FL_NO_BOX);
	input[14] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH,"Width");
	input[14]-> value("");
	for (int i = 14; i < 15; i++) input[i]->align(FL_ALIGN_RIGHT);
	{
	  Fl_Button *o = new Fl_Button
	    (L+2*WB, 2*WB+3*BH+0.4*BH, 1.5*BB, BH, "layup define");
	  o->callback(pop_com_define, (void*)"define");
	}
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg, (void*)"Crec");
	}
      }
      o->end();
    }
    o->end();
  }
  group[0]->end();
  
 
  
  group[1] = new Fl_Group(L,0, width, height,"Shape: I");
  {
    Fl_Tabs *o = new Fl_Tabs(L + WB, WB, width - 10*WB, height - 2 * WB);
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Isotropic");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, IW/1.7, BH, "Shape: I");
	box1 -> box(FL_NO_BOX);
	input[3] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH,"h");
	input[3]-> value("");
	input[4] = new Fl_Input(L + 2*WB, 2*WB + 3*BH+0.4*BH, 1.5*BB, BH,"b1(width of bottom flange)");
	input[4]-> value("");
	input[5] = new Fl_Input(L + 2*WB, 2*WB + 4*BH+0.6*BH, 1.5*BB, BH,"b2(width of up flange)");
	input[5]-> value("");
	input[6] = new Fl_Input(L + 2*WB, 2*WB + 5*BH+0.8*BH, 1.5*BB, BH,"t1(thickness of bottom flange)");
	input[6]-> value("");
	input[7] = new Fl_Input(L + 2*WB, 2*WB + 6*BH+1.0*BH, 1.5*BB, BH,"t2(thickness of up flange)");
	input[7]-> value("");
	input[8] = new Fl_Input(L + 2*WB, 2*WB + 7*BH+1.2*BH, 1.5*BB, BH,"t3(thickness of web)");
	input[8]-> value("");
	for (int i = 3; i < 9; i++) input[i]->align(FL_ALIGN_RIGHT);
	choice[1] = new Fl_Choice(L+2*WB, 2*WB+8*BH+1.4*BH, 1.5*BB, BH,"Material-id");
	choice[1]->align(FL_ALIGN_RIGHT);
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg,(void*)"I");
	}
      }
      o->end();
    }
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Composites");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, IW/1.7, BH, "Shape: I");
	box1 -> box(FL_NO_BOX);
	input[23] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH,"h");
	input[23]-> value("");
	input[24] = new Fl_Input(L + 2*WB, 2*WB + 3*BH+0.4*BH, 1.5*BB, BH,"b1(width of bottom flange)");
	input[24]-> value("");
	input[25] = new Fl_Input(L + 2*WB, 2*WB + 4*BH+0.6*BH, 1.5*BB, BH,"b2(width of up flange)");
	input[25]-> value("");	      
	for (int i = 23; i < 26; i++) input[i]->align(FL_ALIGN_RIGHT);
        {
	  Fl_Button *o = new Fl_Button
	    (L+2*WB, 2*WB+5*BH+0.8*BH, 1.5*BB, BH, "layup define");
	  o->callback(pop_com_define, (void*)"define_I");
	}
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg, (void*)"C_I");
	}
      }
      o->end();
    }

    o->end();
  }
  group[1]->end();
  
  	  
   group[2] = new Fl_Group(L,0, width, height,"Shape: Box");
  {
    Fl_Tabs *o = new Fl_Tabs(L + WB, WB, width - 10*WB, height - 2 * WB);
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Isotropic");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, IW/1.4, BH, "Shape: Box");
	box1 -> box(FL_NO_BOX);
	input[0] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH,"Width");
	input[0]-> value("");
	input[1] = new Fl_Input(L + 2*WB, 2*WB + 3*BH+0.4*BH, 1.5*BB, BH,"Height");
	input[1]-> value("");
	input[2] = new Fl_Input(L + 2*WB, 2*WB + 4*BH+0.6*BH, 1.5*BB, BH,"Thickness(top)");
	input[2]-> value("");
	input[20] = new Fl_Input(L + 2*WB, 2*WB + 5*BH+0.8*BH, 1.5*BB, BH,"Thickness(left)");
	input[20]-> value("");
	input[21] = new Fl_Input(L + 2*WB, 2*WB + 6*BH+1*BH, 1.5*BB, BH,"Thickness(bottom)");
	input[21]-> value("");
	input[22] = new Fl_Input(L + 2*WB, 2*WB + 7*BH+1.2*BH, 1.5*BB, BH,"Thickness(right)");
	input[22]-> value("");
	for (int i = 0; i < 3; i++) input[i]->align(FL_ALIGN_RIGHT);
	for (int i = 20; i < 23; i++) input[i]->align(FL_ALIGN_RIGHT);
	choice[0] = new Fl_Choice(L+2*WB, 2*WB+8*BH+1.4*BH, 1.5*BB, BH,"Material-id");
	choice[0]->align(FL_ALIGN_RIGHT);
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg, (void*)"box");
	}
      }
       o->end();
    }
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Composites");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, IW/1.4, BH, "Shape: Box");
	box1 -> box(FL_NO_BOX);
	input[18] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH,"Width");
	input[18]-> value("");
	input[19] = new Fl_Input(L + 2*WB, 2*WB + 3*BH+0.4*BH, 1.5*BB, BH,"Height");
	input[19]-> value("");
	//input[20] = new Fl_Input(L + 2*WB, 2*WB + 4*BH+0.6*BH, 1.5*BB, BH,"Thickness");
	//input[20]-> value("");	      
	for (int i = 18; i < 21; i++) input[i]->align(FL_ALIGN_RIGHT);
        {
	  Fl_Button *o = new Fl_Button
	    (L+2*WB, 2*WB+4*BH+0.6*BH, 1.5*BB, BH, "layup define");
	  o->callback(pop_com_define, (void*)"define2");
	}
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg, (void*)"Cbox");
	}
      }
      o->end();
      }
      
    o->end();
  }
  group[2]->end();
	

  group[3] = new Fl_Group(L,0, width, height,"Shape: Circle");
  {
    Fl_Tabs *o = new Fl_Tabs(L + WB, WB, width - 10*WB, height - 2 * WB);
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Isotropic");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, IW/1.3, BH, "Shape: Circle");
	box1 -> box(FL_NO_BOX);
	input[15] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH," R");
	input[15]-> value("");
	input[15]->align(FL_ALIGN_RIGHT);
	choice[3] = new Fl_Choice(L+2*WB, 2*WB+3*BH+0.4*BH, 1.5*BB, BH,"Material-id");
	choice[3]->align(FL_ALIGN_RIGHT);
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg,(void*)"Cir");
	}
      }
      o->end();
    }
    o->end();
  }
  group[3]->end();

  group[4] = new Fl_Group(L,0, width, height,"Shape: Pipe");
  {
    Fl_Tabs *o = new Fl_Tabs(L + WB, WB, width - 10*WB, height - 2 * WB);
    {
      Fl_Group *o = new Fl_Group
	(L + WB, WB + BH, width - 4*WB, height - 2 * WB - BH, "Isotropic");
      {
	Fl_Box *box1 = new Fl_Box(L, 2*WB + 1.1*BH, IW/1.4, BH, "Shape: Pipe");
	box1 -> box(FL_NO_BOX);
	input[16] = new Fl_Input(L + 2*WB, 2*WB + 2*BH+0.2*BH, 1.5*BB, BH,"Radius");
	input[16]-> value("");
	input[16]->align(FL_ALIGN_RIGHT);
	input[17] = new Fl_Input(L + 2*WB, 2*WB + 3*BH+0.4*BH, 1.5*BB, BH,"Thickness");
	input[17]-> value("");
	input[17]->align(FL_ALIGN_RIGHT);
	choice[4] = new Fl_Choice(L+2*WB, 2*WB+4*BH+0.6*BH, 1.5*BB, BH,"Material-id");
	choice[4]->align(FL_ALIGN_RIGHT);
	{
	  Fl_Return_Button *o = new Fl_Return_Button
	    (L + 2*IW + 3*WB, 2 * WB + 14 * BH, BB, BH, "Add");
	  o->callback(comSG_Beam_Reg,(void*)"pipe");
	}
      }
      o->end();
    }
    o->end();
  }
  group[4]->end();
  
  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13::show(int pane)
{
	for (int i = 0; i < 5; i++)
		group[i]->hide();
	group[pane]->show();
	win->show();
}

void geometryContextWindow13::hide(int pane)
{

	win->hide();
}



geometryContextWindow13_1::geometryContextWindow13_1(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 30 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Common SG");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
		
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width -  WB, height - 2 * WB - BH, "Laminate");
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 2 * BH, 2*BB, BH, "Fast generate");
	o->callback(con_geometry_comSG_Beam, (void*)"fast");
      }

      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 4 * BH, 2*BB, BH, "Advanced");
	o->callback(con_geometry_comSG_Beam, (void*)"advanced");
      }
      
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 6 * BH, 2*BB, BH, "Import");
	o->callback(comSG_lam_upload, (void*)"Rbeam");
      }
     
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Exit");
	o->callback(con_exit_cb);
      }

      group[0]->end();
    }
		
    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_1::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_1::hide(int pane)
{

  win->hide();
}

// Prof. Yu, rectangular beam
geometryContextWindow13_2::geometryContextWindow13_2(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);

    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Fast generate");

      static Fl_Menu_Item Matname[] = {
	{"Select material:", 0, 0, 0},
	{ 0 }
      };
  
      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 1.5 * BH, IW * 2, BH, "Material");
      choice[0]->align(FL_ALIGN_RIGHT);     
      input[0] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW * 2, BH, "Layup");
      input[0]->value("");
      input[1] = new Fl_Input(2 * WB, 2 * WB + 4.5 * BH, 2 * IW, BH, "ply thickness");
      input[1]->value("");
      //input[2] = new Fl_Input(2 * WB, 2 * WB + 6 * BH, 2 * IW, BH, "laminate name");
      //input[2]->value("");
      for (int i = 0; i < 2; i++) input[i]->align(FL_ALIGN_RIGHT);
      Fl_Multiline_Output *out = new Fl_Multiline_Output(3.2*IW,2*WB + 3*BH, 1.5*IW ,0.85*IW,"Layup example:");
      out->value("[45/-45]2s denotes 8 plies.\nA slash separates each lamina.\nNumber after square brackets \ndenotes repeated times.\ns denotes symmetry.\nThe above laminate is equal to \n[45/-45/45/-45/-45/45/-45/45].");
      out->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2.1 * BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam,(void*)"rectangular");
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }
      group[0]->end();
    }


    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_2::show(int pane)
{
	for (int i = 0; i < 1; i++)
		group[i]->hide();
	group[pane]->show();
	win->show();
}

void geometryContextWindow13_2::hide(int pane)
{

	win->hide();
}


//Prof. Yu, advanced generate for beam
geometryContextWindow13_3::geometryContextWindow13_3(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 12 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Advanced");
      Fl_Box *box1 = new Fl_Box(3 * WB, 2 * WB + 1 * BH, IW , BH, "thickness");
      box1 -> box(FL_NO_BOX);
      Fl_Box *box2 = new Fl_Box(6 * WB + IW, 2 * WB + 1 * BH, IW , BH, "orientation");
      box2 -> box(FL_NO_BOX);
      Fl_Box *box3 = new Fl_Box(9 * WB + 2*IW, 2 * WB + 1 * BH, IW , BH, "material-id");
      box3 -> box(FL_NO_BOX);
      input[0] = new Fl_Input(6 * WB, 2 * WB + 2 * BH, 0.8*IW, BH, "1 ");
      input[0]->value("");
      input[1] = new Fl_Input(9 * WB + IW, 2 * WB + 2 * BH, 0.8*IW, BH, "");
      input[1]->value("");
      choice[0] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 2 * BH, IW, BH, "");
      //choice[0]->value("");
      input[2] = new Fl_Input(6 * WB, 2 * WB + 3 * BH, 0.8*IW, BH, "2 ");
      input[2]->value("");
      input[3] = new Fl_Input(9 * WB + IW, 2 * WB + 3 * BH, 0.8*IW, BH, "");
      input[3]->value("");
      choice[1] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 3 * BH, IW, BH, "");
      input[4] = new Fl_Input(6 * WB, 2 * WB + 4 * BH, 0.8*IW, BH, "3 ");
      input[4]->value("");
      input[5] = new Fl_Input(9 * WB + IW, 2 * WB + 4 * BH, 0.8*IW, BH, "");
      input[5]->value("");
      choice[2] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 4 * BH, IW, BH, "");
      input[6] = new Fl_Input(6 * WB, 2 * WB + 5 * BH, 0.8*IW, BH, "4 ");
      input[6]->value("");
      input[7] = new Fl_Input(9 * WB + IW, 2 * WB + 5 * BH, 0.8*IW, BH, "");
      input[7]->value("");
      choice[3] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 5 * BH, IW, BH, "");
      input[8] = new Fl_Input(6 * WB, 2 * WB + 6 * BH, 0.8*IW, BH, "5 ");
      input[8]->value("");
      input[9] = new Fl_Input(9 * WB + IW, 2 * WB + 6 * BH, 0.8*IW, BH, "");
      input[9]->value("");
      choice[4] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 6 * BH, IW, BH, "");
      input[10] = new Fl_Input(6 * WB, 2 * WB + 7 * BH, 0.8*IW, BH, "6 ");
      input[10]->value("");
      input[11] = new Fl_Input(9 * WB + IW, 2 * WB + 7 * BH, 0.8*IW, BH, "");
      input[11]->value("");
      choice[5] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 7 * BH, IW, BH, "");
      input[12] = new Fl_Input(6 * WB, 2 * WB + 8 * BH, 0.8*IW, BH, "7 ");
      input[12]->value("");
      input[13] = new Fl_Input(9 * WB + IW, 2 * WB + 8 * BH, 0.8*IW, BH, "");
      input[13]->value("");
      choice[6] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 8 * BH, IW, BH, "");
      input[14] = new Fl_Input(6 * WB, 2 * WB + 9 * BH, 0.8*IW, BH, "8 ");
      input[14]->value("");
      input[15] = new Fl_Input(9 * WB + IW, 2 * WB + 9 * BH, 0.8*IW, BH, "");
      input[15]->value("");
      choice[7] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 9 * BH, IW, BH, "");
      //input[16] = new Fl_Input(6* WB, 2 * WB + 10 * BH, 0.8*IW, BH, "laminate name");
      //input[16]->value("");
      //input[16]->align(FL_ALIGN_RIGHT);

      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  2.1*BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam2,(void*)"Rec");
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }

      group[0]->end();
    }


    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_3::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_3::hide(int pane)
{

  win->hide();
}


geometryContextWindow13_4::geometryContextWindow13_4(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 30 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Common SG");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
		
   		
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width -  WB, height - 2 * WB - BH, "Laminate");
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 2 * BH, 2*BB, BH, "Fast generate");
	o->callback(con_geometry_comSG_Beam, (void*)"fast2");
      }

      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 4 * BH, 2*BB, BH, "Advanced");
	o->callback(con_geometry_comSG_Beam, (void*)"advanced_B");
      }
      
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 6 * BH, 2*BB, BH, "Import");
	o->callback(comSG_lam_upload, (void*)"Bbeam");
      }
     
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Exit");
	o->callback(con_exit_cb);
      }

      group[0]->end();
    }
		
    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_4::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_4::hide(int pane)
{

  win->hide();
}



geometryContextWindow13_5::geometryContextWindow13_5(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
		
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Fast generate");

      static Fl_Menu_Item Matname[] = {
	{"Select material:", 0, 0, 0},
	{ 0 }
      };

      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 1.5 * BH, IW * 2, BH, "Material");
      choice[0]->align(FL_ALIGN_RIGHT);
      
      input[0] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW * 2, BH, "Layup");
      input[0]->value("");
      input[1] = new Fl_Input(2 * WB, 2 * WB + 4.5 * BH, 2 * IW, BH, "ply thickness");
      input[1]->value("");
      lay_name = new Fl_Output(2*WB,2*WB + 6*BH, 2*IW ,BH,"assign layup");
      lay_name->value("Up edge of box beam");
      lay_name->align(FL_ALIGN_RIGHT);
      for (int i = 0; i < 2; i++) input[i]->align(FL_ALIGN_RIGHT);
      Fl_Multiline_Output *out = new Fl_Multiline_Output(3.2*IW,2*WB + 3*BH, 1.5*IW ,0.85*IW,"Layup example:");
      out->value("[45/-45]2s denotes 8 plies.\nA slash separates each lamina.\nNumber after square brackets \ndenotes repeated times.\ns denotes symmetry.\nThe above laminate is equal to \n[45/-45/45/-45/-45/45/-45/45].");
      out->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2.1 * BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam,(void*)"box");
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }
      group[0]->end();
    }
		
    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_5::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_5::hide(int pane)
{

  win->hide();
}


geometryContextWindow13_6::geometryContextWindow13_6(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 12 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Advanced");
      Fl_Box *box1 = new Fl_Box(3 * WB, 2 * WB + 1 * BH, IW , BH, "thickness");
      box1 -> box(FL_NO_BOX);
      Fl_Box *box2 = new Fl_Box(6 * WB + IW, 2 * WB + 1 * BH, IW , BH, "orientation");
      box2 -> box(FL_NO_BOX);
      Fl_Box *box3 = new Fl_Box(9 * WB + 2*IW, 2 * WB + 1 * BH, IW , BH, "material-id");
      box3 -> box(FL_NO_BOX);
      input[0] = new Fl_Input(6 * WB, 2 * WB + 2 * BH, 0.8*IW, BH, "1 ");
      input[0]->value("");
      input[1] = new Fl_Input(9 * WB + IW, 2 * WB + 2 * BH, 0.8*IW, BH, "");
      input[1]->value("");
      choice[0] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 2 * BH, IW, BH, "");
      input[2] = new Fl_Input(6 * WB, 2 * WB + 3 * BH, 0.8*IW, BH, "2 ");
      input[2]->value("");
      input[3] = new Fl_Input(9 * WB + IW, 2 * WB + 3 * BH, 0.8*IW, BH, "");
      input[3]->value("");
      choice[1] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 3 * BH, IW, BH, "");
      input[4] = new Fl_Input(6 * WB, 2 * WB + 4 * BH, 0.8*IW, BH, "3 ");
      input[4]->value("");
      input[5] = new Fl_Input(9 * WB + IW, 2 * WB + 4 * BH, 0.8*IW, BH, "");
      input[5]->value("");
      choice[2] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 4 * BH, IW, BH, "");
      input[6] = new Fl_Input(6 * WB, 2 * WB + 5 * BH, 0.8*IW, BH, "4 ");
      input[6]->value("");
      input[7] = new Fl_Input(9 * WB + IW, 2 * WB + 5 * BH, 0.8*IW, BH, "");
      input[7]->value("");
      choice[3] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 5 * BH, IW, BH, "");
      input[8] = new Fl_Input(6 * WB, 2 * WB + 6 * BH, 0.8*IW, BH, "5 ");
      input[8]->value("");
      input[9] = new Fl_Input(9 * WB + IW, 2 * WB + 6 * BH, 0.8*IW, BH, "");
      input[9]->value("");
      choice[4] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 6 * BH, IW, BH, "");
      input[10] = new Fl_Input(6 * WB, 2 * WB + 7 * BH, 0.8*IW, BH, "6 ");
      input[10]->value("");
      input[11] = new Fl_Input(9 * WB + IW, 2 * WB + 7 * BH, 0.8*IW, BH, "");
      input[11]->value("");
      choice[5] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 7 * BH, IW, BH, "");
      input[12] = new Fl_Input(6 * WB, 2 * WB + 8 * BH, 0.8*IW, BH, "7 ");
      input[12]->value("");
      input[13] = new Fl_Input(9 * WB + IW, 2 * WB + 8 * BH, 0.8*IW, BH, "");
      input[13]->value("");
      choice[6] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 8 * BH, IW, BH, "");
      input[14] = new Fl_Input(6 * WB, 2 * WB + 9 * BH, 0.8*IW, BH, "8 ");
      input[14]->value("");
      input[15] = new Fl_Input(9 * WB + IW, 2 * WB + 9 * BH, 0.8*IW, BH, "");
      input[15]->value("");
      choice[7] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 9 * BH, IW, BH, "");
      lay_name = new Fl_Output(6*WB,2*WB + 10*BH, 2*IW ,BH,"assign layup");
      lay_name->value("Up edge of box beam");
      lay_name->align(FL_ALIGN_RIGHT);

      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  2.1*BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam2,(void*)"box");
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }

      group[0]->end();
    }


    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_6::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_6::hide(int pane)
{

  win->hide();
}


geometryContextWindow13_7::geometryContextWindow13_7(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 30 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Common SG");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
		
   		
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width -  WB, height - 2 * WB - BH, "Laminate");
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 2 * BH, 2*BB, BH, "Fast generate");
	o->callback(con_geometry_comSG_Beam, (void*)"fast_I");
      }

      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 4 * BH, 2*BB, BH, "Advanced");
	o->callback(con_geometry_comSG_Beam, (void*)"advanced_I");
      }
      
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 6 * BH, 2*BB, BH, "Import");
	o->callback(comSG_lam_upload, (void*)"Ibeam");
      }
     
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Exit");
	o->callback(con_exit_cb);
      }

      group[0]->end();
    }
		
    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_7::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_7::hide(int pane)
{

  win->hide();
}


geometryContextWindow13_8::geometryContextWindow13_8(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
		
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Fast generate");

      static Fl_Menu_Item Matname[] = {
	{"Select material:", 0, 0, 0},
	{ 0 }
      };

      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 1.5 * BH, IW * 2, BH, "Material");
      choice[0]->align(FL_ALIGN_RIGHT);
      
      input[0] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW * 2, BH, "Layup");
      input[0]->value("");
      input[1] = new Fl_Input(2 * WB, 2 * WB + 4.5 * BH, 2 * IW, BH, "ply thickness");
      input[1]->value("");
      lay_name = new Fl_Output(2*WB,2*WB + 6*BH, 2*IW ,BH,"assign layup");
      lay_name->value("Bottom edge of I beam");
      lay_name->align(FL_ALIGN_RIGHT);
      for (int i = 0; i < 2; i++) input[i]->align(FL_ALIGN_RIGHT);
      Fl_Multiline_Output *out = new Fl_Multiline_Output(3.2*IW,2*WB + 3*BH, 1.5*IW ,0.85*IW,"Layup example:");
      out->value("[45/-45]2s denotes 8 plies.\nA slash separates each lamina.\nNumber after square brackets \ndenotes repeated times.\ns denotes symmetry.\nThe above laminate is equal to \n[45/-45/45/-45/-45/45/-45/45].");
      out->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2.1 * BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam,(void*)"I");
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }
      group[0]->end();
    }
		
    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_8::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_8::hide(int pane)
{

  win->hide();
}



geometryContextWindow13_9::geometryContextWindow13_9(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 12 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Advanced");
      Fl_Box *box1 = new Fl_Box(3 * WB, 2 * WB + 1 * BH, IW , BH, "thickness");
      box1 -> box(FL_NO_BOX);
      Fl_Box *box2 = new Fl_Box(6 * WB + IW, 2 * WB + 1 * BH, IW , BH, "orientation");
      box2 -> box(FL_NO_BOX);
      Fl_Box *box3 = new Fl_Box(9 * WB + 2*IW, 2 * WB + 1 * BH, IW , BH, "material-id");
      box3 -> box(FL_NO_BOX);
      input[0] = new Fl_Input(6 * WB, 2 * WB + 2 * BH, 0.8*IW, BH, "1 ");
      input[0]->value("");
      input[1] = new Fl_Input(9 * WB + IW, 2 * WB + 2 * BH, 0.8*IW, BH, "");
      input[1]->value("");
      choice[0] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 2 * BH, IW, BH, "");
      input[2] = new Fl_Input(6 * WB, 2 * WB + 3 * BH, 0.8*IW, BH, "2 ");
      input[2]->value("");
      input[3] = new Fl_Input(9 * WB + IW, 2 * WB + 3 * BH, 0.8*IW, BH, "");
      input[3]->value("");
      choice[1] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 3 * BH, IW, BH, "");
      input[4] = new Fl_Input(6 * WB, 2 * WB + 4 * BH, 0.8*IW, BH, "3 ");
      input[4]->value("");
      input[5] = new Fl_Input(9 * WB + IW, 2 * WB + 4 * BH, 0.8*IW, BH, "");
      input[5]->value("");
      choice[2] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 4 * BH, IW, BH, "");
      input[6] = new Fl_Input(6 * WB, 2 * WB + 5 * BH, 0.8*IW, BH, "4 ");
      input[6]->value("");
      input[7] = new Fl_Input(9 * WB + IW, 2 * WB + 5 * BH, 0.8*IW, BH, "");
      input[7]->value("");
      choice[3] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 5 * BH, IW, BH, "");
      input[8] = new Fl_Input(6 * WB, 2 * WB + 6 * BH, 0.8*IW, BH, "5 ");
      input[8]->value("");
      input[9] = new Fl_Input(9 * WB + IW, 2 * WB + 6 * BH, 0.8*IW, BH, "");
      input[9]->value("");
      choice[4] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 6 * BH, IW, BH, "");
      input[10] = new Fl_Input(6 * WB, 2 * WB + 7 * BH, 0.8*IW, BH, "6 ");
      input[10]->value("");
      input[11] = new Fl_Input(9 * WB + IW, 2 * WB + 7 * BH, 0.8*IW, BH, "");
      input[11]->value("");
      choice[5] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 7 * BH, IW, BH, "");
      input[12] = new Fl_Input(6 * WB, 2 * WB + 8 * BH, 0.8*IW, BH, "7 ");
      input[12]->value("");
      input[13] = new Fl_Input(9 * WB + IW, 2 * WB + 8 * BH, 0.8*IW, BH, "");
      input[13]->value("");
      choice[6] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 8 * BH, IW, BH, "");
      input[14] = new Fl_Input(6 * WB, 2 * WB + 9 * BH, 0.8*IW, BH, "8 ");
      input[14]->value("");
      input[15] = new Fl_Input(9 * WB + IW, 2 * WB + 9 * BH, 0.8*IW, BH, "");
      input[15]->value("");
      choice[7] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 9 * BH, IW, BH, "");
      lay_name = new Fl_Output(6*WB,2*WB + 10*BH, 2*IW ,BH,"assign layup");
      lay_name->value("Bottom edge of I beam");
      lay_name->align(FL_ALIGN_RIGHT);

      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  2.1*BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam2,(void*)"Ibeam");
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Exit");    //Prof. Yu
	o->callback(con_exit_cb);
      }

      group[0]->end();
    }


    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow13_9::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow13_9::hide(int pane)
{

  win->hide();
}

//Prof. Yu, common SG for Plate/shell

geometryContextWindow14P::geometryContextWindow14P(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;
  
  int width = 40 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;
  
  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Common SG");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width -  WB, height - 2 * WB - BH, "Laminate");
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 2 * BH, 2*BB, BH, "Fast generate");
	o->callback(con_geometry_comSG_PS, (void*)"fast");
      }
      
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 4 * BH, 2*BB, BH, "Advanced");
	o->callback(con_geometry_comSG_PS, (void*)"advanced");
      }
      
      {
	Fl_Button *o = new Fl_Button
	  (8 * WB, 2 * WB + 6 * BH, 2*BB, BH, "Import");
	o->callback(comSG_lam_upload, (void*)"plate");
      }
      
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Exit");
	o->callback(con_exit_cb);
      }
      
      group[0]->end();
    }

    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow14P::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow14P::hide(int pane)
{
  
  win->hide();
}




//Prof. Yu, common SG for laminate
//Prof. Yu, fast generate
geometryContextWindow14::geometryContextWindow14(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Fast generate");

      static Fl_Menu_Item Matname[] = {
	{"Select material:", 0, 0, 0},
	{ 0 }
      };

      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 1.5 * BH, IW * 2, BH, "Material");
      //choice[0]->menu(Matname);
      choice[0]->align(FL_ALIGN_RIGHT);

      
      input[0] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW * 2, BH, "Layup");
      input[0]->value("");
      input[1] = new Fl_Input(2 * WB, 2 * WB + 4.5 * BH, 2 * IW, BH, "ply thickness");
      input[1]->value("");
      Fl_Multiline_Output *out = new Fl_Multiline_Output(3.2*IW,2*WB + 3*BH, 1.5*IW ,0.85*IW,"Layup example:");
      out->value("[45/-45]2s denotes 8 plies.\nA slash separates each lamina.\nNumber after square brackets \ndenotes repeated times.\ns denotes symmetry.\nThe above laminate is equal to \n[45/-45/45/-45/-45/45/-45/45].");
      out->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
      for (int i = 0; i < 2; i++) input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam,(void*)"plate");
      }


      group[0]->end();
    }


    o->end();
  }
  

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow14::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow14::hide(int pane)
{

  win->hide();
}

//Prof. Yu, advanced generate
geometryContextWindow14_1::geometryContextWindow14_1(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 4 * WB + 12 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Laminate");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Advanced");
      Fl_Box *box1 = new Fl_Box(3 * WB, 2 * WB + 1 * BH, IW , BH, "thickness");
      box1 -> box(FL_NO_BOX);
      Fl_Box *box2 = new Fl_Box(6 * WB + IW, 2 * WB + 1 * BH, IW , BH, "orientation");
      box2 -> box(FL_NO_BOX);
      Fl_Box *box3 = new Fl_Box(9 * WB + 2*IW, 2 * WB + 1 * BH, IW , BH, "material-id");
      box3 -> box(FL_NO_BOX);
      input[0] = new Fl_Input(6 * WB, 2 * WB + 2 * BH, 0.8*IW, BH, "1 ");
      input[0]->value("");
      input[1] = new Fl_Input(9 * WB + IW, 2 * WB + 2 * BH, 0.8*IW, BH, "");
      input[1]->value("");
      choice[0] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 2 * BH, IW, BH, "");
      //choice[0]->value("");
      input[2] = new Fl_Input(6 * WB, 2 * WB + 3 * BH, 0.8*IW, BH, "2 ");
      input[2]->value("");
      input[3] = new Fl_Input(9 * WB + IW, 2 * WB + 3 * BH, 0.8*IW, BH, "");
      input[3]->value("");
      choice[1] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 3 * BH, IW, BH, "");
      input[4] = new Fl_Input(6 * WB, 2 * WB + 4 * BH, 0.8*IW, BH, "3 ");
      input[4]->value("");
      input[5] = new Fl_Input(9 * WB + IW, 2 * WB + 4 * BH, 0.8*IW, BH, "");
      input[5]->value("");
      choice[2] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 4 * BH, IW, BH, "");
      input[6] = new Fl_Input(6 * WB, 2 * WB + 5 * BH, 0.8*IW, BH, "4 ");
      input[6]->value("");
      input[7] = new Fl_Input(9 * WB + IW, 2 * WB + 5 * BH, 0.8*IW, BH, "");
      input[7]->value("");
      choice[3] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 5 * BH, IW, BH, "");
      input[8] = new Fl_Input(6 * WB, 2 * WB + 6 * BH, 0.8*IW, BH, "5 ");
      input[8]->value("");
      input[9] = new Fl_Input(9 * WB + IW, 2 * WB + 6 * BH, 0.8*IW, BH, "");
      input[9]->value("");
      choice[4] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 6 * BH, IW, BH, "");
      input[10] = new Fl_Input(6 * WB, 2 * WB + 7 * BH, 0.8*IW, BH, "6 ");
      input[10]->value("");
      input[11] = new Fl_Input(9 * WB + IW, 2 * WB + 7 * BH, 0.8*IW, BH, "");
      input[11]->value("");
      choice[5] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 7 * BH, IW, BH, "");
      input[12] = new Fl_Input(6 * WB, 2 * WB + 8 * BH, 0.8*IW, BH, "7 ");
      input[12]->value("");
      input[13] = new Fl_Input(9 * WB + IW, 2 * WB + 8 * BH, 0.8*IW, BH, "");
      input[13]->value("");
      choice[6] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 8 * BH, IW, BH, "");
      input[14] = new Fl_Input(6 * WB, 2 * WB + 9 * BH, 0.8*IW, BH, "8 ");
      input[14]->value("");
      input[15] = new Fl_Input(9 * WB + IW, 2 * WB + 9 * BH, 0.8*IW, BH, "");
      input[15]->value("");
      choice[7] = new Fl_Choice(12 * WB + 2*IW, 2 * WB + 9 * BH, IW, BH, "");

      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width -  BB - 2 * WB, 2 * WB + 11 * BH, BB, BH, "Add");
	o->callback(con_geometry_comSG_lam2,(void*)"plate");
      }
			

      group[0]->end();
    }


    o->end();
  }


  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow14_1::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow14_1::hide(int pane)
{

  win->hide();
}


//Prof. Yu, add solid function for homogenization
geometryContextWindow10::geometryContextWindow10(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;
  
  int width = 50 * FL_NORMAL_SIZE;
  int height = 30 * WB + 10 * BH;
  
  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Parameters");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, " Solid");
      
      static Fl_Menu_Item analysis[] = {
	{ "0-elastic", 0, 0, 0 },
	{ "1-thermoelastic", 0, 0, 0 },
	{ "2-conduction", 0, 0, 0 },
	{ "3-piezoelectric/piezomagnetic", 0, 0, 0 },
	{ "4-thermoepiezoelectric/thermopiezomagnetic", 0, 0, 0 },
	{ "5-piezoelectromagnetic", 0, 0, 0 },
	{ "6-thermopiezoelectromagnetic", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item elem_flag[] = {
	{ "0-regular elements", 0, 0, 0 },
	{ "1-one dimension degenerated", 0, 0, 0 },
	{ "2-two dimension degenerated", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item trans_flag[] = {
	{ "0-global coordinate", 0, 0, 0 },
	{ "1-material coordinate", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item temp_flag[] = {
	{ "0-uniform", 0, 0, 0 },
	{ "1-not uniform", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item unit_cell_dimension[] = {
	{ "1D", 0, 0, 0 },
	{ "2D", 0, 0, 0 },
	{ "3D", 0, 0, 0 },
	{ 0 }
      };
      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 1 * BH, IW * 2.5, BH, "Type of analysis");
      choice[0]->menu(analysis);
      choice[1] = new Fl_Choice(2 * WB, 2 * WB + 2 * BH, IW * 2.5, BH, "Type of elements");
      choice[1]->menu(elem_flag);
      choice[2] = new Fl_Choice(2 * WB, 2 * WB + 3 * BH, IW * 2.5, BH, "In which system does material define");
      choice[2]->menu(trans_flag);
      choice[3] = new Fl_Choice(2 * WB, 2 * WB + 4 * BH, IW * 2.5, BH, "Temperature uniformity");
      choice[3]->menu(temp_flag);
      for (int i = 0; i < 4; i++)   choice[i]->align(FL_ALIGN_RIGHT);
      //input[0] = new Fl_Input(2 * WB, 2 * WB + 5 * BH, IW * 2.5, BH, "Unit cell area");
      //input[0]->value("1");
      //input[0]->align(FL_ALIGN_RIGHT);
      
      
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 28 * WB + 9 * BH, BB, BH, "Save");
	o->callback(con_geometry_define_parameter_cb5);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 28 * WB + 9 * BH, BB, BH, "Run");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb, (void*)"homo3");
      }
      
      group[0]->end();
    }
    o->end();
  }
  
  
  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();
  
  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow10::show(int pane)
{
	for (int i = 0; i < 1; i++)
		group[i]->hide();
	group[pane]->show();
	win->show();
}

void geometryContextWindow10::hide(int pane)
{

	win->hide();
}

// Prof. Yu, add beam function for homogenization
geometryContextWindow8::geometryContextWindow8(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 50 * FL_NORMAL_SIZE;
  int height = 30 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Parameters");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      group[0] = new Fl_Group
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, " Beam");

      static Fl_Menu_Item analysis[] = {
	{ "0-elastic", 0, 0, 0 },
	{ "1-thermoelastic", 0, 0, 0 },
	{ "2-conduction", 0, 0, 0 },
	{ "3-piezoelectric/piezomagnetic", 0, 0, 0 },
	{ "4-thermoepiezoelectric/thermopiezomagnetic", 0, 0, 0 },
	{ "5-piezoelectromagnetic", 0, 0, 0 },
	{ "6-thermopiezoelectromagnetic", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item elem_flag[] = {
	{ "0-regular elements", 0, 0, 0 },
	{ "1-one dimension degenerated", 0, 0, 0 },
	{ "2-two dimension degenerated", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item trans_flag[] = {
	{ "0-global coordinate", 0, 0, 0 },
	{ "1-material coordinate", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item temp_flag[] = {
	{ "0-uniform", 0, 0, 0 },
	{ "1-not uniform", 0, 0, 0 },
	{ 0 }
      };
      static Fl_Menu_Item unit_cell_dimension[] = {
	{ "2D", 0, 0, 0 },
	{ "3D", 0, 0, 0 },
	{ 0 }
      };
      
      static Fl_Menu_Item beam_model[] = {
	{ "0-Euler-Bernoulli beam model", 0, 0, 0 },
	{ "1-Timoshenko beam model", 0, 0, 0 },
	{ "2-Vlasov beam model", 0, 0, 0 },
	{ "3-beam model with the trapeze effect", 0, 0, 0 },
	{ 0 }
      };
      choice[8] = new Fl_Choice(2 * WB, 2 * WB + 1 * BH, IW * 2.5, BH, "Type of analysis");
      choice[8]->menu(analysis);
      choice[9] = new Fl_Choice(2 * WB, 2 * WB + 2 * BH, IW * 2.5, BH, "Type of elements");
      choice[9]->menu(elem_flag);
      choice[10] = new Fl_Choice(2 * WB, 2 * WB + 3 * BH, IW * 2.5, BH, "In which system does material define");
      choice[10]->menu(trans_flag);
      choice[11] = new Fl_Choice(2 * WB, 2 * WB + 4 * BH, IW * 2.5, BH, "Temperature uniformity");
      choice[11]->menu(temp_flag);
      for (int i = 8; i < 12; i++)   choice[i]->align(FL_ALIGN_RIGHT);
      //input[8] = new Fl_Input(2 * WB, 2 * WB + 5 * BH, IW * 2.5, BH, "Unit cell area");
      //input[8]->value("1");
      //input[8]->align(FL_ALIGN_RIGHT);

      choice[5] = new Fl_Choice(2 * WB, 2 * WB + 5 * BH, IW * 2.5, BH, "Type of models");
      choice[5]->menu(beam_model);
      choice[5]->align(FL_ALIGN_RIGHT);
      input[1] = new Fl_Input(2 * WB, 2 * WB + 6 * BH, IW * 2.5, BH, "curvatures k11");
      input[1]->value("0");
      input[2] = new Fl_Input(2 * WB, 2 * WB + 7 * BH, IW * 2.5, BH, "curvatures k12");
      input[2]->value("0");
      input[3] = new Fl_Input(2 * WB, 2 * WB + 8 * BH, IW * 2.5, BH, "curvatures k13");
      input[3]->value("0");
      input[4] = new Fl_Input(2 * WB, 2 * WB + 9 * BH, IW * 2.5, BH, "oblique_cos(y1,x1)");
      input[4]->value("1");
      input[5] = new Fl_Input(2 * WB, 2 * WB + 10 * BH, IW * 2.5, BH, "oblique_cos(y2,x1)");
      input[5]->value("0");
      for (int i = 1; i < 6; i++)   input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 28 * WB + 9 * BH, BB, BH, "Save");
	o->callback(con_geometry_define_parameter_cb6);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 28 * WB + 9 * BH, BB, BH, "Run");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb, (void*)"homo1");
      }
      
      group[0]->end();
    }
    o->end();
  }
  

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow8::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

void geometryContextWindow8::hide(int pane)
{

  win->hide();
}

// Prof. Yu, add shell function for homogenization
geometryContextWindow9::geometryContextWindow9(int deltaFontSize)
{
	FL_NORMAL_SIZE -= deltaFontSize;

	int width = 50 * FL_NORMAL_SIZE;
	int height = 30 * WB + 10 * BH;

	win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
		"Parameters");
	win->box(GMSH_WINDOW_BOX);
	{
		Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);

		{
			group[0] = new Fl_Group
				(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, " Plate");

			static Fl_Menu_Item analysis[] = {
				{ "0-elastic", 0, 0, 0 },
				{ "1-thermoelastic", 0, 0, 0 },
				{ "2-conduction", 0, 0, 0 },
				{ "3-piezoelectric/piezomagnetic", 0, 0, 0 },
				{ "4-thermoepiezoelectric/thermopiezomagnetic", 0, 0, 0 },
				{ "5-piezoelectromagnetic", 0, 0, 0 },
				{ "6-thermopiezoelectromagnetic", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item elem_flag[] = {
				{ "0-regular elements", 0, 0, 0 },
				{ "1-one dimension degenerated", 0, 0, 0 },
				{ "2-two dimension degenerated", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item trans_flag[] = {
				{ "0-global coordinate", 0, 0, 0 },
				{ "1-material coordinate", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item temp_flag[] = {
				{ "0-uniform", 0, 0, 0 },
				{ "1-not uniform", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item unit_cell_dimension[] = {
				{ "1D", 0, 0, 0 },
				{ "2D", 0, 0, 0 },
				{ "3D", 0, 0, 0 },
				{ 0 }
			};

			static Fl_Menu_Item Plate_model[] = {
				{ "0-Kirchhoff-Love plate", 0, 0, 0 },
				{ "1-Reissner-Mindlin plate", 0, 0, 0 },
				{ 0 }
			};


			choice[18] = new Fl_Choice(2 * WB, 2 * WB + 1 * BH, IW * 2.5, BH, "Type of analysis");
			choice[18]->menu(analysis);
			choice[19] = new Fl_Choice(2 * WB, 2 * WB + 2 * BH, IW * 2.5, BH, "Type of elements");
			choice[19]->menu(elem_flag);
			choice[20] = new Fl_Choice(2 * WB, 2 * WB + 3 * BH, IW * 2.5, BH, "In which system does material define");
			choice[20]->menu(trans_flag);
			choice[21] = new Fl_Choice(2 * WB, 2 * WB + 4 * BH, IW * 2.5, BH, "Temperature uniformity");
			choice[21]->menu(temp_flag);
			for (int i = 18; i < 22; i++)   choice[i]->align(FL_ALIGN_RIGHT);


			choice[7] = new Fl_Choice(2 * WB, 2 * WB + 5 * BH, IW * 2.5, BH, "Type of models");
			choice[7]->menu(Plate_model);
			choice[7]->align(FL_ALIGN_RIGHT);

			{
				Fl_Return_Button *o = new Fl_Return_Button
					(width - 2 * BB - 5 * WB, 28 * WB + 9 * BH, BB, BH, "Save");
				o->callback(con_geometry_define_parameter_cb8);
			}
		{
			Fl_Return_Button *o = new Fl_Return_Button
				(width - BB - 2 * WB, 28 * WB + 9 * BH, BB, BH, "Run");    //Prof. Yu
			o->callback(vamuch_choose_executable_cb, (void*)"homo2");
		}

		group[0]->end();
		}



		{
			group[1] = new Fl_Group
				(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, " Shell");

			static Fl_Menu_Item analysis[] = {
				{ "0-elastic", 0, 0, 0 },
				{ "1-thermoelastic", 0, 0, 0 },
				{ "2-conduction", 0, 0, 0 },
				{ "3-piezoelectric/piezomagnetic", 0, 0, 0 },
				{ "4-thermoepiezoelectric/thermopiezomagnetic", 0, 0, 0 },
				{ "5-piezoelectromagnetic", 0, 0, 0 },
				{ "6-thermopiezoelectromagnetic", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item elem_flag[] = {
				{ "0-regular elements", 0, 0, 0 },
				{ "1-one dimension degenerated", 0, 0, 0 },
				{ "2-two dimension degenerated", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item trans_flag[] = {
				{ "0-global coordinate", 0, 0, 0 },
				{ "1-material coordinate", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item temp_flag[] = {
				{ "0-uniform", 0, 0, 0 },
				{ "1-not uniform", 0, 0, 0 },
				{ 0 }
			};
			static Fl_Menu_Item unit_cell_dimension[] = {
				{ "1D", 0, 0, 0 },
				{ "2D", 0, 0, 0 },
				{ "3D", 0, 0, 0 },
				{ 0 }
			};


			static Fl_Menu_Item Plate_model[] = {
				{ "0-Kirchhoff-Love shell", 0, 0, 0 },
				{ "1-Reissner-Mindlin shell", 0, 0, 0 },
				{ 0 }
			};

			choice[13] = new Fl_Choice(2 * WB, 2 * WB + 1 * BH, IW * 2.5, BH, "Type of analysis");
			choice[13]->menu(analysis);
			choice[14] = new Fl_Choice(2 * WB, 2 * WB + 2 * BH, IW * 2.5, BH, "Type of elements");
			choice[14]->menu(elem_flag);
			choice[15] = new Fl_Choice(2 * WB, 2 * WB + 3 * BH, IW * 2.5, BH, "In which system does material define");
			choice[15]->menu(trans_flag);
			choice[16] = new Fl_Choice(2 * WB, 2 * WB + 4 * BH, IW * 2.5, BH, "Temperature uniformity");
			choice[16]->menu(temp_flag);
			for (int i = 13; i < 17; i++)   choice[i]->align(FL_ALIGN_RIGHT);


			choice[6] = new Fl_Choice(2 * WB, 2 * WB + 5 * BH, IW * 2.5, BH, "Type of models");
			choice[6]->menu(Plate_model);
			choice[6]->align(FL_ALIGN_RIGHT);
			input[6] = new Fl_Input(2 * WB, 2 * WB + 6 * BH, IW * 2.5, BH, "curvatures k12");
			input[6]->value("0");
			input[7] = new Fl_Input(2 * WB, 2 * WB + 7 * BH, IW * 2.5, BH, "curvatures k21");
			input[7]->value("0");
			for (int i = 6; i < 8; i++)   input[i]->align(FL_ALIGN_RIGHT);
			{
				Fl_Return_Button *o = new Fl_Return_Button
					(width - 2 * BB - 5 * WB, 28 * WB + 9 * BH, BB, BH, "Save");
				o->callback(con_geometry_define_parameter_cb7);
			}
		{
			Fl_Return_Button *o = new Fl_Return_Button
				(width - BB - 2 * WB, 28 * WB + 9 * BH, BB, BH, "Run");    //Prof. Yu
			o->callback(vamuch_choose_executable_cb, (void*)"homo2");
		}

		group[1]->end();
		}




		o->end();
	}


	win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
	win->end();

	FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow9::show(int pane)
{
	for (int i = 0; i < 2; i++)
		group[i]->hide();
	group[pane]->show();
	win->show();
}

void geometryContextWindow9::hide(int pane)
{

	win->hide();
}
//Prof. Wenbin Yu



geometryContextWindow5::geometryContextWindow5(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 70 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Parameters");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      
      group[0] = new Fl_Group

	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "elastic"); //Prof. Wenbin Yu

      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW / 2, BH, "v1");
      input[0]->value("0");
      input[1] = new Fl_Input(2 * WB + IW, 2 * WB + 1 * BH, IW / 2, BH, "v2");
      input[1]->value("0");
      input[2] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW / 2, BH, "v3");
      input[2]->value("0");
      input[3] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW / 2, BH, "C11");
      input[3]->value("1");
      input[4] = new Fl_Input(2 * WB + IW, 2 * WB + 2 * BH, IW / 2, BH, "C12");
      input[4]->value("0");
      input[5] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 2 * BH, IW / 2, BH, "C13");
      input[5]->value("0");
      input[6] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW / 2, BH, "C21");
      input[6]->value("0");
      input[7] = new Fl_Input(2 * WB + IW, 2 * WB + 3 * BH, IW / 2, BH, "C22");
      input[7]->value("1");
      input[8] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 3 * BH, IW / 2, BH, "C23");
      input[8]->value("0");
      input[9] = new Fl_Input(2 * WB, 2 * WB + 4 * BH, IW / 2, BH, "C31");
      input[9]->value("0");
      input[10] = new Fl_Input(2 * WB + IW, 2 * WB + 4 * BH, IW / 2, BH, "C32");
      input[10]->value("0");
      input[11] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 4 * BH, IW / 2, BH, "C33");
      input[11]->value("1");
      input[12] = new Fl_Input(2 * WB, 2 * WB + 5 * BH, IW / 2, BH, "e11");
      input[12]->value("0");
      input[13] = new Fl_Input(2 * WB + IW, 2 * WB + 5 * BH, IW / 2, BH, "e22");
      input[13]->value("0");
      input[14] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 5 * BH, IW / 2, BH, "e33");
      input[14]->value("0");
      input[15] = new Fl_Input(2 * WB + 3 * IW, 2 * WB + 5 * BH, IW / 2, BH, "2e23");
      input[15]->value("0");
      input[16] = new Fl_Input(2 * WB + 4 * IW, 2 * WB + 5 * BH, IW / 2, BH, "2e13");
      input[16]->value("0");
      input[17] = new Fl_Input(2 * WB + 5 * IW, 2 * WB + 5 * BH, IW / 2, BH, "2e12");
      input[17]->value("0");
      //Prof. Wenbin Yu
      for (int i = 0; i < 18; i++)   input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 2 * WB + 9 * BH, BB, BH, "Save");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb2);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Run");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb, (void*)"dehomo3");
      }
      
      //group[0]->end();              //Prof. Wenbin Yu
      group[0]->end();                //Prof. Wenbin Yu
    }
    
    o->end();
  }

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();
  
  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow5::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}
void geometryContextWindow5::hide(int pane)
{

	win->hide();
}


//dehomo, beam
geometryContextWindow11::geometryContextWindow11(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;
  
  int width = 70 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;
  
  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Parameters");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {

      group[0] = new Fl_Group
	
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "elastic");    //Prof. Wenbin Yu
      
      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW / 2, BH, "v1");
      input[0]->value("0");
      input[1] = new Fl_Input(2 * WB + IW, 2 * WB + 1 * BH, IW / 2, BH, "v2");
      input[1]->value("0");
      input[2] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW / 2, BH, "v3");
      input[2]->value("0");
      input[3] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW / 2, BH, "C11");
      input[3]->value("1");
      input[4] = new Fl_Input(2 * WB + IW, 2 * WB + 2 * BH, IW / 2, BH, "C12");
      input[4]->value("0");
      input[5] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 2 * BH, IW / 2, BH, "C13");
      input[5]->value("0");
      input[6] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW / 2, BH, "C21");
      input[6]->value("0");
      input[7] = new Fl_Input(2 * WB + IW, 2 * WB + 3 * BH, IW / 2, BH, "C22");
      input[7]->value("1");
      input[8] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 3 * BH, IW / 2, BH, "C23");
      input[8]->value("0");
      input[9] = new Fl_Input(2 * WB, 2 * WB + 4 * BH, IW / 2, BH, "C31");
      input[9]->value("0");
      input[10] = new Fl_Input(2 * WB + IW, 2 * WB + 4 * BH, IW / 2, BH, "C32");
      input[10]->value("0");
      input[11] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 4 * BH, IW / 2, BH, "C33");
      input[11]->value("1");
      input[12] = new Fl_Input(2 * WB, 2 * WB + 5 * BH, IW / 2, BH, "e11");
      input[12]->value("0");
      input[13] = new Fl_Input(2 * WB + IW, 2 * WB + 5 * BH, IW / 2, BH, "k11");
      input[13]->value("0");
      input[14] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 5 * BH, IW / 2, BH, "k12");
      input[14]->value("0");
      input[15] = new Fl_Input(2 * WB + 3 * IW, 2 * WB + 5 * BH, IW / 2, BH, "k13");
      input[15]->value("0");
      //Prof. Wenbin Yu
      for (int i = 0; i < 16; i++)   input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 2 * WB + 9 * BH, BB, BH, "Save");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb3);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Run");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb, (void*)"dehomo1");
      }
      
      //group[0]->end();              //Prof. Wenbin Yu
      group[0]->end();                //Prof. Wenbin Yu
    }

    
    o->end();
  }
  
  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();
  
  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow11::show(int pane)
{
	for (int i = 0; i < 1; i++)
		group[i]->hide();
	group[pane]->show();
	win->show();
}
void geometryContextWindow11::hide(int pane)
{

	win->hide();
}


geometryContextWindow12::geometryContextWindow12(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;
  
  int width = 70 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;
  
  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
			  "Parameters");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    
    {
      
      group[0] = new Fl_Group
	
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "elastic");                       //Prof. Wenbin Yu

      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW / 2, BH, "v1");
      input[0]->value("0");
      input[1] = new Fl_Input(2 * WB + IW, 2 * WB + 1 * BH, IW / 2, BH, "v2");
      input[1]->value("0");
      input[2] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW / 2, BH, "v3");
      input[2]->value("0");
      input[3] = new Fl_Input(2 * WB, 2 * WB + 2 * BH, IW / 2, BH, "C11");
      input[3]->value("1");
      input[4] = new Fl_Input(2 * WB + IW, 2 * WB + 2 * BH, IW / 2, BH, "C12");
      input[4]->value("0");
      input[5] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 2 * BH, IW / 2, BH, "C13");
      input[5]->value("0");
      input[6] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW / 2, BH, "C21");
      input[6]->value("0");
      input[7] = new Fl_Input(2 * WB + IW, 2 * WB + 3 * BH, IW / 2, BH, "C22");
      input[7]->value("1");
      input[8] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 3 * BH, IW / 2, BH, "C23");
      input[8]->value("0");
      input[9] = new Fl_Input(2 * WB, 2 * WB + 4 * BH, IW / 2, BH, "C31");
      input[9]->value("0");
      input[10] = new Fl_Input(2 * WB + IW, 2 * WB + 4 * BH, IW / 2, BH, "C32");
      input[10]->value("0");
      input[11] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 4 * BH, IW / 2, BH, "C33");
      input[11]->value("1");
      input[12] = new Fl_Input(2 * WB, 2 * WB + 5 * BH, IW / 2, BH, "e11");
      input[12]->value("0");
      input[13] = new Fl_Input(2 * WB + IW, 2 * WB + 5 * BH, IW / 2, BH, "e22");
      input[13]->value("0");
      input[14] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 5 * BH, IW / 2, BH, "2e12");
      input[14]->value("0");
      input[15] = new Fl_Input(2 * WB + 3 * IW, 2 * WB + 5 * BH, IW / 2, BH, "k11");
      input[15]->value("0");
      input[16] = new Fl_Input(2 * WB + 4 * IW, 2 * WB + 5 * BH, IW / 2, BH, "k22");
      input[16]->value("0");
      input[17] = new Fl_Input(2 * WB + 5 * IW, 2 * WB + 5 * BH, IW / 2, BH, "k12+k21");
      input[17]->value("0");
      //Prof. Wenbin Yu
      for (int i = 0; i < 18; i++)   input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 2 * WB + 9 * BH, BB, BH, "Save");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb4);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 9 * BH, BB, BH, "Run");    //Prof. Yu
	o->callback(vamuch_choose_executable_cb, (void*)"dehomo2");
      }
      
      //group[0]->end();              //Prof. Wenbin Yu
      group[0]->end();                //Prof. Wenbin Yu
    }
    

    o->end();
  }

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();
  
  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow12::show(int pane)
{
  for (int i = 0; i < 1; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}
void geometryContextWindow12::hide(int pane)
{
  win->hide();
}
// Prof. Yu



// Add conductivity functions
geometryContextWindow21::geometryContextWindow21(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 40 * FL_NORMAL_SIZE;
  int height = 4 * WB + 9 * BH;

  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,
                          "Material Properties");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    {
      group[0] = new Fl_Group                                             
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Isotropic");         

      //Prof Yu add thermal parameters
      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW/2, BH, "Material ID number");
      input[0]->value("1");
      input[1] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW, BH, "Material Name");
      input[1]->value("MAT1");
      input[2] = new Fl_Input(2 * WB, 2 * WB + 3.5 * BH, IW/2, BH, "rho");
      input[2]->value("0");
      input[3] = new Fl_Input(2 * WB + IW, 2 * WB + 3.5 * BH, IW/2, BH, "Ti");
      input[3]->value("0");
      input[4] = new Fl_Input(2 * WB, 2 * WB + 2.5 * BH, IW/2, BH, "k");
      input[4]->value("0");

      for(int i = 0; i < 5; i++)   input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 2 * WB + 8 * BH, BB, BH, "Add");    
	o->callback(define_conductivity1);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 8 * BH, BB, BH, "Exit");    
	o->callback(con_exit_cb);
      }
	  group[0]->end();               
    }

    // 2: Add Orthotropic Material                                        
    {
      group[1] = new Fl_Group                                               
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Orthotropic");        
      input[5] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW/2, BH, "Material ID number");
      input[5]->value("1");
      input[6] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW, BH, "Material Name");
      input[6]->value("MAT1");
      input[7] = new Fl_Input(2 * WB, 2 * WB + 3.5 * BH, IW/2, BH, "rho");
      input[7]->value("0");
      input[8] = new Fl_Input(2 * WB+ IW, 2 * WB + 3.5 * BH, IW/2, BH, "Ti");
      input[8]->value("0");
      input[9] = new Fl_Input(2 * WB, 2 * WB + 2.5 * BH, IW/2, BH, "k11");
      input[9]->value("0");
      input[10] = new Fl_Input(2 * WB + IW, 2 * WB + 2.5 * BH, IW/2, BH, "k22");
      input[10]->value("0");
      input[11] = new Fl_Input(2 * WB + 2*IW, 2 * WB + 2.5 * BH, IW/2, BH, "k33");
      input[11]->value("0");

      for (int i = 5; i < 12; i++)   input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 2 * WB + 8 * BH, BB, BH, "Add");    
	o->callback(define_conductivity2);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 8 * BH, BB, BH, "Exit");    
	o->callback(con_exit_cb);
      }
      group[1]->end();                
    }

    // 3: Add Anisotropic Material                               
    {
      group[2] = new Fl_Group                    
	(WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Anisotropic");
      
      input[12] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW/2, BH, "Material ID number");
      input[12]->value("1");
      input[13] = new Fl_Input(2 * WB + 2 * IW, 2 * WB + 1 * BH, IW, BH, "Material Name");
      input[13]->value("MAT1");
      input[14] = new Fl_Input(2 * WB, 2 * WB + 5.5 * BH, IW/2, BH, "rho");
      input[14]->value("0");
      input[15] = new Fl_Input(2 * WB+ IW, 2 * WB + 5.5 * BH, IW/2, BH, "Ti");
      input[15]->value("0");
      input[16] = new Fl_Input(2 * WB, 2 * WB + 2.5 * BH, IW/2, BH, "k11");
      input[16]->value("0");
      input[17] = new Fl_Input(2 * WB + IW, 2 * WB + 2.5 * BH, IW/2, BH, "k12");
      input[17]->value("0");
      input[18] = new Fl_Input(2 * WB + 2*IW, 2 * WB + 2.5 * BH, IW/2, BH, "k13");
      input[18]->value("0");
      input[19] = new Fl_Input(2 * WB + IW, 2 * WB + 3.5 * BH, IW/2, BH, "k22");
      input[19]->value("0");
      input[20] = new Fl_Input(2 * WB + 2*IW, 2 * WB + 3.5 * BH, IW/2, BH, "k23");
      input[20]->value("0");
      input[21] = new Fl_Input(2 * WB + 2*IW, 2 * WB + 4.5 * BH, IW/2, BH, "k33");
      input[21]->value("0");
      
      for(int i = 12; i < 22; i++)   input[i]->align(FL_ALIGN_RIGHT);
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - 2 * BB - 5 * WB, 2 * WB + 8 * BH, BB, BH, "Add");    
	o->callback(define_conductivity3);
      }
      {
	Fl_Return_Button *o = new Fl_Return_Button
	  (width - BB - 2 * WB, 2 * WB + 8 * BH, BB, BH, "Exit");   
	o->callback(con_exit_cb);
      }
      group[2]->end();              
    }
    o->end();
  }

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow21::show(int pane)
{
  for(int i = 0; i < 3; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}
void geometryContextWindow21::hide(int pane)
{
  win->hide();
}


meshContextWindow::meshContextWindow(int deltaFontSize)
{
  FL_NORMAL_SIZE -= deltaFontSize;

  static Fl_Menu menu_transfinite_dir[] = {
    {"Left", 0, 0, 0},
    {"Right", 0, 0, 0},
    {"Alternated", 0, 0, 0},
    {0}
  };

  int width = 29 * FL_NORMAL_SIZE;
  int height = 4 * WB + 4 * BH;

  win = new paletteWindow
    (width, height, CTX::instance()->nonModalWindows, "Contextual Mesh Definitions");
  win->box(GMSH_WINDOW_BOX);
  {
    Fl_Tabs *o = new Fl_Tabs(WB, WB, width - 2 * WB, height - 2 * WB);
    // 0: Element size at points
    {
      group[0] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Element size at points");
      input[0] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW, BH, "Value");
      input[0]->value("0.1");
      input[0]->align(FL_ALIGN_RIGHT);
      group[0]->end();
    }
    // 1: Transfinite line
    {
      group[1] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Transfinite Line");
      input[1] = new Fl_Input(2 * WB, 2 * WB + 1 * BH, IW, BH, "Number of points");
      input[1]->value("10");
      input[2] = new Fl_Input(2 * WB, 2 * WB + 3 * BH, IW, BH, "Parameter");
      input[2]->value("1");
      for(int i = 1; i < 3; i++) {
        input[i]->align(FL_ALIGN_RIGHT);
      }
      static Fl_Menu_Item menu_trsf_mesh[] = {
        {"Progression", 0, 0, 0},
        {"Bump", 0, 0, 0},
        {0}
      };
      choice[0] = new Fl_Choice(2 * WB, 2 * WB + 2 * BH, IW, BH, "Type");
      choice[0]->menu(menu_trsf_mesh);
      choice[0]->align(FL_ALIGN_RIGHT);
      group[1]->end();
    }

    // 2: Transfinite surface
    {
      group[2] = new Fl_Group
        (WB, WB + BH, width - 2 * WB, height - 2 * WB - BH, "Transfinite Surface");

      choice[1] = new Fl_Choice
        (2 * WB, 2 * WB + 1 * BH, IW, BH, "Transfinite Arrangement");
      choice[1]->menu(menu_transfinite_dir);
      choice[1]->align(FL_ALIGN_RIGHT);

      group[2]->end();
    }
    o->end();
  }

  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void meshContextWindow::show(int pane)
{
  for(int i = 0; i < 3; i++)
    group[i]->hide();
  group[pane]->show();
  win->show();
}

static void SelectGroup_CB2(Fl_Widget*, void*){
  //std::string str((const char*)data);
  if(FlGui::instance()->geoContext20->bro->value()==2)
    fl_message("duang!");

}

geometryContextWindow20::geometryContextWindow20(int deltaFontSize)
{
  
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 18 * FL_NORMAL_SIZE;
  int height = 4 * WB + 10 * BH;
  //int L = 7 * FL_NORMAL_SIZE;
  int BW = width - 4 * WB;
  win = new paletteWindow(width, height, CTX::instance()->nonModalWindows ? true : false,"Materials edit");
  
  win->box(GMSH_WINDOW_BOX);
  bro = new Fl_Hold_Browser(0,0,width, height);
  bro->box(GMSH_SIMPLE_RIGHT_BOX);
  bro->has_scrollbar(Fl_Browser_::VERTICAL);
  bro->add("Materials:");
  //bro->add("Rectangular");
  //bro->add("I");
  //bro->add("Box");
  //bro->add("Circle");
  //bro->add("Pipe");
  //bro->callback(SelectGroup_CB);
  bro->value(1);
  bro->callback(SelectGroup_CB2);
  width = 32 * FL_NORMAL_SIZE;
  
  win->position(CTX::instance()->ctxPosition[0], CTX::instance()->ctxPosition[1]);
  win->end();

  FL_NORMAL_SIZE += deltaFontSize;
}

void geometryContextWindow20::show(int pane)
{
	win->show();
}

void geometryContextWindow20::hide(int pane)
{

	win->hide();
}


/* */
void msh4_1dsg(std::string name, std::string t3name, int sg_flags){
  std::ofstream inputSC;
  std::ifstream t3file(t3name.c_str());
  inputSC.open((name.c_str()));
  //change_sg(1);

  std::string tfilename = GModel::current()->getFileName() + ".t";
  std::ifstream tfile(tfilename.c_str());
  std::string readout;
  std::string ThreeD = "3D";
  std::string shell = "shell";
  std::string plate = "plate";
  std::vector<std::string> thdchar;
  std::vector<std::string> BSPchar;
  std::string tempthD;
  std::string tempBSP;
  int thermal_flags=0;
  while (getline(tfile, readout))
    {
      if (readout.find(shell) != std::string::npos)
	{
	  size_t pos = readout.find(shell);
	  readout.erase(0, pos + 6);
	  while (readout.find(",") != std::string::npos)
	    {
	      size_t pos1 = readout.find(",");
	      tempBSP = readout.substr(0, pos1);
	      readout.erase(0, pos1 + 1);
	      BSPchar.push_back(tempBSP);
	    }
	  BSPchar.push_back(readout);
	  if (BSPchar[0] == "0-Kirchhoff-Love shell") inputSC << 0 << "      # structural submode\n";
	  else if (BSPchar[0] == "1-Reissner-Mindlin shell") inputSC << 1 << "      # structural submode\n";
	  inputSC <<  BSPchar[1].c_str() << " " <<  BSPchar[2].c_str() << "  # initial	curvatures\n";
	}
      if (readout.find(plate) != std::string::npos)
	{
	  size_t pos = readout.find(plate);
	  readout.erase(0, pos + 6);
	  while (readout.find(",") != std::string::npos)
	    {
	      size_t pos1 = readout.find(",");
	      tempBSP = readout.substr(0, pos1);
	      readout.erase(0, pos1 + 1);
	      BSPchar.push_back(tempBSP);
	    }
	  BSPchar.push_back(readout);
	  if (BSPchar[0] == "0-Kirchhoff-Love plate") inputSC << 0 << "      # structural submode\n";
	  else if (BSPchar[0] == "1-Reissner-Mindlin plate") inputSC << 1 << "      # structural submode\n";
	  inputSC << 0 << "  " << 0 << "   # initial	curvatures\n";
	}
      if (readout.find(ThreeD) != std::string::npos)
	{
	  size_t pos = readout.find(ThreeD);
	  readout.erase(0, pos + 3);
	  //tempthD = readout;
	  while (readout.find(",") != std::string::npos)
	    {
	      size_t pos1 = readout.find(",");
	      tempthD = readout.substr(0, pos1);
	      readout.erase(0, pos1 + 1);
	      thdchar.push_back(tempthD);
	    }
	  thdchar.push_back(readout);
	  for (int i = 0; i < 4; i++){
	    if (thdchar[i] == "0-elastic")  inputSC << "0  ";
	    else if (thdchar[i] == "1-thermoelastic") {inputSC << "1  "; thermal_flags=1;}
	    else if (thdchar[i] == "2-conduction") inputSC << "2  ";
	    else if (thdchar[i] == "3-piezoelectric/piezomagnetic") inputSC << "3  ";
	    else if (thdchar[i] == "4-thermoepiezoelectric/thermopiezomagnetic") inputSC << "4  ";
	    else if (thdchar[i] == "5-piezoelectromagnetic") inputSC << "5  ";
	    else if (thdchar[i] == "6-thermopiezoelectromagnetic") inputSC << "6  ";
	    else if (thdchar[i] == "0-regular elements") inputSC << "0  ";
	    else if (thdchar[i] == "1-one dimension degenerated") inputSC << "1  ";
	    else if (thdchar[i] == "2-two dimension degenerated") inputSC << "2  ";
	    else if (thdchar[i] == "0-global coordinate") inputSC << "0  ";
	    else if (thdchar[i] == "1-material coordinate") inputSC << "1  ";
	    else if (thdchar[i] == "0-uniform")
	      inputSC << "0        # analysis elem_flag trans_flag temp_flag\n";
	    else if (thdchar[i] == "1-not uniform")
	      inputSC << "1      # analysis elem_flag trans_flag temp_flag\n";
	  }
	}
    }


  while (getline(t3file, readout)){
      inputSC << readout << "\n";
  }
  
  std::string geoName = GModel::current()->getFileName();
  std::ifstream geofile(geoName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string Mattype1 = "orthotropic";
  std::string Mattype2 = "isotropic";
  std::string Mattype3 = "anisotropic";
  int lines = 0;
  int matinfor = 0;
  while (getline(geofile, readoutline)) {
    /* read orthotropic materials */
    if ((readoutline.find(Mattype1) != std::string::npos) && thermal_flags==0)
      { matinfor = 5; lines = matinfor; }
    else if ((readoutline.find(Mattype1) != std::string::npos) && thermal_flags==1)
      { matinfor = 6; lines = matinfor; }
    else if ((readoutline.find(Mattype1) != std::string::npos) && thermal_flags==2)
      { matinfor = 3; lines = matinfor; }
    /* read isotripic materials */
    if ((readoutline.find(Mattype2) != std::string::npos) && thermal_flags==0)
      { matinfor = 3; lines = matinfor; }
     else if ((readoutline.find(Mattype2) != std::string::npos) && thermal_flags==1)
       { matinfor = 4; lines = matinfor; }
     else if ((readoutline.find(Mattype2) != std::string::npos) && thermal_flags==2)
       { matinfor = 3; lines = matinfor; }
    /* read anisotropic materials */
    if ((readoutline.find(Mattype3) != std::string::npos) && thermal_flags==0)
      { matinfor = 8; lines = matinfor; }
    else if ((readoutline.find(Mattype3) != std::string::npos) && thermal_flags==1)
      { matinfor = 9; lines = matinfor; }
    else if ((readoutline.find(Mattype3) != std::string::npos) && thermal_flags==2)
      { matinfor = 5; lines = matinfor; }
    
    if (lines < matinfor && lines>0) {
      lines = lines - 1;
      inputSC << readoutline << "\n";
    }
    
    if (readoutline.find(point) != std::string::npos)
      {
	size_t pos = readoutline.find(point);
	readoutline.erase(0, pos + 16);
        inputSC << readoutline << "\n";
	lines = lines - 1;
      }
  } 

  
  if(sg_flags==1)
    inputSC << "\n\n" << len4SG << "\n";
  else
    inputSC << "\n\n" << 1 << "\n";
  t3file.close();
  geofile.close();
  inputSC.close();

}


