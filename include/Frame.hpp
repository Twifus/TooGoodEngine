#pragma once

#include <ctime>

namespace TooGoodEngine
{
	class Frame
	{
	private:
		std::time_t lastFrame;
		std::time_t deltaFrame;

	public:
		Frame();
		void computeDeltaFrame();
		double getDeltaFrame() const;
	};
}