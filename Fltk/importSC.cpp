#include "importSC.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctype.h>
#include <cmath>
#include <FL/fl_ask.H>

#include "GmshDefines.h"
#include "Context.h"
#include "GModel.h"

#ifdef __linux
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#endif

using namespace std;

ImportSC::ImportSC(string scfile, string mfile, int sc_n):sc(scfile),msh(mfile),sc_model(sc_n){
  readin();
  get_infor();
  type();
  writeout();
}

//read sc file and remove blank lines
void ImportSC::readin(){
  ifstream readinp(sc.c_str());
  string line;
  while(getline(readinp,line)){
    if(line.empty()) continue;
    scinp.push_back(line);
  }
  readinp.close();
}

void ImportSC::get_infor(){
  if(sc_model==1) skip=4;
  else if(sc_model==2) skip=3;
  else if(sc_model==3) skip=1;
  else
    return;

  stringstream stream(scinp[skip]);
  int k=0;
  while(1){
    int n;
    stream >> n;
    k++;
    if (k==2)
      node_n=n;
    else if (k==3)
      {ele_n=n;break;}
  }

  string ss_file=sc+".sn";
  ifstream ss(ss_file.c_str());
  string ssline;
  while(getline(ss,ssline)){
    if(!ssline.empty()){
      stringstream ss1(ssline);
      int i1,i2;
      ss >> i1 >> i2;
      id=i2;
      break;
    }
  }
  ss.close();

}

void ImportSC::type(){
  if (id==2) ele_type=1;
  else if (id==3) ele_type=2;
  else if (id==4) {
    if(sc_model==2) ele_type=3;
    else if(sc_model==3) ele_type=4;
    else
      {fl_message("Wrong element type!");return;}
  }
  else if (id==8) ele_type=5;
  else if (id==6) ele_type=9;
  else if (id==9) ele_type=10;
  else if (id==10) ele_type=11;
  else if (id==20) ele_type=17;
  else
    {fl_message("Wrong element type!");return;}    
}


void ImportSC::writeout(){
  ofstream mshout;
  mshout.open(msh.c_str());
  mshout << "$MeshFormat\n" << "2.2 0 8\n" << "$EndMeshFormat\n" <<"$Nodes\n";
  mshout << node_n << "\n";
  for(int i=0;i<node_n;i++)
    mshout << scinp[skip+1+i] << "\n";
  mshout << "$EndNodes\n" << "$Elements\n" << ele_n << "\n";
  int line_n1=skip+node_n+1;
  for(int i=0;i<ele_n;i++){
    int k=0;
    int mat_id,ele[8];
    stringstream stream(scinp[line_n1+i]);
    while(1){
      k++;
      int n;
      stream >> n;
      if (k==2)
	mat_id=n;
      else if(k>2&&k<11)
	ele[k-3]=n;
      else if (k>=11)
	break;      
    }
    mshout << i+1 << " " << ele_type <<" 2 " << mat_id << " 2 ";
    for(int j=0;j<k-3;j++)
      mshout << ele[j] << " ";
    mshout << "\n";
  }
  mshout << "$EndElements\n";
  
  string dis_file=sc+".u";
  string ss_file=sc+".sn";
  string line;
  vector<double> n1,n2,n3;
  ifstream get_dis(dis_file.c_str());
  if(!get_dis) return;
  while(getline(get_dis,line)){
    if(!line.empty()){
      stringstream ss(line);
      int i;
      double coor1,coor2,coor3;
      ss >> i >> coor1 >> coor2 >> coor3;
      n1.push_back(coor1);
      n2.push_back(coor2);
      n3.push_back(coor3);
    }
  }
  get_dis.close();

  mshout << "$NodeData\n";
  mshout << "1\n" << "\"U-Magnitude\"\n" << "1\n" << "0\n";
  mshout << "3\n" << "0\n" << "1\n";
  mshout << n1.size() << "\n";
  for (int ind = 0; ind < n1.size(); ind++)
    mshout << ind + 1 << " " << sqrt(n1[ind]*n1[ind] + n2[ind]*n2[ind] + n3[ind] * n3[ind]) << "\n";
  mshout << "$NodeData\n";
  mshout << "1\n" << "\"U1\"\n" << "1\n" << "0\n";
  mshout << "3\n" << "0\n" << "1\n";
  mshout << n1.size() << "\n";
  for (int ind = 0; ind < n1.size(); ind++)
    mshout << ind + 1 << " " << n1[ind] << "\n";
  mshout << "$NodeData\n";
  mshout << "1\n" << "\"U2\"\n" << "1\n" << "0\n";
  mshout << "3\n" << "0\n" << "1\n";
  mshout << n1.size() << "\n";
  for (int ind = 0; ind < n1.size(); ind++)
    mshout << ind + 1 << " " << n2[ind] << "\n";
  mshout << "$NodeData\n";
  mshout << "1\n" << "\"U3\"\n" << "1\n" << "0\n";
  mshout << "3\n" << "0\n" << "1\n";
  mshout << n1.size() << "\n";
  for (int ind = 0; ind < n1.size(); ind++)
    mshout << ind + 1 << " " << n3[ind] << "\n"; 
  mshout << "$EndNodeData\n";

  string elementdata[12][ele_n];
  ifstream ss(ss_file.c_str());
  string ssline;
  string plottitle[] = { "E11","E22","E33","2E23","2E13","2E12","S11","S22","S33","S23","S13","S12" };
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
  ss.close();
  for (int i; i < 12; i++){
    mshout << "$ElementNodeData\n";
    mshout << "1\n";
    mshout << "\"" << plottitle[i] << "\"\n";
    mshout << "1\n";
    mshout << "0\n";
    mshout << "3\n";
    mshout << "0\n";
    mshout << "1\n";
    mshout << ele_n << "\n";
    for (int j = 0; j < ele_n; j++) mshout << elementdata[i][j] << "\n";
    mshout << "$EndElementNodeData\n";
  }
  mshout.close();

}



void run_homo(int m, string name, int anal_type){
  string b="3D";
  string hpar="H";
  string dhpar="L";
  if(m==1)  b="1D";
  else if (m==2) b="2D";
  else if (m==3) b="3D";
  else return;

  const char *exe1 = name.c_str();
  const char *exe2 = b.c_str();
  const char *exe3 = hpar.c_str();
  const char *exe5 = dhpar.c_str(); 
  
  
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
  stringstream ss;
  string wok;
  ss << buf;
  ss >> wok;
  string pathname = wok + "SwiftComp";
  string pathname1 = "swiftcomp";
  const char *exe4 = pathname1.c_str();
  
  std::string workingdir = name;
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

  string result = name + ".k";
  remove(result.c_str());

  Msg::StatusBar(true, "Calculating...");
  pid_t pid;
  pid=fork();
  if(pid==0) {
    chdir(addworking);
    if(anal_type==1) execlp( exe4, exe4, exe1, exe2, exe3, NULL);
    else if (anal_type==2) execlp( exe4, exe4, exe1, exe2, exe5, NULL);
    else return;
  }
  else
    wait(NULL);


  if (anal_type==1){
    ifstream ifile(result.c_str());
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


}
