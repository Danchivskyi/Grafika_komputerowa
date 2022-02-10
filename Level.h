#pragma once

#include <algorithm>
#include <vector>
#include <list>

class Level {
public:
    class Point {
    public:
        float x, y, z;

        Point(float x = 0.0, float y = 0.0, float z = 0.0) : x(x), y(y), z(z) {}

        Point operator- (const Point& p) const;
        Point operator+ (const Point& p) const;
        Point operator^ (const Point& p) const;
        float operator* (const Point& p) const;
    };

    class Triangle {
    private:
        static float sign(const Point& a, const Point& b, const Point& c);

    public:
        Point a, b, c;

        Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c) {};

        bool isInside(const Point& p) const;
        Point getNormal() const;
    };

    class Obstacle {
    public:
        Point pos;
        float r;

        static std::vector<Obstacle*> list;

        Obstacle(const Point& pos, float r) : pos(pos), r(r) { Obstacle::list.push_back(this); };
        ~Obstacle() { Obstacle::list.erase(std::remove(Obstacle::list.begin(), Obstacle::list.end(), this), Obstacle::list.end()); };
    };

private:
    int size;
    int scale;

    float* map;
    float* shades;

    std::vector<Obstacle*>* obstacles;

    static int vert;
    static int range;

    Triangle getTriangle(const Point& p) const;

public:
    Level(int scale = 1);
    ~Level();

    float getDistance(const Point& p) const;
    std::vector<Obstacle*> getObstacles(const Point& p) const;
    bool canMove(const Point& p) const;

    void render() const;
    void renderFlat() const;
    void renderPoly() const;
};


