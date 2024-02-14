//
// Created by Yağız Özcan on 13.02.2024.
//

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#define PI 3.141592654



void Game::run(const std::string& config) {
    init(config);

    while(s_window.isOpen())
    {
        em_entities.update();
        sf::Event event;

        deltaTime = deltaClock.restart();
        dtSeconds = deltaTime.asSeconds();

        while(s_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                s_window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    SpawnBullet(Vec2((float)event.mouseButton.x,(float)event.mouseButton.y));
                }
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
        sRender();
        sEnemySpawner();
        sMovement();
        sCollision();
    }
}

void Game::init(const std::string& path) {

    std::ifstream fin(path);

    fin >> g_windowConfig.W >> g_windowConfig.H >> g_windowConfig.FL >> g_windowConfig.AA;
    fin >> g_fontConfig.path >> g_fontConfig.FS >> g_fontConfig.FG >> g_fontConfig.FR >> g_fontConfig.FB;
    fin >> g_playerConfig.SR >> g_playerConfig.CR >> g_playerConfig.FR >> g_playerConfig.FG>> g_playerConfig.FB >> g_playerConfig.OR >> g_playerConfig.OG >> g_playerConfig.OB >> g_playerConfig.OT >> g_playerConfig.V >> g_playerConfig.S;
    fin >> g_enemyConfig.SR >> g_enemyConfig.CR>> g_enemyConfig.SMIN >> g_enemyConfig.SMAX >> g_enemyConfig.OR >> g_enemyConfig.OG >> g_enemyConfig.OB>>g_enemyConfig.OT>>g_enemyConfig.VMIN>>g_enemyConfig.VMAX>>g_enemyConfig.L>>g_enemyConfig.SP;
    fin >> g_bulletConfig.SR >> g_bulletConfig.CR >> g_bulletConfig.S >> g_bulletConfig.FR >> g_bulletConfig.FG >> g_bulletConfig.FB >> g_bulletConfig.OR >> g_bulletConfig.OG >> g_bulletConfig.OB >> g_bulletConfig.OT >> g_bulletConfig.V >> g_bulletConfig.L;


    s_window.create(sf::VideoMode(g_windowConfig.W,g_windowConfig.H),"ASSIGMENT 2");
    s_window.setFramerateLimit(g_windowConfig.FL);
    if(!font.loadFromFile(g_fontConfig.path)){}
    scoreText.setFont(font);
    scoreText.setCharacterSize(g_fontConfig.FS);
    scoreText.setFillColor(sf::Color(g_fontConfig.FR,g_fontConfig.FG,g_fontConfig.FB));
    scoreText.setPosition(10,10);
    scoreText.setString("0");
    SpawnPlayer();
}

void Game::sRender() {
    s_window.clear(sf::Color::Black);
    for(auto& e : em_entities.getEntities())
    {
        if(e->cLifespan != nullptr)
        {
            if(e->cLifespan->total != 0)
            {
                e->cLifespan->remaining -= dtSeconds;
                e->cShape->circle.setFillColor(sf::Color(e->cShape->circle.getFillColor().r,e->cShape->circle.getFillColor().g,e->cShape->circle.getFillColor().b,255*(e->cLifespan->remaining / e->cLifespan->total)));
                e->cShape->circle.setOutlineColor(sf::Color(e->cShape->circle.getOutlineColor().r,e->cShape->circle.getOutlineColor().g,e->cShape->circle.getOutlineColor().b,255*(e->cLifespan->remaining / e->cLifespan->total)));
                if(e->cLifespan->remaining <= 0)
                {
                    e->destroy();
                }
            }
        }
        if(e->cTransform->pos.x - e->cShape->circle.getRadius() <= 0 && e->cTransform->vel.x < 0)
        {
            e->cTransform->vel.x = -e->cTransform->vel.x;
        }
        if(e->cTransform->pos.x + e->cShape->circle.getRadius() >= s_window.getSize().x && e->cTransform->vel.x > 0)
        {
            e->cTransform->vel.x = -e->cTransform->vel.x;
        }
        if(e->cTransform->pos.y - e->cShape->circle.getRadius() <= 0 && e->cTransform->vel.y < 0)
        {
            e->cTransform->vel.y = -e->cTransform->vel.y;
        }
        if(e->cTransform->pos.y + e->cShape->circle.getRadius() >= s_window.getSize().y && e->cTransform->vel.y > 0)
        {
            e->cTransform->vel.y = -e->cTransform->vel.y;
        }
        e->cTransform->pos = Vec2(e->cTransform->vel.x + e->cTransform->pos.x,
                                  e->cTransform->vel.y + e->cTransform->pos.y);
    }
    for(auto& e : em_entities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x,e->cTransform->pos.y);
        e->cShape->circle.rotate(e->cTransform->angle);
        s_window.draw(e->cShape->circle);
    }
    scoreText.setString(std::to_string(score));
    s_window.draw(scoreText);
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
    e->cTransform = std::make_shared<CTransform>(Vec2(s_window.getSize().x/2,s_window.getSize().y/2),Vec2(0.0,0.0),2);
    e->cShape = std::make_shared<CShape>(g_playerConfig.SR,g_playerConfig.V,sf::Color(g_playerConfig.FR,g_playerConfig.FG,g_playerConfig.FB),sf::Color(g_playerConfig.OR,g_playerConfig.OG,g_playerConfig.OB),g_playerConfig.OT);
    e->cCollision = std::make_shared<CCollision>(g_playerConfig.CR);
    e->cInput = std::make_shared<CInput>();
    e_player = e;
}

