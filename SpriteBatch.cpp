#include "SpriteBatch.h"
#include <algorithm>

namespace NeroEngine{
	Glyph::Glyph(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color) :
		texture(Texture), depth(Depth){

		topLeft.color = color;
		topLeft.setPosition(descRect.x, descRect.y + descRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(descRect.x, descRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(descRect.x + descRect.z, descRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(descRect.x + descRect.z, descRect.y + descRect.w);

		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
	Glyph::Glyph(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color& color,float angle) :
		texture(Texture), depth(Depth){

		glm::vec2 halfDims(descRect.z/2.0f,descRect.w/2.0f);

		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		//Ðý×ª×ø±ê
		tl = rotatePoint(tl, angle)+halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;


		topLeft.color = color;
		topLeft.setPosition(descRect.x+tl.x, descRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(descRect.x+bl.x, descRect.y+bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(descRect.x +br.x, descRect.y+br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(descRect.x+tr.x, descRect.y + tr.y);

		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
	glm::vec2 Glyph::rotatePoint(glm::vec2 pos, float angle){
		glm::vec2 newv;
		newv.x = pos.x*cos(angle)-pos.y*sin(angle);
		newv.y = pos.x*sin(angle)+pos.y*cos(angle);
		return newv;
	
	}
	SpriteBatch::SpriteBatch():_vbo(0),_vao(0){
	}
	SpriteBatch::~SpriteBatch(){
	}

	void SpriteBatch::init(){
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /*GlyphSortType::TEXTURE*/){
		_sortType = sortType;
		_renderBatches.clear();
		
		_glyphs.clear();

	}
	void SpriteBatch::end(){
		_glyphsPointers.resize(_glyphs.size());
		
		for (int i = 0; i < _glyphs.size();i++){
			_glyphsPointers[i] = &_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint texture,float depth, const Color& color){


		_glyphs.emplace_back(descRect,uvRect,texture,depth,color);

	}
	void SpriteBatch::draw(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, float angle){
		_glyphs.emplace_back(descRect, uvRect, texture, depth, color,angle);
	}
	void SpriteBatch::draw(const glm::vec4& descRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color, glm::vec2& dir){
		const glm::vec2 right(1.0f, 0.0f);

		float angle = acos(glm::dot(right, dir));
		if (dir.y<0){
			angle = -angle;
		}
		_glyphs.emplace_back(descRect, uvRect, texture, depth, color,angle);

	}

	void SpriteBatch::renderBatch(){
		glBindVertexArray(_vao);
		for (int i = 0; i < _renderBatches.size();i++){
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}
	
	}
	void SpriteBatch::createRenderBatches(){
		std::vector<Vertex> vertices;
		vertices.resize(_glyphsPointers.size() * 6);
		if (_glyphsPointers.empty()){
			return;
		}

		int offset = 0;
		int cv = 0;//current vertex
		_renderBatches.emplace_back(offset, 6, _glyphsPointers[0]->texture);
		vertices[cv++] = _glyphsPointers[0]->topLeft;
		vertices[cv++] = _glyphsPointers[0]->bottomLeft;
		vertices[cv++] = _glyphsPointers[0]->bottomRight;
		vertices[cv++] = _glyphsPointers[0]->bottomRight;
		vertices[cv++] = _glyphsPointers[0]->topRight;
		vertices[cv++] = _glyphsPointers[0]->topLeft;
		offset += 6;

		for (int cg = 1;/*current glyph*/cg < _glyphsPointers.size(); cg++){
			if (_glyphsPointers[cg]->texture != _glyphsPointers[cg - 1]->texture){
				_renderBatches.emplace_back(offset, 6, _glyphsPointers[cg]->texture);
			}
			else{
				_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = _glyphsPointers[cg]->topLeft;
			vertices[cv++] = _glyphsPointers[cg]->bottomLeft;
			vertices[cv++] = _glyphsPointers[cg]->bottomRight;
			vertices[cv++] = _glyphsPointers[cg]->bottomRight;	
			vertices[cv++] = _glyphsPointers[cg]->topRight;
			vertices[cv++] = _glyphsPointers[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER,0,vertices.size()*sizeof(Vertex),vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER,0) ;
		
	}
	void SpriteBatch::createVertexArray(){
		if (_vao==0){
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);


		if (_vbo == 0){
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER,_vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//position attrib pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
		//color attrib pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
		//uv attrib pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
	void SpriteBatch::sortGlyphs(){
		switch (_sortType)
		{
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareFrontToBack);
			break;
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), comapreTexture);
			break;
		default:
			break;
		}
		//std::stable_sort()
	}
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b){
		return(a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b){
		return(a->depth > b->depth);
	}
	bool SpriteBatch::comapreTexture(Glyph* a, Glyph* b){
		return(a->texture < b->texture);
	}
}