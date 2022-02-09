#include "Game.h"
#include "../src/components/ECS.h"
#include "../src/components/components.h"
#include "../src/gameObject/GameObject.h"
#include "../src/textureManager/TextureManager.h"

GameObject *player;

SDL_Renderer *Game::renderer = NULL;
Manager manager;
auto &newPlayer(manager.addEntity());

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

        player = new GameObject("../assets/images/player/player_sheet.png", 0, 0);

        newPlayer.addComponent<PositionComponent>();
        newPlayer.getComponent<PositionComponent>().setPos(500, 500);

        isRunning = true;
    } else {
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
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
    player->Update();
    manager.update();
    std::cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}

void Game::render() {
    SDL_RenderClear(renderer);
    player->Render();
    // stuff that needs rendering goes here
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