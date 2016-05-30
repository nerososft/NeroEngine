#include "ParticleBatch2D.h"

namespace NeroEngine{
	
	ParticleBatch2D::ParticleBatch2D()
	{
	}


	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] _particles;

	}
	
	void ParticleBatch2D::init(int maxParticlesNum, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> funcUpdate /*= defaultUpdateFunc*/){
		_maxParticlesNum = maxParticlesNum;
		_particles = new Particle2D[_maxParticlesNum];
		_decayRate = decayRate;
		_texture = texture;
		_funcUpdate = funcUpdate;

	}
	void ParticleBatch2D::update(float deltaTime){
		for (int i = 0; i < _maxParticlesNum;i++){
			if (_particles[i]._life>0){
				_funcUpdate(_particles[i], deltaTime);
				_particles[i]._life -= _decayRate*deltaTime;
			}
		}
	}
	void ParticleBatch2D::draw(SpriteBatch* spriteBatch){
	
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	
		for (int i = 0; i < _maxParticlesNum; i++){
			auto &p = _particles[i];
			if (p._life>0){
				glm::vec4 destRect(p._position.x,p._position.y,p._width,p._width);
				spriteBatch->draw(destRect,uvRect,_texture.id,0.0f,p._color);
			}
		}

	}
	void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity,
		const Color& color,
		float width){
		int particleIndex = findFreeParticles();

		auto& p = _particles[particleIndex];

		p._life = 1.0f;
		p._position = position;
		p._velocity = velocity;
		p._color = color;
		p._width = width;
	}
	int ParticleBatch2D::findFreeParticles(){
		for (int i = _lastFreeParticles; i < _maxParticlesNum;i++){
			if (_particles[i]._life<=0){
				_lastFreeParticles = i;
				return i;
			}
		}

		for (int i = 0; i < _lastFreeParticles; i++){
			if (_particles[i]._life <= 0){
				_lastFreeParticles = i;
				return i;
			}
		}

		//Î´·¢ÏÖ
		return 0;
	}
}