#include "LinkContactGenerator.hpp"

namespace TooGoodEngine
{
	LinkContactGenerator::LinkContactGenerator(std::array<Particle*, 2> particles) : particles(particles) {}

	double TooGoodEngine::LinkContactGenerator::CurrentLength() const
	{
		return (particles[1]->position - particles[0]->position).Magnitude();
	}
}