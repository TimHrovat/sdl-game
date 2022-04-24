#include "Menu.h"

bool Menu::isRunning;
bool Menu::enterPressed;

SDL_Renderer *Menu::renderer = NULL;
SDL_Event Menu::event;
Game *Menu::game = new Game();
bool Menu::gameRunning = false;
std::string Menu::currentPlayerName = "player 1";

MainMenu *Menu::mainMenu = new MainMenu();
LevelSelection *Menu::levelSelection = new LevelSelection();
Scoreboard *Menu::scoreboard = new Scoreboard();
ChooseName *Menu::chooseName = new ChooseName();
ScoreboardLevel *Menu::levelScores = new ScoreboardLevel();

void Menu::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL initialized!..." << std::endl;

        IMG_Init(IMG_INIT_PNG); // initializes img libary
        IMG_Init(IMG_INIT_JPG);
        TTF_Init();
        if (TTF_Init()) {
            std::cout << "ttf initialized successfully" << std::endl;
        }

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

        chooseName->init();

        isRunning = true;
    } else {
        isRunning = false;
    }
}
void Menu::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                if (Menu::gameRunning) {
                    Menu::gameRunning = false;
                    Menu::game->clean();
                }
                mainMenu->init();
                levelSelection->setActive(false);
                levelScores->setActive(false);
                scoreboard->setActive(false);
                chooseName->setActive(false);
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_RETURN) {
                enterPressed = false;
            }
    }
}

void Menu::update() {
    if (gameRunning) {
        game->update();
        return;
    }

    if (!enterPressed) {
        mainMenu->handleKeyboard();
        mainMenu->update();

        levelSelection->handleKeyboard();
        levelSelection->update();

        scoreboard->handleKeyboard();
        scoreboard->update();

        chooseName->handleKeyboard();
        chooseName->update();
    }
}

void Menu::render() {
    if (gameRunning) {
        game->render();
        return;
    }
    SDL_SetRenderDrawColor(Menu::renderer, 42, 41, 62, 255);
    SDL_RenderClear(Menu::renderer);

    mainMenu->render();
    levelSelection->render();
    scoreboard->render();
    chooseName->render();
    levelScores->render();

    SDL_RenderPresent(Menu::renderer);
}

bool Menu::running() {
    return isRunning;
}

void Menu::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
