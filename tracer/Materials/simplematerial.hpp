#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H

#include "../qbLinAlg/qbVector.h"
#include <memory>
#include "../Primitives/objectbase.hpp"
#include "../Lights/lightbase.hpp"
#include "../ray.hpp"
#include "materialbase.hpp"


namespace sempRT {
  
  class SimpleMaterial : public MaterialBase { 

  public:
    SimpleMaterial();
    virtual ~SimpleMaterial() override;

    virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords) override;


    qbVector<double> ComputeSpecular(const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords);

  public:
    qbVector<double> m_baseColor {std::vector<double>{1.0, 1.0, 1.0}};
    double m_reflectivity=0.0;
    double m_shine=0.0;
};
}
#endif // !SIMPLEMATERIAL_H

