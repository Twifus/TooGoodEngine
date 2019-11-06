#pragma once

#include <vector>

#include "Contacts/Contact.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		class Resolver
		{
		private:
			std::vector<Contact> contacts;

		public:
			void AddContact(Contact contact);
			void Clear();
			void Resolve();
		};
	}
}