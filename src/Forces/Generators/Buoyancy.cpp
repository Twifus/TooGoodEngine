#include "Forces/Generators/Buoyancy.hpp"

namespace TooGoodEngine
{
	namespace Forces
	{
		namespace Generators
		{
			Buoyancy::Buoyancy(double maxDepth, double volume, double liquidHeight, double density) :
				maxDepth(maxDepth), volume(volume), liquidHeight(liquidHeight), density(density) {}

			void Buoyancy::UpdateForce(Particle& particle, double time) const
			{
				double d = (liquidHeight + maxDepth - (particle.position).Dot(Vector3::up)) / (2 * maxDepth);
				if (d <= 0)
					return;
				else if (d >= 1)
					particle.AddForce(volume * density * Vector3::up);
				else
					particle.AddForce(d * volume * density * Vector3::up);
			}
		}
	}
}