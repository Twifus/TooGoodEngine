#include "Contacts/Resolver.hpp"
#include <algorithm>

namespace TooGoodEngine
{
	namespace Contacts
	{
		void Resolver::AddContact(Contact contact)
		{
			contacts.push_back(std::move(contact));
		}

		void Resolver::Clear()
		{
			contacts.clear();
		}

		void Resolver::Resolve()
		{
			int i = 0;
			while (i < 2 * contacts.size())
			{
				auto maxElement = std::max_element(contacts.begin(), contacts.end(), [](Contact& c1, Contact& c2) { return c1.ApproachVelocity() < c2.ApproachVelocity(); });
				if (maxElement->ApproachVelocity() <= 0)
					break;
				maxElement->Resolve();
				++i;
			}
		}
	}
}