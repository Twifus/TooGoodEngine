#include "RigidBody.hpp"

namespace TooGoodEngine
{
    // Basic constructor
    RigidBody::RigidBody(double m)
    {
        double defaultDumping = 0.95;
        mass = m;
        inverseMass = (m == 0) ? 99999 : 1/m;
        linearDamping = defaultDumping;
        angularDamping = defaultDumping;
        orientation = Quaternion::identity;
    }


    // Setter useful for inheritence
    void RigidBody::SetInertiaTensorLocal(Matrix3 &inertiaTensor)
    {
        inertiaTensorLocal = inertiaTensor;
    }


    // Apply a force at center of mass
    void RigidBody::AddForce(const Vector3 &force)
    {
        AddForceAtBodyPoint(force, Vector3::zero);
    }


    // Apply a force at a point in world space
    void RigidBody::AddForceAtPoint(const Vector3 &force, const Vector3 &point)
    {
        Vector3 local_point = transformMatrix * point;
        AddForceAtBodyPoint(force, local_point);
    }


    // Apply a force at a point relative to center of mass
    void RigidBody::AddForceAtBodyPoint(const Vector3 &force, const Vector3 &point)
    {
        forceAcum += force;
        torqueAcum += point.Cross(force);
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
        Matrix3 m = Matrix3(orientation).Inverse();
        transformMatrix = Matrix4(m, -position);

        // World inertia tensor
        Matrix3 orientationMatrix(orientation);
        inverseInertiaTensor = orientationMatrix * inertiaTensorLocal * orientationMatrix.Inverse();

    }

    // Fonction appelée à chaque nouvelle itération du moteur
    void RigidBody::Update(double time)
    {
        // Compute linear acceleration
        acceleration = acceleration + forceAcum * inverseMass;

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

    Vector3 RigidBody::GetVelocity() const
    {
        return velocity;
    }
} // namespace TooGoodEngine
