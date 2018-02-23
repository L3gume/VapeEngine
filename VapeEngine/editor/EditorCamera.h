//
// Created by l3gume on 22/02/18.
//

#ifndef VAPEENGINE_EDITORCAMERA_H
#define VAPEENGINE_EDITORCAMERA_H

#if EDITOR

#include <input/InputMessage.h>
#include <glm/detail/type_mat.hpp>
#include <VapeGL.h>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/vec3.hpp>
#include <input/InputListener.h>
#include <glm/glm.hpp>

using namespace VapeInput;

class EditorCamera : public InputListener {
public:
    explicit EditorCamera(GLFWwindow* _window) : InputListener(true, true, true, false, true), m_window(_window),
            m_bMoveForward(false), m_bMoveBack(false), m_bMoveLeft(false),
    m_bMoveRight(false), m_bMoveUp(false),
    m_bMoveDown(false), m_bCaptureMoveMovement(false),
    m_bRightClickHeld(false), m_bMiddleClickHeld(false),
    m_bPerspective(true), m_bOrthogonal(false), m_pos(glm::vec3(0.f, 15.f, 15.f)), m_fvAngle(-glm::radians(45.f))
    { /* Default constructor */ }

    /* Getters and Setters, implemented in .h file since its basically nothing */
    inline void setMoveSpeed(float _speed) { m_fSpeed = _speed; }
    inline float getMoveSpeed() const { return m_fSpeed; }
    inline void setMouseSpeed(float _mouse_speed) { m_fMouseSpeed = _mouse_speed; }
    inline float getMouseSpeed() const { return m_fMouseSpeed; }
    inline void setFov(float _fov) { m_fFov = _fov; }
    inline float getFov() const { return m_fFov; }

    void onKeyPressed(const VapeInput::KeyboardInputMessage &_kbdMsg) override;
    void onMouseMoved(const VapeInput::MouseMovedInputMessage &_msMsg) override;
    void onMousePressed(const VapeInput::MouseClickedInputMessage &_msMsg) override;
    void onMouseScrolled(const VapeInput::MouseScrolledInputMessage &_msMsg) override;
    glm::mat4 getMVP(float _deltaTime, glm::mat4 _modelMatrix);
    void update(const float _deltaTime) {
        computeMatricesFromInputs(_deltaTime);
    }

private:
    void computeMatricesFromInputs(float _deltaTime);

    GLFWwindow *m_window;

    glm::vec3 m_pos = glm::vec3(0.f, 0.f, 5.f); // Position of the camera
    glm::vec3 m_rot = glm::vec3(0.f, 0.f, 0.f); // Rotation of the camera
    float m_fhAngle = 3.14f; // horizontal angle
    float m_fvAngle = 0.0f; // vertical angle
    float m_fFov = 90.0f; // Field of view
    float m_fSpeed = 3.0f; // speed of camera, in units per second
    float m_fMaxSpeed = 40.f;
    float m_fMouseSpeed = 0.055f; // Mouse sensitivity
    glm::mat4 m_projMat; // Projection matrix
    glm::mat4 m_viewMat; // View matrix
    glm::mat4 m_rotMat;

    /* Mouse position */
    double m_dMouseXPos = -1.0;
    double m_dMouseYPos = -1.0;

    /* Movement bits */
    bool m_bMoveForward         : 1;
    bool m_bMoveBack            : 1;
    bool m_bMoveLeft            : 1;
    bool m_bMoveRight           : 1;
    bool m_bMoveUp              : 1;
    bool m_bMoveDown            : 1;
    /* Flags */
    bool m_bCaptureMoveMovement : 1; // Indicates whether or not to move the camera with the mouse
    bool m_bRightClickHeld      : 1; // Indicates that the right mouse button is held
    bool m_bMiddleClickHeld     : 1; // Indicates that the scroll wheel button is held
    bool m_bPerspective         : 1; // Perspective view mode
    bool m_bOrthogonal          : 1; // Orthogonal view mode
};

#endif

#endif //VAPEENGINE_EDITORCAMERA_H