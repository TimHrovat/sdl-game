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

void Game::init(int level) {
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

    time = 0;
    prevTime = SDL_GetTicks();

    isRunning = true;
}

void Game::update() {
    manager.refresh();
    int thisTime = SDL_GetTicks();
    if (thisTime - prevTime >= 1000) {
        time++;
        prevTime = thisTime;
    }
    std::cout << time << std::endl;
    // manager.update();
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
        reset("YOU WON");
    } else {
        SDL_RenderPresent(Menu::renderer);
    }
}

void Game::clean() {
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
    // animalCollisions.clear();
    clean();
    init(level);
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
    std::ofstream data("assets/restore/lvl.txt");
    data << level;
    data.close();

    data.open("assets/restore/animals.bin", std::ios::binary);
    for (auto &a : animals) {
    }
}
