#include "Page.h"

void LevelSelection::init() {
    texts.clear();
    texts.push_back(new Text("Level 1", 0, 180 + 0 * 70, 40, true));
    texts.push_back(new Text("Level 2", 0, 180 + 1 * 70, 40, true));
    texts.push_back(new Text("Level 3", 0, 180 + 2 * 70, 40, true));
    active = true;
    selection = 0;
}

void LevelSelection::handleKeyboard() {
    if (active) {
        if (Menu::event.type == SDL_KEYDOWN) {
            switch (Menu::event.key.keysym.sym) {
                case SDLK_DOWN:
                    if (selection == texts.size() - 1) {
                        selection = 0;
                        return;
                    }
                    selection++;
                    break;
                case SDLK_UP:
                    if (selection == 0) {
                        selection = texts.size() - 1;
                        return;
                    }
                    selection--;
                    break;
                case SDLK_RETURN:
                    if (!Menu::enterPressed)
                        handleSelection();
                    break;
            }
        }
    }
}

void LevelSelection::handleSelection() {
    Menu::gameRunning = true;
    Menu::game->init(selection + 1);

    active = false;
}