#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D normal;
};  

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
};
  
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos; 
  
uniform Material material;

uniform Light light;

void main()
{
    vec3 normal = vec3(texture(material.normal, TexCoord));
    normal = normalize(normal * 2.0 - 1.0);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));

	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));  

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, 1.0);
}