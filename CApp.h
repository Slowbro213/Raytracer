#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "tracer/sempImage.hpp"
#include "tracer/scene.hpp"
#include "tracer/camera.hpp"



class CApp
{
  public:
    CApp();
    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnExit();

  private:
    void PrintVector(const qbVector<double> &vec);

  private:
    SempImage m_image;
    sempRT::Scene m_scene;
    //SDL2 stuff
    bool isRunning;
    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
};

#endif // !CAPP_H

