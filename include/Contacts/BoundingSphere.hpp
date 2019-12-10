#pragma once

#include "Vector3.hpp"

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
			bool Intersection(BoundingSphere &other) { return ((other.center - this->center).Magnitude() <= (this->radius + other.radius)); }
		};
	}
}