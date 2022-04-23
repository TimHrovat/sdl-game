#include "Map.h"
#include "../ECS/Components.h"
#include "../textureManager/TextureManager.h"

using namespace std;

Map::Map(int level) {
    // ground = TextureManager::LoadTexture((char *)"../assets/background/ground.png");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 75; j++) {
            Game::AddTile(0, j * 40, i * 40 + 600, 40, 40);
        }
    }

    LoadMap(level);
}

void Map::LoadMap(int level) {
    Platform temp;
    char *filename;
    switch (level) {
        case 1:
            filename = "assets/levels/level_1.bin";
            break;
        case 2:
            filename = "assets/levels/level_2.bin";
            break;
        case 3:
            filename = "assets/levels/level_3.bin";
            break;
    }
    ifstream data(filename, ios::binary);

    if (data.is_open()) {
        while (data.read((char *)&temp, sizeof(temp))) {
            Game::AddTile(0, temp.x, temp.y, temp.w, temp.h);
            if (temp.hasEnemy)
                Game::AddEnemy(temp.x, temp.y, temp.w);
            if (temp.hasAnimal)
                Game::AddAnimal(temp.animalXPos, temp.y);
        }
    } else {
        std::cout << "MAP LOAD FAILED" << std::endl;
    }

    data.close();
}