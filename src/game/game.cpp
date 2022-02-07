#include "Game.h"
#include "../src/textureManager/TextureManager.h"

SDL_Texture *playerTexture;          //! remove
SDL_Rect srcrect = {0, 0, 38, 38};   //! remove
SDL_Rect dstrect = {10, 10, 38, 38}; //! remove

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL initialized!..." << std::endl;
        IMG_Init(IMG_INIT_PNG);
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

        playerTexture = TextureManager::LoadTexture("assets/images/player/player_sheet.png", renderer);

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
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTexture, &srcrect, &dstrect);
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