#include "errorcheck.h"
#include <FL/Fl.H>
#include <FL/fl_ask.H>

int period_flags;
int com_flags;
int mat_flags;
int extru_flags;
int boxlay_flags;
int Ilay_flags;
int layname_flags;
int scmat_flags;

void perio_chec::passvalue(int f){
  if (f != 0)
    flags = 1;
}

void change_period_value(int f){
  if (f == 1)
    period_flags = 1;
  else
    period_flags = 0;
}

void change_com_value(int f){
  if (f == 1)
    com_flags = 1;
  else
    com_flags = 0;
}

void change_mat_value(int f){
  if (f == 1)
    mat_flags = 1;
  else
    mat_flags = 0;
}

void change_extru_value(int f){
  if (f == 1)
    extru_flags = 1;
  else
    extru_flags = 0;
}

void change_boxlay_value(int f){
  if (f == 0)
    boxlay_flags = 0;
  else
    boxlay_flags += f;
}

void change_Ilay_value(int f){
  if (f == 0)
    Ilay_flags = 0;
  else
    Ilay_flags += f;
}

void change_layname_value(int f){
  if (f == 0)
    layname_flags = 0;
  else
    layname_flags += f;
}

void change_scelem_value(int f){
  if (f == 0)
    scmat_flags = 0;
  else
    scmat_flags += f;

}

int mesh_chec_cal::m_flags=0;
int mesh_chec_cal::inp_flags=0;
int mesh_chec_cal::assign_flags=0;

int mesh_chec_cal::re(){return m_flags;}

int mesh_chec_cal::re0(){
  m_flags=0;
  return m_flags;
}

int mesh_chec_cal::re1(){
  m_flags=1;
  return m_flags;
}

void mesh_chec_cal::ch_inp(int f){
  inp_flags = f;
}

int mesh_chec_cal::ch_inp0(){return inp_flags;}

int mesh_chec_cal::get_assig(int f){
  assign_flags = f;
  return assign_flags;
}
