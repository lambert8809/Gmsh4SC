#ifndef _ERRORCHECK_H_
#define _ERRORCHECK_H_

#include <string>


extern int period_flags;
extern int com_flags;
extern int mat_flags;
extern int extru_flags;
extern int boxlay_flags;
extern int Ilay_flags;
extern int layname_flags;
extern int scmat_flags;

void change_period_value(int);
void change_com_value(int);
void change_mat_value(int);
void change_extru_value(int);
void change_boxlay_value(int);
void change_layname_value(int);
void change_Ilay_value(int);

void change_scelem_value(int); // assign sc_mat to element

class perio_chec{
 public:
  int flags;
  void passvalue(int);

};

class mesh_chec_cal{
 public:
  static int m_flags;
  static int inp_flags;
  static int assign_flags;
  static int re();
  static int re0();
  static int re1();
  static void ch_inp(int);
  static int ch_inp0();
  static int get_assig(int);
};


#endif
