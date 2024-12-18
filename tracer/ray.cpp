#include "ray.hpp"


sempRT::Ray::Ray(const qbVector<double> &point1, const qbVector<double> &point2)
{
  m_point1 = point1;
  m_point2 = point2;
  m_lab = point2 - point1;
}


qbVector<double> sempRT::Ray::GetPoint1() const
{
  return m_point1;
}


qbVector<double> sempRT::Ray::GetPoint2() const
{
  return m_point2;
}

