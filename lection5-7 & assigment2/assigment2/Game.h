//
// Created by Yağız Özcan on 13.02.2024.
//
#include "EntityManager.h"
class Game {
    EntityManager em_entities;
    sf::RenderWindow s_window;
    std::shared_ptr<Entity> e_player;
    void init();

    void sRender();
    void sMovement();
    void sCollision();

    void SpawnEnemy();
    void SpawnPlayer();
    void SpawnBullet();

public:
    void run();
};