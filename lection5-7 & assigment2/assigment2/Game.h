//
// Created by Yağız Özcan on 13.02.2024.
//
#include "EntityManager.h"

struct PlayerConfig {int SR,CR,FR,FG,FB,OR,OG,OB,OT,V;float S;};
struct EnemyConfig {int SR,CR,OG,OR,OB,OT,VMIN,VMAX,SP;float L,SMIN,SMAX;};
struct BulletConfig {int SR,CR,FR,FG,FB,OR,OG,OB,OT,V;float L,S;};
struct WindowConfig {int W,H,FL,AA;};
struct FontConfig {std::string path; int FS,FR,FG,FB;};

class Game {
    EntityManager em_entities;
    sf::RenderWindow s_window;
    std::shared_ptr<Entity> e_player;

    sf::Clock s_clock;
    float elapsedTime = 0.0f;

    sf::Clock deltaClock;
    sf::Time deltaTime;
    float dtSeconds = 0;

    int score = 0;
    sf::Font font;
    sf::Text scoreText;

    void init(const std::string& path);

    void sRender();
    void sMovement();
    void sCollision();
    void sEnemySpawner();

    PlayerConfig g_playerConfig;
    FontConfig g_fontConfig;
    EnemyConfig g_enemyConfig;
    WindowConfig g_windowConfig;
    BulletConfig g_bulletConfig;

    void SpawnEnemy(const Vec2& vel,const Vec2& pos,const float radius,const float pointCount,const float lifeTime);
    void SpawnPlayer();
    void SpawnBullet(const Vec2& mousePos);

public:
    void run(const std::string& config);
};