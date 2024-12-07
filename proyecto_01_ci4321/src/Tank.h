#ifndef TANK_H
#define TANK_H

#include "Geometry.h"

using namespace std;
const int wheelsCount = 5;
const int boltsCount = 2;

class Tank
{
public:

	Tank(unsigned int metalG, unsigned int blocks, unsigned int metal, unsigned int metalNorm, unsigned int blocksNorm);
	void Draw(const Shader& shader);
	void Clear();
	void moveForward(const Shader& ourShader);
	void moveBackwards(const Shader& ourShader);
	unsigned int metalG;
	unsigned int blocks;
	unsigned int metal;
	unsigned int metalNorm;
	unsigned int blocksNorm;
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

private:

	Cube* body;
	Sphere* top;
	Cylinder* canon;
	Cylinder* wheels[wheelsCount];
	Cube* bolts[boltsCount * wheelsCount];
	Cylinder* projectile;
	bool hasProjectile;
	bool hasBeenShot;
};

#endif

