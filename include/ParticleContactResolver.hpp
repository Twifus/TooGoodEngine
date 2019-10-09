#pragma once

#include <vector>

#include "ParticleContact.hpp"

namespace TooGoodEngine
{
	class ParticleContactResolver
	{
	private:
		std::vector<ParticleContact> contacts;

	public:
		void AddContact(ParticleContact contact);
		void Clear();
		void Resolve(double time);
	};
}