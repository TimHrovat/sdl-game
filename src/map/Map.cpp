#include "Map.h"
#include "../ECS/Components.h"
#include "../textureManager/TextureManager.h"

Map::Map() {
    // ground = TextureManager::LoadTexture((char *)"../assets/background/ground.png");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 48; j++) {
            Game::AddTile(0, j * 40, i * 40 + 600, 40, 40);
        }
    }

    Game::AddTile(0, 400, 300, 100, 20);
}