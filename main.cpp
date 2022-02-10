#include <GL/glut.h>

#include "Level.h"
#include "Lazik.h"
#include "Drzewo.h"
#include "Krzak.h"

#include <iostream>

void tick(int);
void display();
void cameraControl();

int xRot = -135;
int zRot = -45;
double scale = 0.005;

bool keyboard[256] = {};
bool cam_keyboard[256] = {};

Drzewo drzewo_a(Level::Point(-50, -50, 14.5));
Drzewo drzewo_b(Level::Point(60, 40, 8.5));

Krzak krzak_a(-50, 40, 20, 18);
Krzak krzak_b(20, -60, 3, 15);
Krzak krzak_c(90, -40, 10, 15);
Krzak krzak_d(70, 70, 5, 15);
Krzak krzak_e(-43, -90, 13, 19);

Level level(3);
Lazik lazik(&level, keyboard, 0, 0, -8);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("lazik marsjanski");
	glutInitWindowSize(1280, 720);
	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(display);

	glutSpecialFunc([](int k, int, int) { cam_keyboard[k] = true; });
	glutSpecialUpFunc([](int k, int, int) { cam_keyboard[k] = false; });
	glutKeyboardFunc([](unsigned char k, int, int) { keyboard[k] = true; });
	glutKeyboardUpFunc([](unsigned char k, int, int) { keyboard[k] = false; });

	glutTimerFunc(33.33, tick, 0);
	glutMainLoop();

	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glLoadIdentity();
	glRotated(xRot, 1.0, 0.0, 0.0);
	glRotated(zRot, 0.0, 0.0, 1.0);
	glScaled(scale, scale, scale);

	level.renderPoly();
	lazik.render();

	drzewo_a.render();
	drzewo_b.render();

	krzak_a.render();
	krzak_b.render();
	krzak_c.render();
	krzak_d.render();
	krzak_e.render();

	glFlush();
	glutSwapBuffers();
}

void tick(int) {
	lazik.tick();
	cameraControl();

	glutPostRedisplay();
	glutTimerFunc(33.33, tick, 0);
}

void cameraControl() {
	if (cam_keyboard[GLUT_KEY_RIGHT]) zRot = (zRot - 2) % 360;
	if (cam_keyboard[GLUT_KEY_LEFT]) zRot = (zRot + 2) % 360;
	if (cam_keyboard[GLUT_KEY_UP]) xRot = (xRot - 2) % 360;
	if (cam_keyboard[GLUT_KEY_DOWN]) xRot = (xRot + 2) % 360;
	if (cam_keyboard[GLUT_KEY_F1]) scale += 0.0002;
	if (cam_keyboard[GLUT_KEY_F2]) scale -= 0.0002;
}



