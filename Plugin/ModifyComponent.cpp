// Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@geuz.org>.

#include <vector>
#include <algorithm>
#include "GmshConfig.h"
#include "ModifyComponent.h"
#include "OctreePost.h"
#include "mathEvaluator.h"

StringXNumber ModifyComponentOptions_Number[] = {
  {GMSH_FULLRC, "Component", NULL, -1.},
  {GMSH_FULLRC, "TimeStep", NULL, -1.},
  {GMSH_FULLRC, "View", NULL, -1.},
  {GMSH_FULLRC, "OtherTimeStep", NULL, -1.},
  {GMSH_FULLRC, "OtherView", NULL, -1.},
  {GMSH_FULLRC, "ForceInterpolation", NULL, 0.}
};

StringXString ModifyComponentOptions_String[] = {
  {GMSH_FULLRC, "Expression", NULL, "v0 * Sin(x)"}
};

extern "C"
{
  GMSH_Plugin *GMSH_RegisterModifyComponentPlugin()
  {
    return new GMSH_ModifyComponentPlugin();
  }
}

std::string GMSH_ModifyComponentPlugin::getHelp() const
{
  return "Plugin(ModifyComponent) sets the `Component'-th "
    "component of the `TimeStep'-th time step in the "
    "view `View' to the expression `Expression'.\n\n"
    "`Expression' can contain:\n\n"
    "- the usual mathematical functions (Log, Sqrt, "
    "Sin, Cos, Fabs, ...) and operators (+, -, *, /, ^);\n\n"
    "- the symbols x, y and z, to retrieve the "
    "coordinates of the current node;\n\n"
    "- the symbols Time and TimeStep, to retrieve the "
    "current time and time step values;\n\n"
    "- the symbol v, to retrieve the `Component'-th "
    "component of the field in `View' at the "
    "`TimeStep'-th time step;\n\n"
    "- the symbols v0, v1, v2, ..., v8, to retrieve each "
    "component of the field in `View' at the "
    "`TimeStep'-th time step;\n\n"
    "- the symbol w, to retrieve the `Component'-th "
    "component of the field in `OtherView' at the "
    "`OtherTimeStep'-th time step. If `OtherView' "
    "and `View' are based on different spatial grids, "
    "or if their data types are different, `OtherView' "
    "is interpolated onto `View';\n\n"
    "- the symbols w0, w1, w2, ..., w8, to retrieve each "
    "component of the field in `OtherView' at the "
    "`OtherTimeStep'-th time step.\n\n"
    "If `TimeStep' < 0, the plugin automatically loops "
    "over all the time steps in `View' and evaluates "
    "`Expression' for each one.\n\n"
    "If `OtherTimeStep' < 0, the plugin uses `TimeStep' "
    "instead.\n\n"
    "If `Component' < 0, the plugin automatically  ops\n"
    "over all the components in the view and "
    "evaluates `Expression' for each one.\n\n"
    "If `View' < 0, the plugin is run on the current view.\n\n"
    "If `OtherView' < 0, the plugin uses `View' instead.\n\n"
    "Plugin(ModifyComponent) is executed in-place.";
}

int GMSH_ModifyComponentPlugin::getNbOptions() const
{
  return sizeof(ModifyComponentOptions_Number) / sizeof(StringXNumber);
}

StringXNumber *GMSH_ModifyComponentPlugin::getOption(int iopt)
{
  return &ModifyComponentOptions_Number[iopt];
}

int GMSH_ModifyComponentPlugin::getNbOptionsStr() const
{
  return sizeof(ModifyComponentOptions_String) / sizeof(StringXString);
}

StringXString *GMSH_ModifyComponentPlugin::getOptionStr(int iopt)
{
  return &ModifyComponentOptions_String[iopt];
}

