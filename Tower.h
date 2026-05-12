#ifndef Tower_h
#define Tower_h
#include<SFML/Graphics.hpp>
#include"Global.h"
#include"Enemy.h"
extern sf::Texture cannontex;
extern sf::Texture snipertex;
extern sf::Texture machinetex;
class Bullet {
private:
    sf::Vector2f pos;
    sf::Vector2f velocity;
    float speed;
    sf::Vector2f startpos;
    float maxrange;
public:
    bool active;
    Bullet();
    void fire(sf::Vector2f start, sf::Vector2f target, float towerrange);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPos() const {
        return pos;
    }
};
class Tower {
protected:
    sf::Vector2f pos;
    float firetimer;

public:
    Tower(float x, float y);
    virtual void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Tower(){}
};
class CannonTower : public Tower {
private:
    sf::Sprite sprite;
    float range;
    float firerate;
public:
    CannonTower(float x, float y);
    void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) override;
      
    void draw(sf::RenderWindow& window) override;
};
class SniperTower : public Tower {
private:
    sf::Sprite sprite;
    float range;
    float firerate;
public:
    SniperTower(float x, float y);
    void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) override;           
    void draw(sf::RenderWindow& window) override;
};
class MachineGunTower : public Tower {
private:
    sf::Sprite sprite;
    float range;
    float firerate;
public:
    MachineGunTower(float x, float y);
    void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) override;
    void draw(sf::RenderWindow& window) override;
};
#endif