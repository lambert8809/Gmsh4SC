// Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#include <string.h>
#include <sstream>
#include "GmshConfig.h"
#include "GmshMessage.h"
#include "GModel.h"
#include "Numeric.h"
#include "StringUtils.h"
#include "Geo.h"
#include "GeoStringInterface.h"
#include "OpenFile.h"
#include "Context.h"
#include "OS.h"
#include "CheckGEO.h" // Prof. Yu

#include "onelabGroup.h"
#include "drawContext.h"
#include <FL/fl_ask.H>

#if defined(HAVE_PARSER)
#include "Parser.h"
#endif

#if defined(HAVE_ONELAB)
#include "onelab.h"
#endif
#if defined(HAVE_ONELAB2)
#include "OnelabDatabase.h"
#endif

void add_infile(std::string text, std::string fileName, bool forceDestroy)
{
  std::vector<std::string> split = SplitFileName(fileName);
  std::string noExt = split[0] + split[1], ext = split[2];
#if defined(HAVE_COMPRESSED_IO) && defined(HAVE_LIBZ)
  bool compressed = false;
  if(ext == ".gz"){
    ext = SplitFileName(noExt)[2];
    compressed = true;
  }
#endif
  // make sure we don't add stuff in a non-geo file
  if(!CTX::instance()->expertMode) {
    if(ext.size() && ext != ".geo" && ext != ".GEO" ){
      std::ostringstream sstream;
      sstream <<
        "A scripting command is going to be appended to a non-`.geo' file. Are\n"
        "you sure you want to proceed?\n\n"
        "You probably want to create a new `.geo' file containing the command\n"
        "`Merge \"" << split[1] + split[2] << "\";' and use that file instead.\n\n"
        "(To disable this warning in the future, select `Enable expert mode'\n"
        "in the option dialog.)";
      int ret = Msg::GetAnswer(sstream.str().c_str(), 2, "Cancel", "Proceed as is",
                               "Create new `.geo' file");
      if(ret == 2){
        std::string newFileName = split[0] + split[1] + ".geo";
        if(CTX::instance()->confirmOverwrite) {
          if(!StatFile(newFileName)){
            std::ostringstream sstream;
            sstream << "File '" << fileName << "' already exists.\n\n"
              "Do you want to replace it?";
            if(!Msg::GetAnswer(sstream.str().c_str(), 0, "Cancel", "Replace"))
              return;
          }
        }
        FILE *fp = Fopen(newFileName.c_str(), "w");
        if(!fp) {
          Msg::Error("Unable to open file '%s'", newFileName.c_str());
          return;
        }
        fprintf(fp, "Merge \"%s\";\n%s\n", (split[1] + split[2]).c_str(), text.c_str());
        fclose(fp);
        OpenProject(newFileName);
        return;
      }
      else if(ret == 0)
        return;
    }
  }

#if defined(HAVE_PARSER)
  std::string tmpFileName = CTX::instance()->homeDir + CTX::instance()->tmpFileName;
  gmshFILE gmsh_yyin_old = gmsh_yyin;
  FILE *tmp_file;
  if(!(tmp_file = Fopen(tmpFileName.c_str(), "w"))) {
    Msg::Error("Unable to open temporary file '%s'", tmpFileName.c_str());
    return;
  }
  fprintf(tmp_file, "%s\n", text.c_str());
  fclose(tmp_file);
  gmsh_yyin = gmshopen(tmpFileName.c_str(), "r");
  while(!gmsheof(gmsh_yyin)) {
    gmsh_yyparse();
  }
  gmshclose(gmsh_yyin);
  gmsh_yyin = gmsh_yyin_old;

  if(forceDestroy){
    // we need to start from scratch (e.g. if the command just parsed
    // could have deleted some entities)
    GModel::current()->destroy();
  }
  GModel::current()->importGEOInternals();
  CTX::instance()->mesh.changed = ENT_ALL;

  // here we have to be explicit otherwise we append compressed stuff to ascii
  // file!
#if defined(HAVE_COMPRESSED_IO) && defined(HAVE_LIBZ)
  if(compressed){
    gmshFILE fp = gmshopen(fileName.c_str(), "a");
    if(!fp) {
      Msg::Error("Unable to open file '%s'", fileName.c_str());
      return;
    }
    gmshprintf(fp, "%s\n", text.c_str());
    gmshclose(fp);
  }
  else{
    FILE *fp = Fopen(fileName.c_str(), "a");
    if(!fp) {
      Msg::Error("Unable to open file '%s'", fileName.c_str());
      return;
    }
    fprintf(fp, "%s\n", text.c_str());
    fclose(fp);
  }
#else
  FILE *fp = Fopen(fileName.c_str(), "a");
  if(!fp) {
    Msg::Error("Unable to open file '%s'", fileName.c_str());
    return;
  }
  fprintf(fp, "%s\n", text.c_str());
  fclose(fp);
#endif

#else
  Msg::Error("GEO file creation not available without Gmsh parser");
#endif

  // mark all Gmsh data as changed in onelab (will force e.g. a reload and a
  // remesh)
#if defined(HAVE_ONELAB)
  onelab::server::instance()->setChanged(true, "Gmsh");
#endif
#if defined(HAVE_ONELAB2)
  OnelabDatabase::instance()->setChanged(true, "Gmsh");
#endif
}

void coherence(std::string fileName)
{
  add_infile("Coherence;", fileName, true);
}

static std::string list2string(List_T *list)
{
  std::ostringstream sstream;
  for(int i = 0; i < List_Nbr(list); i++){
    int num;
    List_Read(list, i, &num);
    if(i) sstream << ", ";
    sstream << num;
  }
  return sstream.str();
}

void delet(List_T *list, std::string fileName, std::string what)
{
  std::ostringstream sstream;
  //sstream << "Delete {\n  " << what << "{" << list2string(list) << "};\n}";  //Prof. Yu
  //add_infile(sstream.str(), fileName, true);

  //Prof. Wenbin Yu
    if(what != "Physicals"){
		sstream << "Delete {\n  " << what << "{" << list2string(list) << "};\n}";
		add_infile(sstream.str(), fileName, true);
	}
    if(what == "Physicals"){
		sstream << "Delete Physicals;\n";
		Msg::StatusBar(true, "Done deleting all materialized surfaces");           //Prof. Wenbin Yu
		add_infile(sstream.str(), fileName);
	}
  //Prof. Wenbin Yu

}

void add_charlength(List_T *list, std::string fileName, std::string lc)
{
  std::ostringstream sstream;
  sstream << "Characteristic Length {" << list2string(list) << "} = " << lc << ";";
  add_infile(sstream.str(), fileName);
}

void add_recosurf(List_T *list, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Recombine Surface {" << list2string(list) << "};";
  add_infile(sstream.str(), fileName);
}

void add_trsfline(std::vector<int> &l, std::string fileName, std::string type,
                  std::string typearg, std::string pts)
{
  std::ostringstream sstream;
  sstream << "Transfinite Line {";
  for(unsigned int i = 0; i < l.size(); i++){
    if(i) sstream << ", ";
    sstream << l[i];
  }
  sstream << "} = " << pts;
  if(typearg.size()) sstream << " Using " << type << " " << typearg;
  sstream << ";";
  add_infile(sstream.str(), fileName);
}

void add_trsfsurf(std::vector<int> &l, std::string fileName, std::string dir)
{
  std::ostringstream sstream;
  sstream << "Transfinite Surface {" << l[0] << "}";
  if(l.size() > 1){
    sstream << " = {";
    for(unsigned int i = 1; i < l.size(); i++) {
      if(i > 1) sstream << ", ";
      sstream << l[i];
    }
    sstream << "}";
  }
  if(dir != "Left")
    sstream << " " << dir;
  sstream << ";";
  add_infile(sstream.str(), fileName);
}

