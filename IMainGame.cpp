#include "IMainGame.h"
#include "Timing.h"


#include "ScreenList.h"
#include "IGameScreen.h"
namespace NeroEngine{
	IMainGame::IMainGame()
	{
		_screenList = std::make_unique<ScreenList>(this);
	}


	 IMainGame::~IMainGame()
	{
	}
	 void IMainGame::run(){
		 if (!init()) return;
		 FpsLimter fpsLimter;
		 fpsLimter.setMaxFps(60.0f);
		 _isRunning = true;
		 while (_isRunning)
		 {
			 fpsLimter.begin();
			 //_inputManager.update();
			 draw();

			 _fps = fpsLimter.end();
			 _window.swapBuffer();
		 }
	 }
	 void IMainGame::exitGame(){
		 _currentScreen->onExit();
		 if (_screenList){
			 _screenList->destroy();
			 _screenList.reset();
		 }
		 _isRunning = false;
	 }

	 bool IMainGame::init(){
		 SDL_Init(SDL_INIT_EVERYTHING);

		 SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		 if(!initSystem())return false;

		 onInit();
		 addScreen();

		 _currentScreen = _screenList->getCurrent();
		 _currentScreen->onEntry();
		 _currentScreen->setRunning();
	 }
	 bool IMainGame::initSystem(){
		 _window.create("Default",800,500,0);
		 return true;
	 }
	 void IMainGame::onSDLEvent(SDL_Event& evnt){
		 switch (evnt.type)
		 {
		 case SDL_QUIT:
			 _isRunning = false;
			 break;
		 case SDL_KEYDOWN:
			 _inputManager.pressKey(evnt.key.keysym.sym);
			 break;
		 case SDL_KEYUP:
			 _inputManager.releaseKey(evnt.key.keysym.sym);
			 break;
		 case SDL_MOUSEBUTTONDOWN:
			 _inputManager.pressKey(evnt.button.button);
			 break;
		 case SDL_MOUSEBUTTONUP:
			 _inputManager.releaseKey(evnt.button.button);
			 break;
		 case SDL_MOUSEMOTION:
			 _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			 break;
		 case SDL_MOUSEWHEEL:

			 break;
		 default:
			 break;
		 }
	 }
	 void IMainGame::update(){
		 if (_currentScreen){
			 switch (_currentScreen->getScreenState())
			 {
			 case ScreenState::RUNNING:
				 _currentScreen->update();
				 break;
			 case ScreenState::CHANGE_NEXT:
				 _currentScreen->onExit();
				 _currentScreen = _screenList->moveNext();
				 if (_currentScreen){
					 _currentScreen->setRunning();
					 _currentScreen->onEntry();
				 }
				 break;
			 case ScreenState::CHANGE_PREVIOUS:
				 _currentScreen->onExit();
				 _currentScreen = _screenList->movePrevious();
				 if (_currentScreen){
					 _currentScreen->setRunning();
					 _currentScreen->onEntry();
				 }
				 break;
			 case ScreenState::EXIT_APPLICATION:
				 exitGame();
				 break;
			 default:
				 break;
			 }
		 }
		 else{
			 exitGame();
		 }
	 }
	 void IMainGame::draw(){
		 if (_currentScreen && _currentScreen->getScreenState() == ScreenState::RUNNING){
			 _currentScreen->draw();
		 }
	 }

}
