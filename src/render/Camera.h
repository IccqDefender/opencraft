#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), float yaw = -90.0f, float pitch = 0.0f);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void update(float deltaTime);

    glm::vec3 getPosition() const { return m_position; };
    float getFov() const { return m_fov; };

private:
    void processKeyboardInput(float deltaTime);
    void processMouseInput(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);
    void updateVectors();

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_movementSpeed = 5.0f;
    float m_mouseSensitivity = 1.0f;
    float m_fov = 70.0f;

    static constexpr float S_MIN_FOV = 1.0f;
    static constexpr float S_MAX_FOV = 90.0f;
    static constexpr float S_NEAR_PLANE = 0.1f;
    static constexpr float S_FAR_PLANE = 1000.0f;
};

#endif // CAMERA_H