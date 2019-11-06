#include "Contacts/Generators/Link.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		namespace Generators
		{
			Link::Link(std::array<Particle*, 2> particles) : particles(particles) {}

			double Link::CurrentLength() const
			{
				return (particles[1]->position - particles[0]->position).Magnitude();
			}
		}
	}
}