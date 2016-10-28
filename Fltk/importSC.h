#ifndef IMPORTSC_H_INCLUDED
#define IMPORTSC_H_INCLUDED
#include <string>
#include <vector>

using namespace std;

void run_homo(int m, string name, int anal_type);

class ImportSC{
 public:
  ImportSC(string scfile, string mfile, int sc_n);
 private:
  string sc;
  string msh;
  int sc_model;
  vector<string> scinp;
  //void check();
  void readin();
  void writeout();
  void get_infor();
  int skip;
  int node_n;
  int ele_n;
  int id;
  int ele_type;
  void type();

};
//void importSC(std::string &scfile, std::string &mfile);

#endif
