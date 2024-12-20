#include "scene.hpp"
#include "./Materials/simplematerial.hpp"


sempRT::Scene::Scene()
{


  auto mattest = std::make_shared<sempRT::SimpleMaterial> (sempRT::SimpleMaterial());


  mattest -> m_baseColor = qbVector<double>{std::vector<double> {1,0.0,0.0}};
  mattest -> m_reflectivity = 0.5;
  mattest -> m_shine = 10;

  m_camera.SetPosition(	qbVector<double>{std::vector<double> {0.0, -10.0, -4.0}} );
  m_camera.SetLookAt	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
  m_camera.SetUp			( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
  m_camera.SetHorzSize(0.25);
  m_camera.SetAspect(16.0 / 9.0);
  m_camera.UpdateCameraGeometry();

  m_objectList.push_back(std::make_shared<sempRT::ObjectSphere> (sempRT::ObjectSphere()));
  m_objectList.push_back(std::make_shared<sempRT::ObjectSphere> (sempRT::ObjectSphere()));
  m_objectList.push_back(std::make_shared<sempRT::ObjectSphere> (sempRT::ObjectSphere()));

  m_objectList.push_back(std::make_shared<sempRT::ObjectPlane> (sempRT::ObjectPlane()));
  m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};


  auto mattest2 = std::make_shared<sempRT::SimpleMaterial> (sempRT::SimpleMaterial());

  mattest2 -> m_baseColor = qbVector<double>{std::vector<double> {0.5,0.5,0.5}};
  mattest2 -> m_reflectivity = 0.5;
  mattest2 -> m_shine = 10;
  m_objectList.at(3)->AssignMaterial(mattest2);

  sempRT::Gtform planeMatrix;
  planeMatrix.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});
  m_objectList.at(3) -> SetTransformMatrix(planeMatrix);

  sempRT::Gtform testMatrix1, testMatrix2, testMatrix3;
  testMatrix1.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

  testMatrix2.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

  testMatrix3.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

  m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
  m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
  m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

  m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
  m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
  m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.8, 0.0}};

  m_objectList.at(2) -> AssignMaterial(mattest);

  // Construct a test light.
  m_lightList.push_back(std::make_shared<sempRT::PointLight> (sempRT::PointLight()));
  m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {5.0, -10.0, -5.0}};
  m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};

  m_lightList.push_back(std::make_shared<sempRT::PointLight> (sempRT::PointLight()));
  m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {-5.0, -10.0, -5.0}};
  m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};

  m_lightList.push_back(std::make_shared<sempRT::PointLight> (sempRT::PointLight()));
  m_lightList.at(2) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
  m_lightList.at(2) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};}

sempRT::Scene::~Scene()
{


}


bool sempRT::Scene::Render(SempImage &outputImage)
{
  int xSize = outputImage.GetXSize();
  int ySize = outputImage.GetYSize();

  sempRT::Ray cameraRay;
  qbVector<double> intPoint {3};
  qbVector<double> localNormal {3};
  qbVector<double> localColor {3};


  for (int y = 0; y < ySize; y++) {

    std::cout<<"Rendering row: "<<y<< " out of " <<ySize <<std::endl;

    for (int x = 0; x < xSize; x++) {
      // Normalize coordinates and adjust for aspect ratio
      double normX = (static_cast<double>(x) / static_cast<double>(xSize)) * 2.0 - 1.0;
      double normY = (static_cast<double>(y) / static_cast<double>(ySize)) * 2.0 - 1.0;

      // Generate the ray
      m_camera.GenerateRay(normX, normY, cameraRay);

      std::shared_ptr<sempRT::ObjectBase> closestObject = nullptr;

      qbVector<double> closestIntPoint {3};
      qbVector<double> closestLocalNormal {3};
      qbVector<double> closestLocalColor {3};
      bool hitFlag = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);


      if(hitFlag){
        if(closestObject->hasMaterial)
        {
          sempRT::MaterialBase::m_reflectionDepth = 0;
          qbVector<double> color = closestObject->m_material->ComputeColor(m_objectList, m_lightList, closestObject, closestIntPoint, closestLocalNormal, cameraRay);
          outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));

        }else{

          qbVector<double> matColor = sempRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList, closestObject, closestIntPoint, closestLocalNormal, closestObject->m_baseColor);
          outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
        }
      }

    }
  }

  return true;
}


bool sempRT::Scene::CastRay(const Ray &cameraRay, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor)
{

  qbVector<double> intPoint {3};
  qbVector<double> localNormal {3};
  qbVector<double> localColor {3};

  double minDist = 1e6;
  bool hitFlag = false;

  for (auto currentObject : m_objectList) {

    bool validInt = currentObject -> TestIntersections(cameraRay, intPoint, localNormal, localColor);

    if (validInt)
    {
      hitFlag = true;

      double dist = (intPoint - cameraRay.m_point1).norm();

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
