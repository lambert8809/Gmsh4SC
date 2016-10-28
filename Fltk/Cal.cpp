#include <stdlib.h>
#include <string>
#include <sstream>
#include "CreateFile.h"
#include "GmshDefines.h"
#include "Cal.h"
#include "Context.h"
#include "OS.h"
#include <FL/fl_ask.H>
#include <vector>
#include <fstream>
#include <istream>

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#endif


void inpfile_create(std::string name){
  int lastindex = name.find_last_of(".");
  std::string tIname = name.substr(0, lastindex);
  std::string INPname = tIname + ".inp";  
  if(CTX::instance()->confirmOverwrite) {
    if(!StatFile(INPname))
      if(!fl_choice("File '%s' already exists.\n\nDo you want to replace it?",
                    "Cancel", "Replace", 0, INPname.c_str()))
        return;}
  CreateOutputFile(INPname,FORMAT_INP);
  fl_message("INP file is generated!");
}




void add_mat_cal(std::string name){
  int lastindex = name.find_last_of(".");
  std::string tIname = name.substr(0, lastindex);
  std::string INPname = tIname + ".inp";
  std::string MAT_NAME[10];
  std::ofstream writeINP;
  writeINP.open(INPname.c_str(),std::ofstream::app);
  std::ifstream data(name.c_str());
  std::string readout;
  std::string temp;
  std::vector<std::string> mat_data;
  int count = 0;
  int MAT_TYPE=0;
  while (getline(data,readout)){
    if (readout.find("Physical Point") != std::string::npos)
      MAT_TYPE = atoi(readout.substr(18,1).c_str())+1;
    if (MAT_TYPE != 0)
      count++;
    // take iso mat infor
    if (count == 3 && MAT_TYPE == 1){      
      std::stringstream tran_ss(readout);
      while (tran_ss >> temp)
	mat_data.push_back(temp);
    }
    if (count == 6 && MAT_TYPE == 1){
      std::vector<std::string> mat_infor;
      std::stringstream tran_ss(readout);
      while (tran_ss >> temp)
	mat_infor.push_back(temp);
      MAT_TYPE = 0;
      count = 0;
      writeINP << "*MATERIAL,NAME=" << mat_infor[5] << "\n";
      writeINP << "*ELASTIC" << "\n";
      writeINP << mat_data[0] << ", " << mat_data[1] << "\n";
      mat_data.clear();
    }
    // take orth mat infor
    if (count > 2 && count < 6 && MAT_TYPE == 2){      
      std::stringstream tran_ss(readout);
      while (tran_ss >> temp)
	mat_data.push_back(temp);
    }
    if (count == 8 && MAT_TYPE == 2){
      std::vector<std::string> mat_infor;
      std::stringstream tran_ss(readout);
      while (tran_ss >> temp)
	mat_infor.push_back(temp);
      MAT_TYPE = 0;
      count = 0;
      writeINP << "*MATERIAL,NAME=" << mat_infor[5] << "\n";
      writeINP << "*ELASTIC," << "TYPE=ENGINEERING CONSTANTS\n";
      writeINP << mat_data[0] << ", " << mat_data[1] << ", " << mat_data[2] << ", ";
      writeINP << mat_data[6] << ", " << mat_data[7] << ", " << mat_data[8] << ", ";
      writeINP << mat_data[3] << ", " << mat_data[4] << ",\n";
      writeINP << mat_data[5] << "\n";
      mat_data.clear();
    }
    // take anis mat infor
    if (count > 2 && count < 9 && MAT_TYPE == 3){      
      std::stringstream tran_ss(readout);
      while (tran_ss >> temp)
	mat_data.push_back(temp);
    }
    if (count == 11 && MAT_TYPE == 3){
      std::vector<std::string> mat_infor;
      std::stringstream tran_ss(readout);
      while (tran_ss >> temp)
	mat_infor.push_back(temp);
      MAT_TYPE = 0;
      count = 0;
      writeINP << "*MATERIAL,NAME=" << mat_infor[5] << "\n";
      writeINP << "*ELASTIC," << "TYPE=ANISO\n";
      writeINP << mat_data[0] << ", " << mat_data[1] << ", " << mat_data[6] << ", " << mat_data[2] << ", ";
      writeINP << mat_data[7] << ", " << mat_data[11] << ", " << mat_data[3] << ", " << mat_data[8] << ",\n";
      writeINP << mat_data[12] << ", " << mat_data[15] << ", " << mat_data[4] << ", " << mat_data[9] << ", ";
      writeINP << mat_data[13] << ", " << mat_data[16] << ", " << mat_data[18] << ", " << mat_data[5] << ",\n";
      writeINP << mat_data[10] << ", " << mat_data[14] << ", " << mat_data[17] << ", " << mat_data[19] << ", ";
      writeINP << mat_data[20] << "\n";
      mat_data.clear();
    }      
  }
  writeINP.close();
  data.close();
}




void write_sc_mat(std::string name, int chec_b1, int chec_b2){
  if(chec_b1==0){fl_message("Please generate INP file before this step!"); return;}
  if(chec_b2==0){fl_message("Please mesh the model before this step!"); return;}
  //read sc material properties from .geo file
  int beamtype = 0;
  int lastindex = name.find_last_of(".");
  std::string tIname = name.substr(0, lastindex);
  std::string INPname = tIname + ".inp";
  regen_sc_file(INPname);
  std::ifstream kfile(name.c_str());
  std::string readline,temp;
  std::vector<std::string> scmat;
  int flags=0, countline=0;
  while (getline(kfile, readline)){
    if(readline.find("*SCINPUT") != std::string::npos){
      flags=1;
      scmat.push_back(readline.substr(2));
      continue;
    }
      
    if(flags==1){
      scmat.push_back(readline.substr(2));
      countline++;
      if (countline == 4) {flags=0;countline=0;}
    }
    
  }
  kfile.close();
  //write sc material properties into .inp file    
  std::ofstream writeINP;
  writeINP.open(INPname.c_str(),std::ofstream::app);
  for (int i =0; i < scmat.size(); i++)
    writeINP << scmat[i] << "\n";
  writeINP.close();

  fl_message("SC material is written in file!");
}



