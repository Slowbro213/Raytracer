#include "cone.hpp"
#include <cmath>
#include <array>

sempRT::Cone::Cone()
{

}

sempRT::Cone::~Cone()
{

}

bool sempRT::Cone::TestIntersections(	const sempRT::Ray &castRay, qbVector<double> &intPoint,
																		qbVector<double> &localNormal, qbVector<double> &localColor)
{
	sempRT::Ray bckRay = m_transformMatrix.Apply(castRay, sempRT::BCKTFORM);
	
	qbVector<double> v = bckRay.m_lab;
	v.Normalize();
	
	qbVector<double> p = bckRay.m_point1;
	
	double a = std::pow(v.GetElement(0), 2.0) + std::pow(v.GetElement(1), 2.0) - std::pow(v.GetElement(2), 2.0);
	double b = 2 * (p.GetElement(0)*v.GetElement(0) + p.GetElement(1)*v.GetElement(1) - p.GetElement(2)*v.GetElement(2));
	double c = std::pow(p.GetElement(0), 2.0) + std::pow(p.GetElement(1), 2.0) - std::pow(p.GetElement(2), 2.0);
	
	double numSQRT = sqrtf(std::pow(b, 2.0) - 4 * a * c);
	
	std::array<qbVector<double>, 3> poi;
	std::array<double, 3> t;
	bool t1Valid, t2Valid, t3Valid;
	if (numSQRT > 0.0)
	{
		t.at(0) = (-b + numSQRT) / (2 * a);
		t.at(1) = (-b - numSQRT) / (2 * a);
		
		poi.at(0) = bckRay.m_point1 + (v * t[0]);
		poi.at(1) = bckRay.m_point1 + (v * t[1]);
		
		if ((t.at(0) > 0.0) && (poi.at(0).GetElement(2) > 0.0) && (poi.at(0).GetElement(2) < 1.0))
		{
			t1Valid = true;
		}
		else
		{
			t1Valid = false;
			t.at(0) = 100e6;
		}
		
		if ((t.at(1) > 0.0) && (poi.at(1).GetElement(2) > 0.0) && (poi.at(1).GetElement(2) < 1.0))
		{
			t2Valid = true;
		}
		else
		{
			t2Valid = false;
			t.at(1) = 100e6;
		}
	}
	else
	{
		t1Valid = false;
		t2Valid = false;
		t.at(0) = 100e6;
		t.at(1) = 100e6;
	}
	
	if (CloseEnough(v.GetElement(2), 0.0))
	{
		t3Valid = false;
		t.at(2) = 100e6;
	}
	else
	{	
		t.at(2) = (bckRay.m_point1.GetElement(2) - 1.0) / -v.GetElement(2);
		
		poi.at(2) = bckRay.m_point1 + t.at(2) * v;
		
		if ((t.at(2) > 0.0) && (sqrtf(std::pow(poi.at(2).GetElement(0), 2.0) + std::pow(poi.at(2).GetElement(1), 2.0)) < 1.0))
		{
			t3Valid = true;
		}
		else
		{
			t3Valid = false;
			t.at(2) = 100e6;
		}						
	}
	
	if ((!t1Valid) && (!t2Valid) && (!t3Valid))
		return false;	
		
	int minIndex = 0;
	double minValue = 10e6;
	for (int i=0; i<3; ++i)
	{
		if (t.at(i) < minValue)
		{
			minValue = t.at(i);
			minIndex = i;
		}
	}
	
	qbVector<double> validPOI = poi.at(minIndex);
	if (minIndex < 2)
	{		
		intPoint = m_transformMatrix.Apply(validPOI, sempRT::FWDTFORM);		
			
		qbVector<double> orgNormal {3};
		qbVector<double> newNormal {3};
		qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
		qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, sempRT::FWDTFORM);		
		double tX = validPOI.GetElement(0);
		double tY = validPOI.GetElement(1);
		double tZ = -sqrtf(pow(tX, 2.0) + pow(tY, 2.0));
		orgNormal.SetElement(0, tX);
		orgNormal.SetElement(1, tY);
		orgNormal.SetElement(2, tZ);
		newNormal = m_transformMatrix.Apply(orgNormal, sempRT::FWDTFORM) - globalOrigin;
		newNormal.Normalize();		
		localNormal = newNormal;
			
		localColor = m_baseColor;
	
		return true;
	}
	else
	{
		if (!CloseEnough(v.GetElement(2), 0.0))
		{
			if (sqrtf(std::pow(validPOI.GetElement(0), 2.0) + std::pow(validPOI.GetElement(1), 2.0)) < 1.0)
			{
				intPoint = m_transformMatrix.Apply(validPOI, sempRT::FWDTFORM);				
				
				qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
				qbVector<double> normalVector {std::vector<double> {0.0, 0.0, 1.0}};
				qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, sempRT::FWDTFORM);
				localNormal = m_transformMatrix.Apply(normalVector, sempRT::FWDTFORM) - globalOrigin;
				localNormal.Normalize();
						
				localColor = m_baseColor;
						
				return true;				
			}
			else
			{
				return false;
			}			
		}
		else
		{
			return false;
		}
		
	}		
	
	return false;
}
