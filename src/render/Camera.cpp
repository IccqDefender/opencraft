#include "Camera.h"
#include "../core/Input.h"
#include <GLFW/glfw3.h>
#include <algorithm>

Camera::Camera(glm::vec3 position, float yaw, float pitch)
    : m_position(position)
    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    , m_up(glm::vec3(0.0f, 1.0f, 0.0f))
    , m_right(glm::vec3(1.0f, 0.0f, 0.0f))
    , m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
    , m_yaw(yaw)
    , m_pitch(pitch)
{
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(m_fov), aspectRatio, S_NEAR_PLANE, S_FAR_PLANE);
}

void Camera::update(float deltaTime) {
    processKeyboardInput(deltaTime);

    glm::vec2 mouseDelta = Input::getMouseDelta();
    processMouseInput(mouseDelta.x, -mouseDelta.y);

    float scroll = Input::getScrollDelta();
    if (scroll != 0.0f) {
        processMouseScroll(scroll);
    }
}

void Camera::processKeyboardInput(float deltaTime) {
    float velocity = m_movementSpeed * deltaTime;

    if(Input::isKeyPressed(GLFW_KEY_W)) {
        m_position += m_front * velocity;
    }
    if(Input::isKeyPressed(GLFW_KEY_S)) {
        m_position -= m_front * velocity;
    }
    if(Input::isKeyPressed(GLFW_KEY_A)) {
        m_position -= m_right * velocity;
    }
    if(Input::isKeyPressed(GLFW_KEY_D)) {
        m_position += m_right * velocity;
    }
}

void Camera::processMouseInput(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch) {
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
    }

    updateVectors();
}

void Camera::processMouseScroll(float yoffset) {
    m_fov -= yoffset;
    m_fov = std::clamp(m_fov, S_MIN_FOV, S_MAX_FOV);
}

void Camera::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}