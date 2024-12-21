#include "objectbase.hpp"
#include <math.h>
#include <mutex>

#define EPSILON 1e-21f


sempRT::ObjectBase::ObjectBase() {
}

sempRT::ObjectBase::~ObjectBase() {
}

bool sempRT::ObjectBase::TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localnormal, qbVector<double> &localColor, qbVector<double> &uvCoords) {
  return false;
}


bool sempRT::ObjectBase::CloseEnough(const double f1, const double f2) {
  return (fabs(f1 - f2) < EPSILON);
}


void sempRT::ObjectBase::SetTransformMatrix(const sempRT::Gtform &tfm) {
  m_transformMatrix = tfm;
}

bool sempRT::ObjectBase::AssignMaterial(const std::shared_ptr<MaterialBase> &material) {
  m_material = material;
  hasMaterial = true;
  return true;
}


void sempRT::ObjectBase::SetUVCoords(const qbVector<double>& coords) {
    uvCoords = coords;
}


