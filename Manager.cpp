#include"Manager.h"
#include<cmath>
#include<cstdlib>
#include"Global.h"
EnemyManager::EnemyManager()
    : enemycount(0), spawnTimer(0.f), spawnDelay(1.f), spawnedinWave(0)
{
    for (int i = 0; i < MAX_ENEMIES; i++) enemies[i] = nullptr;
}

EnemyManager::~EnemyManager() { reset(); }

bool EnemyManager::shouldSpawn(int enemiesPerWave) const {
    if (spawnTimer >= spawnDelay && enemycount < MAX_ENEMIES && spawnedinWave < enemiesPerWave) {
        return true;
    }
    else {
        return false;
    }
}

void EnemyManager::spawnEnemy(int wave) {
    if (enemycount >= MAX_ENEMIES) return;

    if (wave == 1) {
        enemies[enemycount] = new BasicEnemy();
    }
    else if (wave == 2) {
        enemies[enemycount] = (rand() % 2 == 0)
            ? static_cast<Enemy*>(new BasicEnemy())
            : static_cast<Enemy*>(new FastEnemy());
    }
    else {
        int r = rand() % 3;
        if (r == 0) enemies[enemycount] = new BasicEnemy();
        else if (r == 1) enemies[enemycount] = new FastEnemy();
        else             enemies[enemycount] = new FlyingEnemy();
    }
    enemycount++;
    spawnedinWave++;
    spawnTimer = 0.f;
}

int EnemyManager::update(float dt, int& lives) {
    int goldEarned = 0;

    for (int i = 0; i < enemycount; i++) {
        if (!enemies[i]) continue;
        enemies[i]->update(dt);
    }

    for (int i = 0; i < enemycount; i++) {
        if (!enemies[i]) continue;

        if (enemies[i]->isDead()) {
            goldEarned += 10;
            delete enemies[i];
            enemies[i] = enemies[enemycount - 1];
            enemies[--enemycount] = nullptr;
            i--;
        }
        else if (enemies[i]->reachedend) {
            lives--;
            delete enemies[i];
            enemies[i] = enemies[enemycount - 1];
            enemies[--enemycount] = nullptr;
            i--;
        }
    }

    return goldEarned;
}

void EnemyManager::draw(sf::RenderWindow& window) {
    for (int i = 0; i < enemycount; i++) {
        if (enemies[i]) enemies[i]->draw(window);
    }
}

void EnemyManager::reset() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    enemycount = 0;
    spawnTimer = 0.f;
    spawnedinWave = 0;
}

TowerManager::TowerManager() : towercount(0) {
    for (int i = 0; i < MAX_TOWERS; i++) towers[i] = nullptr;
}

TowerManager::~TowerManager() { reset(); }

bool TowerManager::isValidPlacement(sf::Vector2f pos) const {
    for (int i = 0; i < PATH_POINTS; i++) {
        float dx = pos.x - Path[i].x;
        float dy = pos.y - Path[i].y;
        if (std::sqrt(dx * dx + dy * dy) < 30.f) return false;
    }
    return true;
}

bool TowerManager::placeTower(TowerType type, sf::Vector2f pos, int& gold) {
    if (towercount >= MAX_TOWERS)       return false;
    if (!isValidPlacement(pos))         return false;

    if (type == CANNON && gold >= Cost_cannon) {
        towers[towercount++] = new CannonTower(pos.x, pos.y);
        gold -= Cost_cannon;
        return true;
    }
    if (type == SNIPER && gold >= cost_sniper) {
        towers[towercount++] = new SniperTower(pos.x, pos.y);
        gold -= cost_sniper;
        return true;
    }
    if (type == MACHINE && gold >= cost_machine) {
        towers[towercount++] = new MachineGunTower(pos.x, pos.y);
        gold -= cost_machine;
        return true;
    }
    return false;   // not enough gold
}

void TowerManager::update(float dt, Enemy* enemies[], int enemyCount, Bullet bullets[]) {
    for (int i = 0; i < towercount; i++) {
        if (towers[i]) towers[i]->update(dt, enemies, enemyCount, bullets);
    }
}

void TowerManager::draw(sf::RenderWindow& window) {
    for (int i = 0; i < towercount; i++) {
        if (towers[i]) towers[i]->draw(window);
    }
}

void TowerManager::reset() {
    for (int i = 0; i < MAX_TOWERS; i++) {
        delete towers[i];
        towers[i] = nullptr;
    }
    towercount = 0;
}