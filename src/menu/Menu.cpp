// #include "Menu.h"

// SDL_Renderer *Menu::renderer = NULL;
// SDL_Event Menu::event;
// Game *Menu::game = NULL;

// Text *play;
// Text *quit;

// void Menu::init(const char *title, int xpos, int ypos, int width, int height) {
//     if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
//         std::cout << "SDL initialized!..." << std::endl;

//         IMG_Init(IMG_INIT_PNG); // initializes img libary
//         IMG_Init(IMG_INIT_JPG);
//         TTF_Init();

//         // Creates a SDL window and checks if it's created successfully
//         window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
//         if (window) {
//             std::cout << "Window successfully created!" << std::endl;
//         }

//         // Creates a SDL renderer and checks if it's created successfully
//         renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//         if (renderer) {
//             std::cout << "Renderer successfully created!" << std::endl;
//         }

//         play = new Text("play", 540 - 200, 150, 300, 100, 24);
//         quit = new Text("quit", 540 - 200, 300, 300, 100, 24);

//         isRunning = true;
//     } else {
//         isRunning = false;
//     }
// }

// void Menu::handleEvents() {
//     SDL_PollEvent(&event);
//     switch (event.type) {
//         case SDL_QUIT:
//             isRunning = false;
//             break;
//         default:
//             break;
//     }
// }

// void Menu::update() {
// }

// void Menu::render() {
//     SDL_SetRenderDrawColor(renderer, 42, 41, 62, 255);
//     SDL_RenderClear(renderer);

//     play->draw();
//     quit->draw();

//     SDL_RenderPresent(renderer);
// }

// void Menu::clean() {
//     SDL_DestroyWindow(window);
//     SDL_DestroyRenderer(renderer);
//     SDL_Quit();
//     std::cout << "Menu quit successfully!" << std::endl;
// }

// bool Menu::running() {
//     return isRunning;
// }
