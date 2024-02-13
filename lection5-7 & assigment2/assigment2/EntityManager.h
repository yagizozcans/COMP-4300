//
// Created by Yağız Özcan on 13.02.2024.
//
#include <vector>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string,EntityVec> EntityMap;

class EntityManager {

    friend class Entity;

    EntityVec em_entities;
    EntityVec em_toAddEntities;
    EntityMap em_entityMap;
    size_t em_totalEntities = 0;
public:
    EntityManager()= default;
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
    void update();
};