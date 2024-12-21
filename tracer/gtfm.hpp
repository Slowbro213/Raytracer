#ifndef GTFM_H
#define GTFM_H


#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"
#include "ray.hpp"


namespace sempRT {
  constexpr bool FWDTFORM = true;
  constexpr bool BCKTFORM = false;

  class Gtform {
  public:
    Gtform();
    ~Gtform();

    Gtform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
    Gtform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale);


    void SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale);
    qbMatrix2<double> GetForward();
    qbMatrix2<double> GetBackward();



    sempRT::Ray Apply(const sempRT::Ray &inputRay, bool dirFlag);
    qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);

    friend Gtform operator*(const Gtform &lhs, const Gtform &rhs);


    Gtform& operator= (const Gtform &rhs);
    void PrintMatrix(bool dirFlag);


    static void PrintVector(const qbVector<double> &vector);

  private:
    void Print(const qbMatrix2<double> &matrix);

  private:
    qbMatrix2<double> m_fwdtfm {4,4};
    qbMatrix2<double> m_bcktfm {4,4};
  };
}

#endif // 
