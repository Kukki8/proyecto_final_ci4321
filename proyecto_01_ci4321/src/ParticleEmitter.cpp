#include "ParticleEmitter.h"
#include <iostream>
#include <gtc/matrix_transform.hpp>

// To do:
// Generar velocidad random de una mejor forma (numero random en c/componente)
// Cambiar como se resta el alpha
// Cambiar donde se estta poniendo el emitter en el tanque
// Pasar color al emitter (broon)

ParticleEmitter::ParticleEmitter(unsigned int textureID, unsigned int amount, glm::vec3 direction, float particleScale, bool continuous)
{
	this->textureID = textureID;
	this->amount = amount;
	this->particleScale = particleScale;
	this->direction = direction;
	this->continuous = continuous;
	this->started = false;

	particles = std::vector<Particle>(amount);
}

void ParticleEmitter::Update(float dt, unsigned int newParticles, glm::vec3 startPos)
{
	if (continuous)
	{
		// Busca los indices de las particulas a reemplazar
		for (int i = 0; i < newParticles; ++i)
		{
			int unusedParticle = FirstUnusedParticle();
			RespawnParticle(particles[unusedParticle], startPos, direction);
		}
	}


	// Actualiza las particulas
    for (int i = 0; i < amount; ++i)
    {
        Particle& p = particles[i];

		p.Life -= dt; // Reduce la vida de la particula
        if (p.Life > 0.0f)
        {	
            // Si la particula actual esta viva, se actualiza
            p.Position -= p.Velocity * dt;
            p.Color.a -= dt * 2.5f;
        }
    }

}

void ParticleEmitter::Draw(const Shader& shader, glm::mat4 view, bool glow)
{
    if (glow)
    {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	for (Particle particle : particles)
	{
		if (particle.Life > 0.0f)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, particle.Position);
			glm::vec3 right = glm::normalize(view[0]);

			shader.setMat4("view", view);
			shader.setMat4("model", model);
			shader.setVec4("color", particle.Color);
			Bind();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
			glBindVertexArray(0);
		}

	}

    if (glow)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

}


void ParticleEmitter::Load()
{
	float size = particleScale / 2.0f;

	float particle_quad[] = {
		-size,-size,0.0f,0.0f, 0.0f,
		 size,-size,0.0f,1.0f, 0.0f,
		 size, size,0.0f,1.0f, 1.0f,
		-size, size,0.0f,0.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ParticleEmitter::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void ParticleEmitter::Play(glm::vec3 startPos)
{
	
	for (int i = 0; i < amount; ++i)
	{
		RespawnParticle(particles[i], startPos, direction);
	}
	started = true;
}

unsigned int ParticleEmitter::FirstUnusedParticle()
{
	// Busca a partir de la ultima particula usada.
    for (int i = lastUsedParticle; i < amount; ++i) {
        if (particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
	// Sino, realiza una busqueda lineal.
    for (int i = 0; i < lastUsedParticle; ++i) {
        if (particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // Caso en el que se vieron todas las particulas, se sobreescribe la primera.
    lastUsedParticle = 0;
    return 0;

}

void ParticleEmitter::RespawnParticle(Particle& particle, glm::vec3 startPos, glm::vec3 direction)
{

	float randomX = ((rand() % 100) - 50) / 100.0f;
	float randomY = ((rand() % 100) - 50) / 100.0f;
	float randomZ = ((rand() % 100)) / 100.0f;

	particle.Position = startPos;
	particle.Velocity = direction + glm::vec3(randomX, randomY, -randomZ);
    particle.Color = glm::vec4(0.41f, 0.41f, 0.41f, 1.0f);
    particle.Life = 1.0f;
}

