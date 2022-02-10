#include <GL/glut.h>
#include <math.h>
#include "Drzewo.h"

const double PI = 3.141592653589793;

float Drzewo::PI2 = 2 * PI + 1e-13;

void Drzewo::renderBody(int r, int h) {
    float tmp_x, tmp_y, alpha;

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.5, 0.3, 0.0);
    glVertex3d(this->pos.x, this->pos.y, this->pos.z);
    for (alpha = 0; alpha <= this->PI2; alpha += PI / 10.0) {
        tmp_x = r * sin(alpha);
        tmp_y = r * cos(alpha);
        glColor3d(0.4, 0.3, 0.0);
        glVertex3d(this->pos.x + tmp_x, this->pos.y + tmp_y, this->pos.z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.5, 0.3, 0.0);
    for (alpha = 0.0; alpha <= this->PI2; alpha += PI / 10.0) {
        tmp_x = r * sin(alpha);
        tmp_y = r * cos(alpha);
        glVertex3d(this->pos.x + tmp_x, this->pos.y + tmp_y, this->pos.z);
        glVertex3d(this->pos.x + tmp_x, this->pos.y + tmp_y, this->pos.z + h);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.5, 0.3, 0.0);
    glVertex3d(this->pos.x, this->pos.y, this->pos.z + h);
    for (alpha = 0; alpha >= -this->PI2; alpha -= PI / 10) {
        tmp_x = r * sin(alpha);
        tmp_y = r * cos(alpha);
        glColor3d(0.4, 0.3, 0.0);
        glVertex3d(this->pos.x + tmp_x, this->pos.y + tmp_y, this->pos.z + h);
    }
    glEnd();
}

void Drzewo::renderHead(int offset, int r, int h) {
    float tmp_x, tmp_y, alpha;

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.0, 0.5, 0.0);
    glVertex3d(this->pos.x, this->pos.y, offset + this->pos.z);
    for (alpha = 0; alpha <= this->PI2; alpha += PI / 10.0) {
        tmp_x = r * sin(alpha);
        tmp_y = r * cos(alpha);
        glColor3d(0.0, 0.8, 0.0);
        glVertex3d(this->pos.x + tmp_x, this->pos.y + tmp_y, offset + this->pos.z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.0, 0.35 - offset / 100, 0.0);
    glVertex3d(this->pos.x, this->pos.y, offset + h + this->pos.z);
    for (alpha = 0; alpha <= this->PI2; alpha += PI / 10.0) {
        tmp_x = r * sin(alpha);
        tmp_y = r * cos(alpha);
        glColor3d(0.0, 0.6, 0.0);
        glVertex3d(this->pos.x + tmp_x, this->pos.y + tmp_y, offset + this->pos.z);
    }
    glEnd();
}

void Drzewo::render() {
    this->renderBody();
    this->renderHead(50, 6);
    this->renderHead(40, 8);
    this->renderHead(30, 10);
}

