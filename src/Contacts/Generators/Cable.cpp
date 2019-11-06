#include "Contacts/Generators/Cable.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		namespace Generators
		{
			Cable::Cable(std::array<Particle*, 2> particles, double maxLength, double restitution) : Link(particles), maxLength(maxLength), restitution(restitution) {}

			void Cable::AddContact(std::vector<Contact>& contacts)
			{
				if (CurrentLength() > maxLength)
				{
					contacts.push_back(Contact(particles[0], particles[1], restitution)); // TOFIX
				}
			}
		}
	}
}