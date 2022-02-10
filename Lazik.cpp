#include <GL/glut.h>
#include <math.h>
#include "Lazik.h"

#include <iostream>

const double PI = 3.141592653589793;

void Lazik::renderBody() {
    double x, y, z = y = x = 0;

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(x, y, z);
    glVertex3d(x, y - 12, z);
    glVertex3d(x + 24, y, z);
    glVertex3d(x + 24, y - 12, z);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.6, 0.0, 0.0);
    glVertex3d(x, y, z - 6);
    glVertex3d(x + 24, y, z - 6);
    glVertex3d(x, y - 12, z - 6);
    glVertex3d(x + 24, y - 12, z - 6);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.5, 0.0, 0.0);
    glVertex3d(x, y, z);
    glVertex3d(x, y, z - 6);
    glVertex3d(x, y - 12, z);
    glVertex3d(x, y - 12, z - 6);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.5, 0.0, 0.0);
    glVertex3d(x + 24, y, z);
    glVertex3d(x + 24, y - 12, z);
    glVertex3d(x + 24, y, z - 6);
    glVertex3d(x + 24, y - 12, z - 6);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.8, 0.0, 0.0);
    glVertex3d(x, y - 12, z);
    glVertex3d(x, y - 12, z - 6);
    glVertex3d(x + 24, y - 12, z);
    glVertex3d(x + 24, y - 12, z - 6);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.8, 0.0, 0.0);
    glVertex3d(x, y, z);
    glVertex3d(x + 24, y, z);
    glVertex3d(x, y, z - 6);
    glVertex3d(x + 24, y, z - 6);
    glEnd();
}

void Lazik::renderWheel(double x, double y, double z) {
    double tmp_x, tmp_z, alpha, r = 2, h_top = 1, h_bot = -1;

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.3, 0.3, 0.3);
    glVertex3d(x, y + h_bot, z);
    for (alpha = 0; alpha <= 2 * PI; alpha += PI / 10.0) {
        tmp_x = r * sin(alpha);
        tmp_z = r * cos(alpha);
        glColor3d(0.1, 0.1, 0.1);
        glVertex3d(x + tmp_x, y + h_bot, z + tmp_z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.1, 0.1, 0.1);
    for (alpha = 0.0; alpha <= 2 * PI; alpha += PI / 10.0) {
        tmp_x = r * sin(alpha);
        tmp_z = r * cos(alpha);
        glVertex3d(x + tmp_x, y + h_bot, z + tmp_z);
        glVertex3d(x + tmp_x, y + h_top, z + tmp_z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(0.3, 0.3, 0.3);
    glVertex3d(x, y + h_top, z);
    for (alpha = 0; alpha >= -2 * PI; alpha -= PI / 10) {
        tmp_x = r * sin(alpha);
        tmp_z = r * cos(alpha);
        glColor3d(0.1, 0.1, 0.1);
        glVertex3d(x + tmp_x, y + h_top, z + tmp_z);
    }
    glEnd();
}

void Lazik::renderHeadlight(double x, double y, double z) {
    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x, y, z);
    glVertex3d(x, y - 2, z);
    glVertex3d(x + 1, y, z);
    glVertex3d(x + 1, y - 2, z);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x, y, z - 1);
    glVertex3d(x + 1, y, z - 1);
    glVertex3d(x, y - 2, z - 1);
    glVertex3d(x + 1, y - 2, z - 1);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x, y, z);
    glVertex3d(x, y, z - 1);
    glVertex3d(x, y - 2, z);
    glVertex3d(x, y - 2, z - 1);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x + 1, y, z);
    glVertex3d(x + 1, y - 2, z);
    glVertex3d(x + 1, y, z - 1);
    glVertex3d(x + 1, y - 2, z - 1);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x, y - 2, z);
    glVertex3d(x, y - 2, z - 1);
    glVertex3d(x + 1, y - 2, z);
    glVertex3d(x + 1, y - 2, z - 1);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 1.0, 1.0);
    glVertex3d(x, y, z);
    glVertex3d(x + 1, y, z);
    glVertex3d(x, y, z - 1);
    glVertex3d(x + 1, y, z - 1);
    glEnd();
}

