#pragma once

#include <vector>

#include "Contacts/ParticleContact.hpp"
#include "Contacts/Generators/LinkContactGenerator.hpp"

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