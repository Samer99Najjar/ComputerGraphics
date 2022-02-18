#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	Light(const glm::vec3& position);
	Light(const glm::vec3& color, const glm::vec3& position);
	virtual ~Light();

	const glm::vec3& GetColor()  const;
	void SetColor(const glm::vec3& color);
	void changepos(float num, int index);

	glm::vec3 color;
	glm::vec3 position;
	glm::vec4 ambient_color = glm::vec4(1, 1, 1, 1.00f);
	glm::vec4 spec_color = glm::vec4(1, 1, 1, 1.00f);
	glm::vec4 diff_color = glm::vec4(1, 1, 1, 1.00f);
	glm::vec3 Light::getpos();
	bool ambient = true, diffuse = false, specular = false, show_ref = false;
	bool flat = false, gour = false, phong = false;


	//bool ambient = true, diffuse = false, specular = false, diffuse_gro = false, diffuse_flat = false,show_ref=false;
	


};