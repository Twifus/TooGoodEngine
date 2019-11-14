#include "RigidBody.hpp"

namespace TooGoodEngine
{
    void RigidBody::UpdateTransformMatrix()
    {
        Matrix3 m = Matrix3(orientation).Inverse();
        transformMatrix = Matrix4(m, -position);
    }


    RigidBody::RigidBody()
    {

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
