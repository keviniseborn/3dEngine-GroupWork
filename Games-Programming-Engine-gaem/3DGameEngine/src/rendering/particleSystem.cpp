#include "rendering\particleSystem.h"

ParticleSystem::ParticleSystem(size_t maxCount)
{
	_particleCount = maxCount;
	_particles.generate(maxCount);
	_emitFlag=true;
	for(size_t i = 0; i < maxCount; ++i)
	{
		_particles._particleAliveFlags[i]=false;
	}

	std::cout << "Particle System Start\n";
}

ParticleSystem::~ParticleSystem()
{
	_updaters.clear();

	std::cout << "Particle System End\n";
}

void ParticleSystem::clear()
{
	for(auto it: _updaters)
	{
		if(it.unique())
		{
			it.reset();
		}
	}
	for(auto it: _emitters)
	{
		if(it.unique())
		{
			it.reset();
		}
	}
}

void ParticleSystem::update(float dt)
{
	if(_emitFlag)
	{
		for(auto _emitter : _emitters)
		{
			if(_emitter!=nullptr)_emitter->emit(dt,&_particles);
		}
	}
	for(size_t i = 0; i < _particleCount; ++i)
	{
		_particles._particleAccelerations[i]=glm::vec4(0.0f);
	}
	for(auto & updaters : _updaters)
	{
		updaters->update(dt,&_particles);
	}
}

void ParticleSystem::addUpdater(SP_ParticleUpdater updater)
{
	_updaters.push_back(updater);
}

void ParticleSystem::addEmitter(SP_ParticleEmitter emitter)
{
	_emitters.push_back(emitter);
}

SP_ParticleEmitter ParticleSystem::getEmitter(int id)
{
	if(id<_emitters.size()){
		return SP_ParticleEmitter();
	}
	else
	{
		return _emitters[id];
	}
}

SP_ParticleUpdater ParticleSystem::getUpdater(Updaters::type type)
{
	for(unsigned int i = 0; i < _updaters.size(); ++i)
	{
		if(_updaters[i]->getType() == type) return _updaters[i];
	}
	return SP_ParticleUpdater();
}

void ParticleSystem::reset()
{
	_particles._aliveParticleCount=0;
}

