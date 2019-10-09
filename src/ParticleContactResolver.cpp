#include "ParticleContactResolver.hpp"
#include <algorithm>

namespace TooGoodEngine
{
	void ParticleContactResolver::AddContact(ParticleContact& contact)
	{
		contacts.push_back(contact);
	}
	
	void ParticleContactResolver::Clear()
	{
		contacts.clear();
	}

	void ParticleContactResolver::Resolve(double time)
	{
		if (contacts.empty())
			return;

		int i = 0;
		do
		{
			auto maxElement = std::max_element(contacts.begin() + i, contacts.end(), [](ParticleContact& c1, ParticleContact& c2) { return c1.ApprochVelocity() < c2.ApprochVelocity(); });
			if (maxElement->ApprochVelocity() < 0)
				break;
			maxElement->Resolve(time);
			std::swap(contacts.begin() + i, maxElement);
			++i;
		} while (contacts.begin() + i < contacts.end());
	}
}