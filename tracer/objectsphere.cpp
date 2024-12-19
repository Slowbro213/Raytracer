#include "objectsphere.hpp"

#include <cmath>


sempRT::ObjectSphere::ObjectSphere() {
}

sempRT::ObjectSphere::~ObjectSphere() {
}

bool sempRT::ObjectSphere::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localnormal, qbVector<double> &localColor) {
  

  sempRT::Ray bcRay = m_transformMatrix.Apply(castRay, sempRT::BCKTFORM);
   

  qbVector<double> vhat = bcRay.m_lab;
  vhat.Normalize();

  double b = 2.0 * qbVector<double>::dot(bcRay.m_point1, vhat); 


  double c = qbVector<double>::dot(bcRay.m_point1, bcRay.m_point1) - 1.0;

  double intTest = b * b - 4.0 * c;

  qbVector<double> poi;

  if (intTest < 0.0) {
    return false;
  }

  double numSqrt = sqrtf(intTest);
  double t1 = (-b + numSqrt) / 2.0;
  double t2 = (-b - numSqrt) / 2.0;

  if(t1 < 0.0 && t2 < 0.0) {
    return false;
  }else {
    if(t1 < t2)
    {
      poi = bcRay.m_point1 + vhat * t1;

    }else {
      poi = bcRay.m_point1 + vhat * t2;
    }


    intPoint = m_transformMatrix.Apply(poi, sempRT::FWDTFORM);


    // Compute the normal (sphere at origin for now)
    qbVector<double> objOrigin = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
    qbVector<double> newObjOrigin = m_transformMatrix.Apply(objOrigin, sempRT::FWDTFORM);
    localnormal = intPoint - newObjOrigin;
    localnormal.Normalize();


    localColor = m_baseColor;

  }


  return true;
}
