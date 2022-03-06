#include "Map.h"
#include "../ECS/Components.h"
#include "../textureManager/TextureManager.h"

Map::Map() {
    // ground = TextureManager::LoadTexture((char *)"../assets/background/ground.png");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 75; j++) {
            Game::AddTile(0, j * 40, i * 40 + 600, 40, 40);
        }
    }

    Game::AddTile(0, 300, 400, 300, 20);
    Game::AddTile(0, 400, 50, 300, 20);
    Game::AddTile(0, 200, -300, 300, 20);
    Game::AddTile(0, 900, -200, 300, 20);
    Game::AddTile(0, 800, 200, 500, 20);
    Game::AddTile(0, 1500, 50, 400, 20);
    Game::AddTile(0, 1900, 300, 400, 20);
    Game::AddTile(0, 2200, -50, 300, 20);
    Game::AddTile(0, 2400, 400, 300, 20);
    Game::AddTile(0, 2600, -250, 100, 20);
    Game::AddTile(0, 900, -50, 300, 20);
    Game::AddTile(0, 1300, 400, 400, 20);
    Game::AddTile(0, 1800, -200, 300, 20);

    addAnimals();
    addEnemies();
}

void Map::addAnimals() {
    Game::AddAnimal(300, 400);
    Game::AddAnimal(250, -300);
    Game::AddAnimal(1000, -200);
    Game::AddAnimal(1500, 400);
    Game::AddAnimal(1600, 50);
    Game::AddAnimal(1800, -200);
    Game::AddAnimal(2600, -250);
}

void Map::addEnemies() {
    Game::AddEnemy(300, 400, 300);
    Game::AddEnemy(800, 200, 500);
    Game::AddEnemy(900, -50, 300);
    Game::AddEnemy(200, -300, 300);
    Game::AddEnemy(2000, 300, 300);
    Game::AddEnemy(2200, -50, 300);
    Game::AddEnemy(1800, -200, 300);
}