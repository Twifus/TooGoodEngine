#pragma once

namespace TooGoodEngine
{
	class BuoyancyForceGenerator
	{
	private:
		double maxDepth, volume, liquidHeight, density;

	public:
		BuoyancyForceGenerator(double maxDepth, double volume, double liquidHeight, double density);
		virtual void UpdateForce(Particle& particle, double time) const;
	};
}