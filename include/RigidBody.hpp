#pragma once

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix3.hpp"

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
		Vector3 velocity;
		Vector3 acceleration;

        Quaternion orientation;
        Vector3 rotation;

        Matrix3 transformMatrix;

        Matrix3 inverseInertiaTensor;

        Vector3 forceAcum;
        Vector3 torqueAcum;

        Vector3 massCenter;
		// Vector3 resultantForce;

    public:
        RigidBody();

        void CalculTransformMatrix(); 

        // Apply F on a precise (world) point of the object
        void addForceAtPoint(Vector3 force, Vector3 point);
        // Apply F on a precise (object) point of the object
        void addForceAtBodyPoint(Vector3 force, Vector3 point);

        void Update(double time);
    };
}