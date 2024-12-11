#include "Tank.h"

Tank::Tank(unsigned int metalG, unsigned int blocks, unsigned int metal, unsigned int metalNorm, unsigned int blocksNorm, unsigned int dirt)
{
	this->metalG = metalG;
	this->blocks = blocks;
	this->metal = metal;
	this->metalNorm = metalNorm;
	this->blocksNorm = blocksNorm;
	this->dirt = dirt;

	body = new Cube(4.0, 1.0, 4.25);
	body->Load();
	


	glm::vec3 topPos = body->position + glm::vec3(0.0f, 0.5f, -0.25f);
	top = new Sphere(1.25f, 36, 18, false);
	top->SetPosition(topPos);
	top->Load();

	light = new Sphere(0.0f);
	light->SetPosition(topPos + glm::vec3(0.0f, 1.35f, 0.0f));
	light->Load();

	glm::vec3 canonPos = top->position + glm::vec3(0.0f, 0.5f, 1.0f);
	canon = new Cylinder(0.25f, 0.25f, 2.0f);
	canon->SetPosition(canonPos);
	canon->Load();

	for (int i = 0; i < wheelsCount; i++) {

		glm::vec3 wheelPos = body->position;
		
		switch (i)
		{
		case 0:
			wheelPos += glm::vec3(0, -1.0, -body->depth/2);
			break;
		case 1:
			wheelPos += glm::vec3(0, -1.0, -body->depth/4);
			break;
		case 2:
			wheelPos += glm::vec3(0, -1.0, 0);
			break;
		case 3:
			wheelPos += glm::vec3(0, -1.0, body->depth / 4);
			break;
		case 4:
			wheelPos += glm::vec3(0, -1.0, body->depth / 2);
			break;
		}

		wheels[i] = new Cylinder(0.52, 0.52, 4);
		wheels[i]->SetPosition(wheelPos);
		wheels[i]->SetRotation(glm::vec3(0.0, glm::radians(90.0), 0.0));

		wheels[i]->Load();

		float centerHeight = wheels[i]->height/2;
		float faceRadius = wheels[i]->baseRadius/2;

		for (int j = boltsCount*i; j < boltsCount*(i + 1); j++) {
			glm::vec3 boltPos = wheels[i]->position;

			switch (j % boltsCount)
			{
			case 0:
				boltPos += glm::vec3(-centerHeight, 0.0, 0.0);
				break;
			case 1:
				boltPos += glm::vec3(centerHeight, 0.0, 0.0);
				break;
			}

			bolts[j] = new Cube(0.1, 0.4, 0.4);
			bolts[j]->SetPosition(boltPos);

			bolts[j]->Load();
		}
	}

	emitter = new ParticleEmitter(dirt, 120, glm::vec3(0.0f, 0.0f, 0.0f),0.05,false);

	emitter->Load();
}

void Tank::Draw(Shader& shader,Shader& particleShader, glm::mat4 view)
{

	shader.use();
	canon->Bind(metal, metalNorm);
	canon->DrawCanon(shader);

	body->Bind(metalG, metalNorm);
	body->Draw(shader);

	top->Bind(metalG, metalNorm);
	top->Draw(shader);

	light->Draw(shader);

	for (int i = 0; i < wheelsCount; i++) {
		wheels[i]->Bind(blocks,blocksNorm);
		wheels[i]->Draw(shader);
	}


	for (int j = 0; j < boltsCount*wheelsCount; j++) {
		bolts[j]->Bind(metal, metalNorm);
		bolts[j]->Draw(shader);
	}

	if (hasProjectile && !hasBeenShot) {

		projectile = new Cylinder(0.05f, 0.05f, 0.3f, 64);
		glm::vec3 projectilePos = canon->position + glm::vec3(0.0f, 0.0f, canon->height / 2);

		glm::vec3 projectileRot = canon->rotation;
		projectile->SetRotation(projectileRot);

		projectile->SetPosition(projectilePos);
		projectile->Load();
		hasBeenShot = true;
		emitter->Play(projectilePos);

	}
	if (hasProjectile && hasBeenShot) {
		particleShader.use();
		emitter->Draw(particleShader, view, false);
		shader.use();

		if (projectile->rotation != glm::vec3(0.0f)) {
			projectile->position += glm::vec3(0.0f, projectile->rotation.y, projectile->rotation.y) * 0.05f * 0.25f;
			projectile->Bind(blocks, blocksNorm);
			projectile->Draw(shader);
		}
		else {
			projectile->position += glm::normalize(glm::vec3(0.0f, 0.0f, 0.50f)) * 0.05f * 0.25f;
			projectile->Bind(blocks, blocksNorm);
			projectile->Draw(shader);
		}		
	}
}

