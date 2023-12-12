
#include "Net.h"
#include "Point3D.h"
#include "Direction.h"
#include "NavGraph.h"

#ifndef _NET_BUILDER_H
#define _NET_BUILDER_H

class NetBuilder {
  /*
  AddRectangle: 
    start => starting point. 
    width => (N, M, 0) | (N, 0, M) | (0, N, M). Creates initial plane. N and M can be negative. 
    dxyz  => jump rate in each dimension. 
    n     => number of layers. 
  */
  public:
    Net *net;
    void AddRectangle(PointIds3D start, PointIds3D dxyz, PointIds3D step, std::size_t n);
    NetBuilder();
    void AddMap(PointIds3D start, PointIds3D dxyzs, PointIds3D end, PointIds3D dxyze);

  private:
    NavGraph* nav_graph;
};

#endif 
