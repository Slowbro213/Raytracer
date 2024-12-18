#ifndef CAMERA_H
#define CAMERA_H

#include "./qbLinAlg/qbVector.h"
#include "ray.hpp"


namespace sempRT {
  class Camera {
    public:
      Camera();

      void SetPosition(const qbVector<double> &newPosition);
      void SetLookAt(const qbVector<double> &newLookAt);
      void SetUp(const qbVector<double> &newUp);
      void SetLength(const double newLength);
      void SetHorzSize(const double newHorzSize);
      void SetAspect (const double newAspect);

      qbVector<double> GetPosition() const;
      qbVector<double> GetLookAt() const;
      qbVector<double> GetUp() const;
      qbVector<double> GetU() const;
      qbVector<double> GetV() const;
      qbVector<double> GetScreenCenter() const;

      double GetLength() const;
      double GetHorzSize() const;
      double GetAspect() const;

      Ray GenerateRay(float proScreenX, float proScreenY) ;

      void UpdateCameraGeometry();


    private:

      qbVector<double> m_cameraPosition;
      qbVector<double> m_cameraLookAt;
      qbVector<double> m_cameraUp;

      double m_cameraLength;
      double m_cameraHorzSie;
      double m_cameraAspectRatio;

      qbVector<double> m_alignmentVector {3};
      qbVector<double> m_projectionScreenU {3};
      qbVector<double> m_projectionScreenV {3};
      qbVector<double> m_projectionScreenCenter {3};

  };
}

#endif // !CAMERA
