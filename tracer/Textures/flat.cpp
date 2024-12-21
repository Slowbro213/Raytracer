#include "flat.hpp"


sempRT::Flat::Flat()
{
  m_color = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}};
}

sempRT::Flat::~Flat()
{

}

qbVector<double> sempRT::Flat::GetColor(const qbVector<double> &uvCoords)
{
    return m_color;
}

void sempRT::Flat::SetColor(const qbVector<double> &color)
{
    m_color = color;
}