void Tank::Clear()
{
	canon->Clean();
	body->Clean();
	top->Clean();

	for (int i = 0; i < wheelsCount; i++) {

		wheels[i]->Clean();

	}

	for (int j = 0; j < boltsCount*wheelsCount; j++) {
		bolts[j]->Clean();
	}

}

void Tank::Update(float dt)
{
	glm::vec3 startPos = canon->position + glm::vec3(0.0f,0.0f, canon->height/2);
	emitter->Update(dt, 5, startPos);
}

void Tank::moveForward(const Shader& ourShader) {
	
	body->moveForward();
	canon->moveForward();
	top->moveForward();
	for (int i = 0; i < wheelsCount; ++i) {
		wheels[i]->moveForward();
		wheels[i]->rotation += glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * 0.05f;

	}
	for (int i = 0; i < boltsCount*wheelsCount; i++) {
		bolts[i]->moveForward();
		bolts[i]->rotation += glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)) * 0.05f;
	}
	
}

void Tank::moveBackwards(const Shader& ourShader) {

	body->moveBackwards();
	canon->moveBackwards();
	top->moveBackwards();
	for (int i = 0; i < wheelsCount; ++i) {
		wheels[i]->moveBackwards();
		wheels[i]->rotation -= glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f)) * 0.05f;
	}
	for (int i = 0; i < boltsCount * wheelsCount; i++) {
		bolts[i]->moveBackwards();
		bolts[i]->rotation -= glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)) * 0.05f;
	}

}

void Tank::moveCanonUp(float deltaTime) {
	
	if (canon->rotation.x <= -0.70f) {
		canon->rotation.x = -0.70f;
	}
	else {
		canon->rotation -= glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)) * deltaTime;
	}
}

void Tank::moveCanonDown(float deltaTime) {
	if (canon->rotation.x >= 0.00f) {
		canon->rotation.x = 0.00f;
	}
	else {
		canon->rotation += glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)) * deltaTime;
	}
}

void Tank::moveCanonRight(float deltaTime) {

	if (canon->rotation.y <= -0.90f) {
		canon->rotation.y = -0.90f;
		
	}
	else {
		canon->rotation -= glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * deltaTime;
		rotateSphereRight(deltaTime);
	}
}

void Tank::moveCanonLeft(float deltaTime) {
	if (canon->rotation.y >= 0.90f) {
		canon->rotation.y = 0.90f;
	}
	else {
		canon->rotation += glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * deltaTime;
		rotateSphereLeft(deltaTime);
	}
}

void Tank::rotateSphereRight(float deltaTime) {
	top->rotation -= glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * deltaTime;
}

void Tank::rotateSphereLeft(float deltaTime) {
	top->rotation += glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * deltaTime;
	}

void Tank::rotateBodyRight(float deltaTime) {
	body->rotation -= glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * deltaTime;
	for (int i = 0; i < wheelsCount; ++i) {
		wheels[i]->rotation -= glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)) * deltaTime;
	}
	
}

void Tank::rotateBodyLeft(float deltaTime) {
	body->rotation += glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * deltaTime;
	for (int i = 0; i < wheelsCount; ++i) {
		wheels[i]->rotation += glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)) * deltaTime;
	}
	
}

void Tank::fire() {
	hasProjectile = true;
}