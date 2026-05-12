#include"Tower.h"
#include<cmath>
sf::Texture cannontex;
sf::Texture snipertex;
sf::Texture machinetex;
class Bullet {
private:
    sf::Vector2f pos;
    sf::Vector2f velocity;
    float speed;
    sf::Vector2f startpos;
    float maxrange;
public:
    bool active;
    Bullet() {
        active = false;
        speed = 300.f;
        maxrange = 200.f;
    }
    void fire(sf::Vector2f start, sf::Vector2f target, float towerrange) {
        pos = start;
        maxrange = towerrange;
        startpos = start;
        sf::Vector2f dir = target - start;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0) {
            dir.x /= len;
            dir.y /= len;
        }
        velocity = { dir.x * speed,dir.y * speed };
        active = true;
    }
    void update(float dt) {
        if (!active) return;

        pos += velocity * dt;
        sf::Vector2f diff = pos - startpos;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (dist >= maxrange) {
            active = false;
        }
    }
    void draw(sf::RenderWindow& window) {
        if (!active) return;

        sf::CircleShape shape(4.f);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition(pos);
        window.draw(shape);
    }
    sf::Vector2f getPos() {
        return pos;

    }
};
class Tower {
protected:
    sf::Vector2f pos;
    float firetimer;

public:
    Tower(float x, float y) :pos(x, y) {
        firetimer = 0.f;
    }

    virtual void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual ~Tower() {

    }
};
class CannonTower : public Tower {
private:
    sf::Sprite sprite;
    float range;
    float firerate;
public:
    CannonTower(float x, float y) : Tower(x, y), sprite(cannontex) {
        range = 140.f;
        firerate = 1.5f;
        sprite.setOrigin({
            cannontex.getSize().x / 2.f,
            cannontex.getSize().y / 2.f
            });
        sprite.setPosition({ x, y });
        sprite.setScale({ 0.25f,0.25f });

    }

    void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) override {
        firetimer += dt;

        if (firetimer >= firerate) {
            for (int i = 0; i < enemycount; i++) {
                if (!enemies[i]) continue;
                sf::Vector2f diff = {
                    enemies[i]->getX() - pos.x,
                    enemies[i]->getY() - pos.y
                };

                float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

                if (dist < range) {

                    for (int b = 0; b < MAX_BULLETS; b++) {
                        if (!bullets[b].active) {
                            bullets[b].fire(pos,
                                { enemies[i]->getX(), enemies[i]->getY() },
                                range);
                            break;
                        }
                    }

                    firetimer = 0.f;
                    return;
                }
            }
        }
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};
class SniperTower : public Tower {
private:
    sf::Sprite sprite;
    float range;
    float firerate;
public:
    SniperTower(float x, float y) : Tower(x, y), sprite(snipertex) {
        range = 250.f;
        firerate = 2.0f;
        sprite.setOrigin({
            snipertex.getSize().x / 2.f,
            snipertex.getSize().y / 2.f
            });
        sprite.setPosition({ x,y });
        sprite.setScale({ 0.25f,0.25f });
    }

    void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) override {
        firetimer += dt;

        if (firetimer >= firerate) {

            int target = -1;
            float maxDist = 0;

            for (int i = 0; i < enemycount; i++) {
                if (!enemies[i]) continue;
                sf::Vector2f diff = {
                    enemies[i]->getX() - pos.x,
                    enemies[i]->getY() - pos.y
                };

                float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

                if (dist < range && dist > maxDist) {
                    maxDist = dist;
                    target = i;
                }
            }

            if (target != -1) {

                for (int b = 0; b < MAX_BULLETS; b++) {
                    if (!bullets[b].active) {
                        bullets[b].fire(pos,
                            { enemies[target]->getX(), enemies[target]->getY() },
                            range);
                        break;
                    }
                }

                firetimer = 0.f;
            }
        }
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};
class MachineGunTower : public Tower {
private:
    sf::Sprite sprite;
    float range;
    float firerate;
public:
    MachineGunTower(float x, float y) : Tower(x, y), sprite(machinetex) {
        range = 110.f;
        firerate = 0.2f;
        sprite.setOrigin({
            machinetex.getSize().x / 2.f,
            machinetex.getSize().y / 2.f
            });
        sprite.setPosition({ x,y });
        sprite.setScale({ 0.25f,0.25f });
    }
    // Fix the MachineGunTower update method:
    void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]) override {
        firetimer += dt;

        if (firetimer >= firerate) {
            for (int i = 0; i < enemycount; i++) {
                if (!enemies[i]) continue;  // ADD THIS CHECK

                sf::Vector2f diff = {
                    enemies[i]->getX() - pos.x,
                    enemies[i]->getY() - pos.y
                };

                float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

                if (dist < range) {
                    for (int b = 0; b < MAX_BULLETS; b++) {
                        if (!bullets[b].active) {
                            bullets[b].fire(pos,
                                { enemies[i]->getX(), enemies[i]->getY() },
                                range);
                            break;
                        }
                    }
                    firetimer = 0.f;
                    return;
                }
            }
        }
    }
    void draw(sf::RenderWindow& window) override {
        window.draw(sprite);
    }
};