#include "Page.h"

void MainMenu::init() {
    texts.clear();

    texts.push_back(new Text("play", 660, 150 + 0 * 70, 40, false));
    texts.push_back(new Text("restore", 660, 150 + 1 * 70, 40, false));
    texts.push_back(new Text("scoreboard", 660, 150 + 2 * 70, 40, false));
    texts.push_back(new Text("replay", 660, 150 + 3 * 70, 40, false));
    texts.push_back(new Text("choose name", 660, 150 + 4 * 70, 40, false));
    texts.push_back(new Text("quit", 660, 150 + 5 * 70, 40, false));
    texts.push_back(new Text("Welcome, ", 150, 270, 50, false));
    texts.push_back(new Text("", 150, 340, 50, false));

    char chr[16];

    for (int i = 0; i < Menu::currentPlayerName.size(); i++)
        chr[i] = Menu::currentPlayerName[i];
    chr[Menu::currentPlayerName.size()] = '\0';

    texts[7]->update(chr);

    active = true;
    selection = 0;
}

void MainMenu::handleKeyboard() {
    if (active) {
        if (Menu::event.type == SDL_KEYDOWN) {
            switch (Menu::event.key.keysym.sym) {
                case SDLK_DOWN:
                    if (selection == texts.size() - 3) {
                        selection = 0;
                        return;
                    }
                    selection++;
                    break;
                case SDLK_UP:
                    if (selection == 0) {
                        selection = texts.size() - 3;
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
            Menu::game->Restore();
            break;
        case 2: // scoreboard
            Menu::scoreboard->init();
            break;
        case 3: // replay
            Menu::game->Replay();
            break;
        case 4: // choose name
            Menu::chooseName->setActive(true);
            break;
        case 5: // quit
            Menu::isRunning = false;
            break;
    }

    active = false;
}

void MainMenu::update() {
    if (active) {
        for (auto &t : texts) {
            t->changeColorBrightness(255);
        }
        texts[selection]->changeColorBrightness(180);

        char chr[16];

        for (int i = 0; i < Menu::currentPlayerName.size(); i++)
            chr[i] = Menu::currentPlayerName[i];
        chr[Menu::currentPlayerName.size()] = '\0';

        // puts(chr);
        texts[7]->update(chr);
    }
}