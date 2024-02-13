//
// Created by Yağız Özcan on 13.02.2024.
//

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Game::run() {
    init();
    SpawnPlayer();
    while(s_window.isOpen())
    {
        em_entities.update();
        sf::Event event;
        while(s_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                s_window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                SpawnBullet();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        e_player->cInput->upKey = true;
                        break;
                    case sf::Keyboard::S:
                        e_player->cInput->downKey = true;
                        break;
                    case sf::Keyboard::A:
                        e_player->cInput->leftKey = true;
                        break;
                    case sf::Keyboard::D:
                        e_player->cInput->rightKey = true;
                        break;
                    default:
                        break;
                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code) {
                    case sf::Keyboard::W:
                        e_player->cInput->upKey = false;
                        break;
                    case sf::Keyboard::S:
                        e_player->cInput->downKey = false;
                        break;
                    case sf::Keyboard::A:
                        e_player->cInput->leftKey = false;
                        break;
                    case sf::Keyboard::D:
                        e_player->cInput->rightKey = false;
                        break;
                    default:
                        break;
                }
            }
        }
        SpawnEnemy();
        sMovement();
        sCollision();
        sRender();
    }
}

void Game::SpawnEnemy() {
    auto e = em_entities.addEntity("Enemy");
    e->cTransform = std::make_shared<CTransform>(Vec2(rand() % s_window.getSize().x,rand() % s_window.getSize().y),Vec2(10.0,-2.0),2);
    e->cShape = std::make_shared<CShape>(20,3,sf::Color::Cyan,sf::Color::Red,2);
    e->cCollision = std::make_shared<CCollision>(100);
}

void Game::init() {
    s_window.create(sf::VideoMode(800,600),"ASSIGMENT 2");
    s_window.setFramerateLimit(60);
}

void Game::sRender() {
    s_window.clear(sf::Color::Black);
    for(auto& e : em_entities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x,e->cTransform->pos.y);
        s_window.draw(e->cShape->circle);
    }
    for(auto& e : em_entities.getEntities())
    {
        e->cTransform->pos = Vec2(e->cTransform->vel.x + e->cTransform->pos.x,
                                  e->cTransform->vel.y + e->cTransform->pos.y);
    }
    s_window.display();
}



void Game::sMovement() {
    e_player->cTransform->vel = {0.0,0.0};
    if(e_player->cInput->upKey)
    {
        e_player->cTransform->vel.y = -5;
    }
    if(e_player->cInput->downKey)
    {
        e_player->cTransform->vel.y = 5;
    }
    if(e_player->cInput->rightKey)
    {
        e_player->cTransform->vel.x = 5;
    }
    if(e_player->cInput->leftKey)
    {
        e_player->cTransform->vel.x = -5;
    }

}

void Game::SpawnPlayer() {
    auto e = em_entities.addEntity("Player");
    e->cTransform = std::make_shared<CTransform>(Vec2(s_window.getSize().x/2,s_window.getSize().y/2),Vec2(0.0,0.0),0);
    e->cShape = std::make_shared<CShape>(20,10,sf::Color::Black,sf::Color::Red,2);
    e->cCollision = std::make_shared<CCollision>(20);
    e->cInput = std::make_shared<CInput>();
    e_player = e;
}

void Game::sCollision() {
    for(auto& e : em_entities.getEntities("Enemy"))
    {
        for(auto& b:em_entities.getEntities("Bullet"))
        {
            if((e->cTransform->pos.x - b->cTransform->pos.x) * (e->cTransform->pos.x - b->cTransform->pos.x)
            +  (e->cTransform->pos.y - b->cTransform->pos.y) * (e->cTransform->pos.y - b->cTransform->pos.y)
            < (e->cShape->circle.getRadius() + b->cShape->circle.getRadius()) * (e->cShape->circle.getRadius() + b->cShape->circle.getRadius())
            )
            {
                e->destroy();
                b->destroy();
            }
        }
    }
}

void Game::SpawnBullet() {
    auto e = em_entities.addEntity("Bullet");
    e->set_tag("Bullet");
    e->cTransform = std::make_shared<CTransform>(Vec2(e_player->cTransform->pos.x,e_player->cTransform->pos.y)
            ,Vec2((float)sf::Mouse::getPosition().x - e->cTransform->pos.x
                  ,(float)sf::Mouse::getPosition().y - e->cTransform->pos.y).normalize(),0);
    e->cShape = std::make_shared<CShape>(20,3,sf::Color::Cyan,sf::Color::Red,2);
    e->cCollision = std::make_shared<CCollision>(100.0);
}
