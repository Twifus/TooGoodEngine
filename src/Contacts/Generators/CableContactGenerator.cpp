#include "Contacts/Generators/CableContactGenerator.hpp"

namespace TooGoodEngine
{
	CableContactGenerator::CableContactGenerator(std::array<Particle*, 2> particles, double maxLength, double restitution) : LinkContactGenerator(particles), maxLength(maxLength), restitution(restitution) {}

	void CableContactGenerator::AddContact(std::vector<ParticleContact>& contacts)
	{
		if (CurrentLength() > maxLength)
		{
			contacts.push_back(ParticleContact(particles[0], particles[1], restitution)); // TOFIX
		}
	}
}