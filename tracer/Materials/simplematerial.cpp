#include "simplematerial.hpp"
#include <mutex>

sempRT::SimpleMaterial::SimpleMaterial()
{
}

sempRT::SimpleMaterial::~SimpleMaterial()
{
}


qbVector<double> sempRT::SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords)
{
  qbVector<double> matcolor {3};
  qbVector<double> refcolor {3};
  qbVector<double> difColor {3};
  qbVector<double> spcColor {3};


  if(!m_hasTexture)
  {
    difColor = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, m_baseColor, uvCoords);
  }
  else {
    difColor = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, m_textures.at(0)->GetColor(uvCoords), uvCoords);
  }

  if(m_reflectivity > 0.0)
  {
    refcolor = ComputeReflectionColor(objectList, lightList, currentObject, intPoint, localNormal, ray, uvCoords);
    m_reflectionDepth--;
  }

  matcolor = (refcolor * m_reflectivity) + difColor*(1.0 - m_reflectivity);

  if(m_shine > 0.0)
  {
    spcColor = ComputeSpecular(objectList, lightList, currentObject, intPoint, localNormal, ray, uvCoords);
  }


  matcolor = matcolor + spcColor;

  return matcolor; 
}


qbVector<double> sempRT::SimpleMaterial::ComputeSpecular( const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords){

  qbVector<double> spcColor {3};
  double red = 0.0;
  double green = 0.0;
  double blue = 0.0;

  for (auto currentLight : lightList)
  {
    double intensity = 0.0;

    qbVector<double> lightDir = (currentLight->m_location - intPoint).Normalized();

    qbVector<double> start = intPoint + (lightDir * 1e-3);

    sempRT::Ray lightRay(start, start + lightDir);

    qbVector<double> poi {3};
    qbVector<double> poiNormal {3};
    qbVector<double> poiColor {3};
    bool validInt = false;
    for (auto sceneObject : objectList)
    {
        validInt = sceneObject -> TestIntersections(lightRay, poi, poiNormal, poiColor, uvCoords);

      if (validInt)
        break;
    }

    if(!validInt)
    {
      qbVector<double> d = lightRay.m_lab;
      qbVector<double> r = d - 2 * qbVector<double>::dot(d, localNormal) * localNormal;
      r.Normalize();

      qbVector<double> v = ray.m_lab;
      v.Normalize();

      double angle = qbVector<double>::dot(r, v);

      if (angle > 0.0)
      {
        intensity = m_reflectivity * pow(angle, m_shine);
      }

      red += intensity * currentLight->m_color.GetElement(0);
      green += intensity * currentLight->m_color.GetElement(1);
      blue += intensity * currentLight->m_color.GetElement(2);

      spcColor.SetElement(0, red);
      spcColor.SetElement(1, green);
      spcColor.SetElement(2, blue);

    }
  }

  return spcColor;
}
