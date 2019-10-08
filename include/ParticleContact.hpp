#pragma once

#include <array>
#include <memory>

#include "Particle.hpp"
#include "Vector3.hpp"

namespace TooGoodEngine
{
	class ParticleContact
	{
	private:
		std::array<std::shared_ptr<Particle>, 2> particles;
		double restitution;
		double interpenetration;
		Vector3 normal;

		void ResolveResultingVelocity(double time);
		void ResolveInterpenetration();

	public:
		ParticleContact()
		double ApproachVelocity() const;
		void Resolve(double time);
	};
}