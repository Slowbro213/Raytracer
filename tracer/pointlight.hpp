#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightbase.hpp"

namespace sempRT {
  class PointLight : public LightBase {
  public:
    PointLight();
    virtual ~PointLight() override;

    virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<sempRT::ObjectBase>>& objectList, const std::shared_ptr<sempRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity) override;

  private:

  };
}

#endif // !POINTLIGHT_H

