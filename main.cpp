
#include <GL/freeglut.h>
#include <GL/glu.h>

#include "src/farmyard.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 6.0, 23.0,
        0.0, 0.0, -1.0,
        0.0, 1.0, 0.0
    );

    drawFarmyard();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(55.0, (float)w / h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 800);

    glutCreateWindow("Farmers Day - Scene 3: Farmyard");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
