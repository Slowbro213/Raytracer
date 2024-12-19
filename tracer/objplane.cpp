#include "objplane.hpp"
#include <cmath>

sempRT::ObjectPlane::ObjectPlane() {
}

sempRT::ObjectPlane::~ObjectPlane() {
}

bool sempRT::ObjectPlane::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localnormal, qbVector<double> &localColor) {

  sempRT::Ray bcRay = m_transformMatrix.Apply(castRay, sempRT::BCKTFORM);
	
	// Copy the m_lab vector from bckRay and normalize it.
	qbVector<double> k = bcRay.m_lab;
	k.Normalize();
	

  if(CloseEnough(k.GetElement(2),0.0)) {
    return false;
  }

  double t = -bcRay.m_point1.GetElement(2) / k.GetElement(2);

  if(t < 0.0) {
    return false;
  }

  double u = bcRay.m_point1.GetElement(0) + t * k.GetElement(0);
  double v = bcRay.m_point1.GetElement(1) + t * k.GetElement(1);

  if(u < -1.0 || u > 1.0 || v < -1.0 || v > 1.0) {
    return false;
  }


  qbVector<double> poi = bcRay.m_point1 + k * t;


  intPoint = m_transformMatrix.Apply(poi, sempRT::FWDTFORM);

  qbVector<double> localOrigin = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
  qbVector<double> normalVector = qbVector<double>{std::vector<double>{0.0, 0.0, -1.0}};
  qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, sempRT::FWDTFORM);
  localnormal = m_transformMatrix.Apply(normalVector, sempRT::FWDTFORM);
  localnormal.Normalize();

  localColor = m_baseColor;

  return true;
}
