#include "Page.h"

void Page::update() {
    if (active) {
        for (auto &t : texts) {
            t->changeColorBrightness(255);
        }
        texts[selection]->changeColorBrightness(180);
    }
}

void Page::render() {
    if (active) {
        for (auto &t : texts) {
            t->draw();
        }
    }
}
