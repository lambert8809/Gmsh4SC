// Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#ifndef _FL_GUI_H_
#define _FL_GUI_H_

#include <string>
#include <vector>
#include "SPoint2.h"

#define GMSH_WINDOW_BOX FL_FLAT_BOX
#define GMSH_SIMPLE_RIGHT_BOX (Fl_Boxtype)(FL_FREE_BOXTYPE+1)
#define GMSH_SIMPLE_TOP_BOX (Fl_Boxtype)(FL_FREE_BOXTYPE+2)

#define IW (10 * FL_NORMAL_SIZE)    // input field width
#define BB (7 * FL_NORMAL_SIZE)     // width of a button with internal label
#define BH (2 * FL_NORMAL_SIZE + 1) // button height
#define WB (5)                      // window border

class graphicWindow;
class openglWindow;
class optionWindow;
class fieldWindow;
class pluginWindow;
class statisticsWindow;
class visibilityWindow;
class highOrderToolsWindow;
class clippingWindow;
class manipWindow;
class geometryContextWindow;


class geometryContextWindow1;  //Prof. Wenbin Yu
class geometryContextWindow7;  //Prof. Yu
class geometryContextWindow7_1;  //Prof. Yu
class geometryContextWindow2;  //Prof. Wenbin Yu
class geometryContextWindow8;  //Prof. Yu, beam homogenization 
class geometryContextWindow9;  //Prof. Yu, Shell/Plate homogenization 
class geometryContextWindow10;  //Prof. Yu, Solid homogenization
class geometryContextWindow5;  //Prof. Yu, Solid dehomogenization
class geometryContextWindow11;  //Prof. Yu, beam dehomogenization 
class geometryContextWindow12;  //Prof. Yu, Shell/Plate dehomogenization
class geometryContextWindow13; //Prof. Yu, Common mdel for Beam
class geometryContextWindow13_1; //Prof. Yu, Common mdel for Beam (layup-define)
class geometryContextWindow13_2; //Prof. Yu, Common mdel for Beam (layup-define-fast)
class geometryContextWindow13_3; //Prof. Yu, Common mdel for Beam (layup-define-advanced)
class geometryContextWindow13_4; //Prof. Yu, Common mdel for Beam (box-define)
class geometryContextWindow13_5; //Prof. Yu, Common mdel for Beam (box-define-fast)
class geometryContextWindow13_6; //Prof. Yu, Common mdel for Beam (box-define-advanced)
class geometryContextWindow13_7; //Prof. Yu, Common mdel for Beam (I-define)
class geometryContextWindow13_8; //Prof. Yu, Common mdel for Beam (I-define-fast)
class geometryContextWindow13_9; //Prof. Yu, Common mdel for Beam (I-define-advance)
class geometryContextWindow14; //Prof. Yu, Common mdel for Laminate (fast generate)
class geometryContextWindow14P; //Prof. Yu, Common mdel for Plate/shell (laminate)
class geometryContextWindow14_1; //Prof. Yu, Common mdel for laminate (Advanced)

class geometryContextWindow21; //Prof. Yu, add thermal material properties
class geometryContextWindow20; //Prof. Yu, add edit material windows


class meshContextWindow;
class helpWindow;
class onelabGroup;
class Fl_Widget;

class GVertex;
class GEdge;
class GFace;
class GRegion;
class MElement;

class FlGui{
 private:
  static FlGui *_instance;
  static std::string _openedThroughMacFinder;
  int _in_main_thread;
  std::string _lastStatus;
 public:
  std::vector<GVertex*> selectedVertices;
  std::vector<GEdge*> selectedEdges;
  std::vector<GFace*> selectedFaces;
  std::vector<GRegion*> selectedRegions;
  std::vector<MElement*> selectedElements;
  std::vector<SPoint2> selectedPoints;
 public:
  std::vector<graphicWindow*> graph;
  optionWindow *options;
  fieldWindow *fields;
  pluginWindow *plugins;
  statisticsWindow *stats;
  visibilityWindow *visibility;
  highOrderToolsWindow *highordertools;
  clippingWindow *clipping;
  manipWindow *manip;
  geometryContextWindow *geoContext;
  
