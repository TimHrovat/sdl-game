#pragma once

#include "../game/Game.h"
#include "../text/text.h"
#include "SDL.h"
#include "pages/Page.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Text;
class Page;
class MainMenu;
class LevelSelection;
class Scoreboard;
class ScoreboardLevel;
class ChooseName;

class Menu {

  protected:
    SDL_Window *window;

  public:
    static bool isRunning;
    static std::string currentPlayerName;
    static bool gameRunning;
    Menu(){};
    ~Menu(){};

    void init(const char *title, int xpos, int ypos, int width, int height);

    bool running();

    void handleEvents();
    void update();
    void render();
    void clean();

    static SDL_Renderer *renderer;
    static Game *game;
    static SDL_Event event;

    static MainMenu *mainMenu;
    static LevelSelection *levelSelection;
    static Scoreboard *scoreboard;
    static ChooseName *chooseName;
    static ScoreboardLevel *levelScores;
    static bool enterPressed;
};
