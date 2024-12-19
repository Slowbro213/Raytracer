#ifndef OBJECTSPHERE_H
#define OBJECTSPHERE_H

#include "objectbase.hpp"
#include "gtfm.hpp"

namespace sempRT {
  class ObjectSphere : public ObjectBase {
  public:
    ObjectSphere();
    virtual ~ObjectSphere() override;

    virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localnormal, qbVector<double> &localColor) override;


  private:

  };
}
#endif // !OBJECTSPHERE_H

