#include "camera.hpp"
#include "ray.hpp"
#include <math.h>


sempRT::Camera::Camera()
{
  m_cameraPosition = qbVector<double> {std::vector<double>{0.0, -10.0, 0.0}};
  m_cameraLookAt = qbVector<double> {std::vector<double>{0.0, 0.0, 0.0}};
  m_cameraUp = qbVector<double> {std::vector<double>{0.0, 0.0, 1.0}};
  m_cameraLength = 1.0;
  m_cameraHorzSie = 1.0;
  m_cameraAspectRatio = 1.0;
}


void sempRT::Camera::SetPosition(const qbVector<double> &newPosition)
{
  m_cameraPosition = newPosition;
}

void sempRT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
  m_cameraLookAt = newLookAt;
}

void sempRT::Camera::SetUp(const qbVector<double> &newUp)
{
  m_cameraUp = newUp;
}

void sempRT::Camera::SetLength(const double newLength)
{
  m_cameraLength = newLength;
}

void sempRT::Camera::SetHorzSize(const double newHorzSize)
{
  m_cameraHorzSie = newHorzSize;
}

void sempRT::Camera::SetAspect(const double newAspect)
{
  m_cameraAspectRatio = newAspect;
}

qbVector<double> sempRT::Camera::GetPosition() const
{
  return m_cameraPosition;
}

qbVector<double> sempRT::Camera::GetLookAt() const
{
  return m_cameraLookAt;
}

qbVector<double> sempRT::Camera::GetUp() const
{
  return m_cameraUp;
}

qbVector<double> sempRT::Camera::GetU() const
{
  return m_projectionScreenU;
}

qbVector<double> sempRT::Camera::GetV() const
{
  return m_projectionScreenV;
}

double sempRT::Camera::GetAspect() const
{
  return m_cameraAspectRatio;
}

double sempRT::Camera::GetHorzSize() const
{
  return m_cameraHorzSie;
}

double sempRT::Camera::GetLength() const
{
  return m_cameraLength;
}

qbVector<double> sempRT::Camera::GetScreenCenter() const
{
  return m_projectionScreenCenter;
}

void sempRT::Camera::UpdateCameraGeometry()
{
  m_alignmentVector = m_cameraLookAt - m_cameraPosition;
  m_alignmentVector.Normalize();

  m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
  m_projectionScreenU.Normalize();

  m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
  m_projectionScreenV.Normalize();

  m_projectionScreenCenter = m_cameraPosition + m_alignmentVector * m_cameraLength;

  m_projectionScreenU = m_projectionScreenU * m_cameraHorzSie;
  m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSie / m_cameraAspectRatio);
}


bool sempRT::Camera::GenerateRay(float proScreenX, float proScreenY, Ray &ray)
{
  qbVector<double> screenWorldPart1 = m_projectionScreenCenter + m_projectionScreenU * proScreenX;
  qbVector<double> screenWorldCoordinate = screenWorldPart1 + m_projectionScreenV * proScreenY;

  ray.m_point1 = m_cameraPosition;
  ray.m_point2 = screenWorldCoordinate;
  ray.m_lab = screenWorldCoordinate - m_cameraPosition;

  return true;
}
