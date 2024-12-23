#include "checker.hpp"

sempRT::Checker::Checker()
{
    m_color1 = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}};
    m_color2 = qbVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}};
}

sempRT::Checker::~Checker()
{
}


qbVector<double> sempRT::Checker::GetColor(const qbVector<double> &uvCoords)
{
 qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	qbVector<double> localColor {4};
	int check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV));
	
	if ((check % 2) == 0)
	{
		localColor = m_color1;
	}
	else
	{
		localColor = m_color2;
	}
	
	return localColor;
}


void sempRT::Checker::SetColor1(const qbVector<double> &color)
{
    m_color1 = color;
}

void sempRT::Checker::SetColor2(const qbVector<double> &color)
{
    m_color2 = color;
}


