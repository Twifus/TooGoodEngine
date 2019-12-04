#pragma once

namespace TooGoodEngine
{
	namespace Contacts
	{
		class BoundingSphere
		{
		public:
			Vector3 center;
			double radius;

			BoundingSphere(Vector3 center, double radius) : center(center), radius(radius) {}
		};
	}
}