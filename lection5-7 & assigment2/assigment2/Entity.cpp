//
// Created by Yağız Özcan on 13.02.2024.
//
#include "Entity.h"

const std::string Entity::tag() const {
    return e_tag;
}

bool Entity::isActive() const {
    return e_isActive;
}

Entity::Entity(const std::string &tag, size_t id) {
}

const void Entity::set_tag(const std::string& tag) {
    e_tag = tag;
}

const void Entity::destroy() {
    e_isActive = false;
}
