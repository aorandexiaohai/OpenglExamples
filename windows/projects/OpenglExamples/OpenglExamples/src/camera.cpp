#include "camera.h"

Camera::Camera(const glm::vec3 pos, float pitch, float yaw, float move_speed, float rotate_speed)
{
    m_pos = pos;
    m_pitch = pitch;
    m_yaw = yaw;
    m_move_speed = move_speed;
    m_rotate_speed = rotate_speed;
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(m_pos, m_pos + getCameraFront(), getCameraUp());
}

glm::vec3 Camera::getCameraFront() const
{
    return getCameraRotateMatrix() * glm::vec4(CONST_CAMERA_FRONT, 1.0f);
}

glm::vec3 Camera::getCameraUp() const
{
    return getCameraRotateMatrix() * glm::vec4(CONST_CAMERA_UP, 1.0f);
}

void Camera::moveFront(float elapsed_time)
{
    m_pos += m_move_speed * getCameraFront();
}
void Camera::moveBack(float elapsed_time)
{
    m_pos -= m_move_speed * getCameraFront();
}
void Camera::moveLeft(float elapsed_time)
{
    m_pos -= glm::normalize(glm::cross(getCameraFront(), getCameraUp())) * m_move_speed;
}
void Camera::moveRight(float elapsed_time)
{
    m_pos += glm::normalize(glm::cross(getCameraFront(), getCameraUp())) * m_move_speed;
}

void Camera::pitchUp(float elapsed_time)
{
    m_pitch += elapsed_time * m_rotate_speed;
    clampPitch();
}
void Camera::pitchDown(float elapsed_time)
{
    m_pitch -= elapsed_time * m_rotate_speed;
    clampPitch();
}

void Camera::yawRight(float elapsed_time)
{
    m_yaw += elapsed_time * m_rotate_speed;
}

void Camera::yawLeft(float elapsed_time)
{
    m_yaw -= elapsed_time * m_rotate_speed;
}

void Camera::update(RenderContext *context)
{
    auto elapsed_time = context->elapsed_time;
    if (context->press_list['w'])
    {
        this->moveFront(elapsed_time);
    }
    if (context->press_list['s'])
    {
        this->moveBack(elapsed_time);
    }
    if (context->press_list['a'])
    {
        this->moveLeft(elapsed_time);
    }
    if (context->press_list['d'])
    {
        this->moveRight(elapsed_time);
    }

    if (context->isMoveDown())
    {
        this->pitchDown(elapsed_time * context->yDiff());
    }
    if (context->isMoveUp())
    {
        this->pitchUp(elapsed_time * context->yDiff());
    }

    if (context->isMoveLeft())
    {
        this->yawLeft(elapsed_time * context->xDiff());
    }
    if (context->isMoveRight())
    {
        this->yawRight(elapsed_time * context->xDiff());
    }
}
