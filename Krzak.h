#pragma once

class Krzak {
private:
    float x, y, z, alpha;
    int leaves;
    void renderBody(int r = 1);
    void renderLeaf(float angle, int xdir, int ydir, int r = 1, int h = 15);

public:
    Krzak(float x, float y, float z, int leaves);
    ~Krzak() {};

    void render();
};


