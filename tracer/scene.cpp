#include "scene.hpp"


sempRT::Scene::Scene()
{

  m_camera.SetPosition(	qbVector<double>{std::vector<double> {0.0, -10.0, -2.0}} );
  m_camera.SetLookAt	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
  m_camera.SetUp			( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
  m_camera.SetHorzSize(0.25);
  m_camera.SetAspect(16.0 / 9.0);
  m_camera.UpdateCameraGeometry();

  // Construct a test sphere.
  m_objectList.push_back(std::make_shared<sempRT::ObjectSphere> (sempRT::ObjectSphere()));
  m_objectList.push_back(std::make_shared<sempRT::ObjectSphere> (sempRT::ObjectSphere()));
  m_objectList.push_back(std::make_shared<sempRT::ObjectSphere> (sempRT::ObjectSphere()));

  // Construct a test plane.
  m_objectList.push_back(std::make_shared<sempRT::ObjectPlane> (sempRT::ObjectPlane()));
  m_objectList.at(3) -> m_baseColor = qbVector<double>{std::vector<double> {0.5, 0.5, 0.5}};

  // Define a transform for the plane.
  sempRT::Gtform planeMatrix;
  planeMatrix.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});
  m_objectList.at(3) -> SetTransformMatrix(planeMatrix);

  // Modify the spheres.
  sempRT::Gtform testMatrix1, testMatrix2, testMatrix3;
  testMatrix1.SetTransform(	qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});

  testMatrix2.SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});

  testMatrix3.SetTransform(	qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
      qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

  m_objectList.at(0) -> SetTransformMatrix(testMatrix1);
  m_objectList.at(1) -> SetTransformMatrix(testMatrix2);
  m_objectList.at(2) -> SetTransformMatrix(testMatrix3);

  m_objectList.at(0) -> m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
  m_objectList.at(1) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
  m_objectList.at(2) -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.8, 0.0}};

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
      if(hitFlag) {
        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;
        bool lightHit = false;

        double intensity;
        qbVector<double> color {3};
        bool validIllum = false;
        for (auto currentLight : m_lightList) {
          validIllum = currentLight->ComputeIllumination(closestIntPoint, closestLocalNormal, m_objectList, closestObject, color, intensity);

          if(validIllum) {
            lightHit = true;
            red += color.GetElement(0) * intensity;
            green += color.GetElement(1) * intensity;
            blue += color.GetElement(2) * intensity;
          }
        }
        if(lightHit) {
          red*=closestLocalColor.GetElement(0);
          green*=closestLocalColor.GetElement(1);
          blue*=closestLocalColor.GetElement(2);
          outputImage.SetPixel(x, y, red, green, blue);
        }

      }

    }
  }

  return true;
}
