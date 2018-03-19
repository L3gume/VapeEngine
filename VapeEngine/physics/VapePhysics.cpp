#include <physics/VapePhysics.h>

void physics::applyImpulse(RigidBodyComponent& _target, glm::vec3 _direction, const float _magnitude) {
    glm::vec3 last_accel = _target.accel; // get the previous acceleration
    glm::vec3 new_accel = (_direction * _magnitude) / _target.mass; // compute the new acceleration using Newton's second law
    _target.accel = (last_accel + new_accel) / 2.f; // update the acceleration with average
    _target.velocity += _target.accel; // update velocity, position will be update in the system
}

void physics::applyForce(RigidBodyComponent& _target, glm::vec3 _direction, const float _magnitude, const float _deltaTime) {
    glm::vec3 last_accel = _target.accel; // get the previous acceleration
    glm::vec3 new_accel = (_direction * _magnitude) / _target.mass; // compute the new acceleration using Newton's second law
    _target.accel = (last_accel + new_accel) / 2.f; // update the acceleration with average
    _target.velocity += _target.accel * _deltaTime; // update velocity, position will be update in the system
}
