//
// Created by Yağız Özcan on 13.02.2024.
//

#include "EntityManager.h"
#include <map>
void EntityManager::update() {
    for(const auto& e : em_entities)
    {
        if(e != nullptr)
        {
            if(!(e -> isActive()))
            {
                auto it = std::find(em_entities.begin(),em_entities.end(),e);
                auto itMap = std::find(em_entityMap[e->tag()].begin(),em_entityMap[e->tag()].end(),e);
                em_entityMap[e->tag()].erase(itMap);
                em_entities.erase(it);
            }
        }
    }
    for(const auto& e : em_toAddEntities)
    {
        em_entities.push_back(e);
        em_entityMap[e->tag()].push_back(e);
    }
    em_toAddEntities.clear();
}

EntityVec &EntityManager::getEntities() {
    return em_entities;
}

EntityVec &EntityManager::getEntities(const std::string &tag) {
    return em_entityMap[tag];
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
    auto e = std::make_shared<Entity>(tag,em_totalEntities++);
    e->set_tag(tag);
    em_toAddEntities.push_back(e);
    return e;
}


