//
// Created by notjustin on 12/31/17.
//

#include "Camera.h"

/*
 * _deltaTime is not used, will probably have to be removed
 */
glm::mat4 Camera::getMVP(const float _deltaTime, const glm::mat4 _modelMat) {
    m_transform.rotation = {
            glm::cos(m_fvAngle) * glm::sin(m_fhAngle),
            glm::sin(m_fvAngle),
            glm::cos(m_fvAngle) * glm::cos(m_fhAngle)
    };

    glm::mat4 projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);

    glm::mat4 viewMat;

    if (m_parent) {
        viewMat = glm::lookAt(
                m_absoluteTransform.position,                        // Camera is here
                m_absoluteTransform.position + m_transform.rotation, // and looks here : at the same pos, plus "rotation"
                glm::vec3(0, 1, 0)                     // Head is up (set to 0,-1,0 to look upside-down)
        );
    } else {
        viewMat = glm::lookAt(
                m_transform.position,                        // Camera is here
                m_transform.position + m_transform.rotation, // and looks here : at the same pos, plus "rotation"
                glm::vec3(0, 1, 0)                     // Head is up (set to 0,-1,0 to look upside-down)
        );
    }

    return projMat * viewMat * _modelMat;
}

void Camera::update(const float _deltaTime) {
    GameObject::update(_deltaTime);
}