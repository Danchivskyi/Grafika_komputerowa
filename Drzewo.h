#pragma once

#include "level.h"

class Drzewo : private Level::Obstacle {
private:
    void renderBody(int r = 1, int h = 50);
    void renderHead(int offset = 0, int r = 6, int h = 25);

    static float PI2;

public:
    Drzewo(const Level::Point& pos) : Obstacle(pos, 6) {};
    ~Drzewo() {};

    void render();
};

