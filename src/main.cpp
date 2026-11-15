
#include <GL/freeglut.h>

#include "sunrise.h"
#include "bedroom.h"
#include "farmyard.h"
#include "milking.h"
#include "packaging.h"
#include "journey.h"
#include "shop.h"
#include "sunset.h"

namespace
{
    int startTime = 0;
    float elapsedSeconds = 0.0f;

    constexpr float SCENE_DURATION = 20.0f;

    void display()
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(0.0f, 5.0f, 22.0f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f);

        if (elapsedSeconds < SCENE_DURATION)
        {
            updateSunrise(elapsedSeconds);
        }
        else if (elapsedSeconds < SCENE_DURATION * 2.0f)
{
    updateBedroom(elapsedSeconds - SCENE_DURATION);
    glClearColor(0.65f, 0.70f, 0.75f, 1.0f);
}
        else if (elapsedSeconds < SCENE_DURATION * 3.0f)
        {
            glClearColor(0.55f, 0.70f, 0.82f, 1.0f);
        }
        else if (elapsedSeconds < SCENE_DURATION * 4.0f)
        {
            glClearColor(0.55f, 0.62f, 0.55f, 1.0f);
        }
        else if (elapsedSeconds < SCENE_DURATION * 5.0f)
        {
            glClearColor(0.72f, 0.76f, 0.75f, 1.0f);
        }
        else if (elapsedSeconds < SCENE_DURATION * 6.0f)
        {
            updateJourney(
                elapsedSeconds - SCENE_DURATION * 5.0f,
                false
            );
        }
        else if (elapsedSeconds < SCENE_DURATION * 7.0f)
        {
            glClearColor(0.68f, 0.72f, 0.68f, 1.0f);
        }
        else if (elapsedSeconds < SCENE_DURATION * 8.0f)
        {
            updateJourney(
                elapsedSeconds - SCENE_DURATION * 7.0f,
                true
            );
        }
        else
        {
            glClearColor(0.35f, 0.20f, 0.22f, 1.0f);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLfloat lightPosition[] = {-6.0f, 5.0f, -9.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        if (elapsedSeconds < SCENE_DURATION)
        {
            drawSunrise();
        }
        else if (elapsedSeconds < SCENE_DURATION * 2.0f)
        {
            drawBedroom();
        }
        else if (elapsedSeconds < SCENE_DURATION * 3.0f)
        {
            drawFarmyard();
        }
        else if (elapsedSeconds < SCENE_DURATION * 4.0f)
        {
            drawMilkingArea(elapsedSeconds - SCENE_DURATION * 3.0f);
        }
        else if (elapsedSeconds < SCENE_DURATION * 5.0f)
        {
            drawPackagingRoom();
        }
        else if (elapsedSeconds < SCENE_DURATION * 6.0f)
        {
            drawJourney(
                elapsedSeconds - SCENE_DURATION * 5.0f,
                false
            );
        }
        else if (elapsedSeconds < SCENE_DURATION * 7.0f)
        {
          drawVillageShop(elapsedSeconds - SCENE_DURATION * 6.0f);
        }
        else if (elapsedSeconds < SCENE_DURATION * 8.0f)
        {
            drawJourney(
                elapsedSeconds - SCENE_DURATION * 7.0f,
                true
            );
        }
        else
        {
            drawSunset();
        }

        glutSwapBuffers();
    }

    void update(int value)
    {
        elapsedSeconds =
            (glutGet(GLUT_ELAPSED_TIME) - startTime) / 1000.0f;

        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
    }

    void init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);

        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

        GLfloat ambient[]  = {0.45f, 0.45f, 0.45f, 1.0f};
        GLfloat diffuse[]  = {0.90f, 0.85f, 0.75f, 1.0f};
        GLfloat specular[] = {0.35f, 0.35f, 0.35f, 1.0f};

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

        glMatrixMode(GL_MODELVIEW);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH
    );

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("A Day in the Life of a Farmer");

    init();

    startTime = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