void add_trsfvol(std::vector<int> &l, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Transfinite Volume{" << l[0] << "} = {";
  for(unsigned int i = 1; i < l.size(); i++) {
    if(i > 1) sstream << ", ";
    sstream << l[i];
  }
  sstream << "};";
  add_infile(sstream.str(), fileName);
}

void add_embedded(std::string what, std::vector<int> &l, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Point{";
  for(unsigned int i = 1; i < l.size(); i++) {
    if(i > 1) sstream << ", ";
    sstream << l[i];
  }
  sstream << "} In Surface{" << l[0] << "};";
  add_infile(sstream.str(), fileName, true);
}

//Prof. Yu, add check data function
bool is_ok(std::string checknum){
  for(int i = 0; i < checknum.length(); i++)
    if(! (checknum[i] >= '0' && checknum[i] <= '9' || checknum[i] == ' ' || checknum[i] == 'e' || checknum[i] == '.' || checknum[i] == 'E' || checknum[i] == '-')) return false;
  return true;
}


//Prof. Wenbin Yu

void add_param(std::string num, std::string e1, std::string e2, std::string e3,
	       std::string g1, std::string g2, std::string g3,
	       std::string v1, std::string v2, std::string v3,
	       std::string rho, std::string ti,
	       std::string alpha1, std::string alpha2,std::string alpha3,std::string ce,
	       std::string name,std::string fileName)
{
  // Check if input contains illege char
  if(std::atof(e1.c_str())==0) {fl_message("Young's Modules cannot be 0!"); return;};
  if (!is_ok(e1)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(e2)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(e3)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(g1)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(g2)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(g3)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(v1)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(v2)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(v3)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(rho)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ti)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha1)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha2)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha3)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ce)) {fl_message("Inputs contain illegal characters!"); return;};
  
  //Prof. Yu, check if the material has already been defined.
  std::ifstream geofile(fileName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string tempnum;
  while (getline(geofile, readoutline)) {
    if (readoutline.find(point) != std::string::npos)
      {
	size_t pos = readoutline.find(point);
	readoutline.erase(0, pos + 16);
	std::istringstream iss(readoutline);
	iss >> tempnum;
      }
    if (tempnum == num || num == "0") {
      fl_message("Please input a different material ID number!");
      return;
    }
  }
  geofile.close();
  // Prof, Yu.

  std::ostringstream sstream;

   //Prof. Wenbin Yu
  sstream << "\n// #" << num << ", orthotropic material\n// Material constants are arranged as:\n// temperature density\n// E1 E2 E3\n// G1 G2 G3\n// v1 v2 v3\n"
	  << "Physical Point(\"" << num << " 1 1\n"
	  << ti << " " << rho << "\n"
	  << e1 << " " << e2 << " " << e3 << "\n"
	  << g1 << " " << g2 << " " << g3 << "\n"
	  << v1 << " " << v2 << " " << v3 << "\n"
	  << alpha1 << " " << alpha2 << " " << alpha3 << " " << ce << "\n\") = {};\n"
	  << "// Material name: " << num
	  << " -- " << name << "\n";

   //Prof. Wenbin Yu
  add_infile(sstream.str(), fileName);
  std::string message = "Material " + num + " has been added !";
  fl_message(message.c_str());
  Msg::StatusBar(true, "Done adding an orthotropic material");           //Prof. Wenbin Yu
}



//Prof. Wenbin Yu
void add_param1(std::string num, std::string e, std::string v,
		std::string rho, std::string ti, std::string alpha, std::string ce,
		std::string name,std::string fileName)
{
  // Check if input contains illege char
  if(std::atof(e.c_str())==0) {fl_message("Young's Modules cannot be 0!"); return;};
  if (!is_ok(e)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(v)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ce)) {fl_message("Inputs contain illegal characters!"); return;};
  
//Prof. Yu, check if the material has already been defined.
  std::ifstream geofile(fileName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string tempnum;
  while (getline(geofile, readoutline)) {
    if (readoutline.find(point) != std::string::npos)
      {
	size_t pos = readoutline.find(point);
	readoutline.erase(0, pos + 16);
	std::istringstream iss(readoutline);
	iss >> tempnum;
      }
    if (tempnum == num || num == "0") {
      fl_message("Please input a different material ID number!");
      return;
    }
  }
  geofile.close();
  //Prof, Yu.

  std::ostringstream sstream;
  sstream << "\n// #" << num << ", isotropic material\n// Material constants are arranged as:\n// temperature density \n// E v\n"
	  << "Physical Point(\"" << num << " 0 1\n"
	  << ti << " " << rho << "\n"
	  << e << " " << v << "\n"
	  << alpha << " " << ce << "\n\") = {};\n"
	  << "// Material name: " << num
	  << " -- " << name << "\n";

  add_infile(sstream.str(), fileName);
  std::string message = "Material " + num + " has been added !";
	fl_message(message.c_str());
  Msg::StatusBar(true, "Done adding an isotropic material");
}

//void add_matname(std::string num, std::string name, std::string fileName){
  //std::ostringstream sstream;
  //sstream << "// Material name: " << num << " -- " << name << "\n";
  //add_infile(sstream.str(), fileName);
//}

void add_param2(std::string num, std::string c11, std::string c12, std::string c13, std::string c14, std::string c15, std::string c16,
		std::string c22, std::string c23, std::string c24, std::string c25, std::string c26,
		std::string c33, std::string c34, std::string c35, std::string c36,
		std::string c44, std::string c45, std::string c46,
		std::string c55, std::string c56,
		std::string c66,
		std::string rho, std::string ti,
		std::string alpha1, std::string alpha2,std::string alpha3,
		std::string alpha4, std::string alpha5,std::string alpha6,std::string ce,
		std::string name,std::string fileName)
{
  // Check if input contains illege char
  if(std::atof(c11.c_str())==0) {fl_message("Young's Modules cannot be 0!"); return;};
  if(std::atof(c22.c_str())==0) {fl_message("Young's Modules cannot be 0!"); return;};
  if(std::atof(c33.c_str())==0) {fl_message("Young's Modules cannot be 0!"); return;};
  if (!is_ok(c11)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c12)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c13)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c14)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c15)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c16)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c22)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c23)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c24)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c25)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c26)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c33)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c34)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c35)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c36)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c44)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c45)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c46)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c55)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c56)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(c66)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(rho)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ti)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha1)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha2)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha3)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha4)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha5)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(alpha6)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ce)) {fl_message("Inputs contain illegal characters!"); return;};
  
  //Prof. Yu, check if the material has already been defined.
  std::ifstream geofile(fileName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string tempnum;
  while (getline(geofile, readoutline)) {
    if (readoutline.find(point) != std::string::npos)
      {
	size_t pos = readoutline.find(point);
	readoutline.erase(0, pos + 16);
	std::istringstream iss(readoutline);
	iss >> tempnum;
      }
    if (tempnum == num || num == "0") {
      fl_message("Please input a different material ID number!");
      return;
    }
  }
  geofile.close();
  //Prof, Yu.

  std::ostringstream sstream;
  sstream << "\n// #" << num << ", anisotropic material\n// Material constants are arranged as:\n// temperature density\n// c11 c12 c13 c14 c15 c16\n// c22 c23 c24 c25 c26\n// c33 c34 c35 c36\n// c44 c45 c46\n// c55 c56\n// c66\n"
	  << "Physical Point(\"" << num << " 2 1\n"
	  << ti << " " << rho << "\n"
	  << c11 << " " << c12 << " " << c13 << " " << c14 << " " << c15 << " " << c16 <<"\n"
	  << c22 << " " << c23 << " " << c24 << " " << c25 << " " << c26 <<"\n"
	  << c33 << " " << c34 << " " << c35 << " " << c36 <<"\n"
	  << c44 << " " << c45 << " " << c46 <<"\n"
	  << c55 << " " << c56 <<"\n"
	  << c66 << "\n"
	  << alpha1 << " " << alpha2 << " " << alpha3 << " " << alpha4 << " " << alpha5 << " "\
	  << alpha6 << " "<< ce << "\n\") = {};\n"
	  << "// Material name: " << num
	  << " -- " << name << "\n";

  add_infile(sstream.str(), fileName);
  std::string message = "Material " + num + " has been added !";
  fl_message(message.c_str());
  Msg::StatusBar(true, "Done adding an anisotropic material");
}


