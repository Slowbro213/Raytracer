#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"
#include "gtfm.hpp"


namespace sempRT {
  
  class ObjectBase {
  public:
    ObjectBase();
    virtual ~ObjectBase();
    virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localnormal, qbVector<double> &localColor);
    void SetTransformMatrix(const sempRT::Gtform &tfm);
    bool CloseEnough(const double f1, const double f2);


  public:
    qbVector<double> m_baseColor {3};
    sempRT::Gtform m_transformMatrix;
  };
}

#endif // OBJECTBASE_H
