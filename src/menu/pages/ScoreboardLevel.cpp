#include "../../game/Game.h"
#include "Page.h"
#include <fstream>
#include <string>

void ScoreboardLevel::init() {
    texts.clear();

    texts.push_back(new Text("", 0, 150, 40, true));
    texts.push_back(new Text("", 0, 150, 40, true));
    texts.push_back(new Text("", 0, 150 + 70, 40, true));
    texts.push_back(new Text("", 0, 150 + 70, 40, true));
    texts.push_back(new Text("", 0, 150 + 70 * 2, 40, true));
    texts.push_back(new Text("", 0, 150 + 70 * 2, 40, true));
    texts.push_back(new Text("", 0, 150 + 70 * 3, 40, true));
    texts.push_back(new Text("", 0, 150 + 70 * 3, 40, true));
    texts.push_back(new Text("", 0, 150 + 70 * 4, 40, true));
    texts.push_back(new Text("", 0, 150 + 70 * 4, 40, true));

    selection = 0;
}

void ScoreboardLevel::update(int level) {
    std::ifstream data;

    switch (level) {
        case 1:
            data.open("assets/scores/level1_time.bin", std::ios::binary);
            break;
        case 2:
            data.open("assets/scores/level2_time.bin", std::ios::binary);
            break;
        case 3:
            data.open("assets/scores/level3_time.bin", std::ios::binary);
            break;
    }

    scoreWin temp;
    for (int i = 0; i < texts.size(); i++) {
        if (i % 2 == 0) {
            if (!(data.read((char *)&temp, sizeof(temp))))
                break;
        }
        std::string time = std::to_string(temp.time / 60) + ":" + std::to_string(temp.time % 60);
        std::string name = temp.name;
        if (i % 2 == 0)
            texts[i]->updateScoreboard(name.c_str(), true, false);
        else
            texts[i]->updateScoreboard(time.c_str(), false, true);
    }
    data.close();
}

void ScoreboardLevel::handleKeyboard() {}
