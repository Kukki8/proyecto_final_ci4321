#ifndef SKYBOX_H
#define SKYBOX_H

#include "Geometry.h"

class Skybox 
{
public:


	Skybox();
	void Load(vector<std::string> faces);
	void Draw(Shader& shader, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, glm::mat4 projection);

private:
	Cubemap* box;
	unsigned int textureID;
	float rotationAngle = 0.0f;
	void LoadTexture(vector<std::string> faces);
};


#endif