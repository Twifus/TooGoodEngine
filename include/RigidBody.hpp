#pragma once

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"

#include <ostream>

namespace TooGoodEngine
{
	class RigidBody
	{
    private:
        double mass;
        double inverseMass;
		double linearDamping;
        double angularDamping;

		Vector3 velocity;
        Vector3 rotation;

		Vector3 acceleration;
        Vector3 angularAccel;

        Matrix4 transformMatrix;

        Matrix3 inertiaTensorLocal;
        Matrix3 inverseInertiaTensor;

        Vector3 forceAcum;
        Vector3 torqueAcum;

        Vector3 massCenter;
		// Vector3 resultantForce;

    protected:
       void SetInertiaTensorLocal(Matrix3 &inertiaTensor);

    public:
        // public attributes
        Vector3 position;
        Quaternion orientation;

        // Constructor
        RigidBody(double m, const Vector3 &pos = Vector3::zero, const Quaternion &ori = Quaternion::identity);

        void UpdateDerivedData(); 

        void AddForce(const Vector3 &force);
        // Apply F on a precise (world) point of the object
        void AddForceAtPoint(const Vector3 &force, const Vector3 &point);
        // Apply F on a precise (object) point of the object
        void AddForceAtBodyPoint(const Vector3 &force, const Vector3 &point);

        void ClearAccumulation();

        void Update(double time);

        double GetMass() const;

        const Vector3 GetVelocity() const;
        const Vector3 GetRotation() const;

        Vector3 BodyToWorld(const Vector3 &v) const;
        Vector3 WorldToBody(const Vector3 &v) const;

    };
}