void Game::SpawnEnemy(const Vec2& vel,const Vec2& pos,const float radius,const float pointCount,const float lifeTime) {
    auto e = em_entities.addEntity("Enemy");
    e->cTransform = std::make_shared<CTransform>(Vec2(pos.x,pos.y),Vec2(vel.x,vel.y),2);
    e->cShape = std::make_shared<CShape>(radius,pointCount,sf::Color::Cyan,sf::Color::Red,2);
    e->cCollision = std::make_shared<CCollision>(radius);
    e->cLifespan = std::make_shared<CLifespan>(lifeTime);
    e->cScore = std::make_shared<CScore>(pointCount * 100);
}

void Game::SpawnBullet(const Vec2& mousePos) {
    auto e = em_entities.addEntity("Bullet");
    Vec2 speed = Vec2(mousePos.x-e_player->cTransform->pos.x,mousePos.y-e_player->cTransform->pos.y);
    e->cTransform = std::make_shared<CTransform>(Vec2(e_player->cTransform->pos.x,e_player->cTransform->pos.y),speed.normalize() * g_bulletConfig.S,0);
    e->cShape = std::make_shared<CShape>(g_bulletConfig.SR,g_bulletConfig.V,sf::Color(g_bulletConfig.FR,g_bulletConfig.FG,g_bulletConfig.FB),sf::Color(g_bulletConfig.FG,g_bulletConfig.FG,g_bulletConfig.FB),g_bulletConfig.OT);
    e->cCollision = std::make_shared<CCollision>(g_bulletConfig.CR);
    std::cout<<g_bulletConfig.L;
    e->cLifespan = std::make_shared<CLifespan>(g_bulletConfig.L);
}

void Game::sCollision() {
    for(auto& e : em_entities.getEntities("Enemy"))
    {
        for(auto& b:em_entities.getEntities("Bullet"))
        {
            if(b->isActive())
            {
                bool isCollided =
                        (e->cTransform->pos.x - b->cTransform->pos.x) * (e->cTransform->pos.x - b->cTransform->pos.x)
                        +  (e->cTransform->pos.y - b->cTransform->pos.y) * (e->cTransform->pos.y - b->cTransform->pos.y)
                        <= (e->cShape->circle.getRadius() + b->cShape->circle.getRadius()) * (e->cShape->circle.getRadius() + b->cShape->circle.getRadius());
                if(isCollided)
                {
                    b->destroy();
                    e->destroy();
                    score += e->cScore->score;
                    if(e->cLifespan->total == 0)
                    {
                        for(int i = 0; i < e->cShape->circle.getPointCount(); i++)
                        {
                            float rad = (360/(int)e->cShape->circle.getPointCount()) * i * PI / 180;
                            float xVel = (cosf(rad));
                            float yVel = (sinf(rad));
                            SpawnEnemy(Vec2(xVel * 2,yVel * 2),Vec2(e->cTransform->pos.x,e->cTransform->pos.y),e->cShape->circle.getRadius(),e->cShape->circle.getPointCount(),g_enemyConfig.L);
                        }
                    }
                }
            }
        }
        if((e->cTransform->pos.x - e_player->cTransform->pos.x) * (e->cTransform->pos.x - e_player->cTransform->pos.x)
                                                        +  (e->cTransform->pos.y - e_player->cTransform->pos.y) * (e->cTransform->pos.y - e_player->cTransform->pos.y)
                                                        <= (e->cShape->circle.getRadius() + e_player->cShape->circle.getRadius()) * (e->cShape->circle.getRadius() + e_player->cShape->circle.getRadius()))
        {
            e_player->cTransform->pos = Vec2(s_window.getSize().x / 2,s_window.getSize().y / 2);
            score = 0;
        }
    }
}



void Game::sEnemySpawner() {
    elapsedTime = s_clock.getElapsedTime().asSeconds();
    if(elapsedTime >= g_enemyConfig.SP)
    {
        SpawnEnemy(Vec2(g_enemyConfig.SMIN+((float)rand()) / RAND_MAX * (g_enemyConfig.SMAX-g_enemyConfig.SMIN),
                        g_enemyConfig.SMIN+((float)rand()) / RAND_MAX * ((g_enemyConfig.SMAX-g_enemyConfig.SMIN))),
                   Vec2(rand() % s_window.getSize().x,rand() % s_window.getSize().y),
                   g_enemyConfig.SR,g_enemyConfig.VMIN + rand() % (g_enemyConfig.VMIN - g_enemyConfig.VMAX),0);
        s_clock.restart();
    }
}
