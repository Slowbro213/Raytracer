#ifndef CHECKER_HPP
#define CHECKER_HPP


#include "texturebase.hpp"

namespace sempRT
{
    class Checker : public TextureBase
    {
    public:
        Checker();
        virtual ~Checker();

        qbVector<double> GetColor(const qbVector<double> &uvCoords) override;
        void SetColor1(const qbVector<double> &color);
        void SetColor2(const qbVector<double> &color);

    private:
        qbVector<double> m_color1{4} ;
        qbVector<double> m_color2{4};
    };
}

#endif // !
