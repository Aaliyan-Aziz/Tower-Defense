#include"Game.h"
#include<iostream>
#include<cmath>
GameManager::GameManager():window(sf::VideoMode({800,600}),"Tower Defense"),background(backgroundTexture),pathline(sf::PrimitiveType::LineStrip,PATH_POINTS),lives(20),gold(200),wave(1),enemiesPerWave(5),gameOver(false),gameFinished(false),selectedTower(NONE),placingTower(false),ui(600.f){
}
bool GameManager::loadAssets() {
    if (!cannontex.loadFromFile("cannontower.png")) {
        std::cout << "FATAL: cannot load cannontower.png\n";
        return false;
    }
    if (!snipertex.loadFromFile("sniper.png")) {
        std::cout << "FATAL: cannot load sniper.png\n";
        return false;
    }
    if (!machinetex.loadFromFile("machinegun.png")) {
        std::cout << "FATAL: cannot load machinegun.png\n";
        return false;
    }
    if (!basicEnemyTex.loadFromFile("basicenemy.png")) {
        std::cout << "FATAL: cannot load basicenemy.png\n";
        return false;
    }
    if (!fastEnemyTex.loadFromFile("fastenemy.png")) {
        std::cout << "FATAL: cannot load fastenemy.png\n";
        return false;
    }
    if (!flyingEnemyTex.loadFromFile("flyingenemy.png")) {
        std::cout << "FATAL: cannot load flyingenemy.png\n";
        return false;
    }
    if (!backgroundTexture.loadFromFile("background.jpeg")) {
        std::cout << "Error loading background image\n";
        return false;
    }
    sf::Vector2u texSize = backgroundTexture.getSize();
    sf::Vector2u winSize = window.getSize();

    background.setScale({
        (float)winSize.x / texSize.x,
        (float)winSize.y / texSize.y
        });

    sf::VertexArray pathline(sf::PrimitiveType::LineStrip, PATH_POINTS);
    for (int i = 0; i < PATH_POINTS; i++) {
        pathline[i].position = Path[i];
        pathline[i].color = sf::Color::Red;
    }
    ui.loadFont("arial.ttf");
    return true;
}
void GameManager::resetGame() {
    lives = 20;
    gold = 200;
    wave = 1;
    gameOver = false;
    gameFinished = false;
    enemiesPerWave = 5;
    selectedTower = NONE;
    placingTower = false;
    for (int i = 0; i < MAX_BULLETS; i++)
        bullets[i].active = false;
}
void GameManager::handleEvents() {
    while (auto event = window.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            window.close();
            return;
        }
        if (auto* kp = event->getIf<sf::Event::KeyPressed>()) {
            if (kp->code == sf::Keyboard::Key::R && (gameOver || gameFinished))
                resetGame();
        }
        if (auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mb->button == sf::Mouse::Button::Left) {
                sf::Vector2f pos = {
                    static_cast<float>(mb->position.x),
                    static_cast<float>(mb->position.y)
                };

                // Tower menu selection
                if (ui.clickedCannonBtn(pos)) {
                    selectedTower = CANNON;  placingTower = true;
                }
                else if (ui.clickedSniperBtn(pos)) {
                    selectedTower = SNIPER;  placingTower = true;
                }
                else if (ui.clickedMachineBtn(pos)) {
                    selectedTower = MACHINE; placingTower = true;
                }

                else if (placingTower && selectedTower != NONE) {
                    if (!towerMgr.isValidPlacement(pos)) {
                        ui.setInfoMessage("Can't place tower on path!");
                    }
                    else if (!towerMgr.placeTower(selectedTower, pos, gold)) {
                        ui.setInfoMessage("Not enough Gold!");
                    }
                    placingTower = false;
                    selectedTower = NONE;
                }
            }
        }
    }
    if (placingTower) {
        auto mpos = sf::Mouse::getPosition(window);
        placementPos = { static_cast<float>(mpos.x),static_cast<float>(mpos.y) };
    }
}
void GameManager::update(float dt) {
    if (gameOver || gameFinished) return;

    enemyMgr.tickSpawn(dt);
    if (enemyMgr.shouldSpawn(enemiesPerWave)) {
        enemyMgr.spawnEnemy(wave);
    }

   
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].update(dt);

    for (int b = 0; b < MAX_BULLETS; b++) {
        if (!bullets[b].active) continue;
        Enemy** enemies = enemyMgr.getEnemies();
        int cnt = enemyMgr.getEnemyCount();
        for (int i = 0; i < cnt; i++) {
            if (!enemies[i]) continue;
            sf::Vector2f diff = {
                enemies[i]->getX() - bullets[b].getPos().x,
                enemies[i]->getY() - bullets[b].getPos().y
            };
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            if (dist < 10.f) {
                enemies[i]->damage(20);
                bullets[b].active = false;
                break;
            }
        }
    }

    
    towerMgr.update(dt, enemyMgr.getEnemies(), enemyMgr.getEnemyCount(), bullets);

    gold += enemyMgr.update(dt, lives);

    if (enemyMgr.getspawnedinWave() >= enemiesPerWave && enemyMgr.allDead()) {
        if (wave >= 5) {
            gameFinished = true;
        }
        else {
            wave++;
            enemiesPerWave += 2;
            enemyMgr.resetspawnedinWave();
            std::cout << "Wave " << wave << " starting\n";
        }
    }

    if (lives <= 0) gameOver = true;
}

void GameManager::render() {
    window.clear();
    window.draw(background);
    window.draw(pathline);
    if (placingTower) {
        bool valid = towerMgr.isValidPlacement(placementPos);
        float previewRange = (selectedTower == SNIPER) ? 250.f
            : (selectedTower == CANNON) ? 140.f
            : (selectedTower == MACHINE) ? 110.f : 120.f;
        ui.drawPlacementPreview(window, placementPos, valid, previewRange);
    }
     if (!gameOver && !gameFinished) {
        towerMgr.draw(window);
        for (int i = 0; i < MAX_BULLETS; i++) bullets[i].draw(window);
        enemyMgr.draw(window);
        ui.drawHUD(window, lives, gold, wave);
    }
    else if (gameOver) {
        ui.drawGameOver(window);
    }
    else {
        ui.drawFinished(window);
    }

    ui.drawTowerMenu(window, selectedTower);

    window.display();
}

void GameManager::run() {
    if (!loadAssets()) return;

    while (window.isOpen()) {
        handleEvents();

        float dt = clock.restart().asSeconds();
        if (dt > 0.033f) dt = 0.033f;  

        update(dt);
        render();
    }
}