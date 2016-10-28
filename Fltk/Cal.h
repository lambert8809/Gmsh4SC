//Prof. Wenbin Yu


#ifndef CAL_H_INCLUDED
#define CAL_H_INCLUDED
#include <string>
#include <vector>


void inpfile_create(std::string filename);
void add_mat_cal(std::string filename);
void write_sc_mat(std::string name, int chec_b1, int chec_b2);
void regen_sc_file(std::string filename);
void open_cal_file(std::string filename);
void run_cal(std::string filename);
void show_res(std::string filename);

#endif // 
