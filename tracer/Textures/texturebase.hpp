#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <memory>
#include "../qbLinAlg/qbMatrix.h"
#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"

namespace sempRT
{
   class TextureBase
		{
			public:
				TextureBase();
				virtual ~TextureBase();
				
				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords);

				void SetTransformMatrix(const qbVector<double> &translation, const double &rotation, const qbVector<double> &scale);

				
				static qbVector<double> BlendColors(const std::vector<qbVector<double>> &inputColorList);
				
				qbVector<double> ApplyTransform(const qbVector<double> &inputVector);
				
			private:
			
			private:
				qbMatrix2<double> m_transformMatrix {3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
				
		};}

#endif // TEXTUREBASE_H
