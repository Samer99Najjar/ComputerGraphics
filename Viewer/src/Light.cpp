#include "Light.h"

Light::Light(const glm::vec3&position) :
	color(glm::vec3(1.0, 1.0, 1.0)),
	position(position)
{
}

Light::Light(const glm::vec3& color, const glm::vec3& position) :
	color(color),
	position(position)
{

}


Light::~Light()
{
}

const glm::vec3& Light::GetColor() const
{
	return color;
}

void Light::SetColor(const glm::vec3& color)
{
	this->color = color;
}
glm::vec3 Light::getpos() {
	glm::vec3 mypos = this->position;
	if (this->position[0] >= 1000000000000000)mypos[0] = 100000000000000;
	if (this->position[1] >= 1000000000000000)mypos[1] = 100000000000000;
	if (this->position[2] >= 1000000000000000)mypos[2] = 100000000000000;
	return mypos;
}
