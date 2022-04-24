#include "Page.h"

void Scoreboard::init() {
    texts.clear();

    texts.push_back(new Text("Level 1", 0, 150, 40, true));
    texts.push_back(new Text("Level 2", 0, 150 + 70, 40, true));
    texts.push_back(new Text("Level 3", 0, 150 + 70 * 2, 40, true));

    Menu::levelScores->init();

    active = true;
    selection = 0;
}

void Scoreboard::handleKeyboard() {
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

void Scoreboard::handleSelection() {
    Menu::levelScores->update(selection + 1);
    Menu::levelScores->setActive(true);

    active = false;
}