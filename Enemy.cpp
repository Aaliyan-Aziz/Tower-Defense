#include"Enemy.h"
#include<cmath>
sf::Vector2f Path[PATH_POINTS] = {
    {260.f, 10.f},
    {260.f, 170.f},
    {300.f, 170.f},
    {380.f, 190.f},
    {350.f,250.f},
    {360.f,270.f},
    {400.f, 290.f},
    {460.f, 330.f},
    {455.f, 350.f},
    {400.f, 400.f},
    {390.f, 410.f},
    {400.f,450.f},
    {450.f, 460.f},
    {500.f,440.f},
    {550.f, 410.f},
    {620.f, 460.f}
};
sf::Vector2f airpath[AIR_PATH_POINTS] = {
     {50.f,50.f},
    {80.f,80.f},
    {140.f,100.f},
    {180.f,140.f},
    {240.f,180.f},
    {300.f,240.f},
    {380.f,300.f},
    {460.f,340.f},
    {540.f,400.f},
    {620.f,460.f}
};
sf::Texture basicEnemyTex;
sf::Texture fastEnemyTex;
sf::Texture flyingEnemyTex;
 
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
        float enemySpeed, int enemyHp) : sprite(tex) {
        path = enemyPath;
        pathPoints = totalpoints;

        pos = path[0];
        targetIndex = 1;
        speed = enemySpeed;
        hp = enemyHp;
        maxhp = enemyHp;
        active = true;
        sprite.setScale({ 0.15f,0.15f });
        sprite.setOrigin({
            tex.getSize().x / 2.f,
            tex.getSize().y / 2.f
            });
        sprite.setPosition(pos);
        std::cout << "Enemy created with the path " << pathPoints << " \n";
    }

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
std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Enemy at (" << enemy.pos.x << "," << enemy.pos.y << ") HP: " << enemy.hp << "/" << enemy.maxhp;
    return os;
}
class BasicEnemy : public Enemy {
public:

    BasicEnemy() : Enemy(basicEnemyTex, Path, PATH_POINTS, 100.f, 100) {}
    void update(float dt) override {
        if (targetIndex >= pathPoints) {  // Use path.size()
            reachedend = true;
            return;
        }

        sf::Vector2f dir = path[targetIndex] - pos;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len < 5.f) {
            targetIndex++;
        }
        else {
            dir /= len;
            pos += dir * speed * dt;
            sprite.setPosition(pos);
        }
        if (targetIndex >= pathPoints) {
            reachedend = true;
            std::cout << "Enemy reached end at index " << targetIndex << " size " << pathPoints << std::endl;
            return;
        }
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);

        float ratio = (float)hp / (float)maxhp;

        if (ratio < 0)
            ratio = 0;

        sf::RectangleShape bg({ 30.f,5.f });
        bg.setFillColor(sf::Color::Red);

        bg.setPosition({
            pos.x - 15.f,
            pos.y - 20.f
            });

        sf::RectangleShape hpbar({ 30.f * ratio,5.f });
        hpbar.setFillColor(sf::Color::Green);

        hpbar.setPosition({
            pos.x - 15.f,
            pos.y - 20.f
            });

        window.draw(bg);
        window.draw(hpbar);
    }
};
class FastEnemy : public Enemy {
public:

    FastEnemy() : Enemy(fastEnemyTex, Path, PATH_POINTS, 180.f, 60) {}
    void update(float dt) override {
        if (targetIndex >= pathPoints) {  // Use path.size()
            reachedend = true;
            return;
        }

        sf::Vector2f dir = path[targetIndex] - pos;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len < 5.f) {
            targetIndex++;
        }
        else {
            dir /= len;
            pos += dir * speed * dt;
            sprite.setPosition(pos);
        }
        if (targetIndex >= pathPoints) {
            reachedend = true;
            std::cout << "Enemy reached end at index " << targetIndex << " size " << pathPoints << std::endl;
            return;
        }
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);

        float ratio = (float)hp / (float)maxhp;

        if (ratio < 0)
            ratio = 0;

        sf::RectangleShape bg({ 30.f,5.f });
        bg.setFillColor(sf::Color::Red);

        bg.setPosition({
            pos.x - 15.f,
            pos.y - 20.f
            });

        sf::RectangleShape hpbar({ 30.f * ratio,5.f });
        hpbar.setFillColor(sf::Color::Green);

        hpbar.setPosition({
            pos.x - 15.f,
            pos.y - 20.f
            });

        window.draw(bg);
        window.draw(hpbar);
    }
};
class FlyingEnemy : public Enemy {
public:

    FlyingEnemy() : Enemy(flyingEnemyTex, airpath, AIR_PATH_POINTS, 140.f, 80) {}
    void update(float dt) override {
        if (targetIndex >= pathPoints) {  // Use path.size()
            reachedend = true;
            return;
        }

        sf::Vector2f dir = path[targetIndex] - pos;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len < 5.f) {
            targetIndex++;
        }
        else {
            dir /= len;
            pos += dir * speed * dt;
            sprite.setPosition(pos);
        }
        if (targetIndex >= pathPoints) {
            reachedend = true;
            std::cout << "Enemy reached end at index " << targetIndex << " size " << pathPoints << std::endl;
            return;
        }
    }
    void draw(sf::RenderWindow& window) override
    {
        window.draw(sprite);

        float ratio = (float)hp / (float)maxhp;

        if (ratio < 0)
            ratio = 0;

        sf::RectangleShape bg({ 30.f,5.f });
        bg.setFillColor(sf::Color::Red);

        bg.setPosition({
            pos.x - 15.f,
            pos.y - 20.f
            });

        sf::RectangleShape hpbar({ 30.f * ratio,5.f });
        hpbar.setFillColor(sf::Color::Green);

        hpbar.setPosition({
            pos.x - 15.f,
            pos.y - 20.f
            });

        window.draw(bg);
        window.draw(hpbar);
    }
};