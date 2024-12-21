#include "materialbase.hpp"


sempRT::MaterialBase::MaterialBase()
{
  m_maxReflectionRays = 3;
  m_reflectionDepth = 0;
}

sempRT::MaterialBase::~MaterialBase()
{
}

qbVector<double> sempRT::MaterialBase::ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords)
{
  qbVector<double> color {3};
  return color;
}


qbVector<double> sempRT::MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const qbVector<double> &baseColor, qbVector<double> &uvCoords)
{
  qbVector<double> diffuseColor {3};
  double intensity;

  qbVector<double> color {3};
  bool validLight = false;
  bool lightHit = false;
  double red = 0.0;
  double green = 0.0;
  double blue = 0.0;

  for (auto currentLight : lightList)
  {
    bool validLight = currentLight -> ComputeIllumination(intPoint, localNormal, objectList, currentObject, color, intensity, uvCoords);

    if (validLight)
    {
      lightHit = true;
      red+= color.GetElement(0) * intensity;
      green+= color.GetElement(1) * intensity;
      blue+= color.GetElement(2) * intensity;
    }


  }

  if (lightHit)
  {
    diffuseColor.SetElement(0, red * baseColor.GetElement(0));
    diffuseColor.SetElement(1, green * baseColor.GetElement(1));
    diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
  }

  return diffuseColor;
}

qbVector<double> sempRT::MaterialBase::ComputeReflectionColor( const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords)
{
  qbVector<double> refcolor {3};
  
  qbVector<double> reflectDir = ray.m_lab - (2.0 * qbVector<double>::dot(ray.m_lab, localNormal) * localNormal);

  sempRT::Ray reflectRay(intPoint, intPoint + reflectDir);

  qbVector<double> closestIntPoint {3};
  qbVector<double> closestLocalNormal {3};
  qbVector<double> closestLocalColor {3};
  std::shared_ptr<sempRT::ObjectBase> closestObject;
  
  bool intersect = CastRay(reflectRay, objectList, currentObject,  closestObject, closestIntPoint, closestLocalNormal, closestLocalColor, uvCoords);

  qbVector<double> matColor {3};

  if(intersect && (m_reflectionDepth < m_maxReflectionRays))
  {
    m_reflectionDepth++;

    if(closestObject->hasMaterial)
    {
      matColor = closestObject->m_material->ComputeColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, reflectRay, uvCoords);
    }
    else
    {
      matColor = ComputeDiffuseColor(objectList, lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->m_baseColor, uvCoords);
    }
  }

  return matColor;
}


bool sempRT::MaterialBase::CastRay (const Ray &ray, const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase> &thisObject  , std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor, qbVector<double> &uvCoords)
{
  qbVector<double> intPoint {3};
  qbVector<double> localNormal {3};
  qbVector<double> localColor {3};

  double minDist = 1e6;
  bool hitFlag = false;

  for (auto currentObject : objectList)
  {
    if(currentObject == thisObject)
    {
      continue;
    }
    bool validInt = currentObject -> TestIntersections(ray, intPoint, localNormal, localColor, uvCoords);

    if (validInt)
    {
      hitFlag = true;

      double dist = (intPoint - ray.m_point1).norm();

      if (dist < minDist)
      {
        minDist = dist;
        closestObject = currentObject;
        closestIntPoint = intPoint;
        closestLocalNormal = localNormal;
        closestLocalColor = localColor;
      }
    }
  }

  return hitFlag;
}


void sempRT::MaterialBase::AssignTexture(const std::shared_ptr<sempRT::TextureBase> &texture)
{
  m_textures.push_back(texture);
  m_hasTexture = true;
}
