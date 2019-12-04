#pragma once

namespace TooGoodEngine
{
	namespace Contacts
	{
		class BoundingSphere
		{
		public:
			Vector3 center;
			float radius;

			public BoundingSphere(Vector3 center, float radius) : center(center), radius(radius) {}
		};
	}
}