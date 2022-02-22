#include "Game.h"
#include "../ECS/Components.h"
#include "../collision/Collision.h"
#include "../textureManager/TextureManager.h"
#include "../vector2D/Vector2D.h"

Manager manager;

SDL_Renderer *Game::renderer = NULL;
SDL_Event Game::event;

std::vector<CollisionComponent *> Game::collisions;

auto &player(manager.addEntity());
auto &wall(manager.addEntity());

auto &tile0(manager.addEntity());
auto &tile1(manager.addEntity());
auto &tile2(manager.addEntity());

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL initialized!..." << std::endl;

        IMG_Init(IMG_INIT_PNG); // initializes img libary

        // Creates a SDL window and checks if it's created successfully
        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
        if (window) {
            std::cout << "Window successfully created!" << std::endl;
        }

        // Creates a SDL renderer and checks if it's created successfully
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer successfully created!" << std::endl;
        }

        tile0.addComponent<TileComponent>(200, 100, 60, 60, 0);
        tile0.addComponent<CollisionComponent>("ground");
        tile1.addComponent<TileComponent>(260, 200, 60, 60, 0);
        tile2.addComponent<TileComponent>(320, 300, 60, 60, 0);

        player.addComponent<TransformComponent>(1.5);
        player.addComponent<SpriteComponent>("../assets/player/player_sheet.png");
        player.addComponent<KeyboardHandler>();
        player.addComponent<CollisionComponent>("player");

        wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
        wall.addComponent<SpriteComponent>("../assets/background/background.bmp");
        wall.addComponent<CollisionComponent>("wall");

        isRunning = true;
    } else {
        isRunning = false;
    }
}

void Game::handleEvents() {

    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    manager.refresh();
    manager.update();

    for (auto cc : collisions) {
        Collision::AABB(player.getComponent<CollisionComponent>(), *cc);
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    // stuff that needs rendering goes here
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game quit successfully!" << std::endl;
}

bool Game::running() {
    return isRunning;
}