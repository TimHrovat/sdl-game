#include "Page.h"

void MainMenu::init() {
    texts.clear();

    texts.push_back(new Text("play", 0, 150 + 0 * 70, 40, true));
    texts.push_back(new Text("restore", 0, 150 + 1 * 70, 40, true));
    texts.push_back(new Text("scoreboard", 0, 150 + 2 * 70, 40, true));
    texts.push_back(new Text("replay", 0, 150 + 3 * 70, 40, true));
    texts.push_back(new Text("choose name", 0, 150 + 4 * 70, 40, true));
    texts.push_back(new Text("quit", 0, 150 + 5 * 70, 40, true));

    active = true;
    selection = 0;
}

void MainMenu::handleKeyboard() {
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
                    Menu::enterPressed = true;
                    handleSelection();
                    break;
            }
        }
    }
}

void MainMenu::handleSelection() {
    switch (selection) {
        case 0: // play -> level selection
            Menu::levelSelection->init();
            break;
        case 1: // restore
            break;
        case 2: // scoreboard
            Menu::scoreboard->init();
            break;
        case 3: // replay
            break;
        case 4: // choose name
            Menu::chooseName->init();
            break;
        case 5: // quit
            Menu::isRunning = false;
            break;
    }

    active = false;
}