#ifndef SEMPIMAGE_H
#define SEMPIMAGE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class SempImage
{
  public:
    SempImage();

    ~SempImage();

    void Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer);

    void SetPixel(const int x, const int y, const double r, const double g, const double b);

    void Display(); 

    int GetXSize() const { return m_xSize; }
    int GetYSize() const { return m_ySize; }

  private:
    Uint32 ConvertColor(const double r, const double g, const double b, const double a);
    void InitTexture();

  private:
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    int m_xSize, m_ySize;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;

};

#endif // !
