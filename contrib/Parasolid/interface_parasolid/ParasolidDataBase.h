
#ifndef _PARASOLID_DB_H_
#define _PARASOLID_DB_H_

#include <stdio.h>
#include "parasolid_kernel.h"
#include "kernel_interface.h"
#include "string.h"

#include <iostream>

#include <vector>
#include <list>
#include <string>

#include "frustrum_interface.h"

using namespace std;

extern void set_frustrum_interface_ptr(frustrumInterface *ptr);

class ParasolidDataBase{
  public:
    typedef vector<PK_TOPOL_t>::const_iterator topo_iter;
    typedef vector<PK_CLASS_t>::const_iterator class_iter;
    typedef vector<PK_VERTEX_t>::const_iterator vertex_iter;
    typedef vector<PK_EDGE_t>::const_iterator edge_iter;
    typedef vector<PK_FACE_t>::const_iterator face_iter;
    typedef vector<PK_REGION_t>::const_iterator region_iter;

    ParasolidDataBase(string _schema_path);
    ~ParasolidDataBase();
    void readFile(const string &path, const string &s);

    topo_iter topobegin()const{return topols.begin();};
    topo_iter topoend()const{return topols.end();};
    class_iter classbegin()const{return classes.begin();};
    class_iter classend()const{return classes.end();};
    vertex_iter vertexbegin()const{return vertices.begin();};
    vertex_iter vertexend()const{return vertices.end();};
    edge_iter edgebegin()const{return edges.begin();};
    edge_iter edgeend()const{return edges.end();};
    face_iter facebegin()const{return faces.begin();};
    face_iter faceend()const{return faces.end();};
    region_iter regionbegin()const{return regions.begin();};
    region_iter regionend()const{return regions.end();};


    pair<PK_VERTEX_t,PK_VERTEX_t> getVertices(const PK_EDGE_t &edge)const;
    void getEdgesAndSigns(const PK_LOOP_t &loop, list<PK_EDGE_t> &edges, list<int> &signs)const;

    void createCylinder();
    void createBlock();
    void createTwoBlocks();
    void createCutBlock();
    void createSphere();
    void createCone();
    void createTorus();
    
    void transmit(const string &key);
    void erase_all_parts();

    double get_parasolid_session_precision()const;

  private:
    void registerFrustrum();
    void registerFrustrumDeltas();
    void startParasolidSession();
    
    void displayErrorMessage(const string &s,const PK_ERROR_code_t &e)const;
    void displayBodyConfig()const;
    void fillVector(vector<PK_ENTITY_t> &e, int num, const PK_ENTITY_t *original, const PK_ERROR_code_t &err, const string &s);


    PK_BODY_t body;
    PK_ENTITY_t *parts;
    int num_parts,num_bodies;

    PK_SESSION_frustrum_t fru;
    PK_DELTA_frustrum_t delta_fru;
    PK_PART_receive_o_t receive_options;
    PK_SESSION_start_o_t start_options;
    PK_BODY_ask_topology_o_t topo_ask_options;
    mutable PK_ERROR_code_t err;
    PK_CLASS_t tClass;
  
    frustrumInterface *fi;
    string schema_path;
    
    vector<PK_TOPOL_t> topols;
    vector<PK_CLASS_t> classes;
    
    vector<PK_VERTEX_t> vertices;
    vector<PK_EDGE_t> edges;
    vector<PK_FACE_t> faces;
    vector<PK_REGION_t> regions;
};


#endif
