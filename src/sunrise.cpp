
#include <GL/freeglut.h>
#include <algorithm>
#include <cmath>
#include "shared_sun.h"


#include "../characters/rooster.h"
#include "sunrise.h"
#include "environment_utils.h"

namespace
{
    float sunHeight = 1.0f;
    float sunriseElapsed = 0.0f;

    float smoothTransition(float a, float b, float t)
    {
        t = std::max(0.0f, std::min(1.0f, t));
        t = t * t * (3.0f - 2.0f * t);
        return a + (b - a) * t;
    }

    void updateSky(float elapsed)
    {
        float r, g, b;

        if (elapsed < 8.0f)
        {
            float t = elapsed / 8.0f;
            r = smoothTransition(0.035f, 0.95f, t);
            g = smoothTransition(0.055f, 0.38f, t);
            b = smoothTransition(0.16f, 0.22f, t);
        }
        else
        {
            float t = (elapsed - 8.0f) / 12.0f;
            r = smoothTransition(0.95f, 0.42f, t);
            g = smoothTransition(0.38f, 0.68f, t);
            b = smoothTransition(0.22f, 0.88f, t);
        }

        glClearColor(r, g, b, 1.0f);
    }

    // SUN
    void drawSun()
{
    drawSharedSun(-6.0f, sunHeight, -9.0f, 1.0f);
}
    // CLOUDS
    void drawCloud(float x, float y, float z, float scale)
    {
        glPushMatrix();

        glTranslatef(x, y, z);
        glScalef(scale, scale, scale);

        drawEllipsoid(0.0f, 0.0f, 0.0f,
                      0.75f, 0.38f, 0.35f,
                      0.95f, 0.93f, 0.88f);

        drawEllipsoid(0.55f, 0.10f, 0.0f,
                      0.55f, 0.35f, 0.35f,
                      0.95f, 0.93f, 0.88f);

        drawEllipsoid(-0.55f, 0.0f, 0.0f,
                      0.48f, 0.30f, 0.32f,
                      0.95f, 0.93f, 0.88f);

        drawEllipsoid(0.05f, 0.28f, 0.0f,
                      0.48f, 0.40f, 0.34f,
                      0.98f, 0.96f, 0.91f);

        glPopMatrix();
    }

    // HILLS
    void drawHills()
    {
        glColor3f(0.35f, 0.48f, 0.32f);

        glBegin(GL_TRIANGLE_FAN);

        glVertex3f(-15.0f, -1.8f, -12.0f);
        glVertex3f(-12.0f, -0.5f, -12.0f);
        glVertex3f(-8.0f, 1.0f, -12.0f);
        glVertex3f(-4.0f, -0.4f, -12.0f);
        glVertex3f(0.0f, 0.9f, -12.0f);
        glVertex3f(5.0f, -0.2f, -12.0f);
        glVertex3f(10.0f, 1.2f, -12.0f);
        glVertex3f(15.0f, -1.8f, -12.0f);

        glEnd();

        glColor3f(0.28f, 0.40f, 0.25f);

        glBegin(GL_TRIANGLE_FAN);

        glVertex3f(-15.0f, -1.9f, -10.0f);
        glVertex3f(-10.0f, -0.9f, -10.0f);
        glVertex3f(-6.0f, -1.1f, -10.0f);
        glVertex3f(-2.0f, -0.6f, -10.0f);
        glVertex3f(3.0f, -1.2f, -10.0f);
        glVertex3f(8.0f, -0.7f, -10.0f);
        glVertex3f(15.0f, -1.9f, -10.0f);

        glEnd();
    }

