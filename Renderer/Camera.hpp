#pragma once

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/matrix_access.hpp>
#include<gtc/quaternion.hpp>

enum E_DIRECTION : short
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
private:
	glm::vec3 m_position = glm::vec3(0.f, 0.f, 0.f);
	float m_xAngle = 0.f;
	float m_yAngle = 0.f;
	glm::mat4 m_viewMatrix;
	glm::quat m_rotation;

	static constexpr float MOUSE_SENSITIVTY = 0.05f;
	static constexpr float SPEED = 5.f;

public:
	void Rotate(float dx, float dy)
	{
		m_xAngle += dx;
		m_yAngle += dy;

		glm::quat qx = glm::angleAxis(glm::radians(m_xAngle), glm::vec3(0.f, 1.f, 0.f));
		glm::quat qy = glm::angleAxis(glm::radians(m_yAngle), glm::vec3(1.f, 0.f, 0.f));
		m_rotation = glm::normalize(qx * qy);
	}

	void Move(E_DIRECTION direction, float dt)
	{
		glm::vec3 right = glm::vec3(glm::row(m_viewMatrix, 0));
		glm::vec3 forward = glm::vec3(glm::row(m_viewMatrix, 2));
		glm::vec3 dir;
		
		switch (direction)
		{
		case FORWARD:
			dir = -forward; break;
		case BACKWARD:
			dir = forward; break;
		case LEFT:
			dir = -right; break;
		case RIGHT:
			dir = right; break;
		}

		m_position += dir * dt * SPEED;
	}

	glm::mat4 UpdateView()
	{
		return m_viewMatrix = static_cast<glm::mat4>(m_rotation) * glm::translate(glm::mat4(1.f), -m_position);
	}
};