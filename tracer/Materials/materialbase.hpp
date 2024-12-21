#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include "../qbLinAlg/qbVector.h"
#include <memory>
#include "../Primitives/objectbase.hpp"
#include "../Lights/lightbase.hpp"
#include "../ray.hpp"
#include "../Textures/texturebase.hpp"


namespace sempRT {

  class MaterialBase {
    public:
      MaterialBase();
      virtual ~MaterialBase();

      virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords);

      static qbVector<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const qbVector<double> &baseColor, qbVector<double> &uvCoords);

      bool CastRay(const Ray &ray, const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::shared_ptr<ObjectBase> &thisObject  , std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor, qbVector<double> &uvCoords);

      virtual qbVector<double> ComputeReflectionColor( const std::vector<std::shared_ptr<ObjectBase>> &objectList, const std::vector<std::shared_ptr<LightBase>> &lightList, const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint, const qbVector<double> &localNormal, const sempRT::Ray &ray, qbVector<double> &uvCoords);


      
      void AssignTexture(const std::shared_ptr<sempRT::TextureBase> &texture);



    public: 
      int m_maxReflectionRays;
      int m_reflectionDepth;
      std::vector<std::shared_ptr<sempRT::TextureBase>> m_textures;

      bool m_hasTexture = false;

  };
}

#endif // !MATERIALBASE_H

