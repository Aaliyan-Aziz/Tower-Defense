#ifndef Enemy_h
#define Enemy_h
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Global.h"
extern sf::Vector2f Path[PATH_POINTS];
extern sf::Vector2f Path[PATH_POINTS];

extern sf::Texture basicEnemyTex;
extern sf::Texture fastEnemyTex;
 extern sf::Texture flyingEnemyTex;

 class Enemy {
 protected:
     sf::Vector2f pos;
     int targetIndex;
     float speed;
     int hp;
     int maxhp;
     bool active;
     sf::Sprite sprite;
     sf::Vector2f* path;
     int pathPoints;
 public:
     bool reachedend = false;

     Enemy(sf::Texture& tex, sf::Vector2f enemyPath[], int totalpoints,
         float enemySpeed, int enemyHp);

     virtual  void update(float dt) = 0;

     virtual void draw(sf::RenderWindow& window) = 0;

     float getX() { return pos.x; }
     float getY() { return pos.y; }

     void damage(int d)
     {
         hp -= d;
     }

     bool isDead()
     {
         return hp <= 0;
     }
     virtual ~Enemy() {};
     friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
 };
 class BasicEnemy : public Enemy {
 public:
     BasicEnemy();
     void update(float dt) override;
     void draw(sf::RenderWindow& window) override;
 };
 class FastEnemy : public Enemy {
 public:
     FastEnemy();
     void update(float dt) override;
     void draw(sf::RenderWindow& window) override;
 };
 class FlyingEnemy : public Enemy {
 public:
     FlyingEnemy();
     void update(float dt) override;
     void draw(sf::RenderWindow& window) override;
 };
#endif