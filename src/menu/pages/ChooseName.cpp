#include "Page.h"

void ChooseName::init() {
    texts.clear();

    active = true;
    selection = 0;
}

void ChooseName::handleKeyboard() {
    if (active) {
        if (Menu::event.type == SDL_KEYDOWN) {
            switch (Menu::event.key.keysym.sym) {}
        }
    }
}

void ChooseName::update() {
}

void ChooseName::render() {
}