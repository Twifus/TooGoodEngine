#pragma once

#include <array>
#include <memory>
#include <vector>

#include "Particle.hpp"
#include "Contacts/Contact.hpp"
#include "Contacts/IContactGenerator.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		namespace Generators
		{
			class Link : public IContactGenerator
			{
			protected:
				std::array<Particle*, 2> particles;

				Link(std::array<Particle*, 2> particles);
				double CurrentLength() const;

			public:
				void AddContact(std::vector<Contact>& contacts) = 0;
			};
		}
	}
}