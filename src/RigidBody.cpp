#include "RigidBody.hpp"

// -------------------------------------------------
#include <iostream>

void displayMatrix3(const TooGoodEngine::Matrix3 &m)
{
    for (int i=0; i < 9; i++)
        std::cout << m[i] << " ";
    std::cout << std::endl;
}

// -------------------------------------------------

namespace TooGoodEngine
{
    static constexpr double defaultDamping = 0.95;

    // Basic constructor
    RigidBody::RigidBody(double m, const Vector3 &pos, const Quaternion &ori) :
        mass(m), position(pos), orientation(ori),
        linearDamping(defaultDamping), angularDamping(defaultDamping)
    {
        inverseMass = (m == 0) ? 99999 : 1/m;
        UpdateDerivedData();
    }


    // Setter useful for inheritence
    void RigidBody::SetInertiaTensorLocal(Matrix3 &inertiaTensor)
    {
        inertiaTensorLocal = inertiaTensor;
    }


    // Apply a force at center of mass
    void RigidBody::AddForce(const Vector3 &force)
    {
        AddForceAtPoint(force, position);
    }


    // Apply a force at a point in world space
    void RigidBody::AddForceAtPoint(const Vector3 &force, const Vector3 &point)
    {
        forceAcum += force;
        Vector3 relative_point = point - position;
        torqueAcum += relative_point.Cross(force); 
    }


    // Apply a force at a point relative to center of mass
    void RigidBody::AddForceAtBodyPoint(const Vector3 &force, const Vector3 &point)
    {
        AddForceAtPoint(force, BodyToWorld(point));
    }


    // Conversion for a point position in world<->body 
    Vector3 RigidBody::WorldToBody(const Vector3 &v) const
    {
        return transformMatrix.Inverse() * v;
    }

    Vector3 RigidBody::BodyToWorld(const Vector3 &v) const
    {
        return transformMatrix * v;
    }


    // Vide les accumulateur
    void RigidBody::ClearAccumulation()
    {
        forceAcum = Vector3::zero;
        torqueAcum = Vector3::zero;
    }


    // Update 
    void RigidBody::UpdateDerivedData()
    {
        orientation = orientation.Normalized();

        // Transform Martix
        transformMatrix = Matrix4(orientation, position);

        // World inertia tensor
        Matrix3 orientationMatrix(orientation);
        inverseInertiaTensor = orientationMatrix * inertiaTensorLocal.Inverse() * orientationMatrix.Inverse();

        // -------------------------------------------------
        // std::cout << "torqueAccum : " << torqueAcum << std::endl;
        // std::cout << "orientation : " << orientation << std::endl;
        // std::cout << "position : " << position << std::endl;
        // std::cout << "inertiaTensorLocal :";
        // displayMatrix3(inertiaTensorLocal);
        // std::cout << "inverseIntertiaTensor  ";
        // displayMatrix3(inverseInertiaTensor);
        // std::cout << std::endl;
        // -------------------------------------------------
    }


    // Called at every iteration of the engine
    void RigidBody::Update(double time)
    {
        // Compute linear acceleration
        acceleration = forceAcum * inverseMass;

        // Compute angular acceleration
        angularAccel = inverseInertiaTensor * torqueAcum;

        // Update velocities
        velocity += acceleration * time;
        rotation += angularAccel * time;
     
        // Apply Dampings
        velocity *= pow(linearDamping, time);
        rotation *= pow(angularDamping, time);

        // Update positions
        position += velocity * time;
        orientation += Quaternion(rotation) * orientation * (time * 0.5);

        UpdateDerivedData();
        ClearAccumulation();

    }


    double RigidBody::GetMass() const
    {
        return mass;
    }


    const Vector3 RigidBody::GetVelocity() const
    {
        return velocity;
    }

    const Vector3 RigidBody::GetRotation() const
    {
        return rotation;
    }

} // namespace TooGoodEngine
