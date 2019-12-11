#include "RigidBody.hpp"

#include <cmath>

namespace TooGoodEngine
{
	static constexpr double defaultDamping = 1;

	// Basic constructor
	RigidBody::RigidBody(double m, const Vector3& pos, const Quaternion& ori) :
		mass(m), inverseMass((m == 0) ? std::numeric_limits<double>::max() : 1 / m),
		linearDamping(defaultDamping), angularDamping(defaultDamping),
		position(pos), orientation(ori),
		velocity(), angularVelocity(),
		acceleration(), angularAccel(),
		inertiaTensorLocal(Matrix3::identity), inverseInertiaTensor(Matrix3::identity) 
	{ }

	// Setter useful for inheritence
	void RigidBody::SetInertiaTensorLocal(Matrix3& inertiaTensor)
	{
		inertiaTensorLocal = inertiaTensor;
		UpdateDerivedData();
	}

	// Apply a force at center of mass
	void RigidBody::AddForce(const Vector3& force)
	{
		AddForceAtPoint(force, position);
	}

	// Apply a force at a point in world space
	void RigidBody::AddForceAtPoint(const Vector3& force, const Vector3& point)
	{
		forceAcum += force;
		Vector3 relative_point = point - position;
		torqueAcum += relative_point.Cross(force);
	}

	// Apply a force at a point relative to center of mass
	void RigidBody::AddForceAtBodyPoint(const Vector3& force, const Vector3& point)
	{
		Vector3 forceInWordCoordinates = orientation * force;
		AddForceAtPoint(forceInWordCoordinates, BodyToWorld(point));
	}

	// Conversion for a point position in world<->body 
	Vector3 RigidBody::WorldToBody(const Vector3& v) const
	{
		return orientation.Inverse() * v - position;
	}

	Vector3 RigidBody::BodyToWorld(const Vector3& v) const
	{
		return orientation * v + position;
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

		// World inertia tensor
		Matrix3 orientationMatrix(orientation);
		inverseInertiaTensor = orientationMatrix * inertiaTensorLocal.Inverse() * orientationMatrix.Inverse();
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
		angularVelocity += angularAccel * time;

		// Apply Dampings
		velocity *= pow(linearDamping, time);
		angularVelocity *= pow(angularDamping, time);

		// Update positions
		position += velocity * time;
		orientation += Quaternion(angularVelocity) * orientation * (time * 0.5);

		UpdateDerivedData();
		ClearAccumulation();

	}

	double RigidBody::GetMass() const
	{
		return mass;
	}

	const Vector3 RigidBody::GetPosition() const
	{
		return position;
	}

	void RigidBody::SetPosition(const Vector3& value)
	{
		position = value;
		UpdateDerivedData();
	}

	const Quaternion RigidBody::GetOrientation() const
	{
		return orientation;
	}

	void RigidBody::SetOrientation(const Quaternion& value)
	{
		orientation = value;
		UpdateDerivedData();
	}

	const Vector3 RigidBody::GetVelocity() const
	{
		return velocity;
	}

	const Vector3 RigidBody::GetAngularVelocity() const
	{
		return angularVelocity;
	}
} // namespace TooGoodEngine
