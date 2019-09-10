#pragma once

namespace TooGoodEngine
{
	class Frame
	{
	private:
		double lastFrame;
		double deltaFrame;

	public:
		Frame();
		void computeDeltaFrame();
		double getDeltaFrame() const;
	};
}