#include "Errors.h"
#include <iostream>
#include <SDL\SDL.h>
#include <cstdlib>
namespace NeroEngine{
	void fatalError(std::string errorString){
		std::cout << "fatalError:" << errorString << std::endl;
		std::cout << "Enter anykey to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(0);
	}
}