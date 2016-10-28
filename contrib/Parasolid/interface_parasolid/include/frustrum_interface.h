#ifndef _FRUSTRUM_INTERFACE_H_
#define _FRUSTRUM_INTERFACE_H_

#include <stdio.h>

#include <iostream>
#include <sstream>

#include <string>

using namespace std;

class frustrumInterface{
  public:
    frustrumInterface(){
      filename_path.assign("");
      schema_path.assign("");
    };
    ~frustrumInterface(){};

    void set_filename_path(string s){
//      cout << "s=" << s << endl;
//      cout << "filename_path=" << filename_path << endl;
      filename_path.assign(s);
    };
    void set_schema_path(string s){
//      cout << "s=" << s << endl;
//      cout << "schema_path=" << schema_path << endl;
      schema_path.assign(s);
    };
    string get_filename_path()const{return filename_path;};
    string get_schema_path()const{return schema_path;};

    bool is_schema_file(string name)const{
      size_t s = name.find(".sch_txt");// check schema
      return (s<name.size());
    }

  private:
    string filename_path,schema_path;

};
#endif
