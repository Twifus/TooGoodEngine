#include "Frame.hpp"
#include <chrono>

namespace TooGoodEngine
{
	Frame::Frame()
	{
		lastFrame = std::chrono::high_resolution_clock::now();
		deltaFrame = 0;
	}

	double Frame::getDeltaFrame() const
	{
		return deltaFrame;
	}

	void Frame::computeDeltaFrame()
	{
		clock_tick t = std::chrono::high_resolution_clock::now();
		deltaFrame = std::chrono::duration_cast<std::chrono::nanoseconds>(t - lastFrame).count() / 1e9;
		lastFrame = t;
	}
}