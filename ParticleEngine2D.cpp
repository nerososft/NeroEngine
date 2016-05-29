#include "ParticleEngine2D.h"
#include "SpriteBatch.h"
#include "ParticleBatch2D.h"

namespace NeroEngine{
	ParticleEngine2D::ParticleEngine2D()
	{
	}


	ParticleEngine2D::~ParticleEngine2D()
	{
		for (auto& p : _particleBatch2D){
			delete p;
		}
	}
	
	void ParticleEngine2D::addParticleBatch(ParticleBatch2D* particleBatch2D){
		_particleBatch2D.push_back(particleBatch2D);
	}
	void ParticleEngine2D::update(float deltaTime){
		for (auto& p:_particleBatch2D){
			p->update(deltaTime);
		}
	
	}

	void ParticleEngine2D::draw(SpriteBatch* spriteBatch){
		for (auto& b:_particleBatch2D){
			spriteBatch->begin();
			b->draw(spriteBatch);
			spriteBatch->end();
			spriteBatch->renderBatch();
		}
	}
}