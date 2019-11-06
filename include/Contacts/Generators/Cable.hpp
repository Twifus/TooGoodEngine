#pragma once

#include <vector>

#include "Contacts/Contact.hpp"
#include "Contacts/Generators/Link.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		namespace Generators
		{
			class Cable : Link
			{
			private:
				double maxLength, restitution;

			public:
				Cable(std::array<Particle*, 2> particles, double maxLength, double restitution);
				void AddContact(std::vector<Contact>& contacts) override;
			};
		}
	}
}