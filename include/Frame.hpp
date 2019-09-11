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
		void computeDeltaFrame();		// Compute the time between the current and the last frame
		double getDeltaFrame() const;	// Getter for the time between two frames
	};
}