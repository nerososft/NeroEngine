#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"
namespace NeroEngine{
	
	class Particle2D{
	public:
		friend class ParticleBatch2D;

		void update(float deltaTime);
	private:
		glm::vec2 _position = glm::vec2(0.0f);
		glm::vec2 _velocity = glm::vec2(0.0f);
		Color _color;
		float _life;
		float _width;
	};
	class ParticleBatch2D
	{
	public:
		friend class Particle2D;
		ParticleBatch2D();
		~ParticleBatch2D();
		void init(int maxParticlesNum,float decayRate,GLTexture texture);


		void update(float deltaTime);
		void draw(SpriteBatch* spriteBatch);
		void addParticle(const glm::vec2& position,
			const glm::vec2& velocity,				
			const Color& color,
			float width); 
	private:
		int findFreeParticles();

		float _decayRate = 0.1f;
		Particle2D* _particles = nullptr;
		int _maxParticlesNum = 0;
		int _lastFreeParticles = 0;
		GLTexture _texture;

	};
}
