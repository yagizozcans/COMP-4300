//
// Created by Yağız Özcan on 13.02.2024.
//
#include "Entity.h"

const std::string Entity::tag() const {
    return e_tag;
}

const bool Entity::isActive() const {
    return e_isActive;
}