    // TREES
    void drawTree(float x, float z, float scale)
    {
        glPushMatrix();

        glTranslatef(x, -1.8f, z);
        glScalef(scale, scale, scale);

        glColor3f(0.30f, 0.16f, 0.07f);

        glPushMatrix();
        glTranslatef(0.0f, 1.2f, 0.0f);
        glScalef(0.18f, 1.4f, 0.18f);
        glutSolidCube(1.0);
        glPopMatrix();

        drawCylinder(0.0f, 1.8f, 0.0f,
             -0.55f, 2.7f, 0.0f,
             0.08f, 0.30f, 0.16f, 0.07f);

        drawCylinder(0.0f, 1.8f, 0.0f,
                     0.55f, 2.7f, 0.0f,
                     0.08f, 0.30f, 0.16f, 0.07f);

        drawEllipsoid(0.0f, 2.8f, 0.0f,
                      0.9f, 0.9f, 0.85f,
                      0.13f, 0.35f, 0.12f);

        drawEllipsoid(-0.55f, 2.5f, 0.1f,
                      0.65f, 0.7f, 0.65f,
                      0.18f, 0.42f, 0.15f);

        drawEllipsoid(0.55f, 2.6f, -0.1f,
                      0.7f, 0.75f, 0.7f,
                      0.16f, 0.39f, 0.13f);

        drawEllipsoid(0.0f, 3.35f, 0.0f,
                      0.65f, 0.7f, 0.65f,
                      0.20f, 0.44f, 0.16f);

        glPopMatrix();
    }

