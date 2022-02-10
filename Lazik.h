#pragma once

#include "level.h"

class Lazik {
private:
    double x, y, z, dir, rot, vel, tilt;
    bool* keyboard;
    Level* level;

    void renderBody();
    void renderHead();
    void renderWheel(double x, double y, double z);
    void renderHeadlight(double x, double y, double z);

    int checkSurface();

public:
    Lazik(Level* level, bool* kb, double x, double y, double z) : level{ level }, keyboard{ kb }, x{ x }, y{ y }, z{ z + 8 } { this->dir = this->rot = this->vel = this->tilt = 0; };
    ~Lazik() {};

    void tick();
    void render();
};

