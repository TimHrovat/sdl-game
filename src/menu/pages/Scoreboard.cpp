#include "Page.h"

void Scoreboard::init() {
    texts.clear();

    active = true;
    selection = 0;
}

void Scoreboard::handleKeyboard() {
    if (active) {
        if (Menu::event.type == SDL_KEYDOWN) {
            switch (Menu::event.key.keysym.sym) {}
        }
    }
}

void Scoreboard::update() {
}

void Scoreboard::render() {
}