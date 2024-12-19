#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <vector>
#include "sempImage.hpp"
#include "camera.hpp"
#include "objectsphere.hpp"
#include "pointlight.hpp"
#include "objplane.hpp"
#include <memory>


namespace sempRT{
  class Scene
  {
    public:
      Scene();
      ~Scene();

      bool Render(SempImage &outputImage);

    private:


    private:
      sempRT::Camera m_camera;
      std::vector<std::shared_ptr<ObjectBase>> m_objectList;
      std::vector<std::shared_ptr<LightBase>> m_lightList;
  };
}


#endif // !SCENE

