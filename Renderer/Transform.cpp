#include "Transform.hpp"

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

//TO DELETE
#include <iomanip>

Transform::Transform() :
	m_Position(glm::vec3(0.0f)),
	m_Rotation(glm::vec3(0.0f)),
	m_Scale(glm::vec3(1.0f))
{
	LOG(std::endl << std::fixed << std::setprecision(7));
	LOG_DEBUG("Transform constructor:");
	LOG_DEBUG("Position: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z);
	LOG_DEBUG("Rotation: " << m_Rotation.x << ", " << m_Rotation.y << ", " << m_Rotation.z);
	LOG_DEBUG("Scale: " << m_Scale.x << ", " << m_Scale.y << ", " << m_Scale.z);
	LOG_DEBUG("End of Transform constructor;");
	LOG(std::defaultfloat << std::endl);
}

Transform::Transform(glm::vec3 position) :
	m_Position(position),
	m_Rotation(glm::vec3(0.0f)),
	m_Scale(glm::vec3(1.0f))

{}

Transform::Transform(glm::vec3 position, glm::vec3 rotation) :
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(glm::vec3(1.0f))
{}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(scale)
{}

void Transform::OnCreate(Transform& ob)
{
	ob.m_Position = glm::vec3(0.0f);
	ob.m_Rotation = glm::vec3(0.0f);
	ob.m_Scale = glm::vec3(1.0f);

}

void Transform::Translate(glm::vec3 translation)
{
	m_Position += translation;
}

void Transform::Rotate(glm::vec3 degrees)
{
	m_Rotation += degrees;
	NormalizeRotation(m_Rotation);

}

void Transform::RotateRadians(glm::vec3 radians)
{
	m_Rotation += glm::degrees(radians);
	NormalizeRotation(m_Rotation);

}

void Transform::RotateQ(glm::quat quaternion)
{
	m_Rotation += glm::degrees(glm::eulerAngles(quaternion));
	NormalizeRotation(m_Rotation);

}

void Transform::Position(glm::vec3 position)
{
	m_Position = position;
}

glm::vec3 Transform::Position()
{
	return m_Position;
}

void Transform::Scale(glm::vec3 scale)
{
	m_Scale = scale;
}

glm::vec3 Transform::Scale()
{
	return m_Scale;
}

void Transform::Rotation(glm::vec3 rotation) //set rotation in Degrees
{
	m_Rotation = rotation;
	NormalizeRotation(m_Rotation);

}

glm::vec3 Transform::Rotation() //get rotation in Degrees
{
	return m_Rotation;
}

void Transform::RotationRadians(glm::vec3 radians) //set rotation in radians
{
	m_Rotation = glm::degrees(radians);
	NormalizeRotation(m_Rotation);

}

glm::vec3 Transform::RotationRadians() //get rotation in Euler angles
{
	return glm::radians(m_Rotation);
}


void Transform::RotationQ(glm::quat quaternion) //set rotation in quaternion
{
	m_Rotation = glm::degrees(glm::eulerAngles(quaternion));
	NormalizeRotation(m_Rotation);

}

glm::quat Transform::RotationQ()  //get rotation in quaternion
{
	return glm::quat(glm::radians(m_Rotation));
}

void Transform::NormalizeRotation(glm::vec3& rotation) //set rotation in range [0, 360)
{
	rotation = glm::mod(rotation, glm::vec3(360.0f));

    LOG("rotation x: " << rotation.x);
    LOG("rotation y: " << rotation.y);
    LOG("rotation z: " << rotation.z);

}

glm::mat4 Transform::Matrix()
{
	{ //TO DELETE
		LOG(std::endl << std::fixed << std::setprecision(7));
		LOG_DEBUG("Position: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z);
		LOG_DEBUG("Rotation: " << m_Rotation.x << ", " << m_Rotation.y << ", " << m_Rotation.z);
		LOG_DEBUG("Scale: " << m_Scale.x << ", " << m_Scale.y << ", " << m_Scale.z);
	}
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, m_Position);
	matrix = glm::rotate(matrix, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::rotate(matrix, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::scale(matrix, m_Scale);
	{ //TO DELETE
		LOG_DEBUG("Transformation matrix:");
		for (int16_t i=0; i<4; ++i)
			LOG_VERBOSE("[" << matrix[0][i] << "] " <<
						"[" << matrix[1][i] << "] " <<
						"[" << matrix[2][i] << "] " <<
						"[" << matrix[3][i] << "]");
		LOG(std::defaultfloat << std::endl);
	}
	return matrix;

}

/*

╔══════════════════════════════════════╗
║ Created by Grzegorz Dombrowski, 2024 ║
╚══════════════════════════════════════╝

*/