#pragma once

#include <vector>

#include "Contacts/ParticleContact.hpp"

namespace TooGoodEngine
{
	class ParticleContactGenerator
	{
	public:
		virtual ~ParticleContactGenerator() = default;
		virtual void AddContact(std::vector<ParticleContact>& contacts) = 0;
	};
}