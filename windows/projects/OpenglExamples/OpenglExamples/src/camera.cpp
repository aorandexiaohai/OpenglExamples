#include "camera.h"

void Camera::moveFront(float elapsed_time)
{
	m_pos += m_speed * m_front;
}
void Camera::moveBack(float elapsed_time)
{
	m_pos -= m_speed * m_front;
}
void Camera::moveLeft(float elapsed_time)
{
	m_pos -= glm::normalize(glm::cross(m_front, m_up)) * m_speed;
}
void Camera::moveRight(float elapsed_time)
{
	m_pos += glm::normalize(glm::cross(m_front, m_up)) * m_speed;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

void Camera::moveAccordingPressList(RenderContext* context, float elapsed_time)
{
	if (context->press_list['w']) {
		this->moveFront(elapsed_time);
	}
	if (context->press_list['s']) {
		this->moveBack(elapsed_time);
	}
	if (context->press_list['a']) {
		this->moveLeft(elapsed_time);
	}
	if (context->press_list['d']) {
		this->moveRight(elapsed_time);
	}
}