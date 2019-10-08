#pragma once

#include <vector>

#include "LinkContactGenerator.hpp"
#include "ParticleContact.hpp"

namespace TooGoodEngine
{
	class CableContactGenerator : LinkContactGenerator
	{
	private:
		double maxLength, restitution;

	public:
		CableContactGenerator(std::array<Particle*, 2> particles, double maxLength, double restitution);
		void AddContact(std::vector<ParticleContact>& contacts) override;
	};
}