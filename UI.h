#ifndef UI_h
#define UI_h
#include<SFML/Graphics.hpp>
#include"Global.h"
class UI {
private:
	sf::Font font;
	sf::Text livesText;
	sf::Text goldText;
	sf::Text infoText;
	sf::Text waveText;
	sf::Text gameOverText;
	sf::Text finishedText;
	sf::Text retryText;
	sf::RectangleShape cannonBtn;
	sf::RectangleShape sniperBtn;
	sf::RectangleShape machineBtn;
	sf::Sprite cannonIcon;
	sf::Sprite sniperIcon;
	sf::Sprite machineIcon;
	float menuX;
	float menuY;
public:
	explicit UI(float windowHeight);
	bool loadFont(const std::string& path);
	void setInfoMessage(const std::string& msg);
	void drawHUD(sf::RenderWindow& window, int lives, int gold, int wave);
	void drawTowerMenu(sf::RenderWindow& window, TowerType selectedTower);
	void drawGameOver(sf::RenderWindow& window);
	void drawFinished(sf::RenderWindow& window);
	bool clickedCannonBtn(sf::Vector2f pos)const;
	bool clickedSniperBtn(sf::Vector2f pos)const;
	bool clickedMachineBtn(sf::Vector2f pos)const;
	void drawPlacementPreview(sf::RenderWindow& window, sf::Vector2f pos, bool valid, float range) const;
};
#endif