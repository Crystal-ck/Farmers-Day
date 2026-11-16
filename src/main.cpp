
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>
#include <cstdlib>

#include "journey.h"
#include "sunrise.h"
#include "bedroom.h"
#include "farmyard.h"
#include "milking.h"
#include "packaging.h"
#include "shop.h"
#include "sunset.h"
#include "../characters/primitives.h"

// --------------------------------------------------
// WINDOW SETTINGS
// --------------------------------------------------

const int WIN_W = 1280;
const int WIN_H = 800;

// --------------------------------------------------
// SCENE TIMING
// --------------------------------------------------

const float SUNRISE_DURATION = 8.0f;
const float BEDROOM_DURATION = 8.0f;
const float FARMYARD_DURATION = 13.0f;
const float MILKING_DURATION = 20.0f;
const float PACKAGING_DURATION = 24.0f;
const float JOURNEY_DURATION = 20.0f;
const float SHOP_DURATION = 18.0f;
const float RETURN_JOURNEY_DURATION = 20.0f;
const float SUNSET_DURATION = 18.0f;

// --------------------------------------------------
// SCENES
// --------------------------------------------------

enum Scene
{
    SCENE_SUNRISE,
    SCENE_BEDROOM,
    SCENE_FARMYARD,
    SCENE_MILKING,
    SCENE_PACKAGING,
    SCENE_JOURNEY,
    SCENE_SHOP,
    SCENE_RETURN_JOURNEY,
    SCENE_SUNSET,
    SCENE_FINISHED
};

Scene currentScene = SCENE_SUNRISE;

float sceneTime = 0.0f;
float previousTime = 0.0f;

// --------------------------------------------------
// CAMERA
// --------------------------------------------------

float smoothStep(float t)
{
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    return t * t * (3.0f - 2.0f * t);
}

void setCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (currentScene == SCENE_SUNRISE)
    {
        gluLookAt(
            0, 4, 18,
            0, 0, 0,
            0, 1, 0
        );
    }
    else if (currentScene == SCENE_BEDROOM)
    {
        gluLookAt(
            0.0f, 0.9f, 4.2f,
            0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );
    }
    else if (currentScene == SCENE_FARMYARD)
    {
        float t = smoothStep(sceneTime / FARMYARD_DURATION);

        float camX = 5.0f * t;
        float camY = 6.0f + ((2.5f - 6.0f) * t);
        float camZ = 23.0f + ((7.0f - 23.0f) * t);

        float targetX = 5.0f * t;
        float targetY = -0.8f * t;
        float targetZ = -1.0f + (-2.0f * t);

        gluLookAt(
            camX, camY, camZ,
            targetX, targetY, targetZ,
            0, 1, 0
        );
    }
    else if (currentScene == SCENE_MILKING)
    {
        gluLookAt(
            0.0f, 5.0f, 16.0f,
            0.0f, -0.5f, -1.0f,
            0.0f, 1.0f, 0.0f
        );
    }
    else if (currentScene == SCENE_PACKAGING)
    {
        gluLookAt(
            0.0f, 4.0f, 13.5f,
            0.0f, -0.3f, 0.0f,
            0.0f, 1.0f, 0.0f
        );
    }
    else if (currentScene == SCENE_JOURNEY ||
             currentScene == SCENE_RETURN_JOURNEY)
    {
        gluLookAt(
            0.0f, 6.0f, 23.0f,
            0.0f, 1.0f, -8.0f,
            0.0f, 1.0f, 0.0f
        );
    }
    else if (currentScene == SCENE_SHOP)
    {
        gluLookAt(
            0.0f, 5.0f, 17.0f,
            0.0f, 2.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );
    }
    else if (currentScene == SCENE_SUNSET ||
             currentScene == SCENE_FINISHED)
    {
        gluLookAt(
            0.0f, 8.0f, 25.0f,
            0.0f, 3.0f, -8.0f,
            0.0f, 1.0f, 0.0f
        );
    }
}

// --------------------------------------------------
// INITIALIZATION
// --------------------------------------------------

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(
        GL_FRONT_AND_BACK,
        GL_AMBIENT_AND_DIFFUSE
    );

    glClearColor(0.55f, 0.78f, 0.95f, 1.0f);

    initCowLighting();

    previousTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

    std::cout << "FARMERS DAY STARTED" << std::endl;
    std::cout << "Scene 1: Sunrise" << std::endl;
}

// --------------------------------------------------
// DISPLAY
// --------------------------------------------------

