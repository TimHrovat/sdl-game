#include "Game.h"
#include "../ECS/Components.h"
#include "../collision/Collision.h"
#include "../map/Map.h"
#include "../menu/Menu.h"
#include "../text/text.h"
#include "../textureManager/TextureManager.h"
#include "../vector2D/Vector2D.h"
#include <fstream>
#include <sstream>

Manager manager;
Map *map;
SDL_Rect Game::camera = {0, 0, 1080, 720};
int Game::time;

std::vector<CollisionComponent *> Game::collisions;
std::vector<Entity *> Game::animalCollisions;
std::vector<Entity *> Game::enemyCollisions;

std::ofstream dataout;
std::ifstream datain;

Text *animalCount;
Text *playerLives;
Text *timeScore;

auto &player(manager.addEntity());
auto &bg(manager.addEntity());

enum groupLabels : std::size_t {
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupBackground,
    groupAnimals
};

auto &tiles(manager.getGroup(groupMap));
auto &players(manager.getGroup(groupPlayers));
auto &enemies(manager.getGroup(groupEnemies));
auto &background(manager.getGroup(groupBackground));
auto &animals(manager.getGroup(groupAnimals));

Game::Game() {
}

Game::~Game() {
}

void Game::init(int level, bool restored) {
    animalCollisions.clear();
    enemyCollisions.clear();
    collisions.clear();

    this->level = level;

    map = new Map(level);

    AddPlayer();
    AddBackground();

    animalCount = new Text("", 10, 10, 20, false);
    playerLives = new Text("", 10, 35, 20, false);
    timeScore = new Text("", 10, 60, 20, false);

    if (!replayRunning) {
        if (restored)
            dataout.open("assets/replay/replay.bin", std::ios::binary | std::ios::app);
        else {
            dataout.clear();
            dataout.open("assets/replay/replay.bin", std::ios::binary);
            std::ofstream dlevel("assets/replay/level.txt");
            dlevel << level;
            dlevel.close();
        }
    }

    time = 0;
    prevTime = SDL_GetTicks();

    isRunning = true;
}

void Game::update() {
    manager.refresh();
    if (replayRunning)
        ReplayUpdate();

    int thisTime = SDL_GetTicks();
    if (thisTime - prevTime >= 1000) {
        time++;
        prevTime = thisTime;
    }

    std::string tempStr = "Animals: " + std::to_string(animalCollisions.size());
    animalCount->update(tempStr.c_str());
    tempStr = "Player lives: " + std::to_string(player.getComponent<KeyboardHandler>().playerLives);
    playerLives->update(tempStr.c_str());
    tempStr = "Time: " + std::to_string(time / 60) + ":" + std::to_string(time % 60);
    timeScore->update(tempStr.c_str());

    for (auto &b : background) {
        b->update();
    }
    for (auto &t : tiles) {
        t->update();
    }
    for (auto &a : animals) {
        a->update();
    }
    for (auto &p : players) {
        p->update();
    }
    for (auto &e : enemies) {
        e->update();
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 300;
    camera.y = player.getComponent<TransformComponent>().position.y - 550;

    if (camera.x < 0)
        camera.x = 0;
    else if (camera.x + camera.w >= bg.getComponent<TransformComponent>().width * bg.getComponent<TransformComponent>().scale)
        camera.x = bg.getComponent<TransformComponent>().width * bg.getComponent<TransformComponent>().scale - camera.w;
    if (camera.y < -200) camera.y = -200;

    if (!replayRunning)
        SaveForReplay();
}

void Game::render() {
    SDL_RenderClear(Menu::renderer);

    // stuff that needs rendering goes here
    for (auto &b : background) {
        b->draw();
    }

    animalCount->draw();
    playerLives->draw();
    timeScore->draw();

    for (auto &t : tiles) {
        t->draw();
    }
    for (auto &a : animals) {
        a->draw();
    }
    for (auto &p : players) {
        p->draw();
    }
    for (auto &e : enemies) {
        e->draw();
    }

    if (player.getComponent<KeyboardHandler>().playerLives == 0) {
        reset("YOU LOST");
    } else if (animalCollisions.size() == 0) {
        if (!replayRunning)
            AddScoreWin();
        reset("YOU WON");
    } else {
        SDL_RenderPresent(Menu::renderer);
    }
}

void Game::clean() {
    // if (!replayRunning)
    SaveForRestore();

    for (auto &t : tiles) {
        t->destroy();
    }
    for (auto &a : animals) {
        a->destroy();
    }
    for (auto &e : enemies) {
        e->destroy();
    }
    animalCollisions.clear();
    enemyCollisions.clear();
    tiles.clear();
    animals.clear();
    enemies.clear();
    if (dataout.is_open())
        dataout.close();
    if (replayRunning)
        ReplayClean();
}

bool Game::running() {
    return isRunning;
}

void Game::AddTile(int id, int x, int y, int w, int h) {
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, w, h, id);
    tile.addGroup(groupMap);
}

