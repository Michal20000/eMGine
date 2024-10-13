#pragma once
#include "EntityFragment.hpp"
//#include "RendererUtilities.hpp"
#include <glmtypes.hpp>

#ifdef TRANSFORM_AS_CFRAME
using CFrame = Transform;
#endif

class Transform : public EntityFragment<Transform>
{
	public:
	Transform();
	Transform(glm::vec3 position);
	Transform(glm::vec3 position, glm::vec3 rotation);
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	friend class Renderer;
	static void OnCreate(Transform& ob);

	void Translate(glm::vec3 translation);
	void Rotate(glm::vec3 degrees);
	void RotateRadians(glm::vec3 radians);
	void RotateQ(glm::quat quaternion);

	void Position(glm::vec3 position); //set position
	glm::vec3 Position(); //get position

	void Scale(glm::vec3 scale); //set scale
	glm::vec3 Scale(); //get scale
	
	void Rotation(glm::vec3 degrees); //set rotation in degrees
	glm::vec3 Rotation(); //get rotation in degrees

	void RotationRadians(glm::vec3 radians); //set rotation in radians
	glm::vec3 RotationRadians(); //get rotation in radians

	void RotationQ(glm::quat quaternion); //set rotation in quaternion
	glm::quat RotationQ(); //get rotation in quaternion

	glm::mat4 Matrix();

	private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	void NormalizeRotation(glm::vec3& rotation);

};

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/
