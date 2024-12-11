#ifndef TANK_H
#define TANK_H

#include "Geometry.h"
#include "ParticleEmitter.h"

using namespace std;
const int wheelsCount = 5;
const int boltsCount = 2;

class Tank
{
public:

	Tank(unsigned int metalG, unsigned int blocks, unsigned int metal, unsigned int metalNorm, unsigned int blocksNorm, unsigned int dirt);
	void Draw(Shader& shader,Shader& particleShader, glm::mat4 view);
	void Clear();
	void Update(float dt);
	void moveForward(const Shader& ourShader);
	void moveBackwards(const Shader& ourShader);
	unsigned int metalG;
	unsigned int blocks;
	unsigned int metal;
	unsigned int metalNorm;
	unsigned int blocksNorm;
	unsigned int dirt;
	void moveCanonUp(float deltaTime);
	void moveCanonDown(float deltaTime);
	void moveCanonRight(float deltaTime);
	void moveCanonLeft(float deltaTime);
	void rotateSphereRight(float deltaTime);
	void rotateSphereLeft(float deltaTime);
	void rotateBodyLeft(float deltaTime);
	void rotateBodyRight(float deltaTime);
	void fire();
	inline glm::vec3 getSize()
	{
		return body->size;
	};
	inline glm::vec3 getPosition()
	{
		return body->position;
	};

	inline bool hasBeenShotF() {
		return hasProjectile && hasBeenShot;
	};

	inline Cylinder *getProjectile() {
		return projectile;
	}
	inline void setHasBeenShot() {
		hasProjectile = false;
		hasBeenShot = false;
	}

	inline glm::vec3 getLightPosition()
	{
		return light->position;
	}

private:

	Cube* body;
	Sphere* top;
	Sphere* light;
	Cylinder* canon;
	Cylinder* wheels[wheelsCount];
	Cube* bolts[boltsCount * wheelsCount];
	Cylinder* projectile;
	bool hasProjectile;
	bool hasBeenShot;
	ParticleEmitter* emitter;	
};

#endif

