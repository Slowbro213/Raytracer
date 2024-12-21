#ifndef CONE_H
#define CONE_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace sempRT
{
	class Cone : public ObjectBase
	{
		public:
			// Default constructor.
			Cone();
			
			// Override the destructor.
			virtual ~Cone() override;
			
			// Override the function to test for intersections.
			virtual bool TestIntersections(	const sempRT::Ray &castRay, qbVector<double> &intPoint,
																			qbVector<double> &localNormal, qbVector<double> &localColor, qbVector<double> &uvCoords) override;			
	};
}

#endif
