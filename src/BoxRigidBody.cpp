#include "BoxRigidBody.hpp"

namespace TooGoodEngine
{
    BoxRigidBody::BoxRigidBody(double m, double dx, double dy, double dz)  : RigidBody(m)
    {
        double matrixData[9] = { m*(dy*dy + dz*dz) / 12, 0, 0,
                            0, m*(dx*dx + dz*dz) / 12, 0,
                            0, 0, m*(dx*dx + dy*dy) / 12};
        Matrix3 matrix = Matrix3(matrixData);
        SetInertiaTensorLocal(matrix);
        UpdateDerivedData();
    }
}