void Lazik::renderHead() {
    double x, y, z = y = x = 0;

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(x + 10, y, z + 3);
    glVertex3d(x + 10, y - 12, z + 3);
    glVertex3d(x + 24, y, z + 3);
    glVertex3d(x + 24, y - 12, z + 3);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.6, 0.0, 0.0);
    glVertex3d(x, y, z);
    glVertex3d(x + 24, y, z);
    glVertex3d(x, y - 12, z);
    glVertex3d(x + 24, y - 12, z);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.7, 0.7, 0.7);
    glVertex3d(x + 10, y, z + 3);
    glVertex3d(x, y, z);
    glVertex3d(x + 10, y - 12, z + 3);
    glVertex3d(x, y - 12, z);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.5, 0.0, 0.0);
    glVertex3d(x + 24, y, z + 3);
    glVertex3d(x + 24, y - 12, z + 3);
    glVertex3d(x + 24, y, z);
    glVertex3d(x + 24, y - 12, z);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.7, 0.0, 0.0);
    glVertex3d(x + 10, y - 12, z + 3);
    glVertex3d(x, y - 12, z);
    glVertex3d(x + 24, y - 12, z + 3);
    glVertex3d(x + 24, y - 12, z);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0.7, 0.0, 0.0);
    glVertex3d(x + 10, y, z + 3);
    glVertex3d(x + 24, y, z + 3);
    glVertex3d(x, y, z);
    glVertex3d(x + 24, y, z);
    glEnd();
}

void Lazik::tick() {
    if (this->keyboard['w']) if (this->vel > -10) this->vel -= 0.3 * (1.047 - abs(this->dir) / 2);
    if (this->keyboard['s']) if (this->vel < 5) this->vel += 0.2 * (1.047 - abs(this->dir) / 2);

    if (this->keyboard['a'] && this->dir > 0) this->dir = 0;
    if (this->keyboard['a'] && this->dir > -1.047) this->dir -= 0.0314;
    if (this->keyboard['d'] && this->dir < 0) this->dir = 0;
    if (this->keyboard['d'] && this->dir < 1.047) this->dir += 0.0314;

    if (!this->keyboard['a'] && !this->keyboard['d'] && abs(this->dir) > 0.01) this->dir += this->dir > 0 ? -0.0314 : 0.0314;

    if (abs(this->vel) > 0.1) {
        float dx = cos(this->rot) * this->vel;
        float dy = sin(this->rot) * this->vel;

        // colision
        if (this->level->canMove(Level::Point(this->x + dx, this->y + dy))) {
            this->x += dx;
            this->y += dy;

            this->rot += 0.1 * this->dir;
            if (this->rot > 2 * PI) this->rot -= 2 * PI;
            if (this->rot < -2 * PI) this->rot += 2 * PI;
        }
        else this->vel = 0;

        if (!this->keyboard['w'] && !this->keyboard['s']) this->vel = 0.8 * this->vel;
    }

    float wheel1 = this->level->getDistance(Level::Point(x + 4, y - 6, z - 11));
    float wheel2 = this->level->getDistance(Level::Point(x + 20, y - 6, z - 11));

    this->tilt = atan((wheel1 - wheel2) / 24);

    // surface check
    if (this->level->getDistance(Level::Point(x + 4, y - 0.2, z - 11)) > 1.1) {
        this->z -= 1;
    }
    if (this->level->getDistance(Level::Point(x + 4, y - 0.2, z - 11)) < 1.1) {
        this->z += 1;
    }

}

void Lazik::render() {
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(this->rot * 57, 0.0, 0.0, 1.0);
    // glRotatef(-this->tilt * 57, 0.0, 1.0, 0.0);
    glTranslated(0.0, 6, 0);
    this->renderBody();
    this->renderHead();


    glPushMatrix();
    glTranslated(4, -0.2, -5.5);
    glRotated(this->dir * 57, 0.0, 0.0, 1.0);
    this->renderWheel(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(4, -11.8, -5.5);
    glRotated(this->dir * 57, 0.0, 0.0, 1.0);
    this->renderWheel(0, 0, 0);
    glPopMatrix();
    this->renderWheel(20, -0.2, -5.5);
    this->renderWheel(20, -11.8, -5.5);

    this->renderHeadlight(-0.2, -0.5, -1.2);
    this->renderHeadlight(23.2, -0.5, -1.2);
    this->renderHeadlight(-0.2, -9.5, -1.2);
    this->renderHeadlight(23.2, -9.5, -1.2);

    glPopMatrix();
}


