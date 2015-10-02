#ifndef LIGHT_H
#define LIGHT_H

#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "core\component.h"
#include "core\transform.h"

/*! \brief Light component
	Illuminates the world through superiour lighting
*/
namespace LightType
{
	enum Type{DIRECTION, POINT, SPOT, LIGHTTYPES};
}
#include <iostream>
class Light : public Component
{
public:
	Light();
	ComponentType::Type getType();
	bool isOnePerObject();

	void linkDependency(SPtr_Component component);

	void setLightType(LightType::Type type);
	void setDiffuse(glm::vec3 diff);
	void setSpecular(glm::vec3 specular);
	void setAtteunation(glm::vec3 atten);
	void setSpotDirection(glm::vec3 dir);
	void setSpotIn(float in);
	void setSpotOut(float out);
	LightType::Type getLightType(){return (LightType::Type)_type;}

	glm::vec3 getDiffuse(){return _diffuse;}
	glm::vec3 getSpecular(){return _specular;}
	glm::vec3 getAtteunation(){return _atteunation;}
	glm::vec3 getSpotDirection(){return _spotDir;}
	float getSpotIn() {return _spotIn;}
	float getSpotOut(){return _spotOut;}
	SPtr_Transform getTransform(){return _transform;}

private:
	SPtr_Transform _transform;

	LightType::Type _type;

	glm::vec3 _diffuse;
	glm::vec3 _specular;

	glm::vec3 _atteunation; //x = constant, y = linear, z = quadratic
	
	GLfloat _constant;
	GLfloat _linear;
	GLfloat _quadratic;

	glm::vec3 _spotDir;
	float _spotIn;
	float _spotOut;
};

typedef std::shared_ptr<Light> SPtr_Light;

#endif