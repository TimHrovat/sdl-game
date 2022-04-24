#pragma once

#include "../../text/text.h"
#include "../Menu.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Text;

struct TextTemplate {
    char text[31];
    int x, y;
    int w, h;
    int size;
};

class Page {
  protected:
    std::vector<Text *> texts;
    bool active;
    int selection = 0;

  public:
    Page(){};
    ~Page(){};

    bool isActive() { return active; }
    void setActive(bool setTo) { active = setTo; }

    virtual void handleKeyboard() = 0;
    virtual void init() = 0;
    virtual void update();
    virtual void render();
};

class MainMenu : public Page {
  public:
    void init();
    void handleKeyboard();
    void handleSelection();
    void update() override;
};

class LevelSelection : public Page {
  public:
    void init();
    void handleKeyboard();
    void handleSelection();
};

class ScoreboardLevel : public Page {
  public:
    void init();
    void handleKeyboard();
    void update(int level);
    void handleSelection();
};

class Scoreboard : public Page {
  public:
    void init();
    void handleKeyboard();
    void handleSelection();
};

class ChooseName : public Page {
  private:
    bool shiftPressed = false;
    bool backspacePressed = false;
    std::string newPlayerName = "";

  public:
    void init();
    void handleKeyboard();
    void update() override;
    void render() override;
    void handleSelection();
};