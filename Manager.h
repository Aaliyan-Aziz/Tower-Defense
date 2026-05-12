#ifndef Manager_h
#define Manager_h
#include<SFML/Graphics.hpp>
#include"Enemy.h"
#include"Global.h"
#include"Tower.h"
class EnemyManager {
private:
	Enemy* enemies[MAX_ENEMIES];
	int enemycount;
	float spawnTimer;
	float spawnDelay;
	int spawnedinWave;
public:
	EnemyManager();
	~EnemyManager();
	void spawnEnemy(int wave);
	int update(float dt, int& lives);
	void draw(sf::RenderWindow& window);
	void reset();
	Enemy** getEnemies() { return enemies; }
	int getEnemyCount()const { return enemycount; }
	bool allDead() const { return enemycount == 0; }
	bool shouldSpawn(int enemiesPerWave) const;
	void tickSpawn(float dt) { spawnTimer += dt; }
	void resetSpawnTimer() { spawnTimer = 0.f; }
	void increementSpawned() { spawnedinWave++; }
	int getspawnedinWave() const { return spawnedinWave; }
	void resetspawnedinWave() {
		spawnedinWave = 0;
		spawnTimer = 0.f;
	}
};
class TowerManager {
private:
	Tower* towers[MAX_TOWERS];
	int towercount;
public:
	TowerManager();
	~TowerManager();
	bool isValidPlacement(sf::Vector2f pos) const;
	bool placeTower(TowerType type, sf::Vector2f pos, int& gold);
	void update(float dt, Enemy* enemies[], int enemycount, Bullet bullets[]);
	void draw(sf::RenderWindow& window);
	void reset();
	int gettowercount() { return towercount; }

};
#endif