#include "Exceptions.hpp"
#include <stdexcept>

namespace TooGoodEngine
{
	namespace Exceptions
	{
		divided_by_zero::divided_by_zero() : runtime_error("Math error: Attempted to to divide by 0\n") {}
	}
}