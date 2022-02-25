#include "Map.h"
#include "../ECS/Components.h"
#include "../textureManager/TextureManager.h"

Map::Map() {
    // ground = TextureManager::LoadTexture((char *)"../assets/background/ground.png");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 27; j++) {
            Game::AddTile(0, j * 40, i * 40 + 600, 40, 40);
        }
    }

    Game::AddTile(0, 400, 300, 100, 20);
}

// void Map::DrawMap() {
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 27; j++) {
//             dest.x = j * 40;
//             dest.y = 600 + i * 40;

//             TextureManager::draw(ground, src, dest);
//         }
//     }
// }