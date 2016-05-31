#pragma once
#include <vector>
#define SCREEN_INEDX_NO_SCREEN -1
namespace NeroEngine{
	class IMainGame;
	class IGameScreen;
	class ScreenList
	{
	public:
		ScreenList(IMainGame* game);
		ScreenList::~ScreenList();
		IGameScreen* moveNext();
		IGameScreen* movePrevious();
		
		void setScreen(int nextScreen);
		void addScreen(IGameScreen* newScreen);

		void destroy();

		IGameScreen* getCurrent();
	protected:
		IMainGame* _game = nullptr;
		std::vector<IGameScreen*> _screens;
		int _currentScreenIndex = SCREEN_INEDX_NO_SCREEN;
	};
}
