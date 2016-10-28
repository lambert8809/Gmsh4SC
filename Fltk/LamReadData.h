//Prof. Yu


#ifndef LAMREADDATA_H_INCLUDED
#define LAMREADDATA_H_INCLUDED
#include <string>



void LamInput1(std::string inpName, std::string geoName, int matnum, int flags, int cout, double &len4sg);
void LamInput2(std::string inpName, std::string geoName, int matnum, int flags, int cout, double &len4sg);

class LamInp{
private:
  int num_seg;
  int num_layer;
  int num_rep1;
  int num_rep2;
  bool sym;
  
public:
  void set_nseg(int);
  void set_nlayer(int);
  void set_nrep1(int);
  void set_nrep2(int);
  void set_sym(int);
  int get_nseg();
  int get_nlayer();
  int get_nrep1();
  int get_nrep2();
  bool get_sym();

};

#endif 
