#include "camera.h"

void SimpleCamera::moveFront(float elapsed_time)
{
	m_pos += m_speed * m_front;
}
void SimpleCamera::moveBack(float elapsed_time)
{
	m_pos -= m_speed * m_front;
}
void SimpleCamera::moveLeft(float elapsed_time)
{
	m_pos -= glm::normalize(glm::cross(m_front, m_up)) * m_speed;
}
void SimpleCamera::moveRight(float elapsed_time)
{
	m_pos += glm::normalize(glm::cross(m_front, m_up)) * m_speed;
}

glm::mat4 SimpleCamera::getViewMatrix() const
{
	return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

void SimpleCamera::moveAccordingPressList(RenderContext* context, float elapsed_time)
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