/* add conductivity functions */
// isotropic conductivity
void add_conduc1(std::string num, std::string name,
		 std::string rho, std::string ti, std::string ck,
		 std::string fileName)
{
  // Check if input contains illege char
  if (!is_ok(ck)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(num)) {fl_message("Inputs contain illegal characters!"); return;};
  
//Prof. Yu, check if the material has already been defined.
  std::ifstream geofile(fileName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string tempnum;
  while (getline(geofile, readoutline)) {
    if (readoutline.find(point) != std::string::npos)
      {
	size_t pos = readoutline.find(point);
	readoutline.erase(0, pos + 16);
	std::istringstream iss(readoutline);
	iss >> tempnum;
      }
    if (tempnum == num || num == "0") {
      fl_message("Please input a different material ID number!");
      return;
    }
  }
  geofile.close();
  //Prof, Yu.

  std::ostringstream sstream;
  sstream << "\n// #" << num << ", isotropic material\n// Material constants are arranged as:\n// temperature density \n// k\n"
	  << "Physical Point(\"" << num << " 0 1\n"
	  << ti << " " << rho << "\n"
	  << ck << "\n\") = {};\n"
	  << "// Material name: " << num
	  << " -- " << name << "\n";

  add_infile(sstream.str(), fileName);
  std::string message = "Material " + num + " has been added !";
  fl_message(message.c_str());
  Msg::StatusBar(true, "Done adding an isotropic material");
}

// add orthotropic conductivity
void add_conduc2(std::string num, std::string name,
		 std::string rho, std::string ti,
		 std::string ck11, std::string ck22, std::string ck33,
		 std::string fileName)
{
  // Check if input contains illege char
  if (!is_ok(ck11)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ck22)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ck33)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(num)) {fl_message("Inputs contain illegal characters!"); return;};
  
//Prof. Yu, check if the material has already been defined.
  std::ifstream geofile(fileName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string tempnum;
  while (getline(geofile, readoutline)) {
    if (readoutline.find(point) != std::string::npos)
      {
	size_t pos = readoutline.find(point);
	readoutline.erase(0, pos + 16);
	std::istringstream iss(readoutline);
	iss >> tempnum;
      }
    if (tempnum == num || num == "0") {
      fl_message("Please input a different material ID number!");
      return;
    }
  }
  geofile.close();
  //Prof, Yu.

  std::ostringstream sstream;
   sstream << "\n// #" << num << ", orthotropic material\n// Material constants are arranged as:\n// temperature density\n//k11 k22 k33\n"
	  << "Physical Point(\"" << num << " 1 1\n"
	  << ti << " " << rho << "\n"
	  << ck11 << " " << ck22 << " " << ck33 << "\n\") = {};\n"
	  << "// Material name: " << num
	  << " -- " << name << "\n";

  add_infile(sstream.str(), fileName);
  std::string message = "Material " + num + " has been added !";
  fl_message(message.c_str());
  Msg::StatusBar(true, "Done adding an orthotropic material");
}

//add anisotropic conductivity
void add_conduc3(std::string num, std::string name,
		 std::string rho, std::string ti,
		 std::string ck11, std::string ck12, std::string ck13,
		 std::string ck22, std::string ck23, std::string ck33,
		 std::string fileName)
{
  // Check if input contains illege char
  if (!is_ok(ck11)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ck12)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ck13)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ck22)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ck23)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(ck33)) {fl_message("Inputs contain illegal characters!"); return;};
  if (!is_ok(num)) {fl_message("Inputs contain illegal characters!"); return;};
  
//Prof. Yu, check if the material has already been defined.
  std::ifstream geofile(fileName.c_str());
  std::string readoutline;
  std::string point = "Physical Point(\"";
  std::string tempnum;
  while (getline(geofile, readoutline)) {
    if (readoutline.find(point) != std::string::npos)
      {
	size_t pos = readoutline.find(point);
	readoutline.erase(0, pos + 16);
	std::istringstream iss(readoutline);
	iss >> tempnum;
      }
    if (tempnum == num || num == "0") {
      fl_message("Please input a different material ID number!");
      return;
    }
  }
  geofile.close();
  //Prof, Yu.

  std::ostringstream sstream;
  sstream << "\n// #" << num << ", anisotropic material\n// Material constants are arranged as:\n// temperature density\n// ck11 ck12 ck13\n// ck22 ck23\n// ck33\n"
	  << "Physical Point(\"" << num << " 2 1\n"
	  << ti << " " << rho << "\n"
	  << ck11 << " " << ck12 << " " << ck13 << "\n"
	  << ck22 << " " << ck23 <<"\n"
	  << ck33 << "\n\") = {};\n"
	  << "// Material name: " << num
	  << " -- " << name << "\n";

  add_infile(sstream.str(), fileName);
  std::string message = "Material " + num + " has been added !";
  fl_message(message.c_str());
  Msg::StatusBar(true, "Done adding an anisotropic material");
}


void add_flags1(std::string analysis, std::string elem, std::string trans, std::string temp,
					  std::string fileName)
{
	std::string tempp = fileName + ".t";
	std::ofstream tfile;
	tfile.open(tempp.c_str());
	tfile << "3D " << analysis << "," << elem << "," << trans << "," << temp << "\n";
	tfile.close();
	/*
    std::ostringstream sstream;
    sstream << "\n//type of analysis, type of elements, in which system does material define, temperature uniformity, unit cell dimension number\n"
	  << "Physical Point(\"" << analysis << "," << elem << "," << trans << "," << temp << "," << ndim << "," << area << "\") = {};\n";


  add_infile(sstream.str(), fileName);*/

  Msg::StatusBar(true, "Done setting flags1");
}

// Prof. Yu, add beam function
void add_flags2(std::string analysis, std::string elem, std::string trans, std::string temp,
		std::string Bmodel, std::string curvatures1, std::string curvatures2,
		std::string curvatures3, std::string oblique1,
		std::string oblique2, std::string fileName)
{
	std::string tempp = fileName + ".t";
	std::ofstream tfile;
	tfile.open(tempp.c_str());
	tfile << "beam " << Bmodel << "," << curvatures1 << "," << curvatures2 << "," << curvatures3 << "," << oblique1 << "," << oblique2 << "\n";
	tfile << "3D " << analysis << "," << elem << "," << trans << "," << temp << "\n";
	tfile.close();

	
	std::ostringstream sstream;
	sstream << "\n\n//beam section\n\n";


	add_infile(sstream.str(), fileName);

	Msg::StatusBar(true, "Done setting flags2");
}

// Prof. Yu, add shell function
void add_flags3(std::string analysis, std::string elem, std::string trans, std::string temp,
	        std::string Pmodel, std::string curvatures1, std::string curvatures2, std::string fileName)
{
	std::string tempp = fileName + ".t";
	std::ofstream tfile;
	tfile.open(tempp.c_str());
	tfile << "shell " << Pmodel << "," << curvatures1 << "," << curvatures2 << "\n";
	tfile << "3D " << analysis << "," << elem << "," << trans << "," << temp << "\n";
	tfile.close();
	/*
	std::ostringstream sstream;
	sstream << "\n//type of models,input structural curvatures\n"
		<< "Physical Point(\"" << Pmodel << "," << curvatures1 << ", " << curvatures2 << "\") = {};\n";


	add_infile(sstream.str(), fileName);*/

	Msg::StatusBar(true, "Done setting flags3");
}

// Prof. Yu, add plate function
void add_flags4(std::string analysis, std::string elem, std::string trans, std::string temp,
				std::string Pmodel, std::string fileName)
{
	std::string tempp = fileName + ".t";
	std::ofstream tfile;
	tfile.open(tempp.c_str());
	tfile << "plate " << Pmodel << "\n";
	tfile << "3D " << analysis << "," << elem << "," << trans << "," << temp << "\n";
	tfile.close();
	/*
	std::ostringstream sstream;
	sstream << "\n//type of models,input structural curvatures\n"
		<< "Physical Point(\"" << Pmodel <<  "\") = {};\n";


	add_infile(sstream.str(), fileName);*/

	Msg::StatusBar(true, "Done setting flags4");
}





