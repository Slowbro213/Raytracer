#include "cylinder.hpp"
#include <array>


sempRT::Cylinder::Cylinder()
{
}

sempRT::Cylinder::~Cylinder()
{
}

bool sempRT::Cylinder::TestIntersections(const Ray &ray, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
{

  sempRT::Ray localRay =  m_transformMatrix.Apply(ray, sempRT::BCKTFORM);


  qbVector<double> v = localRay.m_point2 - localRay.m_point1;

  v.Normalize();


  qbVector<double> p = localRay.m_point1;

  double a = v.GetElement(0) * v.GetElement(0) + v.GetElement(1) * v.GetElement(1);

  double b = 2.0 * (v.GetElement(0) * p.GetElement(0) + v.GetElement(1) * p.GetElement(1));

  double c = p.GetElement(0) * p.GetElement(0) + p.GetElement(1) * p.GetElement(1) - 1.0;

  double discriminant = b * b - 4.0 * a * c;

  std::array<qbVector<double>, 4> intPoints;
  std::array<double, 4> t;
  bool t1Flag , t2Flag, t3Flag, t4Flag;

  if (discriminant > 0.0)
  {
    t.at(0) = (-b + sqrt(discriminant)) / (2.0 * a);
    t.at(1) = (-b - sqrt(discriminant)) / (2.0 * a);

    intPoints.at(0) = p + v * t.at(0);
    intPoints.at(1) = p + v * t.at(1);


    if((t.at(0)>0) && (fabs(intPoints.at(0).GetElement(2)) < 1.0))
    {
      t1Flag = true;
    } 
    else {
      t1Flag = false;
      t.at(0) = 100e6;
    }

    if((t.at(1)>0) && (fabs(intPoints.at(1).GetElement(2)) < 1.0))
    {
      t2Flag = true;
    }
    else {
      t2Flag = false;
      t.at(1) = 100e6;
    }

  }else{
    t1Flag = false;
    t2Flag = false;
    t.at(0) = 100e6;
    t.at(1) = 100e6;
  }

  if(CloseEnough(v.GetElement(2), 0.0))
  {
    t3Flag = false;
    t4Flag = false;
    t.at(2) = 100e6;
    t.at(3) = 100e6;
  }else{
    t.at(2) = (localRay.m_point1.GetElement(2) - 1.0) / -v.GetElement(2);
    t.at(3) = (localRay.m_point1.GetElement(2) + 1.0) / -v.GetElement(2);

    intPoints.at(2) = localRay.m_point1 + v * t.at(2);
    intPoints.at(3) = localRay.m_point1 + v * t.at(3);

    if(t.at(2) > 0 && sqrtf(intPoints.at(2).GetElement(0) * intPoints.at(2).GetElement(0) + intPoints.at(2).GetElement(1) * intPoints.at(2).GetElement(1)) < 1.0)
    {
      t3Flag = true;
    }
    else {
      t3Flag = false;
      t.at(2) = 100e6;
    }

    if(t.at(3) > 0 && sqrtf(intPoints.at(3).GetElement(0) * intPoints.at(3).GetElement(0) + intPoints.at(3).GetElement(1) * intPoints.at(3).GetElement(1)) < 1.0)
    {
      t4Flag = true;
    }
    else {
      t4Flag = false;
      t.at(3) = 100e6;
    }

  }

  if(!t1Flag && !t2Flag && !t3Flag && !t4Flag)
  {
    return false;
  }

  int minIndex = 0;
  double minValue = 10e6;

  for(int i = 0; i < 4; i++)
  {
    if(t.at(i) < minValue)
    {
      minValue = t.at(i);
      minIndex = i;
    }
  }

  qbVector<double> intPointLocal = intPoints.at(minIndex);

  if(minIndex < 2)
  {
    intPoint = m_transformMatrix.Apply(intPointLocal, sempRT::FWDTFORM); 

    qbVector<double> orgNormal{3};
    qbVector<double> newNormal{3};
    qbVector<double> localOrigin {std::vector<double>{0.0, 0.0, 0.0}};
    qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, sempRT::FWDTFORM);
    orgNormal.SetElement(0, intPointLocal.GetElement(0));
    orgNormal.SetElement(1, intPointLocal.GetElement(1));
    orgNormal.SetElement(2, 0.0);
    newNormal = m_transformMatrix.Apply(orgNormal, sempRT::FWDTFORM)-globalOrigin;
    newNormal.Normalize();
    localNormal = newNormal;
    localColor = m_baseColor;
    return true;
  }else{

    if(!CloseEnough(v.GetElement(2), 0.0))
    {
      if(sqrtf(intPointLocal.GetElement(0) * intPointLocal.GetElement(0) + intPointLocal.GetElement(1) * intPointLocal.GetElement(1)) < 1.0)
      {
        intPoint = m_transformMatrix.Apply(intPointLocal, sempRT::FWDTFORM);

        qbVector<double> localOirgin {std::vector<double>{0.0, 0.0, 0.0}};
        qbVector<double> globalOrigin = m_transformMatrix.Apply(localOirgin, sempRT::FWDTFORM);
        qbVector<double> normalVector {std::vector<double>{0.0,0.0,0.0 + intPoint.GetElement(2)}};
        localNormal = m_transformMatrix.Apply(normalVector, sempRT::FWDTFORM) - globalOrigin;
        localNormal.Normalize();
        localColor = m_baseColor;
        
        return true;
      }
      else {
        return false;
      }
    }else {
      return false;
    }
  }
  return false;
}
