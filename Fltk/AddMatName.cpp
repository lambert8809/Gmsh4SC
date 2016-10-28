#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "AddMatName.h"
#include "FlGui.h"
#include "contextWindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "errorcheck.h"
//#include <Fl/Fl_Menu_Item.H>

int coutmat = 0;
int ccount;

void AddMatName(std::string fileName){
 
  std::vector<std::string> matname;
  static Fl_Menu_Item Matname2[] = {
    {"Select material:", 0, 0, 0},
    { 0 }
  };
  
  std::ifstream readfile(fileName.c_str());
  std::string readline;
  std::string temp;
  matname.clear();
  
  if (mat_flags == 1){
    ccount += coutmat;
    for (int i = 1; i < ccount+1; i++) (Matname2+i)->deactivate();      
    change_mat_value(0);
  }
  
  while (getline(readfile, readline)){
    if (readline.find("Material name:") != std::string::npos)
      {
        readline.erase(0, 18);
	matname.push_back(readline);
      }
  }
  coutmat = matname.size();

   
  /*std::string check = fileName.c_str();
  std::ofstream wcheck;x
  wcheck.open(check.c_str(),std::ofstream::app);
  for (int i = 0; i < matname.size(); i++)
    wcheck << "//" << matname[i] << "\n";
    wcheck.close();*/
  
  for (int i = 0; i < matname.size(); i++) Matname2 -> add(matname[i].c_str(), 0, 0, 0);
  //Matname2 -> remove(1);
  readfile.close();

  FlGui::instance()->geoContext7_1->choice[5]->menu(Matname2);
  FlGui::instance()->geoContext7_1->choice[6]->menu(Matname2);
  FlGui::instance()->geoContext7_1->choice[7]->menu(Matname2);
  FlGui::instance()->geoContext7->choice[8]->menu(Matname2);
  FlGui::instance()->geoContext7->choice[9]->menu(Matname2);
  FlGui::instance()->geoContext14->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[1]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[2]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[3]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[4]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[5]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[6]->menu(Matname2);
  FlGui::instance()->geoContext14_1->choice[7]->menu(Matname2);
  FlGui::instance()->geoContext13->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext13->choice[1]->menu(Matname2);
  FlGui::instance()->geoContext13->choice[2]->menu(Matname2);
  FlGui::instance()->geoContext13->choice[3]->menu(Matname2);
  FlGui::instance()->geoContext13->choice[4]->menu(Matname2);
  FlGui::instance()->geoContext13_2->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[1]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[2]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[3]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[4]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[5]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[6]->menu(Matname2);
  FlGui::instance()->geoContext13_3->choice[7]->menu(Matname2);
  FlGui::instance()->geoContext13_5->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext13_8->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[1]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[2]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[3]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[4]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[5]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[6]->menu(Matname2);
  FlGui::instance()->geoContext13_6->choice[7]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[0]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[1]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[2]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[3]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[4]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[5]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[6]->menu(Matname2);
  FlGui::instance()->geoContext13_9->choice[7]->menu(Matname2);
}
