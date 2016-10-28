
// Prof. Wenbin Yu
#define _WIN32_WINNT 0x0500
#include <iostream>
#include <sstream>   // important for read .U file and write post view file
#include <fstream>   // important for read .U file and write post view file
#include <stdio.h>
#include <stdlib.h>
#include <fileDialogs.h>

#include <limits>
#include <OS.h>
#include "CreateFile.h"
#include "GmshDefines.h"
#include "Context.h"
#include "GModel.h"   // Prof. Yu get filename for reading temp file
#include <cmath>
#include <vector>
#include <istream>
#include <string>
#include "StringUtils.h"
#include "postswiftcomp.h" // Prof. Yu get .pos file from swiftcomp
#include "OpenFile.h"
#include "onelabGroup.h"
#include "drawContext.h"
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#endif
using namespace std;


void choose_swiftcomp_executable(std::string type)
{
  // choose swiftcomp.exe location, no file path

  //get default mesh file location
  std::string name = CTX::instance()->outputFileName;
  name = GetDefaultFileName(FORMAT_MSH);

  // Prof. Yu, get the temp file name
  std::string name2 = GModel::current()->getFileName();
  std::string temp1 = name2 + ".t";
  std::string temp3 = name2 + ".t3";
  // Prof. Yu

#ifdef _WIN32
  // Prof. Yu, get the path name of SwiftComp.exe
  char buffer[MAX_PATH];
  GetModuleFileName(NULL, buffer, MAX_PATH);
  std::string strSC(buffer);
  std::string wok;
  for (size_t i = strSC.size(); i > 0; i--) {
    if (strSC[i] == '\\') {
      wok = strSC.substr(0, i+1);
      break;
    }
  }
  std::string a = " /k " + wok + "SwiftComp.exe ";

  //std::string a = " /k SwiftComp.exe ";


  std::string b = " 3D H";
  //std::string b = " 3D";
  // Prof. Yu, add condition to automatically choose problem type
  int flagskips = 0;
  std::ifstream is(temp1.c_str());
  std::string readout;
  std::string beam = "beam";
  std::string plate = "plate";
  std::string shell = "shell";
  while (getline(is, readout)) {
    if (readout.find(beam) != std::string::npos){
      b = " 1D H";
      //b = " 1D";
      flagskips = 3;

    }
    else if (readout.find(shell) != std::string::npos) {
      b = " 2D H";
      //b = " 2D";
      flagskips = 2;
    }
    else if (readout.find(plate) != std::string::npos) {
      b = " 2D H";
      //b = " 2D";
      flagskips = 1;
    }
  }
  is.close();


  // Prof. Yu
  if (type == "dehomo" && b == " 3D H") b = " 3D L";
  if (type == "dehomo" && b == " 1D H") b = " 1D L";
  if (type == "dehomo" && b == " 2D H") b = " 2D L";
  /*if (type == "dehomo" && b == " 3D") b = " 3D L";
    if (type == "dehomo" && b == " 1D") b = " 1D L";
    if (type == "dehomo" && b == " 2D") b = " 2D L";*/




  std::string exe1 = a + "\"" + name + "\"" + b;
  const char *exe2 = exe1.c_str();
  //ShellExecute(NULL, "open", "cmd", exe2, NULL, SW_MINIMIZE);
  // Prof. Yu, get working directory
  std::string workingdir = name2;
  std::string spec = "\\";
  std::string add = "";
  std::string address = "";
  size_t pos = 0;
  while ((pos = workingdir.find(spec)) != std::string::npos){
    add = workingdir.substr(0, pos);
    address += add + "\\";
    workingdir.erase(0, pos + spec.length());
  }
  address.erase(address.length() - 1, address.length());
  const char *addworking = address.c_str();
  //Prof. Yu

  std::string result = name + ".k";
  remove(result.c_str());

  Msg::StatusBar(true, "Calculating...");
  SHELLEXECUTEINFO ShExecInfo = { 0 };
  ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
  ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
  ShExecInfo.hwnd = NULL;
  ShExecInfo.lpVerb = "open";
  ShExecInfo.lpFile = "cmd";
  ShExecInfo.lpParameters = exe2;
  ShExecInfo.lpDirectory = addworking;
  ShExecInfo.nShow = SW_SHOW;
  ShExecInfo.hInstApp = NULL;
  ShellExecuteEx(&ShExecInfo);
  WaitForSingleObject(ShExecInfo.hProcess, INFINITE);



  if (type == "homo"){
    std::ifstream ifile(result.c_str());
    if (ifile){
      const char *resultfile = result.c_str();
      Msg::StatusBar(true, "Completed!");
      //std::remove(temp3.c_str());
      ShellExecute(NULL, "open", "notepad.exe", resultfile, NULL, SW_SHOWNORMAL);
    }
    else
      Msg::StatusBar(true, "Failure! Output file is not found!");

  }
#endif

#ifdef __linux
  std::string b = "3D";
  // Prof. Yu, add condition to automatically choose problem type
  int flagskips = 0;
  std::ifstream is(temp1.c_str());
  std::string readout;
  std::string beam = "beam";
  std::string plate = "plate";
  std::string shell = "shell";
  while (getline(is, readout)) {
    if (readout.find(beam) != std::string::npos){
      b = "1D";
      flagskips = 3;
      
    }
    else if (readout.find(shell) != std::string::npos) {
      b = "2D";
      flagskips = 2;
    }
    else if (readout.find(plate) != std::string::npos) {
      b = "2D";
      flagskips = 1;
    }
  }
  is.close();
  // Prof. Yu
  /*if (type == "dehomo" && b == "3D") b = "3D L";
    if (type == "dehomo" && b == "1D") b = "1D L";
    if (type == "dehomo" && b == "2D") b = "2D L";*/
  std::string hpar = "H";
  std::string depar = "L";
  
  
  
  const char *exe1 = name.c_str();
  const char *exe2 = b.c_str();
  const char *exe5 = hpar.c_str();
  const char *exe3 = depar.c_str();

  // Prof. Yu, get directory of SwiftComp
  /*char tempstr[100];
    getcwd(tempstr,100);
    std::stringstream ss;
    std::string wok;
    ss << tempstr;
    ss >> wok;
    std::string wokdir= wok + "/SwiftComp";
		const char *exe4 = wokdir.c_str();*/
  int iii;
  char buf[1024];
  int rslt = readlink("/proc/self/exe", buf, 1024);
  buf[rslt] = '\0';
  for (iii = rslt; iii >= 0; iii--)
    {
      if (buf[iii] == '/')
	{
	  buf[iii + 1] = '\0';
	  break;
	}
    }
  std::stringstream ss;
  std::string wok;
  ss << buf;
  ss >> wok;
  //std::string pathname = wok + "SwiftComp";
  std::string pathname1 = "swiftcomp";
 // const char *exe4 = pathname.c_str(); 
  const char *exe4 = pathname1.c_str();
  
  

  // Prof. Yu, get working directory of data file
  std::string workingdir = name2;
  std::string spec = "/";
  std::string add = "";
  std::string address = "";
  size_t pos = 0;
  while ((pos = workingdir.find(spec)) != std::string::npos){
    add = workingdir.substr(0, pos);
    address += add + "/";
    workingdir.erase(0, pos + spec.length());
  }
  address.erase(address.length() - 1, address.length());
  const char *addworking = address.c_str();
  //const char *addworking = name2.c_str();
  //Prof. Yu


  std::string result = name + ".k";
  remove(result.c_str());
  
  pid_t pid;
  pid=fork();
  if(pid==0) {
    chdir(addworking);
    if (type == "homo") execlp( exe4, exe4, exe1, exe2, exe5, NULL);
    else if (type == "dehomo") execlp( exe4, exe4, exe1, exe2, exe3, NULL);
  }
  else
    wait(NULL);

  if (type == "homo"){
    std::ifstream ifile(result.c_str());
    if (ifile){
      const char *resultfile = result.c_str();
      Msg::StatusBar(true, "Completed!");
      //std::remove(temp3.c_str());
      pid=fork();
      if(pid==0)
	execlp("geany","geany", resultfile, NULL);
      else
	wait(NULL);
    }
    else
      Msg::StatusBar(true, "Failure! Output file is not found !");
    
  }
#endif

  // Prof. Yu, add dehomogenization function
  std::string name3 = GModel::current()->getFileName();
  std::string temp2 = name3 + ".t2";
  int lastindex = name2.find_last_of(".");
  std::string tpostname = name2.substr(0, lastindex);
  std::string postview = tpostname + "VIEW" + ".msh";

  //std::ifstream t3file(temp3.c_str());
  if (type == "dehomo"){
    // if (t3file) return;
    if (postswiftcomp(temp2, name, postview) == 1){
      std::string postfile = tpostname + "VIEW" + ".geo";
      std::ofstream igeofile;
      igeofile.open(postfile.c_str());
      igeofile << "Merge " << "\"" << postview << "\";\n";
      igeofile << "Mesh.SurfaceFaces=0;\n";
      igeofile << "Mesh.Points=0;\n";
      igeofile << "Mesh.SurfaceEdges=0;\n";
      igeofile << "Mesh.VolumeEdges = 0;\n";
      igeofile << "View[0].Visible=1;\n";
      for (int i = 1; i < 16; i++) igeofile << "View[" << i << "].Visible=0;\n";
      igeofile.close();
				
      // Prof. Yu, open post-processing file
      OpenProject(postfile);
      drawContext::global()->draw();
      // Prof. Yu, reload and show the window
      //std::string fileName = GModel::current()->getFileName();
      //ClearProject();
      //GModel::current()->setFileName(fileName);
      //OpenProject(fileName);
      //onelab_cb(0, (void*)"reset"); // this will call OpenProject
      //std::remove(temp1.c_str());
      //std::remove(temp2.c_str());
    }
    
  }
  
}


