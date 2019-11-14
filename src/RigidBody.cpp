#include "RigidBody.hpp"

namespace TooGoodEngine
{

    void RigidBody::SetInertiaTensorLocal(Matrix3 &inertiaTensor)
    {
        inertiaTensorLocal = inertiaTensor;
    }

    void RigidBody::UpdateDerivedData()
    {
        // Transform Martix
        Matrix3 m = Matrix3(orientation).Inverse();
        transformMatrix = Matrix4(m, -position);

        // World inertia tensor
        Matrix3 orientationMatrix(orientation);
        inverseInertiaTensor = orientationMatrix * inertiaTensorLocal * orientationMatrix.Inverse();

    }


    RigidBody::RigidBody()
    {

    }

    RigidBody::RigidBody(double masse)
    {
        double defaultDumping = 0.95;
        inverseMass = (masse == 0) ? 99999 : 1/masse;
        linearDumping = defaultDumping;
        angularDumping = defaultDumping;
    }

    void RigidBody::addForceAtPoint(Vector3 force, Vector3 point)
    {
        // not sure about conversion
        Vector3 local_point = transformMatrix * point;
        addForceAtBodyPoint(force, point - massCenter);
    }

    void RigidBody::addForceAtBodyPoint(Vector3 force, Vector3 point)
    {
        forceAcum += force;
        torqueAcum += point.Cross(force);
    }

    void RigidBody::Update(double time)
    {
        // Compute linear acceleration

        // Compute angular acceleration

        // Update linear velocity

        // Update angular velocity

        // 
    }
} // namespace TooGoodEngine
