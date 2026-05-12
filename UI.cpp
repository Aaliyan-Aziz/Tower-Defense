#include"UI.h"
#include"Tower.h"
#include<iostream>
UI::UI(float windowheight) :livesText(font), goldText(font), infoText(font), waveText(font), gameOverText(font), finishedText(font), retryText(font), cannonIcon(cannontex), sniperIcon(snipertex), machineIcon(machinetex) {
	menuX = 50.f;
	menuY = windowheight - 200.f;

	cannonBtn.setSize({ 60.f,60.f });
	sniperBtn.setSize({ 60.f,60.f });
	machineBtn.setSize({ 60.f,60.f });
	cannonBtn.setPosition({ menuX,menuY });
	sniperBtn.setPosition({ menuX,menuY + 70.f });
	machineBtn.setPosition({ menuX,menuY + 140.f });
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::Blue);
    livesText.setPosition({ 10.f,10.f });

    goldText.setCharacterSize(24);
    goldText.setFillColor(sf::Color::Yellow);
    goldText.setPosition({ 10.f,40.f });

    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::Red);
    infoText.setPosition({ 10.f,70.f });

    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::Cyan);
    waveText.setPosition({ 10.f,100.f });

    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({ 250.f,250.f });

    finishedText.setString("FINISHED THE GAME!");
    finishedText.setCharacterSize(40);
    finishedText.setFillColor(sf::Color::Green);
    finishedText.setPosition({ 140.f,220.f });

    retryText.setString("Press R to Retry");
    retryText.setCharacterSize(30);
    retryText.setFillColor(sf::Color::Blue);
    retryText.setPosition({ 250.f,320.f });

    cannonIcon.setOrigin({
             cannontex.getSize().x / 2.f,
             cannontex.getSize().y / 2.f
        });
    cannonIcon.setPosition({ menuX + 30.f, menuY + 30.f });
    cannonIcon.setScale({ 0.19f, 0.19f });

    sniperIcon.setOrigin({
      snipertex.getSize().x / 2.f,
      snipertex.getSize().y / 2.f
        });
    sniperIcon.setPosition({ menuX + 30.f, menuY + 100.f });
    sniperIcon.setScale({ 0.15f, 0.15f });

    machineIcon.setOrigin({
      machinetex.getSize().x / 2.f,
      machinetex.getSize().y / 2.f
        });
    machineIcon.setPosition({ menuX + 30.f, menuY + 170.f });
    machineIcon.setScale({ 0.2f, 0.2f });
}
bool UI::loadFont(const std::string& path) {
    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Font loading failed\n";
        return false;
    }
    else {
        std::cout << "Font loaded\n";
        return true;
    }
}
void UI::setInfoMessage(const std::string& msg) {
    infoText.setString(msg);
}
void UI::drawHUD(sf::RenderWindow& window, int lives, int gold, int wave) {
    livesText.setString("Lives: " + std::to_string(lives));
    goldText.setString("Gold: " + std::to_string(gold));
    waveText.setString("Wave: " + std::to_string(wave));
    window.draw(livesText);
    window.draw(goldText);
    window.draw(infoText);
    window.draw(waveText);
}
void UI::drawTowerMenu(sf::RenderWindow& window, TowerType selectedTower) {
    auto drawBtn = [&](sf::RectangleShape& btn, TowerType t) {
        btn.setFillColor(sf::Color::Black);
        btn.setOutlineThickness(2.f);
        btn.setOutlineColor(selectedTower == t ? sf::Color::Yellow : sf::Color::Blue);
        window.draw(btn);
        };
    drawBtn(cannonBtn, CANNON);
    drawBtn(sniperBtn, SNIPER);
    drawBtn(machineBtn, MACHINE);
    window.draw(cannonIcon);
    window.draw(sniperIcon);
    window.draw(machineIcon);

}
void UI::drawGameOver(sf::RenderWindow& window) {
    window.draw(gameOverText);
    window.draw(retryText);
}
void UI::drawFinished(sf::RenderWindow& window) {
    window.draw(finishedText);
    window.draw(retryText);
}
bool UI::clickedCannonBtn(sf::Vector2f p) const { return cannonBtn.getGlobalBounds().contains(p); }
bool UI::clickedSniperBtn(sf::Vector2f p) const { return sniperBtn.getGlobalBounds().contains(p); }
bool UI::clickedMachineBtn(sf::Vector2f p) const { return machineBtn.getGlobalBounds().contains(p); }
void UI::drawPlacementPreview(sf::RenderWindow& window, sf::Vector2f pos, bool valid, float range)const {
    sf::CircleShape dot(12.f);
    dot.setFillColor(valid ? sf::Color(0, 255, 0, 120) : sf::Color(255, 0, 0, 120));
    dot.setPosition(pos);
    window.draw(dot);
    
    sf::CircleShape circle(range);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(valid ? sf::Color::Green : sf::Color::Red);
    circle.setOutlineThickness(1.f);
    circle.setOrigin({ range,range });
    circle.setPosition(pos);
    window.draw(circle);
}