  geometryContextWindow1 *geoContext1;    //Prof. Wenbin Yu
  geometryContextWindow7 *geoContext7;    //Prof. Yu
  geometryContextWindow7_1 *geoContext7_1;    //Prof. Yu
  geometryContextWindow2 *geoContext2;    //Prof. Wenbin Yu
  geometryContextWindow8 *geoContext8;    //Prof. Yu
  geometryContextWindow9 *geoContext9;    //Prof. Yu
  geometryContextWindow10 *geoContext10;    //Prof. Yu
  geometryContextWindow5 *geoContext5;    //Prof. Yu
  geometryContextWindow11 *geoContext11;    //Prof. Yu
  geometryContextWindow12 *geoContext12;    //Prof. Yu
  geometryContextWindow13 *geoContext13;    //Prof. Yu
  geometryContextWindow13_1 *geoContext13_1;    //Prof. Yu
  geometryContextWindow13_2 *geoContext13_2;    //Prof. Yu
  geometryContextWindow13_3 *geoContext13_3;    //Prof. Yu
  geometryContextWindow13_4 *geoContext13_4;    //Prof. Yu
  geometryContextWindow13_5 *geoContext13_5;    //Prof. Yu
  geometryContextWindow13_6 *geoContext13_6;    //Prof. Yu
  geometryContextWindow13_7 *geoContext13_7;    //Prof. Yu
  geometryContextWindow13_8 *geoContext13_8;    //Prof. Yu
  geometryContextWindow13_9 *geoContext13_9;    //Prof. Yu
  geometryContextWindow14 *geoContext14;    //Prof. Yu
  geometryContextWindow14P *geoContext14P;    //Prof. Yu
  geometryContextWindow14_1 *geoContext14_1;    //Prof. Yu

  geometryContextWindow20 *geoContext20;    //Prof. Yu
  geometryContextWindow21 *geoContext21;    //Prof. Yu
  
  
  meshContextWindow *meshContext;
  helpWindow *help;
  onelabGroup *onelab;
  openglWindow *fullscreen;
 public:
  FlGui(int argc, char **argv);
  ~FlGui(){}
  // return the single static instance of the GUI
  static FlGui *instance(int argc=0, char **argv=0);
  // check if the GUI is available
  static bool available(){ return (_instance != 0); }
  // run the GUI until there's no window left
  static int run();
  // check (now!) if there are any pending events, and process them
  static void check();
  // wait (possibly indefinitely) for any events, then process them
  static void wait();
  // wait (at most time seconds) for any events, then process them
  static void wait(double time);
  int lock();
  void unlock();
  bool in_main_thread() {return _in_main_thread==0;}
  // is a file opened through the Mac Finder?
  static void setOpenedThroughMacFinder(const std::string &name)
  {
    _openedThroughMacFinder = name;
  }
  static std::string getOpenedThroughMacFinder(){ return _openedThroughMacFinder; }
  // test application-level keyboard shortcuts
  int testGlobalShortcuts(int event);
  // test the arrow shortcuts (not in the application-level shortcuts)
  // since it is used elsewhere (where we want to override widget
  // navigation). This is necessary since FLTK 1.1.
  int testArrowShortcuts();
  // set the title of the graphic windows
  void setGraphicTitle(std::string title);
  // update the GUI when views get modified, added or deleted
  void updateViews(bool numberOfViewsHasChanged, bool deleteWidgets);
  // update the GUI when fields change
  void updateFields();
  // reset the visibility window
  void resetVisibility();
  // store current window positions and sizes in CTX
  void storeCurrentWindowsInfo();
  // get the last opengl window that received an event
  openglWindow *getCurrentOpenglWindow();
  // split the current opengl window
  void splitCurrentOpenglWindow(char how);
  // copy the current opengl window to the clipboard
  void copyCurrentOpenglWindowToClipboard();
  // select an entity in the most recent graphic window
  char selectEntity(int type);
  // display status message
  void setStatus(const std::string &msg, bool opengl=false);
  // redisplay last status message
  void setLastStatus(int col=-1);
  // display status message and update progress bar
  void setProgress(const std::string &msg, double val, double min, double max);
  // create the window for physical context dependant definitions
  void callForSolverPlugin(int dim);
  // add line in message console
  void addMessage(const char *msg);
  // save messages to file
  void saveMessages(const char *fileName);
  // rebuild the tree
  void rebuildTree(bool deleteWidgets);
  // open module in tree
  void openModule(const std::string &name);
  // apply color scheme to widgets
  void applyColorScheme();
};

void redraw_cb(Fl_Widget *w, void *data);
void window_cb(Fl_Widget *w, void *data);

#endif
