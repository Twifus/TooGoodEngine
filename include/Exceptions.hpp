#pragma once

#include <stdexcept>

namespace TooGoodEngine
{
	namespace Exceptions
	{
		class divided_by_zero : std::runtime_error
		{
		public:
			divided_by_zero();
		};
	}
}