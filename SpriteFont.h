#pragma once


#ifndef SpriteFont_h__
#define SpriteFont_h__

#include <TTF/SDL_ttf.h>
#include <glm\glm.hpp>
#include <map>
#include <vector>

#include "Vertex.h"

namespace NeroEngine{
	class GLTexture;
	class SpriteBatch;

	struct  CharGlyph
	{
		public :
			char character;
			glm::vec4 uvRect;
			glm::vec2 size;
	};

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

	enum  class Justification
	{
		LEFT,MIDDLE,RIGHT
	};

	class SpriteFont
	{
	public:
		SpriteFont(const char* font,int size,char cs,char ce);
		SpriteFont(const char* font, int size):
			SpriteFont(font,size,FIRST_PRINTABLE_CHAR,LAST_PRINTABLE_CHAR){

		}
		void dispose();
		int getFontWeight()const { return _fontWeight; }
		glm::vec2 measure(const char s);
		//ColorRGBAB
		void draw(SpriteBatch* batch,
			const char* s,
			glm::vec2 position,
			glm::vec2 scaling,
			float depth,
			Color tint,
			Justification just = Justification::LEFT);

		~SpriteFont();

	private:
		static std::vector<int>* createRows(glm::ivec4* rects,int rectslength,int r,int padding,int& w);

		int _regStart, _regLength;
		CharGlyph* _glyph;
		int _fontWeight;

		unsigned int _texID;
	};
}
#endif

