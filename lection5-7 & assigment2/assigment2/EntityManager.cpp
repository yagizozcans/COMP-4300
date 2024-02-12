//
// Created by Yağız Özcan on 13.02.2024.
//

#include "EntityManager.h"

void EntityManager::update() {
    for(const auto& e : em_toAddEntities)
    {
        em_entities.push_back(e);
        em_entityMap[e->tag()].push_back(e);
    }
    for(const auto& e : em_entities)
    {
        if(!(e -> isActive()))
        {
            em_entities.erase(std::remove(em_entities.begin(),em_entities.end(),e),em_entities.end());
        }
    }
    em_toAddEntities.clear();
}

EntityVec &EntityManager::getEntities() {
    return em_entities;
}

EntityVec &EntityManager::getEntities(const std::string &tag) {
    auto it = em_entityMap.find(tag);
    return it->second;
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
    auto e = std::make_shared<Entity>(tag,em_totalEntities++);
    em_toAddEntities.push_back(e);
    return e;
}