void Game::AddAnimal(int platformX, int platformY) {
    auto &animal(manager.addEntity());
    animal.addComponent<NPC>("animal", platformX, platformY, 0);
    animal.addGroup(groupAnimals);
}

void Game::AddEnemy(int platformX, int platformY, int maxDelta) {
    auto &enemy(manager.addEntity());
    enemy.addComponent<NPC>("enemy", platformX, platformY, maxDelta);
    enemy.addGroup(groupEnemies);
}

void Game::AddBackground() {
    if (!bg.hasComponent<TransformComponent>()) {
        bg.addComponent<TransformComponent>(0, -200, 2160, 3840, 0.5);
        bg.addComponent<SpriteComponent>("../assets/background/background.png");
        bg.addGroup(groupBackground);
    }
}

void Game::reset(const char *txt) {
    Text text(txt, 540 - 150, 360 - 50, 50, true);
    text.draw();
    SDL_RenderPresent(Menu::renderer);

    SDL_Delay(2000);

    player.getComponent<KeyboardHandler>().playerLives = 3;

    clean();
    Menu::gameRunning = false;
    Menu::mainMenu->init();
}

void Game::AddPlayer() {
    if (!player.hasComponent<TransformComponent>()) {
        player.addComponent<TransformComponent>(40.0f, 600.0f - 439 * 0.15f + 1, 439, 232, 0.15);
        player.addComponent<SpriteComponent>();
        player.addComponent<KeyboardHandler>();
        player.addComponent<CollisionComponent>("player");
        player.addComponent<AnimationComponent>();
        player.addComponent<PhysicsComponent>();
        player.addGroup(groupPlayers);
    } else {
        player.getComponent<TransformComponent>().position.x = 40;
        player.getComponent<TransformComponent>().position.y = 600.0f - 439 * 0.15f + 1;
    }
}

void Game::SaveForRestore() {
    std::ofstream data("assets/restore/general.bin", std::ios::binary);
    generalRestore tempGeneral;
    if (data.is_open()) {
        strcpy(tempGeneral.playerName, Menu::currentPlayerName.c_str());
        tempGeneral.time = time;
        tempGeneral.lives = player.getComponent<KeyboardHandler>().playerLives;
        tempGeneral.level = level;
        data.write((char *)&tempGeneral, sizeof(tempGeneral));
        data.close();
    }

    data.open("assets/restore/enemy.bin", std::ios::binary);
    if (data.is_open()) {
        enemyRestore temp;
        for (auto &e : enemies) {
            temp.deltaPos = (int)e->getComponent<NPC>().deltaPos;
            temp.velocity = (int)e->getComponent<TransformComponent>().velocity.x;
            data.write((char *)&temp, sizeof(temp));
        }
        data.close();
    }

    data.open("assets/restore/animal.bin", std::ios::binary);
    if (data.is_open()) {
        animalRestore temp;
        for (auto &a : animals) {
            temp.x = a->getComponent<NPC>().position.x;
            temp.y = a->getComponent<NPC>().position.y;
            data.write((char *)&temp, sizeof(temp));
        }
        data.close();
    }

    data.open("assets/restore/player.bin", std::ios::binary);
    if (data.is_open()) {
        playerRestore tempPlayer;

        tempPlayer.x = player.getComponent<TransformComponent>().position.x + 1;
        tempPlayer.y = player.getComponent<TransformComponent>().position.y + 1;

        std::cout << "GAME SAVED: " << tempPlayer.x << " " << tempPlayer.y << std::endl;
        data.write((char *)&tempPlayer, sizeof(tempPlayer));
        data.close();
    }
}

void Game::Restore() {
    std::ifstream data;

    generalRestore tempGeneral;
    data.open("assets/restore/general.bin", std::ios::binary);
    data.read((char *)&tempGeneral, sizeof(tempGeneral));
    data.close();

    level = tempGeneral.level;

    Menu::gameRunning = true;
    Menu::game->init(level, true);

    data.open("assets/restore/enemy.bin", std::ios::binary);
    if (data.is_open()) {
        enemyRestore temp;
        int i = 0;
        while (data.read((char *)&temp, sizeof(temp))) {
            enemies[i]->getComponent<NPC>().deltaPos = temp.deltaPos;
            enemies[i]->getComponent<TransformComponent>().velocity.x = temp.velocity;
            i++;
        }
        data.close();
    }

    data.open("assets/restore/animal.bin", std::ios::binary);
    if (data.is_open()) {
        animalRestore temp;
        int i = 0;
        while (data.read((char *)&temp, sizeof(temp))) {
            animals[i]->getComponent<NPC>().position.x = temp.x;
            animals[i]->getComponent<NPC>().position.y = temp.y;
            i++;
        }
        animals.erase(animals.begin() + i, animals.end());
        animalCollisions.erase(animalCollisions.begin() + i, animalCollisions.end());
        data.close();
    }

    data.open("assets/restore/player.bin", std::ios::binary);
    playerRestore tempPlayer;
    if (data.is_open()) {
        data.read((char *)&tempPlayer, sizeof(tempPlayer));
        player.getComponent<TransformComponent>().position.x = tempPlayer.x;
        player.getComponent<TransformComponent>().position.y = tempPlayer.y;
        std::cout << "GAME RESTORED" << player.getComponent<TransformComponent>().position.x << " " << player.getComponent<TransformComponent>().position.y << std::endl;
        data.close();
    }

    time = tempGeneral.time;
    Menu::currentPlayerName = tempGeneral.playerName;
    player.getComponent<KeyboardHandler>().playerLives = tempGeneral.lives;
}