/**********************************/
/*      regenerate inp file       */
void regen_sc_file(std::string name){
  std::ifstream refile(name.c_str());
  std::vector<std::string> old_file;
  std::vector<std::string> ele;
  std::vector<std::string> ele_label;
  std::vector<std::string> ele_set;
  std::vector<int> elset_num;
  std::string read,temp;
  int keep_line=0, elset=0;
  int f4_old_file=0, f4_ele=0, f4_set=0;
  while (getline(refile, read)){
    if(read.find("*NODE")!= std::string::npos)
      read=read+",NSET=NALL";
    //read nodes
    if(f4_old_file==0)
      old_file.push_back(read);
    //end read nodes
    if(read.find("*** E L E")!= std::string::npos){
      keep_line=old_file.size()-1;
      f4_old_file=1;
    }
    //set flags to read element
    if(read.find("*ELEMENT")!= std::string::npos){
      f4_ele=1;
      continue;
    }        
    //end read elements and read set label, elements number in set
    if(read.find("*ELSET")!= std::string::npos){
      f4_ele=0;
      ele_label.push_back(read.substr(read.length()-3));
      f4_set=1;
      elset_num.push_back(elset);
      continue;
    }
    //read elements
    if(f4_ele==1)
      ele.push_back(read);
    //read set elemebts
    if(f4_set==1){
      for (int i = 0; i < read.length(); i++)
	if(read[i] == ',') read[i] = ' ';
      std::stringstream linestream(read);
      while(linestream >> temp){
	elset++;
	ele_set.push_back(temp);
      }	
    }
  }
  elset_num.push_back(elset);
  refile.close();

  int estart = atoi(ele_set[0].c_str())-1;
  int tempINT;
  for (int i = 0; i < ele.size(); i++){
    std::size_t found = ele[i].find_first_of(",");
    temp = ele[i].substr(0,found);
    tempINT = atoi(temp.c_str())-estart;
    std::ostringstream convert;
    convert << tempINT;
    temp = convert.str();
    ele[i]= temp + ele[i].erase(0,found);
    //    std::cout << ele[i] << std::endl;
  }  
  
  std::ofstream writeINP;
  writeINP.open(name.c_str());
  for (int i= 0; i< old_file.size(); i++)
    writeINP << old_file[i] <<"\n";
  for (int i = 0; i < ele_label.size(); i++){
    writeINP << "*ELEMENT, type=" << "NB11" << ", ELSET=" << ele_label[i] << "\n";
     for (int j = elset_num[i]; j < elset_num[i+1]; j++)
       writeINP << ele[atoi(ele_set[j].c_str())-estart-1] << "\n";
  }
  writeINP.close();
  
}



/***************************************/
/*  open inp file and define step etc  */
void open_cal_file(std::string name){
  int lastindex = name.find_last_of(".");
  std::string tKname = name.substr(0, lastindex);
  std::string INPname = tKname + ".inp";
#ifdef _WIN32
  ShellExecute(NULL, "open", "notepad.exe", INPname.c_str(), NULL, SW_SHOWNORMAL);
#endif
#ifdef __linux
  pid_t pid;
  pid=fork();
  if(pid==0)
    execlp("geany","geany", INPname.c_str(), NULL);
  else
    wait(NULL);
#endif  
}



/************************/
/*     run inp file     */
void run_cal(std::string name){
  int lastindex = name.find_last_of(".");  
  std::string tKname = name.substr(0, lastindex);  
  std::string INPname = tKname + ".inp";
#ifdef _WIN32
  int dir = name.find_last_of("/\\");
  std::string wokdir = name.substr(0, dir);
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
  std::string a = " /k " + wok + "ccx.exe " + tKname;
  const char *exe = a.c_str();
  //ShellExecute(NULL, "open", "cmd", exe, NULL, SW_MINIMIZE);

  SHELLEXECUTEINFO ShExecInfo = { 0 };
  ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
  ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
  ShExecInfo.hwnd = NULL;
  ShExecInfo.lpVerb = "open";
  ShExecInfo.lpFile = "cmd";
  ShExecInfo.lpParameters = exe;
  ShExecInfo.lpDirectory = wokdir.c_str();
  ShExecInfo.nShow = SW_SHOW;
  ShExecInfo.hInstApp = NULL;
  ShellExecuteEx(&ShExecInfo);
  WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
#endif

#ifdef __linux
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
  std::string pathname = wok + "ccx";

  int dir = name.find_last_of("/");
  std::string wokdir = name.substr(0, dir);
  pid_t pid;
  pid=fork();
  if(pid==0) {
    chdir(wokdir.c_str());
    execlp(pathname.c_str(), pathname.c_str(), tKname.c_str(), NULL);
  }
  else
    wait(NULL);
  fl_message("Job finished!");
#endif
}



/************************/
/*     show results     */
void show_res(std::string name){
  int lastindex = name.find_last_of(".");
  std::string tKname = name.substr(0, lastindex);
  std::string resname = tKname + "_sc.dat";
#ifdef _WIN32
  ShellExecute(NULL, "open", "notepad.exe", resname.c_str(), NULL, SW_SHOWNORMAL);
#endif
#ifdef __linux
  pid_t pid;
  pid=fork();
  if(pid==0)
    execlp("geany","geany", resname.c_str(), NULL);
  else
    wait(NULL);
#endif 
}