    // HELPER FOR FARMHOUSE DETAILS
    void houseBox(float x, float y, float z,
                  float sx, float sy, float sz,
                  float r, float g, float b)
    {
        glColor3f(r, g, b);

        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // FARMHOUSE FOUNDATION
    void drawHouseFoundation()
    {
        houseBox(0.0f, -1.36f, 0.0f,
                 5.0f, 0.32f, 3.45f,
                 0.36f, 0.32f, 0.25f);

        houseBox(0.0f, -1.18f, 0.0f,
                 4.9f, 0.12f, 3.35f,
                 0.56f, 0.49f, 0.37f);

        // Front foundation detail
        houseBox(0.0f, -1.35f, 1.74f,
                 4.9f, 0.16f, 0.08f,
                 0.28f, 0.25f, 0.20f);
    }

    // FARMHOUSE WALLS
    void drawHouseWalls()
    {
        // Main plaster walls
        houseBox(0.0f, -0.15f, 0.0f,
                 4.7f, 2.0f, 3.1f,
                 0.76f, 0.58f, 0.38f);

        // Front facade finish
        houseBox(0.0f, -0.12f, 1.57f,
                 4.62f, 1.88f, 0.07f,
                 0.82f, 0.67f, 0.48f);

        // Horizontal decorative plaster band
        houseBox(0.0f, 0.68f, 1.63f,
                 4.65f, 0.10f, 0.08f,
                 0.91f, 0.79f, 0.61f);

        // Corner wall columns
        houseBox(-2.25f, -0.15f, 1.66f,
                 0.16f, 2.0f, 0.13f,
                 0.91f, 0.77f, 0.56f);

        houseBox(2.25f, -0.15f, 1.66f,
                 0.16f, 2.0f, 0.13f,
                 0.91f, 0.77f, 0.56f);
    }

    // FARMHOUSE WINDOWS
    void drawHouseWindow(float x)
    {
        // Window recess
        houseBox(x, 0.0f, 1.68f,
                 0.95f, 0.95f, 0.09f,
                 0.25f, 0.15f, 0.09f);

        // Glass
        houseBox(x, 0.0f, 1.75f,
                 0.76f, 0.76f, 0.035f,
                 0.28f, 0.48f, 0.55f);

        // Wooden frame
        houseBox(x - 0.46f, 0.0f, 1.79f,
                 0.09f, 1.0f, 0.09f,
                 0.28f, 0.14f, 0.065f);

        houseBox(x + 0.46f, 0.0f, 1.79f,
                 0.09f, 1.0f, 0.09f,
                 0.28f, 0.14f, 0.065f);

        houseBox(x, 0.46f, 1.79f,
                 1.0f, 0.09f, 0.09f,
                 0.28f, 0.14f, 0.065f);

        houseBox(x, -0.46f, 1.79f,
                 1.0f, 0.09f, 0.09f,
                 0.28f, 0.14f, 0.065f);

        // Window crossbars
        houseBox(x, 0.0f, 1.82f,
                 0.055f, 0.78f, 0.045f,
                 0.28f, 0.14f, 0.065f);

        houseBox(x, 0.0f, 1.82f,
                 0.78f, 0.055f, 0.045f,
                 0.28f, 0.14f, 0.065f);

        // Projecting window sill
        houseBox(x, -0.55f, 1.82f,
                 1.15f, 0.12f, 0.24f,
                 0.65f, 0.44f, 0.25f);
    }

    // FRONT DOOR
    void drawHouseDoor()
    {
        // Door frame
        houseBox(0.0f, -0.30f, 1.70f,
                 0.94f, 1.65f, 0.12f,
                 0.28f, 0.15f, 0.075f);

        // Door panel
        houseBox(0.0f, -0.30f, 1.78f,
                 0.76f, 1.48f, 0.06f,
                 0.39f, 0.21f, 0.095f);

        // Upper decorative panel
        houseBox(0.0f, 0.05f, 1.82f,
                 0.52f, 0.45f, 0.035f,
                 0.31f, 0.16f, 0.07f);

        // Lower decorative panel
        houseBox(0.0f, -0.62f, 1.82f,
                 0.52f, 0.52f, 0.035f,
                 0.31f, 0.16f, 0.07f);

        // Door handle
        drawEllipsoid(0.27f, -0.32f, 1.88f,
                      0.055f, 0.055f, 0.055f,
                      0.85f, 0.69f, 0.30f);

        // Doorstep
        houseBox(0.0f, -1.10f, 2.0f,
                 1.35f, 0.18f, 0.65f,
                 0.56f, 0.49f, 0.38f);
    }

    // ROOF
    void drawHouseRoof()
    {
        const float eaveY = 0.90f;
        const float ridgeY = 2.45f;
        const float roofX = 2.65f;
        const float roofZ = 2.0f;

        // Front gable
        glColor3f(0.68f, 0.47f, 0.29f);

        glBegin(GL_TRIANGLES);
        glVertex3f(-2.35f, 0.82f, 1.57f);
        glVertex3f(0.0f, 2.25f, 1.57f);
        glVertex3f(2.35f, 0.82f, 1.57f);
        glEnd();

        // Roof left slope
        glColor3f(0.31f, 0.15f, 0.075f);

        glBegin(GL_QUADS);
        glVertex3f(-roofX, eaveY, roofZ);
        glVertex3f(0.0f, ridgeY, roofZ);
        glVertex3f(0.0f, ridgeY, -roofZ);
        glVertex3f(-roofX, eaveY, -roofZ);
        glEnd();

        // Roof right slope
        glColor3f(0.40f, 0.19f, 0.09f);

        glBegin(GL_QUADS);
        glVertex3f(0.0f, ridgeY, roofZ);
        glVertex3f(roofX, eaveY, roofZ);
        glVertex3f(roofX, eaveY, -roofZ);
        glVertex3f(0.0f, ridgeY, -roofZ);
        glEnd();

        // Front fascia boards
        houseBox(-1.32f, 0.85f, 2.02f,
                 2.85f, 0.16f, 0.16f,
                 0.23f, 0.11f, 0.055f);

        houseBox(1.32f, 0.85f, 2.02f,
                 2.85f, 0.16f, 0.16f,
                 0.23f, 0.11f, 0.055f);

        // Roof ridge
        houseBox(0.0f, 2.42f, 0.0f,
                 0.20f, 0.18f, 4.15f,
                 0.25f, 0.12f, 0.055f);

        // Decorative front gable trim
        drawCylinder(-2.30f, 0.90f, 2.05f,
                     0.0f, 2.30f, 2.05f,
                     0.055f, 0.24f, 0.12f, 0.055f);

        drawCylinder(0.0f, 2.30f, 2.05f,
                     2.30f, 0.90f, 2.05f,
                     0.055f, 0.24f, 0.12f, 0.055f);
    }

    // FRONT PORCH
    void drawHousePorch()
    {
        // Porch roof
        houseBox(0.0f, 0.95f, 2.55f,
                 2.9f, 0.18f, 1.3f,
                 0.32f, 0.16f, 0.07f);

        // Top porch beam
        houseBox(0.0f, 0.82f, 3.12f,
                 2.9f, 0.15f, 0.15f,
                 0.25f, 0.12f, 0.055f);

        // Porch columns
        houseBox(-1.28f, -0.10f, 3.10f,
                 0.16f, 1.85f, 0.16f,
                 0.77f, 0.65f, 0.44f);

        houseBox(1.28f, -0.10f, 3.10f,
                 0.16f, 1.85f, 0.16f,
                 0.77f, 0.65f, 0.44f);

        // Column bases
        houseBox(-1.28f, -1.0f, 3.10f,
                 0.28f, 0.16f, 0.28f,
                 0.49f, 0.35f, 0.22f);

        houseBox(1.28f, -1.0f, 3.10f,
                 0.28f, 0.16f, 0.28f,
                 0.49f, 0.35f, 0.22f);

        // Porch floor
        houseBox(0.0f, -1.15f, 2.60f,
                 3.05f, 0.16f, 1.45f,
                 0.62f, 0.48f, 0.31f);
    }

    // FARMHOUSE
    void drawHouse()
    {
        glPushMatrix();

        // Keep farmhouse in its original sunrise location
        glTranslatef(-5.5f, -0.65f, -3.5f);

        drawHouseFoundation();
        drawHouseWalls();

        drawHouseWindow(-1.45f);
        drawHouseWindow(1.45f);

        drawHouseDoor();
        drawHouseRoof();
        drawHousePorch();

        glPopMatrix();
    }

    // GROUND
    void drawGround()
    {
        glColor3f(0.28f, 0.42f, 0.20f);

        glBegin(GL_QUADS);

        glVertex3f(-30.0f, -2.0f, -20.0f);
        glVertex3f(30.0f, -2.0f, -20.0f);
        glVertex3f(30.0f, -2.0f, 20.0f);
        glVertex3f(-30.0f, -2.0f, 20.0f);

        glEnd();

        // Small grass details
        for (int i = 0; i < 180; i++)
        {
            float x = -12.0f + (i * 37 % 240) / 10.0f;
            float z = -5.0f + (i * 19 % 100) / 10.0f;

            glColor3f(0.18f, 0.36f, 0.12f);

            glBegin(GL_LINES);

            glVertex3f(x, -1.98f, z);
            glVertex3f(x + 0.06f, -1.78f, z);

            glEnd();
        }
    }
}

// UPDATE SUNRISE ANIMATION
void updateSunrise(float deltaTime)
{
    // Accumulate elapsed time instead of repeatedly resetting it
    sunriseElapsed += deltaTime;

    // Complete the sunrise within the 8-second scene
    float progress = std::min(sunriseElapsed / 8.0f, 1.0f);

    // Move the sun from below the horizon into the sky
    sunHeight = smoothTransition(-1.2f, 5.5f, progress);

    // Gradually change the sky from night to morning
    updateSky(sunriseElapsed);
}
// DRAW COMPLETE SUNRISE ENVIRONMENT
void drawSunrise()
{
    drawGround();
    drawHills();

    drawCloud(-7.0f, 5.0f, -10.0f, 1.0f);
    drawCloud(2.0f, 6.0f, -11.0f, 1.2f);
    drawCloud(9.0f, 4.5f, -10.0f, 0.8f);

    // Shared sunrise model
    drawSun();

    drawTree(-10.0f, -4.0f, 1.2f);
    drawTree(9.0f, -5.0f, 1.0f);
    drawTree(12.0f, -8.0f, 1.3f);

    // No farmhouse in Scene 1

    // Rooster crowing
    drawRooster(-8.0f, -1.98f, 3.0f, 1.0f, sunriseElapsed);
}