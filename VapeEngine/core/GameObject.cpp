//
// Created by notjustin on 12/31/17.
//
#include "GameObject.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Core;

void GameObject::update(const float _deltaTime) {
    if (m_parent) {
        Transform *parentTransform = m_parent->getTransform();
        m_absoluteTransform.rotation = parentTransform->rotation;
        m_absoluteTransform.position = parentTransform->position +
                                       (glm::quat(m_absoluteTransform.rotation) * (m_transform.position));
        m_absoluteTransform.scale = m_transform.scale + parentTransform->scale;
    }
    /* Add the rest here */
}

void GameObject::addComponent(Component *_component) {
    m_components.emplace_back(_component);
    if (_component->getParent() != this) {
        _component->setParent(this); // Just in case
    }
}

void GameObject::addChild(GameObject *_child) {
    /*
     * Start by looking up the children list to make we don't add duplicate objects
     */
    bool _found = false;
    if (!_child->getTag().empty()) {
        if (const GameObject *found = findChildByTag(_child->getTag());
        found != nullptr) {
            _found = true;
        }
    } else if (!_child->getID()) { // equal to 0
        if (const GameObject *found = findChildByID(_child->getID());
        found != nullptr) {
            _found = true;
        }
    }

    /*
     * If it wasn't found, add it to children.
     */
    if (!_found) {
        _child->setParent(this); // Just in case
        m_children.emplace_back(_child);
    } else {
        // Does nothing in release build!
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::GAME, VapeLog::LogType::WARNING,
                VapeLog::LogSeverity::MODERATE,
                "This object is already a child, it was not added."));
#endif
    }
}


// TODO