#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <vector>
#include "sempImage.hpp"


namespace sempRT{
  class Scene
  {
    public:
      Scene();
      ~Scene();

      bool Render(SempImage &outputImage);

    private:


    private:
  };
}


#endif // !SCENE

