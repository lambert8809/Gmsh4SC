
#ifndef _PARASOLID_GMODELBUILDER_H_
#define _PARASOLID_GMODELBUILDER_H_

#include "ParasolidDataBase.h"
#include<map>
#include<set>



class GModel;
class GenericField;
class GenericFace;
class GEdge;
class cyl_data;

class ParasolidGModelBuilder{
  public:
    ParasolidGModelBuilder(ParasolidDataBase *_db);
    ~ParasolidGModelBuilder();
    void buildGModel() const;
    void createCompounds()const;
    void mesh(int dim) const;
    void readandwriteGEO() const;
    void test() const;

    void set_alternative_tag(PK_TOPOL_t original, int alternative)const;
    void setMeshSizeFields();

  private:
    const ParasolidDataBase *db;

    // correspondence GenericEntity* <-> PK_ENTITY_t
    mutable map<PK_TOPOL_t,void*> int2ptr;
    mutable map<PK_TOPOL_t,void*> ring_edges;
    // used to re-tag. For instance, use same tag for 2 faces.
    mutable map<int,set<PK_TOPOL_t> > alternative2original_tags;
    mutable map<PK_TOPOL_t,int> original2alternative_tags;


    
    bool checkForRingEdges(const list<int> &edges, map<int,void*> &found_ring_edges)const;
    void treat_ring_edges(GenericFace *current_face,map<int,void*> &found_ring_edges, int &numv, int &nume, GEdge *&cylindre_edge)const;


    GModel *model;
    GenericField *fields;
    cyl_data *cd,*cd2;
};


#endif
