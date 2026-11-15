
#include <GL/freeglut.h>
#include <GL/glu.h>

#include "characters/farmer.h"
#include "characters/primitives.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(3, 2.5, 7,
              0, 1, 0,
              0, 1, 0);

    // Ground
    glColor3f(0.35f, 0.65f, 0.25f);

    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-10, 0, -10);
        glVertex3f(10, 0, -10);
        glVertex3f(10, 0, 10);
        glVertex3f(-10, 0, 10);
    glEnd();

    // Draw our enhanced farmer
    drawFarmer(0, 0, 0, 1.0f);

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.55f, 0.75f, 0.95f, 1.0f);
    initCowLighting();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH
    );

    glutInitWindowSize(900, 700);

    glutCreateWindow("Enhanced Farmer Character");

    init();

    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, 900.0 / 700.0, 0.1, 100);

    glutMainLoop();

    return 0;
}
