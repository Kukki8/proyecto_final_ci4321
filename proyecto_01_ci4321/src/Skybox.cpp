#include "Skybox.h"
#include "stb_image/stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Skybox::Skybox()
{

}

void Skybox::Load(vector<std::string> faces)
{
	LoadTexture(faces);
	box = new Cubemap();
	box->Load();

}

void Skybox::LoadTexture(vector<std::string> faces)
{
	stbi_set_flip_vertically_on_load(0);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

};

void Skybox::Draw(Shader& shader, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, glm::mat4 projection)
{
	rotationAngle += 0.01f;
	box->SetRotation(glm::vec3(0.0, glm::radians(rotationAngle), 0.0));

	glDepthFunc(GL_LEQUAL);
	shader.use();

	glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(
		cameraPos,
		cameraPos + cameraFront,
		cameraUp
	)));

	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	box->Bind(textureID,0);
	box->Draw(shader);

	glDepthFunc(GL_LESS);

}
