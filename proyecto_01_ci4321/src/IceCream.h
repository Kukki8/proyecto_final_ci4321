#ifndef ICECREAM_H
#define ICECREAM_H

#include "Geometry.h"

using namespace std;
const int scoopCount = 3;

class IceCream
{
public:

	IceCream(unsigned int flavor1, unsigned int flavor2, unsigned int flavor3, unsigned int cherryT, unsigned int cone, unsigned int flavor_normal, 
		unsigned int cone_normal, unsigned int cherry_normal);

	void Draw(const Shader& shader);
	void Clear();

	unsigned int flavor1;
	unsigned int flavor2;
	unsigned int flavor3;
	unsigned int cherryT;
	unsigned int cone;
	unsigned int flavor_normal;
	unsigned int cone_normal;
	unsigned int cherry_normal;

	inline glm::vec3 getSize()
	{
		return coneBottom->size;
	};
	inline glm::vec3 getPosition()
	{
		return coneBottom->position;
	};

private:

	Cylinder* coneTop;
	Cylinder* coneBottom;
	Sphere* cherryStalk;
	Sphere* scoops[scoopCount];
	Sphere* cherry;


};




#endif

