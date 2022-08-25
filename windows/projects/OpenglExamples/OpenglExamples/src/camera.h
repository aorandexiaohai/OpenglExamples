#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "render.h"
class SimpleCamera
{
public:
	glm::vec3 m_pos{};
	glm::vec3 m_front{};
	glm::vec3 m_up{};
	float m_speed{};

	void moveFront(float elapsed_time);
	void moveBack(float elapsed_time);
	void moveLeft(float elapsed_time);
	void moveRight(float elapsed_time);
	glm::mat4 getViewMatrix() const;
	void moveAccordingPressList(RenderContext* context, float elapsed_time);
};