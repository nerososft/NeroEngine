#pragma once
#include <glm/glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <functional>
namespace NeroEngine{
	
	class Particle2D{
	public:
		glm::vec2 _position = glm::vec2(0.0f);
		glm::vec2 _velocity = glm::vec2(0.0f);
		Color _color;
		float _life;
		float _width;
	};

	inline void defaultUpdateFunc(Particle2D& particle, float deltaTime){
		particle._position += particle._velocity*deltaTime;
	}

	class ParticleBatch2D
	{
	public:
		friend class Particle2D;
		ParticleBatch2D();
		~ParticleBatch2D();
		void init(int maxParticlesNum,
			float decayRate,
			GLTexture texture,
			std::function<void(Particle2D&, float)> funcUpdate = defaultUpdateFunc);


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
		std::function<void(Particle2D&, float)> _funcUpdate;
	};
}
