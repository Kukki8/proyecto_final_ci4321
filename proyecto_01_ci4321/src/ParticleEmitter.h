#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <glm.hpp>
#include <vector>
#include "Shader.h"

struct Particle {
	glm::vec3 Position;
	glm::vec3 Velocity;
    glm::vec4 Color;
    float     Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class ParticleEmitter {
public:

	ParticleEmitter(unsigned int textureID, unsigned int amount, glm::vec3 direction, float particleScale = 0.1f, float range = 0.5f);

	void Update(float dt, unsigned int newParticles, glm::vec3 startPos);
	void Draw(const Shader& shader, glm::mat4 view,bool glow = false);
	void Load();
	void Bind();

private:
	unsigned int amount;
	unsigned int VAO, VBO, IBO;
	unsigned int textureID;
	float range;
	float particleScale;
	glm::vec3 direction;
	std::vector<Particle> particles;
	unsigned int lastUsedParticle = 0;

	unsigned int indices[6] = {
		0,1,2,
		2,3,0
	};

	unsigned int FirstUnusedParticle();
	void RespawnParticle(Particle& particle, glm::vec3 startPos, glm::vec3 direction);

};




#endif