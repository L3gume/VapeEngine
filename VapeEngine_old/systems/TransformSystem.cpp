//
// Created by l3gume on 19/02/18.
//

#include "../core/Engine.h"
#include "../components/TransformComponent.h"
#include "TransformSystem.h"

void TransformSystem::update(float _deltaTime) {
    std::vector<Entity *> entities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
            getComponentTypeID<TransformComponent>());
    std::sort(std::begin(entities), std::end(entities), [](const Entity* A, const Entity* B) {
        return A->getParent() != nullptr && B->getParent() == nullptr;
    });
    for (auto& e : entities) {
        if (!e->getParent()) {
            continue;
        } else {
            assert(e->getParent()->hasComponent<TransformComponent>());
            auto& parent_transform = e->getParent()->getComponent<TransformComponent>();
            auto& transform = e->getComponent<TransformComponent>();

            transform.abs_position = parent_transform.position + glm::quat(parent_transform.rotation) * transform.position;
            transform.abs_rotation = glm::eulerAngles(glm::quat(parent_transform.rotation) * glm::quat(transform.rotation));
            transform.abs_scale = transform.scale * parent_transform.scale;
        }
    }
}
