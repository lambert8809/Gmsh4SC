//Prof. Wenbin Yu


#ifndef COMBEAMMODEL_H_INCLUDED
#define COMBEAMMODEL_H_INCLUDED
#include <string>
#include <vector>


void reg_box_beam(double w, double h, double t1, double t2,\
		  double t3, double t4, double matid, std::string geofile);
void reg_I_beam(double h, double b1, double b2, double t1, double t2, double t3, double matid, \
		std::string geofile);
void reg_rec_beam(double w, double h, double matid, std::string geofile);
void reg_cir_beam(double r, double matid, std::string geofile);
void reg_pipe_beam(double r, double t, double matid, std::string geofile);
void comp_box_beam(double w, double h, std::string geofile);
void comp_rec_beam(double w, std::string geofile, int cout);
void comp_I_beam(double h, double b1, double b2, std::string geofile);


#endif // COMBEAMMODEL_H_INCLUDED
