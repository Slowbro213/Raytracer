#include "scene.hpp"
#include "./Materials/simplematerial.hpp"
#include "./Textures/checker.hpp"
#include "./Textures/image.hpp"
#include <thread>


sempRT::Scene::Scene() {
    // Create materials
    auto mattest = std::make_shared<sempRT::SimpleMaterial>();
    mattest->m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}};
    mattest->m_reflectivity = 0.5;
    mattest->m_shine = 10;

    // Configure camera
    m_camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, -4.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    m_camera.SetHorzSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // Add objects to the scene
    m_objectList.push_back(std::make_shared<sempRT::Cylinder>());
    m_objectList.push_back(std::make_shared<sempRT::ObjectSphere>());
    m_objectList.push_back(std::make_shared<sempRT::ObjectSphere>());
    m_objectList.push_back(std::make_shared<sempRT::ObjectPlane>());
    // Configure plane material
    auto mattest2 = std::make_shared<sempRT::SimpleMaterial>();
    mattest2->m_baseColor = qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}};
    mattest2->m_reflectivity = 0.5;
    mattest2->m_shine = 10;

    // Add texture to plane material
    sempRT::Checker checker;
    checker.SetTransformMatrix(
        qbVector<double>{std::vector<double>{0.0, 0.0}}, 
        0.0, 
        qbVector<double>{std::vector<double>{16.0, 16.0}}
    );
    mattest2->AssignTexture(std::make_shared<sempRT::Checker>(checker));

    // Assign material and transformation to plane
    m_objectList.at(3)->AssignMaterial(mattest2);
    sempRT::Gtform planeMatrix;
    planeMatrix.SetTransform(
        qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}}, 
        qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
        qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}}
    );
    m_objectList.at(3)->SetTransformMatrix(planeMatrix);

    // Create and configure additional materials
    auto mattest3 = std::make_shared<sempRT::SimpleMaterial>();
    mattest3->m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.5, 0.5}};
    mattest3->m_reflectivity = 0.8;
    mattest3->m_shine = 5;

    auto mattest4 = std::make_shared<sempRT::SimpleMaterial>();
    mattest4->m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.0, 0.4}};
    mattest4->m_reflectivity = 0.2;
    mattest4->m_shine = 2;

    auto planeMaterial1 = std::make_shared<sempRT::SimpleMaterial>();
    planeMaterial1->m_baseColor = qbVector<double>{std::vector<double>{0.0, 0.0, 1}};
    planeMaterial1->m_reflectivity = 0.5;
    planeMaterial1->m_shine = 0;

    auto planeMaterial2 = std::make_shared<sempRT::SimpleMaterial>();
    planeMaterial2->m_baseColor = qbVector<double>{std::vector<double>{1, 0.0, 0.0}};
    planeMaterial2->m_reflectivity = 0.5;
    planeMaterial2->m_shine = 0;

    auto planeMaterial3 = std::make_shared<sempRT::SimpleMaterial>();
    planeMaterial3->m_baseColor = qbVector<double>{std::vector<double>{0.0, 1.0, 0.0}};
    planeMaterial3->m_reflectivity = 0.5;
    planeMaterial3->m_shine = 0;

    // Configure object transformations
    sempRT::Gtform testMatrix1, testMatrix2, testMatrix3, PlaneMatrix1, PlaneMatrix2, PlaneMatrix3;
    testMatrix1.SetTransform(
        qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}}, 
        qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
        qbVector<double>{std::vector<double>{0.4, 0.4, 0.6}}
    );
    testMatrix2.SetTransform(
        qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
        qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
        qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}}
    );
    testMatrix3.SetTransform(
        qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}}, 
        qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
        qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}}
    );
    PlaneMatrix1.SetTransform(
        qbVector<double>{std::vector<double>{3.5, 0.0, 1.0}}, 
        qbVector<double>{std::vector<double>{0.0, 1.6, 0.0}}, 
        qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}}
    );
    PlaneMatrix2.SetTransform(
        qbVector<double>{std::vector<double>{-3, 0.0, 1.0}}, 
        qbVector<double>{std::vector<double>{0.0, 1.8, 0.0}}, 
        qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}}
    );

    PlaneMatrix3.SetTransform(
        qbVector<double>{std::vector<double>{0.0, 1, 0.0}}, 
        qbVector<double>{std::vector<double>{1, 0.1, 0.0}}, 
        qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}}
    );


    // Assign transformations and materials to objects
    m_objectList.at(0)->SetTransformMatrix(testMatrix1);
    m_objectList.at(0)->m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.0, 1.0}};
    m_objectList.at(0)->AssignMaterial(mattest4);

    m_objectList.at(1)->SetTransformMatrix(testMatrix2);
    m_objectList.at(1)->m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
    m_objectList.at(1)->AssignMaterial(mattest3);

    m_objectList.at(2)->SetTransformMatrix(testMatrix3);
    m_objectList.at(2)->m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.8, 0.0}};
    m_objectList.at(2)->AssignMaterial(mattest);


    // Add light to the scene
    m_lightList.push_back(std::make_shared<sempRT::PointLight>());
    m_lightList.at(0)->m_location = qbVector<double>{std::vector<double>{5.0, -10.0, -5.0}};
    m_lightList.at(0)->m_color = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};

    m_lightList.push_back(std::make_shared<sempRT::PointLight>());
    m_lightList.at(1)->m_location = qbVector<double>{std::vector<double>{-5.0, -10.0, -5.0}};
    m_lightList.at(1)->m_color = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};

}

