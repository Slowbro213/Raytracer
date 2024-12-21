#include "gtfm.hpp"


sempRT::Gtform::Gtform()
{
  m_fwdtfm.SetToIdentity(); 
  m_bcktfm.SetToIdentity();
}


sempRT::Gtform::~Gtform()
{
}

sempRT::Gtform::Gtform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
  if( fwd.GetNumRows() != 4 || fwd.GetNumCols() != 4 || bck.GetNumRows() != 4 || bck.GetNumCols() != 4) {
    throw std::invalid_argument("Invalid matrix size for Gtform");
  }


  m_fwdtfm = fwd;
  m_bcktfm = bck;


}


void sempRT::Gtform::SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale)
{
  qbMatrix2<double> transMat {4,4};
  qbMatrix2<double> rotMatX {4,4};
  qbMatrix2<double> rotMatY {4,4};
  qbMatrix2<double> rotMatZ {4,4};
  qbMatrix2<double> scaleMat {4,4};


  transMat.SetToIdentity();
  rotMatX.SetToIdentity();
  rotMatY.SetToIdentity();
  rotMatZ.SetToIdentity();
  scaleMat.SetToIdentity();

  // Set up translation matrix
  transMat.SetElement(0, 3, translation.GetElement(0));
  transMat.SetElement(1, 3, translation.GetElement(1));
  transMat.SetElement(2, 3, translation.GetElement(2));

  rotMatZ.SetElement(0, 0, cos(rotation.GetElement(2)));
  rotMatZ.SetElement(0, 1, sin(rotation.GetElement(2)));
  rotMatZ.SetElement(1, 0, -sin(rotation.GetElement(2)));
  rotMatZ.SetElement(1, 1, cos(rotation.GetElement(2)));

  rotMatX.SetElement(1, 1, cos(rotation.GetElement(0)));
  rotMatX.SetElement(1, 2, sin(rotation.GetElement(0)));
  rotMatX.SetElement(2, 1, -sin(rotation.GetElement(0)));
  rotMatX.SetElement(2, 2, cos(rotation.GetElement(0)));

  rotMatY.SetElement(0, 0, cos(rotation.GetElement(1)));
  rotMatY.SetElement(0, 2, -sin(rotation.GetElement(1)));
  rotMatY.SetElement(2, 0, sin(rotation.GetElement(1)));
  rotMatY.SetElement(2, 2, cos(rotation.GetElement(1)));

  scaleMat.SetElement(0, 0, scale.GetElement(0));
  scaleMat.SetElement(1, 1, scale.GetElement(1));
  scaleMat.SetElement(2, 2, scale.GetElement(2));
  

  m_fwdtfm = transMat * rotMatX * rotMatY * rotMatZ * scaleMat;

  m_bcktfm = m_fwdtfm;
  m_bcktfm.Inverse();



}


qbMatrix2<double> sempRT::Gtform::GetForward()
{
  return m_fwdtfm;
}


qbMatrix2<double> sempRT::Gtform::GetBackward()
{
  return m_bcktfm;
}


sempRT::Ray sempRT::Gtform::Apply(const sempRT::Ray &inputRay, bool dirFlag)
{
  sempRT::Ray outputRay;

  if(dirFlag == FWDTFORM) {
    outputRay.m_point1 = this -> Apply(inputRay.m_point1, sempRT::BCKTFORM);
    outputRay.m_point2 = this -> Apply(inputRay.m_point2, sempRT::BCKTFORM);
    outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;

  }else {
    outputRay.m_point1 = this -> Apply(inputRay.m_point1, sempRT::BCKTFORM);
    outputRay.m_point2 = this -> Apply(inputRay.m_point2, sempRT::BCKTFORM);
    outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
  }

  return outputRay;
}


qbVector<double> sempRT::Gtform::Apply(const qbVector<double> &inputVector, bool dirFlag)
{
    // Extend the input vector to homogeneous coordinates
    std::vector<double> tempData = {
        inputVector.GetElement(0),
        inputVector.GetElement(1),
        inputVector.GetElement(2),
        1.0 // Homogeneous coordinate
    };

    qbVector<double> tempVec {tempData};
    qbVector<double> outputVec {4};

    // Apply the appropriate transformation
    if (dirFlag) {
        outputVec = m_fwdtfm * tempVec;
    } else {
        outputVec = m_bcktfm * tempVec;
    }

    // Return the transformed vector in 3D (ignore the homogeneous coordinate)
    return qbVector<double>{std::vector<double>{
        outputVec.GetElement(0),
        outputVec.GetElement(1),
        outputVec.GetElement(2)
    }};
}

namespace sempRT {


  sempRT::Gtform operator*(const sempRT::Gtform &lhs, const sempRT::Gtform &rhs)
  {
    qbMatrix2<double> fwd = lhs.m_fwdtfm * rhs.m_fwdtfm;
    qbMatrix2<double> bck = fwd;
    bck.Inverse();



    return sempRT::Gtform(fwd, bck);
  }
  
}

sempRT::Gtform& sempRT::Gtform::operator= (const sempRT::Gtform &rhs)
{
  if(this == &rhs) {
    return *this;
  }
  m_fwdtfm = rhs.m_fwdtfm;
  m_bcktfm = rhs.m_bcktfm;

  return *this;
}

void sempRT::Gtform::PrintMatrix(bool dirFlag)
{
  if(dirFlag) {
    Print(m_fwdtfm);
  }else {
    Print(m_bcktfm);
  }
}

void sempRT::Gtform::Print(const qbMatrix2<double> &matrix)
{
  int nRows = matrix.GetNumRows();
  int nCols = matrix.GetNumCols();

  for (int i = 0; i < nRows; i++)
  {
    for (int j = 0; j < nCols; j++)
    {
      std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

void sempRT::Gtform::PrintVector(const qbVector<double> &vector)
{
  int nRows = vector.GetNumDims();

  for (int i = 0; i < nRows; i++)
  {
    std::cout << std::fixed << std::setprecision(2) << vector.GetElement(i) << std::endl;
  }
}





