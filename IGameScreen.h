#pragma once
namespace NeroEngine{
	class  IMainGame;
	
	enum  class ScreenState
	{
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};
	class IGameScreen
	{
	public:
		friend class ScreenList;

		IGameScreen();
		virtual~IGameScreen();
		//when change screen 
		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;
		//called at begin of application & end of application
		virtual void build() = 0;
		virtual void destroy() = 0;

		//called when a screen enters and exits focus
		virtual void onEntry() = 0;
		virtual void onExit() = 0;
		
		//main game loop
		virtual void update() = 0;
		virtual void draw() = 0;

		

		int getScreenIndex() const{
			return _screenIndex;
		}
		ScreenState getScreenState() const{ return _screenState; }
		void setRunning(){ _screenState = ScreenState::RUNNING; }

		void setParentGame(IMainGame* game){
			m_game = game;
		}
	protected:
		ScreenState _screenState = ScreenState::NONE;
		IMainGame* m_game = nullptr;

		int _screenIndex = -1;
	};
}

