#include "sempImage.hpp"

SempImage::SempImage()
{
  m_xSize = 0;
  m_ySize = 0;
  m_pTexture = NULL;
}


SempImage::~SempImage()
{
  if(m_pTexture != NULL)
  {
    SDL_DestroyTexture(m_pTexture);
  }
}


void SempImage::Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer)
{
  m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
  m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
  m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

  m_xSize = xSize;
  m_ySize = ySize;
  m_pRenderer = pRenderer;

  InitTexture();
}


void SempImage::SetPixel(const int x, const int y, const double r, const double g, const double b)
{
  m_rChannel.at(x).at(y) = r;
  m_gChannel.at(x).at(y) = g;
  m_bChannel.at(x).at(y) = b;
}


void SempImage::Display()
{
  Uint32* tempPixels = new Uint32[m_xSize * m_ySize];

  memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

  for(int y = 0; y < m_ySize; y++)
  {
    for(int x = 0; x < m_xSize; x++)
    {
      tempPixels[y * m_xSize + x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y), 1.0);
    }
  }

  SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));

  delete[] tempPixels;

  SDL_Rect srcRect,bounds;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = m_xSize;
  srcRect.h = m_ySize;
  bounds = srcRect;

  SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}


void SempImage::InitTexture()
{
  Uint32 rmask, gmask, bmask, amask;

  #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
  #else 
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
  
  #endif

  if(m_pTexture != NULL)
  {
    SDL_DestroyTexture(m_pTexture);
  }

  SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
  m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);

  SDL_FreeSurface(tempSurface);

}



Uint32 SempImage::ConvertColor(const double r, const double g, const double b, const double a)
{
  unsigned char red = static_cast<unsigned char>(r);
  unsigned char green = static_cast<unsigned char>(g);
  unsigned char blue = static_cast<unsigned char>(b);


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  Uint32 color = (red << 24) + (green << 16) + (blue << 8) + 255;
#else 
  Uint32 color = (255 << 24) + (red << 16) + (green << 8) + blue;
#endif
return color;
}


