# Gmsh - Copyright (C) 1997-2015 C. Geuzaine, J.-F. Remacle
#
# See the LICENSE.txt file for license information. Please report all
# bugs and problems to the public mailing list <gmsh@geuz.org>.

set(SRC
  MeshOpt.cpp
  MeshOptCommon.cpp
  MeshOptimizer.cpp
  MeshOptPatch.cpp
  MeshOptObjectiveFunction.cpp
  MeshOptObjContrib.cpp
  MeshOptObjContribFunc.cpp
  MeshOptVertexCoord.cpp
)

file(GLOB_RECURSE HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
append_gmsh_src(contrib/MeshOptimizer "${SRC};${HDR}")
