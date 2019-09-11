#pragma once

#include <chrono>

namespace TooGoodEngine
{
	using clock_tick = std::chrono::time_point<std::chrono::high_resolution_clock>;
	class Frame
	{
	private:
		clock_tick lastFrame;
		double deltaFrame;

	public:
		Frame();
		void computeDeltaFrame();
		double getDeltaFrame() const;
	};
}