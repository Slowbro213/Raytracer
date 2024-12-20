#include "pointlight.hpp"


sempRT::PointLight::PointLight()
{
  m_color = qbVector<double> {std::vector<double>{1.0, 1.0, 1.0}};
  m_intensity = 1.0;
}

sempRT::PointLight::~PointLight()
{
}

bool sempRT::PointLight::ComputeIllumination(const qbVector<double> &intPoint, const qbVector<double> &localNormal, const std::vector<std::shared_ptr<sempRT::ObjectBase>>& objectList, const std::shared_ptr<sempRT::ObjectBase> &currentObject, qbVector<double> &color, double &intensity)
{
  qbVector<double> lightDir = (m_location -intPoint).Normalized();

  qbVector<double> startPoint = intPoint;

 
	sempRT::Ray lightRay (startPoint, startPoint + lightDir);
	
	qbVector<double> poi				{3};
	qbVector<double> poiNormal	{3};
	qbVector<double> poiColor		{3};
	bool validInt = false;
	for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject -> TestIntersections(lightRay, poi, poiNormal, poiColor);
		}
		
		if (validInt)
			break;
	}

	if (!validInt)
	{
		double angle = acos(qbVector<double>::dot(localNormal, lightDir));
		
		if (angle > 1.5708)
		{
			color = m_color;
			intensity = 0.0;
			return false;
		}
		else
		{
			color = m_color;
			intensity = m_intensity * (1.0 - (angle / 1.5708));
			return true;
		}
	}
	else
	{
		color = m_color;
		intensity = 0.0;
		return false;
	}}
