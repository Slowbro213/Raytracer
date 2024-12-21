#ifndef CYLINDER_H
#define CYLINDER_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace sempRT {
  class Cylinder : public ObjectBase
  {
  public:
    Cylinder();
    ~Cylinder() override;

    Cylinder& operator= (const Cylinder &rhs);

    virtual bool TestIntersections(const Ray &ray, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;

  };
}

#endif // !CYLINDER_H
