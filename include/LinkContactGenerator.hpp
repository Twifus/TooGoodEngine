#pragma once

#include <array>
#include <memory>

#include "Particle.hpp"
#include "ParticleContactGenerator.hpp"

namespace TooGoodEngine
{
	class LinkContactGenerator : ParticleContactGenerator
	{
	protected:
		std::array<Particle> particles;

		double CurrentLength() const;

	public:
		void AddContact() = 0;
	};
}