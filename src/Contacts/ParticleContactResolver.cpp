#include "Contacts/ParticleContactResolver.hpp"
#include <algorithm>

namespace TooGoodEngine
{
	void ParticleContactResolver::AddContact(ParticleContact contact)
	{
		contacts.push_back(std::move(contact));
	}
	
	void ParticleContactResolver::Clear()
	{
		contacts.clear();
	}

	void ParticleContactResolver::Resolve()
	{
		if (contacts.empty())
			return;

		int i = 0;
		do
		{
			auto maxElement = std::max_element(contacts.begin() + i, contacts.end(), [](ParticleContact& c1, ParticleContact& c2) { return c1.ApproachVelocity() < c2.ApproachVelocity(); });
			if (maxElement->ApproachVelocity() < 0)
				break;
			maxElement->Resolve();
			std::iter_swap(contacts.begin() + i, maxElement);
			++i;
		} while (contacts.begin() + i < contacts.end());
	}
}