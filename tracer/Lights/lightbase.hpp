#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"
#include <memory>
#include "../Primitives/objectbase.hpp"


namespace sempRT {
  class LightBase {
  public:
    LightBase();
    virtual ~LightBase();

    virtual bool ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<sempRT::ObjectBase>>& objectList , const std::shared_ptr<sempRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity, qbVector<double> &uvCoords); 

  public:
    qbVector<double> m_color {3};
    qbVector<double> m_location {3};
    double m_intensity;


  private:

  };
}
#endif // !LIGHTBASE_H

