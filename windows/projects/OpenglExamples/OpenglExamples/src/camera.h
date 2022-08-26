#pragma once
#include "render.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
  private:
    glm::vec3 m_pos{}; //位置
    float m_pitch{};   //俯仰角 [-89, 89]
    float m_yaw{};     //偏航角
    float m_move_speed{};
    float m_rotate_speed{};

    static const constexpr glm::vec3 CONST_CAMERA_FRONT = {0.0f, 0.0f, -1.0f};
    static const constexpr glm::vec3 CONST_CAMERA_UP = {0.0f, 1.0f, 0.0f};

  public:
    Camera(const glm::vec3 pos = {}, float pitch = {}, float yaw = {}, float move_speed = 2.5f,
           float rotate_speed = 10.0f);

    glm::mat4 getViewMatrix() const;

    glm::vec3 getCameraFront() const;

    glm::vec3 getCameraUp() const;

    void moveFront(float elapsed_time);

    void moveBack(float elapsed_time);

    void moveLeft(float elapsed_time);

    void moveRight(float elapsed_time);

    void pitchUp(float elapsed_time);

    void pitchDown(float elapsed_time);

    void yawRight(float elapsed_time);

    void yawLeft(float elapsed_time);

    void update(RenderContext *context);

  private:
    glm::mat4 getCameraRotateMatrix() const
    {
        glm::mat4 m(1.0f);
        m = glm::rotate(m, glm::radians(m_pitch), glm::vec3(1, 0, 0));
        return glm::rotate(m, glm::radians(m_yaw), glm::vec3(0, 1, 0));
    }

    void clampPitch()
    {
        if (m_pitch > 89.0f)
        {
            m_pitch = 89.0f;
        }
        else if (m_pitch < -89.0f)
        {
            m_pitch = -89.0f;
        }
    }
};