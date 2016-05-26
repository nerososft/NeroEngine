#include <SDL\SDL.h>
#include <GL\glew.h>
#include "NeroEngine.h"
namespace NeroEngine{
	int init(){
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}
}