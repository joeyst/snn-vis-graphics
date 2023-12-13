
#ifndef _NAV_NODE_H
#define _NAV_NODE_H

#include "Point3D.h"
#include <vector>
#include "Neuron.h"

std::vector<PointIds3D> GetPointIdsInRadius(PointIds3D center, int r);

class NavNode {
  /*
  Stores blocks of neurons. 
  Statistics functions. 
  */
  public:
    std::vector<PointIds3D> PointIds();
    NavNode(PointIds3D xyz_id, int r);
    void Stimulate();
    void Inhibit();

  private:
    std::vector<int> xyz_id;
    int r;
    std::vector<Neuron*> neurons;
};

#endif
