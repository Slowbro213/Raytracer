#include "lightbase.hpp"


sempRT::LightBase::LightBase()
{
}

sempRT::LightBase::~LightBase()
{
}

bool sempRT::LightBase::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<sempRT::ObjectBase>>& objectList , const std::shared_ptr<sempRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity)
{
  return false;
}