void Game::SaveForReplay() {
    replay temp;
    temp.velocityX = player.getComponent<TransformComponent>().velocity.x;
    temp.velocityY = player.getComponent<TransformComponent>().velocity.y;
    temp.positionX = player.getComponent<TransformComponent>().position.x;
    temp.positionY = player.getComponent<TransformComponent>().position.y;
    dataout.write((char *)&temp, sizeof(temp));
    replayAvalible = true;
}

void Game::ReplayUpdate() {
    replay temp;
    if (datain.read((char *)&temp, sizeof(replay))) {
        player.getComponent<TransformComponent>().velocity.x = temp.velocityX;
        player.getComponent<TransformComponent>().velocity.y = temp.velocityY;
        player.getComponent<TransformComponent>().position.x = temp.positionX;
        player.getComponent<TransformComponent>().position.y = temp.positionY;
    } else {
        datain.close();
        player.getComponent<KeyboardHandler>().isActive = true;
        player.getComponent<PhysicsComponent>().isActive = true;
        Menu::gameRunning = false;
        Menu::game->clean();
        Menu::mainMenu->init();
    }
}

void Game::Replay() {
    datain.open("assets/replay/replay.bin", std::ios::binary);
    if (datain.is_open()) {
        replayAvalible = true;
    }
    if (!replayAvalible) {
        Menu::mainMenu->setActive(true);
        return;
    }
    replayRunning = true;
    Menu::gameRunning = true;
    std::ifstream dlevel("assets/replay/level.txt");
    int lvl;
    dlevel >> lvl;
    dlevel.close();
    Menu::game->init(lvl, false);
    player.getComponent<KeyboardHandler>().isActive = false;
    player.getComponent<PhysicsComponent>().isActive = false;
}

void Game::ReplayClean() {
    datain.close();
    player.getComponent<KeyboardHandler>().isActive = true;
    player.getComponent<PhysicsComponent>().isActive = true;

    replayRunning = false;
    player.getComponent<TransformComponent>().velocity.x = 0;
    player.getComponent<TransformComponent>().velocity.y = 0;
}

void Game::AddScoreWin() {
    scoreWin win;
    bool written = false;
    win.time = time;
    strcpy(win.name, Menu::currentPlayerName.c_str());

    std::ifstream data;
    // std::ifstream dataName;
    switch (level) {
        case 1:
            data.open("assets/scores/level1_time.bin", std::ios::binary);
            // dataName.open("assets/scores/level1_name.txt");
            break;
        case 2:
            data.open("assets/scores/level2_time.bin", std::ios::binary);
            // dataName.open("assets/scores/level2_name.txt");
            break;
        case 3:
            data.open("assets/scores/level3_time.bin", std::ios::binary);
            // dataName.open("assets/scores/level3_name.txt");
            break;
    }
    std::ofstream temp("assets/scores/temp.bin", std::ios::binary);
    // std::ofstream tempName("assets/scores/tempName.txt");

    if (data.is_open() && temp.is_open()) {
        scoreWin tempScore;
        while (data.read((char *)&tempScore, sizeof(scoreWin))) {
            if (tempScore.time > win.time && !written) {
                temp.write((char *)&win, sizeof(scoreWin));
                written = true;
            }
            temp.write((char *)&tempScore, sizeof(scoreWin));
        }
        if (!written) {
            temp.write((char *)&win, sizeof(scoreWin));
        }
    }

    temp.close();
    data.close();

    switch (level) {
        case 1:
            remove("assets/scores/level1_time.bin");
            rename("assets/scores/temp.bin", "assets/scores/level1_time.bin");
            break;
        case 2:
            remove("assets/scores/level2_time.bin");
            rename("assets/scores/temp.bin", "assets/scores/level2_time.bin");
            break;
        case 3:
            remove("assets/scores/level3_time.bin");
            rename("assets/scores/temp.bin", "assets/scores/level3_time.bin");
            break;
    }
}