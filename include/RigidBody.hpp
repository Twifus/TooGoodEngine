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
		double linearDumping;
        double angularDumping;

        Vector3 position;
        Quaternion orientation;

		Vector3 velocity;
        Vector3 rotation;

		Vector3 acceleration;

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
        RigidBody();
        RigidBody(double m);

        void UpdateDerivedData(); 

        // Apply F on a precise (world) point of the object
        void addForceAtPoint(Vector3 force, Vector3 point);
        // Apply F on a precise (object) point of the object
        void addForceAtBodyPoint(Vector3 force, Vector3 point);

        void ClearAccumulation();

        void Update(double time);
    };
}