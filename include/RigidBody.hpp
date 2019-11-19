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
        double inverseMass;
		double linearDamping;
        double angularDamping;

        Vector3 position;
        Quaternion orientation;

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
        RigidBody(double m);

        void UpdateDerivedData(); 

        void addForce(const Vector3 &force);
        // Apply F on a precise (world) point of the object
        void addForceAtPoint(const Vector3 &force, const Vector3 &point);
        // Apply F on a precise (object) point of the object
        void addForceAtBodyPoint(const Vector3 &force, const Vector3 &point);

        void ClearAccumulation();

        void Update(double time);
    };
}