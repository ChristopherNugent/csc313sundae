//start Windows
#include "stdafx.h"
#define _USE_MATH_DEFINES
//end Windows

#include <GL/glut.h>
#include <string.h>
#include <iostream>
#include <cmath>
// Display refresh time
const int REFRESH_MS = 5;

// Simulation seconds between state updates
// (large values might cause strange behavior)
const int TICK_TIME = 5;
int tick = 1;

const double Z_DIST = 25.5;


int xRot = 0;
int yRot = 0;

void keyboardFunc(unsigned char Key, int x, int y);
void display(void);
void reshape(int x, int y);
void timer(int value);
void parseArgs(int argc, char **argv);
void drawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(550, 550);
    glutCreateWindow("Gravity Simulation");
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glutKeyboardFunc(keyboardFunc);
    parseArgs(argc, argv);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}


void display(void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glPushMatrix();
    glTranslatef(0, 0, -Z_DIST);
    glRotatef(30, 1, 0, 0);
    glRotatef(yRot, 1, 0, 0);
    glRotatef(xRot, 0, 1, 0);

    // ice cream
    glColor3f(1, 1, 1);
    glutSolidSphere(2, 30, 30);

    // eyes
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(0.7, 0.7, 1);
    // glutSolidSphere(0.7, 30, 30);
    double y = sin(tick / 20.0) / 2;
    drawEllipsoid(30, 30, 0.7, y, 0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7, 0.7, 1);
    // glutSolidSphere(0.7, 30, 30);
    y = 0.7;
    drawEllipsoid(30, 30, 0.7, y, 0.7);
    glPopMatrix();

    //nose
    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(0, 0, 1.4);
    glutSolidSphere(0.7, 30, 30);
    glPopMatrix();

    //hat
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glRotatef(90, -1, 0, 0);
    double r1 = sin(tick / 100.0) * 15;
    double r2 = cos(tick / 100.0) * 15;
    glRotatef(r1, 0, 1, 0);
    glRotatef(r2, 1, 0 , 0);
    glColor3f(1, 1, 0);
    glutSolidCone(2, 4, 30, 30);
    glTranslatef(0, 0, -0.1);
    glColor3f(139 / 255.0, 69 / 255.0, 19 / 255.0);
    glutSolidCone(2.1, 3.75, 30, 30);
    glPopMatrix();

    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(0, -3, 0);
    glutSolidTeapot(3);
    glPopMatrix();

    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.5, 1.5, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, -2.3, 0);
    glRotatef(90, 0, 1 , 0);
    double r = sin(tick / 100.0) * 10;
    glRotatef(r, 1, 0, 0);
    glColor3f(139 / 255.0, 69 / 255.0, 19 / 255.0);
    glutSolidTorus(1, 1.5, 30, 30);
    glColor3f(0.5, 0.5, 1);
    glTranslatef(0, 0, 0.1);
    glutSolidTorus(1, 1.4, 30, 30);
    glPopMatrix();


    glPopMatrix();
    glFlush();
    tick++;
}

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 31.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);  //Use the whole window for rendering
}

// Called back when timer expired [NEW]
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(REFRESH_MS, timer, 0); // next timer call milliseconds later
}


//*****************************************************************************
//  START SIMULATION RELATED CODE
//*****************************************************************************

void keyboardFunc(unsigned char Key, int x, int y) {
    switch (Key) {
    // ROTATE SYSTEM
    case 'w':   yRot--; break;
    case 'a':   xRot--; break;
    case 's':   yRot++; break;
    case 'd':   xRot++; break;


    // EXIT
    case 27:    exit(1); break;
    };
}

void parseArgs(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            std::cout << "Initiating fullscreen." << std::endl;
            glutFullScreen();
        } else {
            std::cout << "Unrecognized option: " << argv[i] << std::endl;
        }

    }
}

void drawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC) {
    float tStep = (M_PI) / (float)uiSlices;
    float sStep = (M_PI) / (float)uiStacks;
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (float t = -M_PI / 2; t <= (M_PI / 2) + .0001; t += tStep)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (float s = -M_PI; s <= M_PI + .0001; s += sStep)
        {
            glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
            glVertex3f(fA * cos(t + tStep) * cos(s), fB * cos(t + tStep) * sin(s), fC * sin(t + tStep));
        }
        glEnd();
    }
}

