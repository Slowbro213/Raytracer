#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"
#include "../gtfm.hpp"


namespace sempRT {

  class MaterialBase;
  
  class ObjectBase {
  public:
    ObjectBase();
    virtual ~ObjectBase();
    virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localnormal, qbVector<double> &localColor);
    void SetTransformMatrix(const sempRT::Gtform &tfm);
    bool CloseEnough(const double f1, const double f2);
    bool AssignMaterial(const std::shared_ptr<MaterialBase> &material);

  public:
    qbVector<double> m_baseColor {3};
    sempRT::Gtform m_transformMatrix;
    std::shared_ptr<MaterialBase> m_material;
    bool hasMaterial = false;
  };
}

#endif // OBJECTBASE_H