PView *GMSH_ModifyComponentPlugin::execute(PView *view)
{
  int component = (int)ModifyComponentOptions_Number[0].def;
  int timeStep = (int)ModifyComponentOptions_Number[1].def;
  int iView = (int)ModifyComponentOptions_Number[2].def;
  int otherTimeStep = (int)ModifyComponentOptions_Number[3].def;
  int otherView = (int)ModifyComponentOptions_Number[4].def;
  int forceInterpolation = (int)ModifyComponentOptions_Number[5].def;

  PView *v1 = getView(iView, view);
  if(!v1) return view;

  PViewData *data1 = v1->getData();

  if(timeStep > data1->getNumTimeSteps() - 1){
    Msg::Error("Invalid time step (%d) in View[%d]: using step 0 instead",
               timeStep, v1->getIndex());
    timeStep = 0;
  }

  PView *v2 = v1;

  if(otherView >= 0){
    if(otherView < (int)PView::list.size())
      v2 = PView::list[otherView];
    else
      Msg::Error("View[%d] does not exist: using self", otherView);
  }

  PViewData *data2 = getPossiblyAdaptiveData(v2);

  if(otherTimeStep < 0 && data2->getNumTimeSteps() != data1->getNumTimeSteps()){
    Msg::Error("Number of time steps don't match: using step 0");
    otherTimeStep = 0;
  }
  else if(otherTimeStep > data2->getNumTimeSteps() - 1){
    Msg::Error("Invalid time step (%d) in View[%d]: using step 0 instead",
               otherTimeStep, v2->getIndex());
    otherTimeStep = 0;
  }

  const char *names[] =
    {"x", "y", "z", "Time", "TimeStep",
     "v", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8",
     "w", "w0", "w1", "w2", "w3", "w4", "w5", "w6", "w7", "w8"};
  unsigned int numVariables = sizeof(names) / sizeof(names[0]);
  std::vector<std::string> expressions(1), variables(numVariables);
  expressions[0] = ModifyComponentOptions_String[0].def;
  for(unsigned int i = 0; i < numVariables; i++) variables[i] = names[i];
  mathEvaluator f(expressions, variables);
  if(expressions.empty()) return view;
  std::vector<double> values(numVariables), res(1);

  OctreePost *octree = 0;
  if(forceInterpolation ||
     (data1->getNumEntities() != data2->getNumEntities()) ||
     (data1->getNumElements() != data2->getNumElements())){
    Msg::Info("Other view based on different grid: interpolating...");
    octree = new OctreePost(v2);
  }

  for(int step = 0; step < data1->getNumTimeSteps(); step++){
    if(timeStep >= 0 && timeStep != step) continue;

    double time = data1->getTime(step);
    int step2 = (otherTimeStep < 0) ? step : otherTimeStep;

    if(data1->isNodeData()){
      // tag all the nodes with "0" (the default tag)
      for(int ent = 0; ent < data1->getNumEntities(step); ent++){
        for(int ele = 0; ele < data1->getNumElements(step, ent); ele++){
          if(data1->skipElement(step, ent, ele)) continue;
          for(int nod = 0; nod < data1->getNumNodes(step, ent, ele); nod++)
            data1->tagNode(step, ent, ele, nod, 0);
        }
      }
    }

    for(int ent = 0; ent < data1->getNumEntities(step); ent++){
      for(int ele = 0; ele < data1->getNumElements(step, ent); ele++){
        if(data1->skipElement(step, ent, ele)) continue;
        int numComp = data1->getNumComponents(step, ent, ele);
        int numComp2 = octree ? 9 : data2->getNumComponents(step2, ent, ele);
        int numNodes = data1->getNumNodes(step, ent, ele);
        std::vector<double> x(numNodes), y(numNodes), z(numNodes);
        std::vector<int> tag(numNodes);
        for(int nod = 0; nod < numNodes; nod++)
          tag[nod] = data1->getNode(step, ent, ele, nod, x[nod], y[nod], z[nod]);
        for(int nod = 0; nod < numNodes; nod++){
          if(data1->isNodeData() && tag[nod]) continue; // node has already been modified
          std::vector<double> v(std::max(9, numComp), 0.);
          for(int comp = 0; comp < numComp; comp++)
            data1->getValue(step, ent, ele, nod, comp, v[comp]);
          std::vector<double> w(std::max(9, numComp2), 0.);
          if(octree){
            int qn = forceInterpolation ? numNodes : 0;
            if(!octree->searchScalar(x[nod], y[nod], z[nod], &w[0], step2,
                                     0, qn, &x[0], &y[0], &z[0]))
              if(!octree->searchVector(x[nod], y[nod], z[nod], &w[0], step2,
                                       0, qn, &x[0], &y[0], &z[0]))
                octree->searchTensor(x[nod], y[nod], z[nod], &w[0], step2,
                                     0, qn, &x[0], &y[0], &z[0]);
          }
          else
            for(int comp = 0; comp < numComp2; comp++)
              data2->getValue(step2, ent, ele, nod, comp, w[comp]);
          for(int comp = 0; comp < numComp; comp++){
            if(component >= 0 && component != comp) continue;
            values[0] = x[nod]; values[1] = y[nod]; values[2] = z[nod];
            values[3] = time; values[4] = step;
            values[5] = v[comp];
            for(int i = 0; i < 9; i++) values[6 + i] = v[i];
            values[15] = w[comp];
            for(int i = 0; i < 9; i++) values[16 + i] = w[i];
            if(f.eval(values, res))
              data1->setValue(step, ent, ele, nod, comp, res[0]);
            if(data1->isNodeData()) data1->tagNode(step, ent, ele, nod, 1);
          }
        }
      }
    }
  }

  if(octree) delete octree;

  data1->finalize();
  v1->setChanged(true);

  return v1;
}
