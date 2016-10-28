#ifndef _CHECKGEO_H_
#define _CHECKGEO_H_

#include <string>


class CheckGEO{
  
  //double uni_area;
 public:
  int nodenum;
  int linenum;
  double** Geonodes(std::string);
  int** Geolines(std::string);
  double uni_area(std::string);
  bool period_re(int, int, std::string);
};

#endif

