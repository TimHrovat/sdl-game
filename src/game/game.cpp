#include "Game.h"
#include "../ECS/Components.h"
#include "../collision/Collision.h"
#include "../map/Map.h"
#include "../textureManager/TextureManager.h"
#include "../vector2D/Vector2D.h"

Manager manager;
Map *map;

SDL_Renderer *Game::renderer = NULL;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, 1080, 720};

std::vector<CollisionComponent *> Game::collisions;

auto &player(manager.addEntity());
auto &bg(manager.addEntity());

enum groupLabels : std::size_t {
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders,
    groupBackground
};

auto &tiles(manager.getGroup(groupMap));
auto &players(manager.getGroup(groupPlayers));
auto &enemies(manager.getGroup(groupEnemies));
auto &background(manager.getGroup(groupBackground));

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL initialized!..." << std::endl;

        IMG_Init(IMG_INIT_PNG); // initializes img libary
        IMG_Init(IMG_INIT_JPG);

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

        map = new Map();

        player.addComponent<TransformComponent>(40.0f, 600.0f - 439 * 0.15f + 1, 439, 232, 0.15);
        player.addComponent<SpriteComponent>();
        player.addComponent<KeyboardHandler>();
        player.addComponent<CollisionComponent>("player");
        player.addComponent<AnimationComponent>();
        player.addComponent<PhysicsComponent>();
        player.addGroup(groupPlayers);

        bg.addComponent<TransformComponent>(0, -200, 2160, 3840, 0.5);
        bg.addComponent<SpriteComponent>("../assets/background/background.png");
        bg.addGroup(groupBackground);

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
    // manager.update();

    for (auto &b : background) {
        b->update();
    }
    for (auto &t : tiles) {
        t->update();
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

    std::cout << "player x: " << player.getComponent<TransformComponent>().position.x << std::endl;
    std::cout << "player y: " << player.getComponent<TransformComponent>().position.y << std::endl;
}

void Game::render() {
    SDL_RenderClear(renderer);
    // stuff that needs rendering goes here
    for (auto &b : background) {
        b->draw();
    }
    for (auto &t : tiles) {
        t->draw();
    }
    for (auto &p : players) {
        p->draw();
    }
    for (auto &e : enemies) {
        e->draw();
    }
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

void Game::AddTile(int id, int x, int y, int w, int h) {
    auto &tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, w, h, id);
    tile.addGroup(groupMap);
}