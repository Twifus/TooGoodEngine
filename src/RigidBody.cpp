#include "RigidBody.hpp"

namespace TooGoodEngine
{
    RigidBody::RigidBody()
    {

    }

    void RigidBody::addForceAtPoint(Vector3 force, Vector3 point)
    {
        // this conversion of "point" is wrong because the body could be rotated
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
