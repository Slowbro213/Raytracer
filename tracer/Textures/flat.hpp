#ifndef FLAT_H
#define FLAT_H
#include "texturebase.hpp"


namespace sempRT
{
    class Flat : public TextureBase
    {
    public:
        Flat();
        virtual ~Flat();

        qbVector<double> GetColor(const qbVector<double> &uvCoords) override;
        void SetColor(const qbVector<double> &color);


    private:
        qbVector<double> m_color{4};
    };
}


#endif // !FLAT_H

