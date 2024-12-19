#include "CApp.h"
#include "tracer/qbLinAlg/qbVector.h"

CApp::CApp()
{
  isRunning = true;
  pWindow = NULL;
  pRenderer = NULL;
}

bool CApp::OnInit()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    return false;
  }

  pWindow = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
  if (pWindow == NULL)
  {
    return false;
  }

  pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
  if (pRenderer == NULL)
  {
    return false;
  }

  m_image.Initialize(1280, 720, pRenderer);


  SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
  SDL_RenderClear(pRenderer);

  m_scene.Render(m_image);

  m_image.Display();

  SDL_RenderPresent(pRenderer);



  return true;
}

int CApp::OnExecute()
{
  SDL_Event Event;

  if (OnInit() == false)
  {
    return -1;
  }

  while (isRunning)
  {
    while (SDL_PollEvent(&Event))
    {
      OnEvent(&Event);
    }

    OnLoop();
    OnRender();
  }

  OnExit();  // Ensure we call OnExit before returning
  return 0;
}

void CApp::OnEvent(SDL_Event* Event)
{
  if (Event->type == SDL_QUIT)
  {
    isRunning = false;
  }
}

void CApp::OnLoop()
{
  // Game/Rendering Logic can go here
}

void CApp::OnRender()
{
  //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
  //SDL_RenderClear(pRenderer);

  //m_scene.Render(m_image);
  //m_image.Display();
  //SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
  // Clean up resources properly
  if (pRenderer != NULL)
  {
    SDL_DestroyRenderer(pRenderer);
    pRenderer = NULL;
  }

  if (pWindow != NULL)
  {
    SDL_DestroyWindow(pWindow);
    pWindow = NULL;
  }

  SDL_Quit();  // Quit SDL subsystems
}


void CApp::PrintVector(const qbVector<double> &vec)
{
  int nRows = vec.GetNumDims();

  for (int i = 0; i < nRows; i++)
  {
    std::cout << std::fixed << std::setprecision(2) << vec.GetElement(i) << std::endl;
  }
}
