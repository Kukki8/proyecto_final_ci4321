#include "IceCream.h"

IceCream::IceCream(unsigned int flavor1, unsigned int flavor2, unsigned int flavor3, unsigned int cherryT,unsigned int cone, unsigned int flavor_normal, unsigned int cone_normal, unsigned int cherry_normal)
{
	this->flavor1 = flavor1;
	this->flavor2 = flavor2;
	this->flavor3 = flavor3;
	this->cherryT = cherryT;
	this->cone = cone;
	this->flavor_normal = flavor_normal;
	this->cone_normal = cone_normal;
	this->cherry_normal = cherry_normal;

	coneBottom = new Cylinder(0.1, 0.2, 1.0);
	glm::vec3 bottomPos = glm::vec3(5.0f, 0.0f, 0.0f);
	coneBottom->SetPosition(bottomPos);
	coneBottom->SetRotation(glm::vec3(glm::radians(-90.0), 0.0f, 0.0f));
	coneBottom->Load();

	glm::vec3 topPos = coneBottom->position + glm::vec3(0.0f, 1.5f, -1.0f);
	coneTop = new Cylinder(0.2, 0.25, 0.1);
	coneTop->SetPosition(topPos);
	coneTop->SetRotation(glm::vec3(glm::radians(-90.0), 0.0f, 0.0f));
	coneTop->Load();

	for (int i = 0; i < scoopCount; i++) {

		glm::vec3 scoopPos = coneTop->position;

		switch (i)
		{
		case 0:
			scoopPos += glm::vec3(0.0, coneTop->height + 0.15, 0.0);
			break;
		case 1:
			scoopPos += glm::vec3(0.05, coneTop->height + 0.5, -0.05);
			break;
		case 2:
			scoopPos += glm::vec3(-0.05, coneTop->height + 0.85, 0);
			break;
		}

		scoops[i] = new Sphere(.3);
		scoops[i]->SetPosition(scoopPos);
		scoops[i]->SetRotation(glm::vec3(0.0, glm::radians(90.0), 0.0));

		scoops[i]->Load();

	}

	glm::vec3 cherryPos = coneTop->position + glm::vec3(0.0f, 1.25f, 0.0f);
	cherry = new Sphere(0.1f);
	cherry->SetPosition(cherryPos);
	cherry->Load();
}

void IceCream::Draw(const Shader& shader)
{
	coneBottom->Bind(cone, cone_normal);
	coneBottom->DrawCanon(shader);

	coneTop->Bind(cone, cone_normal);
	coneTop->Draw(shader);

	cherry->Bind(cherryT, cherry_normal);
	cherry->Draw(shader);

	for (int i = 0; i < scoopCount; i++) {

		switch (i)
		{
		case 0:
			scoops[i]->Bind(flavor1, flavor_normal);
			break;
		case 1:
			scoops[i]->Bind(flavor2, flavor_normal);
			break;
		case 2: 
			scoops[i]->Bind(flavor3, flavor_normal);
			break;
		}

		scoops[i]->Draw(shader);
	}
}

void IceCream::Clear()
{
	coneBottom->Clean();
	coneTop->Clean();
	cherry->Clean();

	for (int i = 0; i < scoopCount; i++) {

		scoops[i]->Clean();

	}

}
