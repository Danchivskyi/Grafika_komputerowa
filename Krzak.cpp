#include <GL/glut.h>
#include <math.h>
#include "Krzak.h"

const double PI = 3.141592653589793;
const double PI_2 = 3.141592653589793;

Krzak::Krzak(float x, float y, float z, int leaves) : x(x), y(y), z(z), leaves(leaves) {
    if (this->leaves < 1) this->leaves = 1;

    this->alpha = PI / (8 * this->leaves);

    if (this->leaves > 8) this->alpha *= 1.1;
    if (this->leaves > 10) this->alpha *= 1.2;
    if (this->leaves > 12) this->alpha *= 1.3;
    if (this->leaves > 14) this->alpha *= 1.4;
    if (this->leaves > 16) this->alpha *= 1.5;
    if (this->leaves > 18) this->leaves = 18;
}

void Krzak::renderBody(int r) {
    double tmp_x, tmp_y, alpha;

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0, 0.3, 0);
    glVertex3d(x, y, z);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 10) {
        tmp_x = r * sin(alpha);
        tmp_y = r * cos(alpha);
        glColor3d(0, 0.3, 0);
        glVertex3d(x + tmp_x, y + tmp_y, z);
    }
    glEnd();
}

void Krzak::renderLeaf(float angle, int xdir, int ydir, int r, int h) {
    float tmp_x, tmp_y, alpha;

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.0, 0.5, 0.0);
    glVertex3d(xdir * cos(angle) * h + x, ydir * cos(angle) * h + y, sin(angle) * h + z);

    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 10) {
        tmp_x = r * sin(alpha);
        tmp_y = r * cos(alpha);
        glColor3d(0.0, 0.3, 0.0);
        glVertex3d(x + tmp_x, y + tmp_y, z);
    }
    glEnd();
}

void Krzak::render() {
    this->renderBody();

    for (int i = 0; i < this->leaves; i++) {
        this->renderLeaf(PI_2 + i * this->alpha, 1, 1);
        this->renderLeaf(PI_2 + i * this->alpha, 1, -1);
        this->renderLeaf(PI_2 + i * this->alpha, 0, 1);
        this->renderLeaf(PI_2 + i * this->alpha, 0, -1);
        this->renderLeaf(PI_2 - i * this->alpha, 1, 1);
        this->renderLeaf(PI_2 - i * this->alpha, 1, 0);
        this->renderLeaf(PI_2 - i * this->alpha, 1, -1);
        this->renderLeaf(PI_2 - i * this->alpha, -1, 0);
    }
}


