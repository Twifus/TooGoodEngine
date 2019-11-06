#pragma once

#include <vector>

#include "Contacts/ParticleContact.hpp"

namespace TooGoodEngine
{
	class ParticleContactResolver
	{
	private:
		std::vector<ParticleContact> contacts;

	public:
		void AddContact(ParticleContact contact);
		void Clear();
		void Resolve();
	};
}