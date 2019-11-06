#pragma once

#include <array>
#include <memory>
#include <vector>

#include "Particle.hpp"
#include "Contacts/ParticleContact.hpp"
#include "Contacts/Generators/ParticleContactGenerator.hpp"

namespace TooGoodEngine
{
	class LinkContactGenerator : public ParticleContactGenerator
	{
	protected:
		std::array<Particle*, 2> particles;

		LinkContactGenerator(std::array<Particle*, 2> particles);
		double CurrentLength() const;

	public:
		void AddContact(std::vector<ParticleContact>& contacts) = 0;
	};
}