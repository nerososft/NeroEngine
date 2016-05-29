#pragma once
#include <GL\glew.h>
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>
namespace NeroEngine{
	enum  class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};
	class Glyph
	{
	public :
		Glyph();
		Glyph(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color);
		Glyph(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color,float angle);
		
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle);
	};

	class RenderBatch{
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :offset(Offset),
			numVertices(NumVertices),
			texture(Texture){
		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;

	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

		void end();

		void draw(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);
		void draw(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color,float angle);
		void draw(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color,glm::vec2& dir);


		void renderBatch();
	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a,Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool comapreTexture(Glyph* a, Glyph* b);

		GLuint _vbo;
		GLuint _vao;
		
		GlyphSortType _sortType;

		std::vector<Glyph*> _glyphsPointers;
		std::vector<Glyph> _glyphs;
		std::vector<RenderBatch> _renderBatches;

	};
}

