#pragma once

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix3.hpp"
#include "Transform.hpp"

namespace TooGoodEngine
{
	class RigidBody
	{
	private:
		double mass = 1;
		double inverseMass = 1;
		double linearDamping = 1;
		double angularDamping = 1;

		Vector3 position;
		Quaternion orientation;

		Vector3 velocity;
		Vector3 angularVelocity;

		Vector3 acceleration;
		Vector3 angularAccel;

		Matrix3 inertiaTensorLocal;
		Matrix3 inverseInertiaTensor;

		Vector3 forceAcum;
		Vector3 torqueAcum;

		Vector3 massCenter;

	protected:
		void SetInertiaTensorLocal(Matrix3& inertiaTensor);

	public:

		// Constructor
		RigidBody(double m, const Vector3& pos = Vector3::zero, const Quaternion& ori = Quaternion::identity);

		void UpdateDerivedData();

		void AddForce(const Vector3& force);
		// Apply F on a precise (world) point of the object
		void AddForceAtPoint(const Vector3& force, const Vector3& point);
		// Apply F on a precise (object) point of the object
		void AddForceAtBodyPoint(const Vector3& force, const Vector3& point);

		void ClearAccumulation();

		void Update(double time);

		double GetMass() const;

		const Vector3 GetPosition() const;
		void SetPosition(const Vector3& value);

		const Quaternion GetOrientation() const;
		void SetOrientation(const Quaternion& value);

		const Vector3 GetVelocity() const;
		const Vector3 GetAngularVelocity() const;

		Vector3 BodyToWorld(const Vector3& v) const;
		Vector3 WorldToBody(const Vector3& v) const;

	};
}