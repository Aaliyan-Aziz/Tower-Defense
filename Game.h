#ifndef Game_h
#define Game_h
#include<SFML/Graphics.hpp>
#include"Global.h"
#include"Enemy.h"
#include"Tower.h"
#include"Manager.h"
#include"UI.h"
class GameManager {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::VertexArray pathline;
	int lives;
	int gold;
	int wave;
	int enemiesPerWave;
	bool gameOver;
	bool gameFinished;
	TowerType selectedTower;
	bool placingTower;
	sf::Vector2f placementPos;
	Bullet bullets[MAX_BULLETS];
	EnemyManager enemyMgr;
	TowerManager towerMgr;
	UI ui;
	bool loadAssets();
	void handleEvents();
	void update(float dt);
	void render();
	void resetGame();
public:
	GameManager();
	void run();
};
#endif