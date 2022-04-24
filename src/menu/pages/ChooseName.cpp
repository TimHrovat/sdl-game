#include "Page.h"

void ChooseName::init() {
    texts.clear();

    texts.push_back(new Text(newPlayerName.c_str(), 300, 280, 40, false));

    active = true;
    selection = 0;
}

void ChooseName::handleKeyboard() {
    if (active) {
        if (Menu::event.type == SDL_KEYDOWN) {
            if (!Menu::enterPressed)
                switch (Menu::event.key.keysym.sym) {
                    case SDLK_RETURN:
                        Menu::currentPlayerName = newPlayerName;
                        Menu::enterPressed = true;
                        active = false;
                        Menu::mainMenu->init();
                        break;
                }
            handleSelection();
        } else if (Menu::event.type == SDL_KEYUP) {
            switch (Menu::event.key.keysym.sym) {
                case SDLK_LSHIFT:
                    shiftPressed = false;
                    break;
                case SDLK_BACKSPACE:
                    backspacePressed = false;
            }
        }
    }
}

void ChooseName::update() {
    std::string line = "Enter name: " + newPlayerName;

    if (active) texts[0]->update(line.c_str());
}

void ChooseName::render() {
    if (active)
        for (auto &t : texts) {
            t->draw();
        }
}

void ChooseName::handleSelection() {
    if (newPlayerName.size() != 0)
        switch (Menu::event.key.keysym.sym) {
            case SDLK_BACKSPACE:
                if (!backspacePressed)
                    newPlayerName.pop_back();
                backspacePressed = true;
                break;
        }
    if (newPlayerName.size() < 15)
        switch (Menu::event.key.keysym.sym) {
            case SDLK_LSHIFT:
                shiftPressed = true;
                break;

            case SDLK_SPACE:
                newPlayerName += "_";
                break;

            case SDLK_a:
                if (shiftPressed)
                    newPlayerName += "A";
                else
                    newPlayerName += "a";
                break;

            case SDLK_b:
                if (shiftPressed)
                    newPlayerName += "B";
                else
                    newPlayerName += "b";
                break;

            case SDLK_c:
                if (shiftPressed)
                    newPlayerName += "C";
                else
                    newPlayerName += "c";
                break;

            case SDLK_d:
                if (shiftPressed)
                    newPlayerName += "D";
                else
                    newPlayerName += "d";
                break;

            case SDLK_e:
                if (shiftPressed)
                    newPlayerName += "E";
                else
                    newPlayerName += "e";
                break;

            case SDLK_f:
                if (shiftPressed)
                    newPlayerName += "F";
                else
                    newPlayerName += "f";
                break;

            case SDLK_g:
                if (shiftPressed)
                    newPlayerName += "G";
                else
                    newPlayerName += "g";
                break;

            case SDLK_h:
                if (shiftPressed)
                    newPlayerName += "H";
                else
                    newPlayerName += "h";
                break;

            case SDLK_i:
                if (shiftPressed)
                    newPlayerName += "I";
                else
                    newPlayerName += "i";
                break;

            case SDLK_j:
                if (shiftPressed)
                    newPlayerName += "J";
                else
                    newPlayerName += "j";
                break;

            case SDLK_k:
                if (shiftPressed)
                    newPlayerName += "K";
                else
                    newPlayerName += "k";
                break;

            case SDLK_l:
                if (shiftPressed)
                    newPlayerName += "L";
                else
                    newPlayerName += "l";
                break;

            case SDLK_m:
                if (shiftPressed)
                    newPlayerName += "M";
                else
                    newPlayerName += "m";
                break;

            case SDLK_n:
                if (shiftPressed)
                    newPlayerName += "N";
                else
                    newPlayerName += "n";
                break;

            case SDLK_o:
                if (shiftPressed)
                    newPlayerName += "O";
                else
                    newPlayerName += "o";
                break;

            case SDLK_p:
                if (shiftPressed)
                    newPlayerName += "P";
                else
                    newPlayerName += "p";
                break;

            case SDLK_q:
                if (shiftPressed)
                    newPlayerName += "Q";
                else
                    newPlayerName += "q";
                break;

            case SDLK_r:
                if (shiftPressed)
                    newPlayerName += "R";
                else
                    newPlayerName += "r";
                break;

            case SDLK_s:
                if (shiftPressed)
                    newPlayerName += "S";
                else
                    newPlayerName += "s";
                break;

            case SDLK_t:
                if (shiftPressed)
                    newPlayerName += "T";
                else
                    newPlayerName += "t";
                break;

            case SDLK_u:
                if (shiftPressed)
                    newPlayerName += "U";
                else
                    newPlayerName += "u";
                break;

            case SDLK_v:
                if (shiftPressed)
                    newPlayerName += "V";
                else
                    newPlayerName += "v";
                break;

            case SDLK_w:
                if (shiftPressed)
                    newPlayerName += "W";
                else
                    newPlayerName += "w";
                break;

            case SDLK_x:
                if (shiftPressed)
                    newPlayerName += "X";
                else
                    newPlayerName += "x";
                break;

            case SDLK_y:
                if (shiftPressed)
                    newPlayerName += "Y";
                else
                    newPlayerName += "y";
                break;

            case SDLK_z:
                if (shiftPressed)
                    newPlayerName += "Z";
                else
                    newPlayerName += "z";
                break;

            case SDLK_0:
                newPlayerName += "0";
                break;

            case SDLK_1:
                newPlayerName += "1";
                break;

            case SDLK_2:
                newPlayerName += "2";
                break;

            case SDLK_3:
                newPlayerName += "3";
                break;

            case SDLK_4:
                newPlayerName += "4";
                break;

            case SDLK_5:
                newPlayerName += "5";
                break;

            case SDLK_6:
                newPlayerName += "6";
                break;

            case SDLK_7:
                newPlayerName += "7";
                break;

            case SDLK_8:
                newPlayerName += "8";
                break;

            case SDLK_9:
                newPlayerName += "9";
                break;
        }
}