void display()
{
    if (currentScene == SCENE_SUNRISE)
        glClearColor(0.55f, 0.78f, 0.95f, 1.0f);
    else if (currentScene == SCENE_BEDROOM)
        glClearColor(0.65f, 0.72f, 0.85f, 1.0f);
    else if (currentScene == SCENE_FARMYARD)
        glClearColor(0.55f, 0.78f, 0.95f, 1.0f);
    else if (currentScene == SCENE_MILKING)
        glClearColor(0.72f, 0.75f, 0.72f, 1.0f);
    else if (currentScene == SCENE_PACKAGING)
        glClearColor(0.72f, 0.78f, 0.82f, 1.0f);
    else if (currentScene == SCENE_SHOP)
        glClearColor(0.65f, 0.78f, 0.88f, 1.0f);
    else if (currentScene == SCENE_SUNSET ||
             currentScene == SCENE_FINISHED)
        glClearColor(0.20f, 0.12f, 0.22f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCamera();

    if (currentScene == SCENE_SUNRISE)
    {
        drawSunrise();
    }
    else if (currentScene == SCENE_BEDROOM)
    {
        drawBedroom();
    }
    else if (currentScene == SCENE_FARMYARD)
    {
        drawFarmyard();
    }
    else if (currentScene == SCENE_MILKING)
    {
        drawMilkingArea(sceneTime);
    }
    else if (currentScene == SCENE_PACKAGING)
    {
        drawPackagingRoom(sceneTime);
    }
    else if (currentScene == SCENE_JOURNEY)
    {
        drawJourney(sceneTime, false);
    }
    else if (currentScene == SCENE_SHOP)
    {
        drawVillageShop(sceneTime);
    }
    else if (currentScene == SCENE_RETURN_JOURNEY)
    {
        drawJourney(sceneTime, true);
    }
    else if (currentScene == SCENE_SUNSET ||
             currentScene == SCENE_FINISHED)
    {
        drawSunset();
    }

    glutSwapBuffers();
}

// --------------------------------------------------
// SCENE TRANSITIONS
// --------------------------------------------------

void nextScene()
{
    sceneTime = 0.0f;

    if (currentScene == SCENE_SUNRISE)
    {
        currentScene = SCENE_BEDROOM;
        std::cout << "Scene 2: Bedroom" << std::endl;
    }
    else if (currentScene == SCENE_BEDROOM)
    {
        currentScene = SCENE_FARMYARD;
        std::cout << "Scene 3: Farmyard" << std::endl;
    }
    else if (currentScene == SCENE_FARMYARD)
    {
        currentScene = SCENE_MILKING;
        std::cout << "Scene 4: Milking" << std::endl;
    }
    else if (currentScene == SCENE_MILKING)
    {
        currentScene = SCENE_PACKAGING;
        std::cout << "Scene 5: Packaging" << std::endl;
    }
    else if (currentScene == SCENE_PACKAGING)
    {
        currentScene = SCENE_JOURNEY;
        std::cout << "Scene 6: Journey to the Shop" << std::endl;
    }
    else if (currentScene == SCENE_JOURNEY)
    {
        currentScene = SCENE_SHOP;
        std::cout << "Scene 7: Selling Milk at the Shop" << std::endl;
    }
    else if (currentScene == SCENE_SHOP)
    {
        currentScene = SCENE_RETURN_JOURNEY;
        std::cout << "Scene 8: Journey Back Home" << std::endl;
    }
    else if (currentScene == SCENE_RETURN_JOURNEY)
    {
        currentScene = SCENE_SUNSET;
        std::cout << "Scene 9: Sunset at Home" << std::endl;
    }
    else if (currentScene == SCENE_SUNSET)
    {
        currentScene = SCENE_FINISHED;
        std::cout << "FARMERS DAY COMPLETED!" << std::endl;
    }
}

// --------------------------------------------------
// UPDATE
// --------------------------------------------------

void update(int value)
{
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float deltaTime = currentTime - previousTime;

    previousTime = currentTime;

    if (deltaTime < 0.0f)
        deltaTime = 0.0f;

    if (currentScene != SCENE_FINISHED)
        sceneTime += deltaTime;

    if (currentScene == SCENE_SUNRISE)
    {
        updateSunrise(deltaTime);

        if (sceneTime >= SUNRISE_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_BEDROOM)
    {
        updateBedroom(deltaTime);

        if (sceneTime >= BEDROOM_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_FARMYARD)
    {
        if (sceneTime >= FARMYARD_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_MILKING)
    {
        if (sceneTime >= MILKING_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_PACKAGING)
    {
        if (sceneTime >= PACKAGING_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_JOURNEY)
    {
        updateJourney(sceneTime, false);

        if (sceneTime >= JOURNEY_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_SHOP)
    {
        if (sceneTime >= SHOP_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_RETURN_JOURNEY)
    {
        updateJourney(sceneTime, true);

        if (sceneTime >= RETURN_JOURNEY_DURATION)
            nextScene();
    }
    else if (currentScene == SCENE_SUNSET)
    {
        if (sceneTime >= SUNSET_DURATION)
            nextScene();
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// --------------------------------------------------
// RESHAPE
// --------------------------------------------------

void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(
        55.0,
        (float)width / (float)height,
        0.1,
        100.0
    );

    glMatrixMode(GL_MODELVIEW);
}

// --------------------------------------------------
// KEYBOARD
// --------------------------------------------------

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);

    if (key == 'n' || key == 'N')
    {
        if (currentScene != SCENE_FINISHED)
            nextScene();

        glutPostRedisplay();
    }
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(WIN_W, WIN_H);
    glutInitWindowPosition(100, 50);

    glutCreateWindow("Farmers Day");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
