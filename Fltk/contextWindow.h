// Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#ifndef _CONTEXT_WINDOW_H_
#define _CONTEXT_WINDOW_H_

#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Hold_Browser.H>

#include <FL/Fl_Round_Button.H> // Prof. Yu
#include <FL/Fl_Check_Button.H> // Prof. Yu
#include <FL/Fl_Output.H> //Prof. Yu
#include <string>


extern double Ibeam_para[6];
extern double Bbeam_para[8];

class passinfo{
  
 public:

  std::string lam_name;
  void set_name(std::string BL){
    this->lam_name = BL;
  }
  const char* get_name(){
    return this->lam_name.c_str();
  }
			 
};


class geometryContextWindow{
 public:
  Fl_Window *win;
  Fl_Input *input[30];
  Fl_Value_Input *value[10];
  Fl_Group *group[10];
 public:
  geometryContextWindow(int deltaFontSize=0);
  void show(int pane);
};


//Prof. Wenbin Yu
class geometryContextWindow1{
 public:
  Fl_Window *win;
  //Fl_Input *input[30];
  Fl_Input *input[60];           //Prof. Wenbin Yu
  //Fl_Value_Input *value[10];
  Fl_Value_Input *value[20];     //Prof. Wenbin Yu
  Fl_Group *group[10];
 public:
  geometryContextWindow1(int deltaFontSize=0);
  void show(int pane);
  void hide(int pane);
};

class geometryContextWindow2{
 public:
  Fl_Window *win;
  //Fl_Input *input[30];
  Fl_Input *input[10];           //Prof. Wenbin Yu
  //Fl_Value_Input *value[10];
  Fl_Value_Input *value[20];     //Prof. Wenbin Yu
  Fl_Group *group[10];
 public:
  geometryContextWindow2(int deltaFontSize=0);
  void show(int pane);
  void hide(int pane);
};



class geometryContextWindow7 {
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[20];           //Prof. Wenbin Yu
	Fl_Choice *choice[20];      //Prof. Wenbin Yu
	Fl_Value_Input *value[20];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow7(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow7_1 {
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[20];           //Prof. Wenbin Yu
	Fl_Choice *choice[20];      //Prof. Wenbin Yu
	Fl_Value_Input *value[20];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow7_1(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};


class geometryContextWindow8{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow8(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow9{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow9(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow10{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow10(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

//Prof. Yu
class geometryContextWindow5 {
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[20];      //Prof. Wenbin Yu
								//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow5(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow11{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow11(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow12{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow12(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow13{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow13_1{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_1(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow13_2{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
	Fl_Round_Button *_select[2];
public:
	geometryContextWindow13_2(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow13_3{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_3(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
	};

// box beam
class geometryContextWindow13_4{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	//Fl_Multiline_Output *lay_name;
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_4(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
	};

class geometryContextWindow13_5{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Output *lay_name;
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_5(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
	};

class geometryContextWindow13_6{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Output *lay_name;
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_6(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
	};

//  I_beam
class geometryContextWindow13_7{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Output *lay_name;
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_7(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
	};

class geometryContextWindow13_8{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Output *lay_name;
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_8(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
	};

class geometryContextWindow13_9{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Output *lay_name;
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow13_9(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
	};

class geometryContextWindow14{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
	Fl_Round_Button *_select[2];
public:
	geometryContextWindow14(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow14P{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
	Fl_Round_Button *_select[2];
public:
	geometryContextWindow14P(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

class geometryContextWindow14_1{
public:
	Fl_Window *win;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
	Fl_Round_Button *_select[2];
public:
	geometryContextWindow14_1(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};


class geometryContextWindow20{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow20(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};


class geometryContextWindow21{
public:
	Fl_Window *win;
	Fl_Hold_Browser *bro;
	//Fl_Input *input[30];
	Fl_Input *input[100];           //Prof. Wenbin Yu
	Fl_Choice *choice[30];      //Prof. Wenbin Yu
	//Fl_Value_Input *value[10];
	Fl_Value_Input *value[100];     //Prof. Wenbin Yu
	Fl_Group *group[10];
public:
	geometryContextWindow21(int deltaFontSize = 0);
	void show(int pane);
	void hide(int pane);
};

//Prof. Yu


class meshContextWindow{
 public:
  Fl_Window *win;
  Fl_Input *input[20];
  Fl_Choice *choice[20];
  Fl_Group *group[10];
public:
  meshContextWindow(int deltaFontSize=0);
  void show(int pane);
  void hide(int pane);  // Prof. Yu
};

#endif
