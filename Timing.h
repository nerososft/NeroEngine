#pragma once

namespace NeroEngine{
	class FpsLimter
	{
	public:
		FpsLimter();
		void init(float maxFPS);

		void setMaxFps(float maxFPS);

		void begin();

		float end();


	private:
		void calculateFPS();
		unsigned int _startTicks;

		float _maxFPS;
		float _fps;
		float _frameTime;

	};

}