#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"

namespace sempRT {
  class ObjectPlane : public ObjectBase {
  public:
    ObjectPlane();
    virtual ~ObjectPlane() override;

    bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localnormal, qbVector<double> &localColor, qbVector<double> &uvCoords) override;
  };
}

#endif // !OBJPLANE_H