sempRT::Scene::~Scene()
{


}




bool sempRT::Scene::Render(SempImage &outputImage) {
    double time = SDL_GetTicks();
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();
    
    const int threshold = 256; 

    RenderRecursive(outputImage, 0, 0, xSize, ySize, threshold);

    std::cout << "Rendering complete." << std::endl;
    std::cout << "Time taken: " << (SDL_GetTicks() - time) / 1000 << "s" << std::endl;

    return true;
}

void sempRT::Scene::RenderRecursive(SempImage &outputImage, int xStart, int yStart, int xEnd, int yEnd, int threshold) {
    int width = xEnd - xStart;
    int height = yEnd - yStart;

    if (width <= threshold || height <= threshold) {
        for (int y = yStart; y < yEnd; ++y) {
            for (int x = xStart; x < xEnd; ++x) {
                // Normalize coordinates and adjust for aspect ratio
                double normX = (static_cast<double>(x) / static_cast<double>(outputImage.GetXSize())) * 2.0 - 1.0;
                double normY = (static_cast<double>(y) / static_cast<double>(outputImage.GetYSize())) * 2.0 - 1.0;

                sempRT::Ray cameraRay;
                m_camera.GenerateRay(normX, normY, cameraRay);

                qbVector<double> closestIntPoint{3}, closestLocalNormal{3}, closestLocalColor{3};
                std::shared_ptr<sempRT::ObjectBase> closestObject = nullptr;

                qbVector<double> uvCoords{2};
                bool hitFlag = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor, uvCoords);

                qbVector<double> pixelColor{3};
                if (hitFlag) {
                    if (closestObject->hasMaterial) {
                        
                        pixelColor = closestObject->m_material->ComputeColor(
                            m_objectList, m_lightList, closestObject,
                            closestIntPoint, closestLocalNormal, cameraRay, uvCoords
                        );
                    } else {
                        pixelColor = sempRT::MaterialBase::ComputeDiffuseColor(
                            m_objectList, m_lightList, closestObject,
                            closestIntPoint, closestLocalNormal, closestObject->m_baseColor, uvCoords
                        );
                    }
                }

                outputImage.SetPixel(x, y, pixelColor.GetElement(0), pixelColor.GetElement(1), pixelColor.GetElement(2));
            }
        }
        return;
    }

    int midX = (xStart + xEnd) / 2;
    int midY = (yStart + yEnd) / 2;

    std::vector<std::thread> threads;

    threads.emplace_back([this, &outputImage, xStart, yStart, midX, midY, threshold]() {
        RenderRecursive(outputImage, xStart, yStart, midX, midY, threshold);
    });

    threads.emplace_back([this, &outputImage, midX, yStart, xEnd, midY, threshold]() {
        RenderRecursive(outputImage, midX, yStart, xEnd, midY, threshold);
    });

    threads.emplace_back([this, &outputImage, xStart, midY, midX, yEnd, threshold]() {
        RenderRecursive(outputImage, xStart, midY, midX, yEnd, threshold);
    });

    threads.emplace_back([this, &outputImage, midX, midY, xEnd, yEnd, threshold]() {
        RenderRecursive(outputImage, midX, midY, xEnd, yEnd, threshold);

    });

    for (auto &t : threads) {
        t.join();
    }
}

bool sempRT::Scene::CastRay(const Ray &cameraRay, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor, qbVector<double> &uvCoords)
{

  qbVector<double> intPoint {3};
  qbVector<double> localNormal {3};
  qbVector<double> localColor {3};

  double minDist = 1e6;
  bool hitFlag = false;

  for (auto currentObject : m_objectList) {

    bool validInt = currentObject -> TestIntersections(cameraRay, intPoint, localNormal, localColor, uvCoords);

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
