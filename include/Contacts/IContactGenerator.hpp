#pragma once

#include <vector>

#include "Contacts/Contact.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		class IContactGenerator
		{
		public:
			virtual ~IContactGenerator() = default;
			virtual void AddContact(std::vector<Contact>& contacts) = 0;
		};
	}
}