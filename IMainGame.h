#pragma once
#include "Window.h"
#include "InputManager.h"
#include <memory>
namespace NeroEngine{
	class ScreenList;
	class IGameScreen;
	class IMainGame
	{
	public:
		IMainGame();
		virtual ~IMainGame();

		void run();
		void exitGame();

		virtual void onInit() = 0;
		virtual void addScreen() = 0;
		virtual void onExit() = 0;

		
		const float getFps() const{
			return _fps;
		}
	protected:
		virtual void update();
		virtual void draw();



		bool init();
		bool initSystem();

		void onSDLEvent(SDL_Event& evnt);

		std::unique_ptr<ScreenList> _screenList;
		IGameScreen* _currentScreen = nullptr;
		bool _isRunning = false;
		float _fps;

		Window _window;

		InputManager _inputManager;
		
	};
}

