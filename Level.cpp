#include <GL/glut.h>
#include <cmath>
#include <random>
#include "level.h"

#include <iostream>

int Level::vert = 10;
int Level::range = 15;

std::vector<Level::Obstacle*> Level::Obstacle::list;

Level::Level(int scale) : scale(scale) {
    if (this->scale < 1) this->scale = 1;

    this->size = 100 * this->scale;

    int n = this->vert * this->vert;
    this->map = new float[n];
    this->shades = new float[n * 2];

    this->obstacles = new std::vector<Obstacle*>[this->scale * this->scale];

    std::default_random_engine engine;
    std::uniform_real_distribution<float> dist(-this->range, this->range);

    for (int i = 0; i < n; i++) {
        this->map[i] = dist(engine);
        this->shades[i * 2] = 0.15 + this->map[i] / 120;
        this->shades[i * 2 + 1] = 0.4 + this->map[i] / 45;
    }

    // populate obsticle map
    for (const auto o : Obstacle::list) {
        int x = (o->pos.x + this->size / 2) / 100;
        int y = (o->pos.y + this->size / 2) / 100;

        this->obstacles[this->scale * x + y].push_back(o);
    }
}

Level::~Level() {
    delete[] this->map;
    delete[] this->shades;
    delete[] this->obstacles;
}

Level::Point Level::Point::operator- (const Point& p) const {
    return Point(this->x - p.x, this->y - p.y, this->z - p.z);
}

Level::Point Level::Point::operator+ (const Point& p) const {
    return Point(this->x + p.x, this->y + p.y, this->z + p.z);
}

float Level::Point::operator* (const Point& p) const {
    return this->x * p.x + this->y * p.y + this->z * p.z;
}

Level::Point Level::Point::operator^ (const Point& p) const {
    return Point(this->y * p.z - this->z * p.y, this->z * p.x - this->x * p.z, this->x * p.y - this->y * p.x);
}

float Level::Triangle::sign(const Point& a, const Point& b, const Point& c) {
    return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}

bool Level::Triangle::isInside(const Point& p) const {
    float d1 = Level::Triangle::sign(p, this->a, this->b);
    float d2 = Level::Triangle::sign(p, this->b, this->c);
    float d3 = Level::Triangle::sign(p, this->c, this->a);

    bool neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(neg && pos);
}

Level::Point Level::Triangle::getNormal() const {
    return (this->b - this->a) ^ (this->c - this->a);
}

Level::Triangle Level::getTriangle(const Point& p) const {
    int step = this->size / (this->vert - 1);
    int offset = this->size / 2;
    int x = (p.x + offset) / step;
    int y = (p.y + offset) / step;

    Point pts[] = { Point(x * step - offset, y * step - offset, this->map[x * this->vert + y]),
                    Point((x + 1) * step - offset, y * step - offset, this->map[(x + 1) * this->vert + y]),
                    Point(x * step - offset, (y + 1) * step - offset, this->map[x * this->vert + y + 1]),
                    Point((x + 1) * step - offset, (y + 1) * step - offset, this->map[(x + 1) * this->vert + y + 1]) };

    bool side = Triangle(pts[0], pts[1], pts[2]).isInside(Point(p.x, p.y));

    return Triangle(side ? pts[0] : pts[3], pts[1], pts[2]);
}

float Level::getDistance(const Point& p) const {
    Triangle t = this->getTriangle(p);
    Point n = t.getNormal();

    return p.z + (p.x * n.x + p.y * n.y - (n * t.a)) / n.z;
}

std::vector<Level::Obstacle*> Level::getObstacles(const Point& p) const {
    float half = this->size / 2;
    int x = (p.x + half) / 100;
    int y = (p.y + half) / 100;

    return this->obstacles[x * this->scale + y];
}

bool Level::canMove(const Point& p) const {
    for (const auto o : this->getObstacles(p)) {
        float x = o->pos.x - (p.x - 12);
        float y = o->pos.y - (p.y + 6);

        if (sqrt(x * x + y * y) < (o->r + 12)) return false;
    }

    return true;
}

void Level::render() const {
    double x = 100 * this->scale, z = 100 * this->scale, y, i, j;

    glBegin(GL_TRIANGLE_STRIP);
    for (i = -x; i < x; i += 1) {
        glColor3d(0.15, .8 + sin(i / 10) * .5, 0.15);

        double h1 = sin(i / 10) * 10;
        double h2 = sin((i + 1) / 10) * 10;

        for (j = -z; j < z; j += 1) {
            glVertex3d(i, j, h1);
            glVertex3d(i + 1, j, h2);
            glVertex3d(i, j + 1, h1);
            glVertex3d(i + 1, j + 1, h2);
        }
    }
    glEnd();
}

void Level::renderFlat() const {
    double x = 100 * this->scale;

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.15, 0.4, 0.15);
    glVertex3d(-x, -x, 0);
    glVertex3d(-x, x, 0);
    glVertex3d(x, -x, 0);
    glVertex3d(x, x, 0);
    glEnd();
}

void Level::renderPoly() const {
    int end = this->vert - 1;
    int half = this->size / 2;
    float step = static_cast<float>(this->size) / end;

    for (int i = 0; i < end; i++) {
        int color = 2 * i * this->vert;

        glBegin(GL_TRIANGLE_STRIP);
        glColor3d(this->shades[color], this->shades[color + 1], this->shades[color]);
        glVertex3d(-half + i * step, -half, this->map[i * this->vert]);

        for (int j = 0; j < end; j++) {
            int col_cur = 2 * ((i + 1) * this->vert + j);
            int col_next = 2 * (i * this->vert + j + 1);
            glColor3d(this->shades[col_cur], this->shades[col_cur + 1], this->shades[col_cur]);
            glVertex3d(-half + (i + 1) * step, -half + j * step, this->map[(i + 1) * this->vert + j]);
            glColor3d(this->shades[col_next], this->shades[col_next + 1], this->shades[col_next]);
            glVertex3d(-half + i * step, -half + (j + 1) * step, this->map[i * this->vert + j + 1]);
        }

        color = 2 * ((i + 1) * this->vert + end);
        glColor3d(this->shades[color], this->shades[color + 1], this->shades[color]);
        glVertex3d(-half + (i + 1) * step, half, this->map[(i + 1) * this->vert + end]);
        glEnd();
    }
}


