#pragma once

namespace TooGoodEngine
{
	class ParticleContactGenerator
	{
	public:
		virtual ~ParticleContactGenerator() = default;
		virtual void AddContact() = 0;
	};
}