// Prof. Yu, add common 2D SG
void add_Model1(std::string SG2model, std::string volumef, std::string volumeI, std::string mat1, std::string mat2, std::string mat3, std::string fileName)
{
  std::ostringstream sstream;
  double vf1 = atof(volumef.c_str());
  double vf2 = atof(volumeI.c_str());
  double w, h1, h2, f1, r1, f2, r2, r12, r22, lc, zero;
  w = 1;
  h1 = 1;
  zero = 0;
  h2 = sqrt(3);
  f1 = vf1*w*h1;
  r1 = sqrt(f1 / 3.1415926);
  f2 = w*h2;
  r2 = sqrt(vf1*f2/2/3.1415926);
  r12 = sqrt((vf1 + vf2) / 3.1415926);
  r22 = sqrt((vf1+vf2)*f2/2/3.1415926);

  lc = 0.1;

  if (SG2model == "Select type of models:") {fl_message("Please chosse a model !"); return;}
  if (mat1 == "Select material:") {fl_message("Fiber properties have not been defined !"); return;}
  if (mat2 == "Select material:") {fl_message("Matrix properties have not been defined !"); return;}
  if (mat3 == "Select material:" && vf2 != 0) {fl_message("Interphase properties have not been defined !"); return;}
  if (mat1 == mat2 || mat1 == mat3 || mat2 == mat3)  {fl_message("Materials id number must be different for fiber, matrix and interphase !"); return;}

  std::string mmat1, mmat2, mmat3;
  std::istringstream iss1(mat1);
  std::istringstream iss2(mat2);
  std::istringstream iss3(mat3);
  iss1 >> mmat1;
  iss2 >> mmat2;
  iss3 >> mmat3;

  if (SG2model == "Square Pack Microstructure") {
    if (vf1 + vf2 > 0.785) {fl_message("Wrong volume fraction!"); return;}
    if ( vf2 < 0.000001){
      sstream << "// Typical 2D SG: " << SG2model << " ;\n"
			<< "\n//Define fiber volume\n"
	      << "//MATID " << mmat1 << " " << mmat2 << " ;\n"
			<< "//volume fraction = " << vf1 << ";\n"
			<< "r = " << r1 << " ;\n\n"
			<< "Point(1) = {" << -h1 / 2 << ", " << -w / 2 << ", 0, "<< lc << "};\n"
			<< "Point(2) = {" << h1 / 2 << ", " << -w / 2 << ", 0, " << lc << "};\n"
			<< "Point(3) = {" << h1 / 2 << ", " << w / 2 << ", 0, " << lc << "};\n"
			<< "Point(4) = {" << -h1 / 2 << ", " << w / 2 << ", 0, " << lc << "};\n"
			<< "Point(5) = {" << zero << ", " << zero << ", 0, " << lc << "};\n"
			<< "Point(6) = {" << zero << ", " << r1 << ", 0, " << lc << "};\n"
			<< "Point(7) = {" << zero << ", " << -r1 << ", 0, " << lc << "};\n"
			<< "Point(8) = {" << r1 << ", " << zero << ", 0, " << lc << "};\n"
			<< "Point(9) = {" << -r1 << ", " << zero << ", 0, " << lc << "};\n"
			<< "Line(1) = { 4, 1 }; \n"
			<< "Line(2) = { 1, 2 }; \n"
			<< "Line(3) = { 2, 3 }; \n"
			<< "Line(4) = { 3, 4 }; \n"
			<< "Circle(5) = {9, 5, 7}; \n"
			<< "Circle(6) = {7, 5, 8}; \n"
			<< "Circle(7) = {8, 5, 6}; \n"
			<< "Circle(8) = { 6, 5, 9}; \n"
			<< "Line Loop(9) = { 4, 1, 2, 3 }; \n"
			<< "Line Loop(10) = { 8, 5, 6, 7 }; \n"
			<< "Plane Surface(11) = { 9, 10 }; \n"
			<< "Plane Surface(12) = { 10 }; \n"
			<< "Physical Surface(" << mmat1 << ") = { 12 }; \n"
				<< "Physical Surface(" << mmat2 << ") = { 11 }; \n"
				<< "Transfinite Line {1, 4, 3, 2} = 50 Using Progression 1; \n"
				<< "Periodic Line {1} = {-3}; \n"
				<< "Periodic Line {2} = {-4}; \n";
    }
		else {
			/*for (int i = 0; i < mindex.size(); i++)
				if ( mindex[i] == mat3 ) matflag = 1;
				if (matflag != 1) {
					fl_message("Interphase material is not defined!");
					return;
				}*/
			sstream << "// Typical 2D SG: " << SG2model << " ;\n"
			<< "\n//Define fiber volume\n"
			<< "//fiber volume fraction = " << vf1 << ";\n"
			<< "//interpharse volume fraction = " << vf2 << ";\n"
			<< "r1 = " << r1 << ";\n"
			<< "r2 = " << r12 << ";\n\n"
			<< "Point(1) = {" << -h1 / 2 << ", " << -w / 2 << ", 0, "<< lc << "};\n"
			<< "Point(2) = {" << h1 / 2 << ", " << -w / 2 << ", 0, " << lc << "};\n"
			<< "Point(3) = {" << h1 / 2 << ", " << w / 2 << ", 0, " << lc << "};\n"
			<< "Point(4) = {" << -h1 / 2 << ", " << w / 2 << ", 0, " << lc << "};\n"
			<< "Point(5) = {" << zero << ", " << zero << ", 0, " << lc << "};\n"
			<< "Point(6) = {" << zero << ", " << r1 << ", 0, " << lc << "};\n"
			<< "Point(7) = {" << zero << ", " << -r1 << ", 0, " << lc << "};\n"
			<< "Point(8) = {" << r1 << ", " << zero << ", 0, " << lc << "};\n"
			<< "Point(9) = {" << -r1 << ", " << zero << ", 0, " << lc << "};\n"
			<< "Point(10) = {" << zero << ", " << r12 << ", 0, " << lc << "};\n"
			<< "Point(11) = {" << zero << ", " << -r12 << ", 0, " << lc << "};\n"
			<< "Point(12) = {" << r12 << ", " << zero << ", 0, " << lc << "};\n"
			<< "Point(13) = {" << -r12 << ", " << zero << ", 0, " << lc << "};\n"
			<< "Line(3) = {3, 4}; \n"
			<< "Line(4) = {4, 1}; \n"
			<< "Line(5) = {1, 2}; \n"
			<< "Line(6) = {2, 3}; \n"
			<< "Circle(7) = {6, 5, 9}; \n"
			<< "Circle(8) = {9, 5, 7}; \n"
			<< "Circle(9) = {7, 5, 8}; \n"
			<< "Circle(10) = {8, 5, 6}; \n"
			<< "Circle(11) = {10, 5, 13}; \n"
			<< "Circle(12) = {13, 5, 11}; \n"
			<< "Circle(13) = {11, 5, 12}; \n"
			<< "Circle(14) = {12, 5, 10}; \n"
			<< "Line Loop(15) = {3, 4, 5, 6}; \n"
			<< "Line Loop(16) = {11, 12, 13, 14}; \n"
			<< "Plane Surface(17) = {15, 16}; \n"
			<< "Line Loop(18) = {7, 8, 9, 10}; \n"
			<< "Plane Surface(19) = {16, 18}; \n"
			<< "Plane Surface(20) = {18}; \n"
			<< "Physical Surface(" << mmat1 << ") = { 20 }; \n"
			<< "Physical Surface(" << mmat2 << ") = { 17 }; \n"
			<< "Physical Surface(" << mmat3 << ") = { 19 }; \n"
		        << "Transfinite Line {5, 4, 3, 6} = 50 Using Progression 1; \n"
			<< "Periodic Line {4} = {-6}; \n"
				<< "Periodic Line {3} = {-5}; \n";
		}

	}

	if (SG2model == "Hexagonal Pack Microstructure") {
	  if (vf1 + vf2 > 0.9) {fl_message("Wrong volume fraction!"); return;}
	  if ( vf2 < 0.000001){
		sstream << "// Typical 2D SG: " << SG2model << " ;\n"
			<< "\n//Define fiber volume\n"
			<< "//volume fraction = " << vf1 << ";\n"
			<< "l = " << w << ";\n\n"
			<< "Point(1) = {" << -w / 2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(2) = {" <<  w / 2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(3) = {" <<  w / 2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(4) = {" << -w / 2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(5) = {" << -w / 2 + r2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(6) = {" << -w / 2 << ", " << h2/ 2 - r2 << ", 0, " << lc << "};\n"
			<< "Point(7) = {" <<  w / 2 - r2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(8) = {" <<  w / 2 << ", " << h2 / 2 - r2 << ", 0, " << lc << "};\n"
			<< "Point(9) = {" <<  w / 2 << ", " << -h2 / 2 + r2 << ", 0, " << lc << "};\n"
			<< "Point(10) = {" <<  w / 2 - r2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(11) = {" << -w / 2 + r2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(12) = {" << -w / 2 << ", " << -h2 / 2 + r2 << ", 0, " << lc << "};\n"
			<< "Point(13) = {" << 0 << ", " << 0 << ", 0, " << lc << "};\n"
			<< "Point(14) = {" << 0 << ", " << -r2 << ", 0, " << lc << "};\n"
			<< "Point(15) = {" << r2 << ", " << 0 << ", 0, " << lc << "};\n"
			<< "Point(16) = {" << 0 << ", " << r2 << ", 0, " << lc << "};\n"
			<< "Point(17) = {" << -r2 << ", " << 0 << ", 0, " << lc << "};\n"
			<< "Line(3) = {2, 7}; \n"
			<< "Line(4) = {7, 5}; \n"
			<< "Line(5) = {5, 1}; \n"
			<< "Line(6) = {1, 6}; \n"
			<< "Line(7) = {6, 12}; \n"
			<< "Line(8) = {12, 4}; \n"
			<< "Line(9) = {4, 11}; \n"
			<< "Line(10) = {11, 10}; \n"
			<< "Line(11) = {10, 3}; \n"
			<< "Line(12) = {3, 9}; \n"
			<< "Line(13) = {9, 8}; \n"
			<< "Line(14) = {8, 2}; \n"
			<< "Circle(15) = {5, 1, 6}; \n"
			<< "Circle(16) = {12, 4, 11}; \n"
			<< "Circle(17) = {10, 3, 9}; \n"
			<< "Circle(18) = {8, 2, 7}; \n"
			<< "Circle(19) = {16, 13, 17}; \n"
			<< "Circle(20) = {17, 13, 14}; \n"
			<< "Circle(21) = {14, 13, 15}; \n"
			<< "Circle(22) = {15, 13, 16}; \n"
			<< "Line Loop(23) = {5, 6, -15}; \n"
			<< "Plane Surface(24) = {23}; \n"
			<< "Line Loop(25) = {3, -18, 14}; \n"
			<< "Plane Surface(26) = {25}; \n"
			<< "Line Loop(27) = {20, 21, 22, 19}; \n"
			<< "Plane Surface(28) = {27}; \n"
			<< "Line Loop(29) = { 8, 9, -16}; \n"
			<< "Plane Surface(30) = {29}; \n"
			<< "Line Loop(31) = { 11, 12, -17}; \n"
			<< "Plane Surface(32) = {31}; \n"
			<< "Line Loop(33) = {4, 15, 7, 16, 10, 17, 13, 18}; \n"
			<< "Plane Surface(34) = {33, 27}; \n"
			<< "Physical Surface(" << mmat1 << ") = { 24, 26, 28, 30, 32 }; \n"
			<< "Physical Surface(" << mmat2 << ") = { 34 }; \n"
			<< "Transfinite Line {6, 5, 4, 3, 14, 12, 11, 10, 9, 8} = 8 Using Progression 1; \n"
			<< "Transfinite Line {7, 13} = 20 Using Progression 1; \n"
			<< "Transfinite Line {15,16,17,18,19,20,21,22} = 10 Using Progression 1; \n"
			<< "Periodic Line {6} = {-14}; \n"
			<< "Periodic Line {7} = {-13}; \n"
			<< "Periodic Line {8} = {-12}; \n"
			<< "Periodic Line {3} = {-11}; \n"
			<< "Periodic Line {4} = {-10}; \n"
			<< "Periodic Line {5} = {-9}; \n";

	  }
	  else {
			/*for (int i = 0; i < mindex.size(); i++)
				if ( mindex[i] == mat3 ) matflag = 1;
				if (matflag != 1) {
					fl_message("Interphase material is not defined!");
					return;
				}*/
	    sstream << "// Typical 2D SG: " << SG2model << " ;\n"
	     	        << "\n//Define fiber volume\n"
			<< "//fiber volume fraction = " << vf1 << ";\n"
			<< "//interpharse volume fraction = " << vf2 << ";\n"
			<< "r1 = " << r2 << ";\n"
			<< "r2 = " << r22 << ";\n\n"
		    	<< "Point(1) = {" << -w / 2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(2) = {" <<  w / 2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(3) = {" <<  w / 2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(4) = {" << -w / 2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(5) = {" << -w / 2 + r2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(6) = {" << -w / 2 << ", " << h2/ 2 - r2 << ", 0, " << lc << "};\n"
			<< "Point(7) = {" <<  w / 2 - r2 << ", " << h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(8) = {" <<  w / 2 << ", " << h2 / 2 - r2 << ", 0, " << lc << "};\n"
			<< "Point(9) = {" <<  w / 2 << ", " << -h2 / 2 + r2 << ", 0, " << lc << "};\n"
			<< "Point(10) = {" <<  w / 2 - r2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(11) = {" << -w / 2 + r2 << ", " << -h2 / 2 << ", 0, " << lc << "};\n"
			<< "Point(12) = {" << -w / 2 << ", " << -h2 / 2 + r2 << ", 0, " << lc << "};\n"
			<< "Point(13) = {" << 0 << ", " << 0 << ", 0, " << lc << "};\n"
			<< "Point(14) = {" << 0 << ", " << -r2 << ", 0, " << lc << "};\n"
			<< "Point(15) = {" << r2 << ", " << 0 << ", 0, " << lc << "};\n"
			<< "Point(16) = {" << 0 << ", " << r2 << ", 0, " << lc << "};\n"
			<< "Point(17) = {" << -r2 << ", " << 0 << ", 0, " << lc << "};\n"
		    << "Point(18) = {" << -w/2 + r22 << " ," <<  h2/2 << ", 0, " << lc << "};\n"
		    << "Point(19) = {" << -w/2  << " ," <<  h2/2 - r22 << ", 0, " << lc << "};\n"
		    << "Point(20) = {" << w/2 -r22 << " ," <<  h2/2 << ", 0, " << lc << "};\n"
		    << "Point(21) = {" << w/2  << " ," <<  h2/2-r22 << ", 0, " << lc << "};\n"
		    << "Point(22) = {" << w/2  << " ," <<  -h2/2+r22 << ", 0, " << lc << "};\n"
		    << "Point(23) = {" << w/2-r22  << " ," << -h2/2 << ", 0, " << lc << "};\n"
		    << "Point(24) = {" << -w/2+r22  << " ," << -h2/2 << ", 0, " << lc << "};\n"
		    << "Point(25) = {" << -w/2  << " ," << -h2/2+r22 << ", 0, " << lc << "};\n"
		    << "Point(26) = {" << 0  << " ," << -r22 << ", 0, " << lc << "};\n"
		    << "Point(27) = {" << r22  << " ," << 0 << ", 0, " << lc << "};\n"
		    << "Point(28) = {" << 0  << " ," << r22 << ", 0, " << lc << "};\n"
		    << "Point(29) = {" << -r22  << " ," << 0 << ", 0, " << lc << "};\n"
	            << "Line(3) = {2, 7}; \n"
		    << "Line(4) = {7, 20}; \n"
		    << "Line(5) = {20, 18}; \n"
		    << "Line(6) = {18, 5}; \n"
		    << "Line(7) = {5, 1}; \n"
		    << "Line(8) = {1, 6}; \n"
		    << "Line(9) = {6, 19}; \n"
		    << "Line(10) = {19, 25}; \n"
		    << "Line(11) = {25, 12}; \n"
		    << "Line(12) = {12, 4}; \n"
		    << "Line(13) = {4, 11}; \n"
		    << "Line(14) = {11, 24}; \n"
		    << "Line(15) = {24, 23}; \n"
		    << "Line(16) = {23, 10}; \n"
		    << "Line(17) = {10, 3}; \n"
		    << "Line(18) = {3, 9}; \n"
		    << "Line(19) = {9, 22}; \n"
		    << "Line(20) = {22, 21}; \n"
		    << "Line(21) = {21, 8}; \n"
		    << "Line(22) = {8, 2}; \n"
		    << "Circle(23) = {6, 1, 5}; \n"
		    << "Circle(24) = {19, 1, 18}; \n"
		    << "Circle(25) = {7, 2, 8}; \n"
		    << "Circle(26) = {20, 2, 21}; \n"
		    << "Circle(27) = {11, 4, 12}; \n"
		    << "Circle(28) = {24, 4, 25}; \n"
		    << "Circle(29) = {9, 3, 10}; \n"
		    << "Circle(30) = {22, 3, 23}; \n"
		    << "Circle(31) = {16, 13, 17}; \n"
		    << "Circle(32) = {17, 13, 14}; \n"
		    << "Circle(33) = {14, 13, 15}; \n"
		    << "Circle(34) = {15, 13, 16}; \n"
		    << "Circle(35) = {28, 13, 29}; \n"
		    << "Circle(36) = {29, 13, 26}; \n"
		    << "Circle(37) = {26, 13, 27}; \n"
		    << "Circle(38) = {27, 13, 28}; \n"
		    << "Line Loop(39) = {31, 32, 33, 34}; \n"
		    << "Plane Surface(40) = {39}; \n"
		    << "Line Loop(41) = {7, 8, 23}; \n"
		    << "Plane Surface(42) = {41}; \n"
		    << "Line Loop(43) = {3, 25, 22}; \n"
		    << "Plane Surface(44) = {43}; \n"
		    << "Line Loop(45) = {27, 12, 13}; \n"
		    << "Plane Surface(46) = {45}; \n"
		    << "Line Loop(47) = {29, 17, 18}; \n"
		    << "Plane Surface(48) = {47}; \n"
		    << "Line Loop(49) = {24, 6, -23, 9}; \n"
		    << "Plane Surface(50) = {49}; \n"
		    << "Line Loop(51) = {26, 21, -25, 4}; \n"
		    << "Plane Surface(52) = {51}; \n"
		    << "Line Loop(53) = {28, 11, -27, 14}; \n"
		    << "Plane Surface(54) = {53}; \n"
		    << "Line Loop(55) = {30, 16, -29, 19}; \n"
		    << "Plane Surface(56) = {55}; \n"
		    << "Line Loop(57) = {38, 35, 36, 37}; \n"
		    << "Plane Surface(58) = {57, 39}; \n"
		    << "Line Loop(59) = {5, -24, 10, -28, 15, -30, 20, -26}; \n"
		    << "Plane Surface(60) = {59, 57}; \n"
		    << "Physical Surface(" << mmat1 << ") = {40, 42, 44, 46, 48}; \n"
		    << "Physical Surface(" << mmat3 << ") = {50, 52, 54, 56, 58}; \n"
		    << "Physical Surface(" << mmat2 << ") = {60}; \n"
	      << "Transfinite Line {8, 7, 3, 22, 18, 17, 13, 12, 5, 15} = 8 Using Progression 1; \n"
			<< "Transfinite Line {10, 20} = 20 Using Progression 1; \n"
		    << "Periodic Line {8} = {-22}; \n"
			<< "Periodic Line {9} = {-21}; \n"
			<< "Periodic Line {10} = {-20}; \n"
			<< "Periodic Line {11} = {-19};	\n"
			<< "Periodic Line {12} = {-18}; \n"
			<< "Periodic Line {3} = {-17}; \n"
			<< "Periodic Line {4} = {-16}; \n"
			<< "Periodic Line {5} = {-15}; \n"
			<< "Periodic Line {6} = {-14}; \n"
			<< "Periodic Line {7} = {-13}; \n";
	      }
	}

	add_infile(sstream.str(), fileName);

	ClearProject();
	//GModel::current()->setFileName(fileName);
	//onelab_cb(0, (void*)"reset"); // this will call OpenProject
	//
	OpenProject(fileName);
	drawContext::global()->draw();
	Msg::StatusBar(true, "Done setting 2D SG");

}


void add_Model2(std::string SG3model, std::string volumef, std::string mat1, std::string mat2, std::string fileName)
{

	std::ostringstream sstream;
	double vf = atof(volumef.c_str());
	double w = 1;
	double h = 1;
	double t = 1;
	double f, r, r3, lc1, lc;
	f = vf*w*h*t;
	r3 = 3 * f / 4 / 3.1415926;
	r = pow(r3, 0.333333);
	double minn = (w < h) ? w : h;
	lc1 = (minn < t) ? minn : t;
	lc = lc1 / 10;

	if (SG3model == "Select type of models:") {fl_message("Please chosse a model !"); return;}
	if (mat1 == mat2){
	  fl_message("Materials id number must be different for fiber and matrix!");
	  return;
	}

	if (mat1 == "Select material:") {fl_message("Fiber properties have not been defined !"); return;}
	if (mat2 == "Select material:") {fl_message("Matrix properties have not been defined !"); return;}

	if (mat1 == mat2 )  {
	  fl_message("Materials id number must be different for fiber, matrix and interphase !");
	  return;
	}

	std::string mmat1, mmat2;
	std::istringstream iss1(mat1);
	std::istringstream iss2(mat2);
	iss1 >> mmat1;
	iss2 >> mmat2;


	if (SG3model == "Spherical Inclusions Microstructure") {
	  if (vf > 0.5236) {fl_message("Wrong volume fraction!"); return;}
		sstream << "// Typical 3D SG: " << SG3model << " ;\n"
			<< "\n//Define fiber volume\n"
			<< "//volume fraction = " << f << ";\n"
			<< "r = " << r << ";\n\n"
			<< "Point(1) = { " << -h / 2 << ", " << -w / 2 << ", " << -t / 2 << " , " << lc << " };\n"
			<< "Point(2) = { " << -h / 2 << ", " << w / 2 << ", " << -t / 2 << " , " << lc << " };\n"
			<< "Point(3) = { " << -h / 2 << ", " << w / 2 << ", " << t / 2 << " , " << lc << " };\n"
			<< "Point(4) = { " << -h / 2 << ", " << -w / 2 << ", " << t / 2 << " , " << lc << " };\n"
			<< "Translate{ 1, 0, 0 } { \n"
			<< "    Duplicata { Point{ 2, 3, 4, 1 }; }\n"
			<< "}\n"
			<< "Line(1) = { 6, 7 }; \n"
			<< "Line(2) = { 7, 8 }; \n"
			<< "Line(3) = { 8, 5 }; \n"
			<< "Line(4) = { 5, 6 }; \n"
			<< "Line(5) = { 2, 3 }; \n"
			<< "Line(6) = { 3, 4 }; \n"
			<< "Line(7) = { 4, 1 }; \n"
			<< "Line(8) = { 1, 2 }; \n"
			<< "Line(9) = { 2, 5 }; \n"
			<< "Line(10) = { 8, 1 }; \n"
			<< "Line(11) = { 7, 4 }; \n"
			<< "Line(12) = { 3, 6 }; \n"
			<< "Line Loop(13) = { 6, -11, -1, -12 }; \n"
			<< "Plane Surface(14) = { 13 }; \n"
			<< "Line Loop(15) = { 4, -12, -5, 9 }; \n"
			<< "Plane Surface(16) = { 15 }; \n"
			<< "Line Loop(17) = { 5, 6, 7, 8 }; \n"
			<< "Plane Surface(18) = { 17 }; \n"
			<< "Line Loop(19) = { 10, -7, -11, 2 }; \n"
			<< "Plane Surface(20) = { 19 }; \n"
			<< "Line Loop(21) = { 2, 3, 4, 1 }; \n"
			<< "Plane Surface(22) = { 21 }; \n"
			<< "Line Loop(23) = { 10, 8, 9, -3 }; \n"
			<< "Plane Surface(24) = { 23 }; \n"
			<< "Surface Loop(25) = { 14, 18, 16, 22, 20, 24 }; \n"
			<< "Point(9) = { 0, 0, 0, 0.1 }; \n"
			<< "Point(10) = { " << -r << ", 0, 0, 0.1 }; \n"
			<< "Point(11) = { 0," << r << ", 0, 0.1 }; \n"
			<< "Point(12) = { 0, 0," << r << ", 0.1 }; \n"
			<< "Circle(27) = { 11, 9, 10 }; \n"
			<< "Circle(28) = { 10, 9, 12 }; \n"
			<< "Circle(29) = { 12, 9, 11 }; \n"
			<< "Line Loop(30) = { 27, 28, 29 }; \n"
			<< "Ruled Surface(31) = { 30 }; \n"
			<< "Rotate{ { 0, 0, 1 },{ 0, 0, 0 }, Pi / 2 } {\n"
			<< "    Duplicata{ Surface{ 31 }; }\n"
			<< "}\n"
			<< "Rotate{ { 0, 0, 1 },{ 0, 0, 0 }, Pi / 2 } {\n"
			<< "    Duplicata{ Surface{ 32 }; }\n"
			<< "}\n"
			<< "Rotate{ { 0, 0, 1 },{ 0, 0, 0 }, Pi / 2 } {\n"
			<< "    Duplicata{ Surface{ 35 }; }\n"
			<< "}\n"
			<< "Rotate{ { 0, 1, 0 },{ 0, 0, 0 }, -Pi / 2 } {\n"
			<< "    Duplicata{ Surface{ 31 }; }\n"
			<< "}\n"
			<< "Rotate{ { 0, 1, 0 },{ 0, 0, 0 }, -Pi / 2 } {\n"
			<< "    Duplicata{ Surface{ 40 }; }\n"
			<< "}\n"
			<< "Rotate{ { 0, 0, 1 },{ 0, 0, 0 }, Pi / 2 } {\n"
			<< "    Duplicata{ Surface{ 40 }; }\n"
			<< "}\n"
			<< "Rotate{ { 0, 0, 1 },{ 0, 0, 0 }, Pi / 2 } {\n"
			<< "    Duplicata{ Surface{ 46 }; }\n"
			<< "}\n"
			<< "Surface Loop(50) = { 35, 49, 46, 40, 43, 38, 31, 32 };\n"
			<< "Volume(51) = { 25, 50 }; \n"
			<< "Volume(52) = { 50 };\n"
			<< "Transfinite Surface {22}; \n"
			<< "Transfinite Surface {18}; \n"
			<< "Transfinite Surface {14}; \n"
			<< "Transfinite Surface {16}; \n"
			<< "Transfinite Surface {20}; \n"
			<< "Transfinite Surface {24}; \n"
			<< "Physical Volume(" << mmat1 << ") = { 52 }; \n"
			<< "Physical Volume(" << mmat2 << ") = { 51 }; \n"
			<< "Periodic Surface 14{12, 6, 11, 1} = 24{9, -8, 10, -3}; \n"
			<< "Periodic Surface 16{4, 9, 5, 12} = 20{-2, -11, -7, -10}; \n"
			<< "Periodic Surface 18{5, 8, 7, 6} = 22{4, 3, 2, 1}; \n"
			<< "Mesh.Algorithm3D = 4 ;";
	}

	add_infile(sstream.str(), fileName);

	ClearProject();
	//GModel::current()->setFileName(fileName);
	//onelab_cb(0, (void*)"reset"); // this will call OpenProject
	//drawContext::global()->draw();
	OpenProject(fileName);
	drawContext::global()->draw();
	Msg::StatusBar(true, "Done setting 3D SG");

}


//Prof. Yu, generate dehomogenization file
void add_dehomoSolid1(std::string v1, std::string v2, std::string v3,
	std::string C11, std::string C12, std::string C13,
	std::string C21, std::string C22, std::string C23,
	std::string C31, std::string C32, std::string C33,
	std::string e1, std::string e2, std::string e3, std::string e4, std::string e5, std::string e6, std::string fileName)
{
	std::string tpostname;
	std::string suffix = ".geo";
	if (fileName.find(suffix) != std::string::npos)
		tpostname = fileName.substr(0,fileName.length() - 4);
	else
		tpostname = fileName;
	std::string temp = tpostname + ".msh" + ".glb";

	if(fileName.find(".sc")!=std::string::npos) temp=tpostname+".glb";
	  
	std::ofstream defile;
	defile.open(temp.c_str());
	defile << v1 << " " << v2 << " " << v3 << " \n"
		<< C11 << " " << C12 << " " << C13 << " \n"
		<< C21 << " " << C22 << " " << C23 << " \n"
		<< C31 << " " << C32 << " " << C33 << " \n"
		<< e1 << " " << e2 << " " << e3 << " " << e4 << " " << e5 << " " << e6 << " \n";
	defile.close();

	Msg::StatusBar(true, "Done writing input file for dehomogenization.");           //Prof. Wenbin Yu
}

void add_dehomoBeam1(std::string v1, std::string v2, std::string v3,
	std::string C11, std::string C12, std::string C13,
	std::string C21, std::string C22, std::string C23,
	std::string C31, std::string C32, std::string C33,
	std::string e11, std::string k11, std::string k12, std::string k13, std::string fileName)
{
	std::string tpostname;
	std::string suffix = ".geo";
	if (fileName.find(suffix) != std::string::npos)
		tpostname = fileName.substr(0,fileName.length() - 4);
	else
		tpostname = fileName;
	std::string temp = tpostname + ".msh" + ".glb";

	if(fileName.find(".sc")!=std::string::npos) temp=tpostname+".glb";
	
	std::ofstream defile;
	defile.open(temp.c_str());
	defile << v1 << " " << v2 << " " << v3 << " \n"
		<< C11 << " " << C12 << " " << C13 << " \n"
		<< C21 << " " << C22 << " " << C23 << " \n"
		<< C31 << " " << C32 << " " << C33 << " \n"
		<< e11 << " " << k11 << " " << k12 << " " << k13 << " \n";
	defile.close();

	Msg::StatusBar(true, "Done writing input file for dehomogenization.");           //Prof. Wenbin Yu
}

void add_dehomoSP1(std::string v1, std::string v2, std::string v3,
	std::string C11, std::string C12, std::string C13,
	std::string C21, std::string C22, std::string C23,
	std::string C31, std::string C32, std::string C33,
	std::string e1, std::string e2, std::string e3, std::string e4, std::string e5, std::string e6, std::string fileName)
{
	std::string tpostname;
	std::string suffix = ".geo";
	if (fileName.find(suffix) != std::string::npos)
		tpostname = fileName.substr(0,fileName.length() - 4);
	else
		tpostname = fileName;
	std::string temp = tpostname + ".msh" + ".glb";

	if(fileName.find(".sc")!=std::string::npos) temp=tpostname+".glb";
	
	std::ofstream defile;
	defile.open(temp.c_str());
	defile << v1 << " " << v2 << " " << v3 << " \n"
		<< C11 << " " << C12 << " " << C13 << " \n"
		<< C21 << " " << C22 << " " << C23 << " \n"
		<< C31 << " " << C32 << " " << C33 << " \n"
		<< e1 << " " << e2 << " " << e3 << " " << e4 << " " << e5 << " " << e6 << " \n";
	defile.close();

	Msg::StatusBar(true, "Done writing input file for dehomogenization.");           //Prof. Wenbin Yu
}


//Prof. Wenbin Yu
static std::string periodiclist2string(List_T *list)
{
  std::ostringstream sstream;

  for(int i = 0; i < List_Nbr(list); i++){
    if(i%2==0) {
		int num;
		if(i) sstream << ",";
		List_Read(list, i, &num);
		sstream << num;
	}
  }
  sstream << "}={";
  for(int i = 0; i < List_Nbr(list); i++){
    if(i%2==1) {
		int num;
		if(i-1) sstream << ",";
		List_Read(list, i, &num);
		sstream << -num;
	}
  }

  return sstream.str();
}

//Prof. Wenbin Yu
void add_periodic_line(List_T *list, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Periodic Line {" << periodiclist2string(list) << "};";
  add_infile(sstream.str(), fileName);
}

//wenbin yu, periodic surface
static std::string periodicsurflist2string(List_T *list)
{
  //Prof. Yu
  std::vector<int> pnum;
  int p1, p2;
  CheckGEO test1;
  std::string namen = GModel::current()->getFileName();


	std::ostringstream sstream;
//example: input: Periodic Surface {14, 20, 11, 12, 4, 2, 5, 10, 6, 8};
//example: output: Periodic Surface 14 {-11, 4, 5, 6} = 20 {-12, -2, -10, -8};
	for (int i = 0; i < List_Nbr(list); i++){
		if (i % 2 == 0) {
			int num;
			if (i>3) sstream << ",";
			List_Read(list, i, &num);
			if (i > 1) pnum.push_back(num);
			sstream << num;
			if (!i) sstream << " {";
		}
	}
	sstream << "} = ";
	for (int i = 0; i < List_Nbr(list); i++){
		if (i % 2 == 1) {
			int num;
			if (i>4) sstream << ",";
			List_Read(list, i, &num);
			if (i > 1) pnum.push_back(num);
			if (i > 1 && test1.period_re(pnum[(i+1)/2-2], pnum[(i+1)/2+2], namen.c_str())) num = -num;
			sstream << num;
			if (!(i-1)) sstream << " {";
		}
	}


	return sstream.str();
}

void add_periodic_surface(List_T *list, std::string fileName)
{
	std::ostringstream sstream;
	sstream << "Periodic Surface " << periodicsurflist2string(list) << "};";
	add_infile(sstream.str(), fileName);
}

/*void add_param(std::string par, std::string value, std::string label,
               std::string path, std::string fileName)
{
  std::ostringstream sstream;
  sstream << par << " = DefineNumber[ " << value;
  sstream << ", Name \"";
  if(path.size() && label.size())
    sstream << path << "/" << label;
  else if(path.size())
    sstream << path << "/" << par;
  else if(label.size())
    sstream << label;
  else
    sstream << par;
  sstream << "\" ];";
  add_infile(sstream.str(), fileName);
}*/

void add_point(std::string fileName, std::string x, std::string y,
               std::string z, std::string lc)
{
  std::ostringstream sstream;
  sstream << "Point(" << NEWPOINT() << ") = {" << x << ", " << y << ", "
          << z ;
  if(lc.size()) sstream << ", " << lc;
  sstream << "};";
  add_infile(sstream.str(), fileName);
}

void add_field_option(int field_id, std::string option_name,
                      std::string option_value, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Field[" << field_id << "]." << option_name << " = "
          << option_value << ";";
  add_infile(sstream.str(), fileName);
}

void add_field(int field_id, std::string type_name, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Field[" << field_id << "] = " << type_name << ";";
  add_infile(sstream.str(), fileName);
}

void delete_field(int field_id, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Delete Field [" << field_id << "];";
  add_infile(sstream.str(), fileName);
}

void set_background_field(int field_id, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Background Field = " << field_id << ";";
  add_infile(sstream.str(), fileName);
}

void add_multline(std::string type, std::vector<int> &p, std::string fileName)
{
  std::ostringstream sstream;
  sstream << type << "(" << NEWLINE() << ") = {";
  for(unsigned int i = 0; i < p.size(); i++) {
    if(i) sstream << ", ";
    sstream << p[i];
  }
  sstream << "};";
  add_infile(sstream.str(), fileName);
}

void add_circ(int p1, int p2, int p3, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Circle(" << NEWLINE() << ") = {" << p1 << ", " << p2 << ", "
          << p3 << "};";
  add_infile(sstream.str(), fileName);
}

void add_ell(int p1, int p2, int p3, int p4, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Ellipse(" << NEWLINE() << ") = {" << p1 << ", " << p2 << ", "
          << p3 << ", " << p4 << "};";
  add_infile(sstream.str(), fileName);
}

void add_lineloop(List_T *list, std::string fileName, int *numloop)
{
  if(recognize_loop(list, numloop)) return;
  *numloop = NEWLINELOOP();
  std::ostringstream sstream;
  sstream << "Line Loop(" << *numloop << ") = {" << list2string(list) << "};";
  add_infile(sstream.str(), fileName);
}

void add_surf(std::string type, List_T *list, std::string fileName)
{
  std::ostringstream sstream;
  sstream << type << "(" << NEWSURFACE() << ") = {" << list2string(list) << "};";
  add_infile(sstream.str(), fileName);
}

void add_surfloop(List_T *list, std::string fileName, int *numloop)
{
  if(recognize_surfloop(list, numloop)) return;
  *numloop = NEWSURFACELOOP();
  std::ostringstream sstream;
  sstream << "Surface Loop(" << *numloop << ") = {" << list2string(list) << "};";
  add_infile(sstream.str(), fileName);
}

void add_vol(List_T *list, std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Volume(" << NEWVOLUME() << ") = {" << list2string(list) << "};";
  add_infile(sstream.str(), fileName);
}

void add_physical(std::string type, List_T *list, std::string fileName, std::string num)
{
  std::ostringstream sstream;
  //sstream << "Physical " << type << "(" << NEWPHYSICAL() << ") = {"               //Prof. Wenbin Yu
  sstream << "Physical " << type << "(" << num << ") = {"
          << list2string(list) << "};";
  add_infile(sstream.str(), fileName);
}

void add_compound(std::string type, List_T *list, std::string fileName)
{
  std::ostringstream sstream;
  if(SplitFileName(fileName)[2] != ".geo") sstream << "CreateTopology;\n";
  if (type == "Surface"){
    sstream << "Compound " << type << "(" << NEWSURFACE()+1000 << ") = {"
	    << list2string(list) << "};";
  }
  else if (type == "Line"){
    sstream << "Compound " << type << "(" << NEWLINE()+1000 << ") = {"
	    << list2string(list) << "};";
  }
  else{
    sstream << "Compound " << type << "(" << NEWREG() << ") = {"
	    << list2string(list) << "};";
  }
  add_infile(sstream.str(), fileName);
}

void translate(int add, List_T *list, std::string fileName, std::string what,
               std::string tx, std::string ty, std::string tz)
{
  std::ostringstream sstream;
  sstream << "Translate {" << tx << ", " << ty << ", " << tz << "} {\n  ";
  if(add) sstream << "Duplicata { ";
  sstream << what << "{" << list2string(list) << "};";
  if(add) sstream << " }";
  sstream << "\n}";
  add_infile(sstream.str(), fileName);
}

void rotate(int add, List_T *list, std::string fileName, std::string what,
            std::string ax, std::string ay, std::string az,
            std::string px, std::string py, std::string pz, std::string angle)
{
  std::ostringstream sstream;
  sstream << "Rotate {{" << ax << ", " << ay << ", " << az << "}, {"
          << px << ", " << py << ", " << pz << "}, " << angle << "} {\n  ";
  if(add) sstream << "Duplicata { ";
  sstream << what << "{" << list2string(list) << "};";
  if(add) sstream << " }";
  sstream << "\n}";
  add_infile(sstream.str(), fileName);
}

void dilate(int add, List_T *list, std::string fileName, std::string what,
            std::string dx, std::string dy, std::string dz, std::string df)
{
  std::ostringstream sstream;
  sstream << "Dilate {{" << dx << ", " << dy << ", " << dz << "}, " << df << "} {\n  ";
  if(add) sstream << "Duplicata { ";
  sstream << what << "{" << list2string(list) << "};";
  if(add) sstream << " }";
  sstream << "\n}";
  add_infile(sstream.str(), fileName);
}

void symmetry(int add, List_T *list, std::string fileName, std::string what,
              std::string sa, std::string sb, std::string sc, std::string sd)
{
  std::ostringstream sstream;
  sstream << "Symmetry {" << sa << ", " << sb << ", " << sc << ", " << sd << "} {\n  ";
  if(add) sstream << "Duplicata { ";
  sstream << what << "{" << list2string(list) << "};";
  if(add) sstream << " }";
  sstream << "\n}";
  add_infile(sstream.str(), fileName);
}

void extrude(List_T *list, std::string fileName, std::string what,
             std::string tx, std::string ty, std::string tz)
{
  std::ostringstream sstream;
  sstream << "Extrude {" << tx << ", " << ty << ", " << tz << "} {\n  " << what
          << "{" << list2string(list) << "};\n}";
  add_infile(sstream.str(), fileName);
}

void protude(List_T *list, std::string fileName, std::string what,
             std::string ax, std::string ay, std::string az,
             std::string px, std::string py, std::string pz, std::string angle)
{
  std::ostringstream sstream;
  sstream << "Extrude {{" << ax << ", " << ay << ", " << az << "}, {"
          << px << ", " << py << ", " << pz << "}, " << angle << "} {\n  "
          << what << "{" << list2string(list) << "};\n}";
  add_infile(sstream.str(), fileName);
}

void split_edge(int edge_id, List_T *vertices,std::string fileName)
{
  std::ostringstream sstream;
  sstream << "Split Line(" << edge_id << ") {" << list2string(vertices) << "};";
  add_infile(sstream.str(), fileName, true);
}
