
#include <GL/freeglut.h>
#include <cmath>
#include "sunset.h"

namespace
{
    constexpr float PI = 3.14159265f;

    void sunsetBox(float x, float y, float z,
                   float sx, float sy, float sz,
                   float r, float g, float b)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glColor3f(r, g, b);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    void sunsetSphere(float x, float y, float z,
                      float sx, float sy, float sz,
                      float r, float g, float b)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glColor3f(r, g, b);
        glutSolidSphere(1.0, 24, 20);
        glPopMatrix();
    }

    void sunsetCylinder(float x, float y, float z,
                        float radius, float height,
                        float r, float g, float b)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(r, g, b);

        GLUquadric* quad = gluNewQuadric();
        gluCylinder(quad, radius, radius * 0.9f,
                    height, 18, 4);
        gluDisk(quad, 0.0, radius, 18, 1);

        glTranslatef(0.0f, 0.0f, height);
        gluDisk(quad, 0.0, radius * 0.9f, 18, 1);

        gluDeleteQuadric(quad);
        glPopMatrix();
    }

    void drawSunsetSky()
{
    glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT |
                 GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);

        // Bottom: warm orange near the horizon
        glColor3f(1.0f, 0.48f, 0.18f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);

        // Top: deep evening purple
        glColor3f(0.16f, 0.10f, 0.30f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);

    glEnd();

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glDepthMask(GL_TRUE);
    glPopAttrib();
}

    void drawSun()
    {
        // Low sun near the horizon
        sunsetSphere(-10.0f, 5.0f, -30.0f,
                     2.0f, 2.0f, 0.35f,
                     1.0f, 0.68f, 0.28f);

        // Soft glow around the sun
        sunsetSphere(-10.0f, 5.0f, -30.5f,
                     2.8f, 2.8f, 0.15f,
                     0.95f, 0.47f, 0.25f);
    }

    void drawDistantHills()
    {
        glDisable(GL_LIGHTING);

        glColor3f(0.30f, 0.25f, 0.30f);

        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 1.5f, -31.0f);
            glVertex3f(-30.0f, -2.0f, -31.0f);
            glVertex3f(-23.0f, 3.0f, -31.0f);
            glVertex3f(-15.0f, 1.5f, -31.0f);
            glVertex3f(-7.0f, 5.0f, -31.0f);
            glVertex3f(3.0f, 2.0f, -31.0f);
            glVertex3f(13.0f, 4.0f, -31.0f);
            glVertex3f(22.0f, 1.0f, -31.0f);
            glVertex3f(30.0f, -2.0f, -31.0f);
        glEnd();

        glEnable(GL_LIGHTING);
    }

    void drawGround()
    {
        // Main compound
        sunsetBox(0.0f, -0.35f, -2.0f,
                  45.0f, 0.45f, 45.0f,
                  0.24f, 0.31f, 0.20f);

        // Dirt path to the farmhouse
        sunsetBox(0.0f, -0.08f, 8.0f,
                  4.2f, 0.08f, 19.0f,
                  0.48f, 0.34f, 0.22f);

        // Path stones
        for (int i = 0; i < 8; i++)
        {
            float x = (i % 2 == 0) ? -1.3f : 1.3f;
            float z = 1.0f + i * 2.0f;

            sunsetBox(x, -0.015f, z,
                      0.65f, 0.07f, 0.48f,
                      0.48f, 0.45f, 0.39f);
        }

        // Long evening shadows from the house
        glDisable(GL_LIGHTING);

        glColor3f(0.13f, 0.18f, 0.13f);

        glBegin(GL_TRIANGLES);
            glVertex3f(-6.0f, -0.105f, -1.0f);
            glVertex3f(6.0f, -0.105f, -1.0f);
            glVertex3f(10.0f, -0.105f, 12.0f);

            glVertex3f(-6.0f, -0.105f, -1.0f);
            glVertex3f(10.0f, -0.105f, 12.0f);
            glVertex3f(-8.0f, -0.105f, 14.0f);
        glEnd();

        glEnable(GL_LIGHTING);
    }

    void drawHouseWalls()
    {
        // Main farmhouse walls
        sunsetBox(0.0f, 2.35f, -2.0f,
                  12.0f, 4.7f, 8.0f,
                  0.72f, 0.57f, 0.40f);

        // Front facade plaster finish
        sunsetBox(0.0f, 2.35f, 2.08f,
                  11.8f, 4.6f, 0.08f,
                  0.80f, 0.67f, 0.49f);

        // Foundation strip
        sunsetBox(0.0f, 0.12f, 2.15f,
                  12.1f, 0.3f, 0.25f,
                  0.38f, 0.30f, 0.22f);

        // Front door
        sunsetBox(0.0f, 1.75f, 2.18f,
                  1.55f, 3.35f, 0.16f,
                  0.30f, 0.18f, 0.10f);

        sunsetBox(0.0f, 1.75f, 2.28f,
                  1.30f, 3.1f, 0.06f,
                  0.43f, 0.25f, 0.13f);

        // Door panels
        sunsetBox(0.0f, 2.2f, 2.32f,
                  0.9f, 1.0f, 0.035f,
                  0.35f, 0.20f, 0.11f);

        sunsetBox(0.0f, 0.95f, 2.32f,
                  0.9f, 0.9f, 0.035f,
                  0.35f, 0.20f, 0.11f);

        // Door handle
        sunsetSphere(0.48f, 1.7f, 2.38f,
                     0.09f, 0.09f, 0.07f,
                     0.82f, 0.66f, 0.30f);

        // Front windows with warm interior glow
        for (int side = -1; side <= 1; side += 2)
        {
            float x = side * 3.6f;

            // Outer frame
            sunsetBox(x, 2.8f, 2.18f,
                      2.1f, 1.85f, 0.18f,
                      0.28f, 0.17f, 0.09f);

            // Glowing glass
            sunsetBox(x, 2.8f, 2.30f,
                      1.78f, 1.55f, 0.05f,
                      1.0f, 0.62f, 0.24f);

            // Window crossbars
            sunsetBox(x, 2.8f, 2.36f,
                      0.09f, 1.65f, 0.05f,
                      0.28f, 0.17f, 0.09f);

            sunsetBox(x, 2.8f, 2.36f,
                      1.85f, 0.09f, 0.05f,
                      0.28f, 0.17f, 0.09f);

            // Window sills
            sunsetBox(x, 1.82f, 2.25f,
                      2.3f, 0.15f, 0.35f,
                      0.42f, 0.28f, 0.17f);
        }
    }

    void drawHouseRoof()
    {
        // Two sloping roof panels
        glColor3f(0.28f, 0.17f, 0.12f);

        glBegin(GL_QUADS);
            // Left roof slope
            glVertex3f(-6.7f, 4.65f, 2.8f);
            glVertex3f(0.0f, 7.0f, 2.8f);
            glVertex3f(0.0f, 7.0f, -6.8f);
            glVertex3f(-6.7f, 4.65f, -6.8f);

            // Right roof slope
            glVertex3f(0.0f, 7.0f, 2.8f);
            glVertex3f(6.7f, 4.65f, 2.8f);
            glVertex3f(6.7f, 4.65f, -6.8f);
            glVertex3f(0.0f, 7.0f, -6.8f);
        glEnd();

        // Front gable triangle
        glColor3f(0.72f, 0.55f, 0.38f);

        glBegin(GL_TRIANGLES);
            glVertex3f(-6.0f, 4.65f, 2.15f);
            glVertex3f(6.0f, 4.65f, 2.15f);
            glVertex3f(0.0f, 6.85f, 2.15f);
        glEnd();

        // Roof ridge
        sunsetBox(0.0f, 7.0f, -2.0f,
                  0.22f, 0.22f, 10.0f,
                  0.20f, 0.12f, 0.09f);

        // Front roof fascia
        sunsetBox(0.0f, 4.65f, 2.85f,
                  13.5f, 0.25f, 0.22f,
                  0.20f, 0.12f, 0.08f);

        // Porch roof
        sunsetBox(0.0f, 4.0f, 3.4f,
                  7.0f, 0.22f, 2.0f,
                  0.30f, 0.19f, 0.12f);

        // Porch supports
        for (int side = -1; side <= 1; side += 2)
        {
            sunsetBox(side * 3.1f, 1.95f, 4.2f,
                      0.22f, 3.9f, 0.22f,
                      0.34f, 0.22f, 0.12f);
        }
    }

    void drawTree(float x, float z, float scale)
    {
        sunsetCylinder(x, -0.1f, z,
                       0.25f * scale, 3.0f * scale,
                       0.27f, 0.17f, 0.10f);

        sunsetSphere(x, 3.2f * scale, z,
                     1.35f * scale, 1.4f * scale,
                     1.2f * scale,
                     0.15f, 0.29f, 0.13f);

        sunsetSphere(x - 0.8f * scale, 2.8f * scale, z,
                     0.9f * scale, 1.0f * scale,
                     0.9f * scale,
                     0.19f, 0.34f, 0.15f);

        sunsetSphere(x + 0.8f * scale, 2.9f * scale, z,
                     0.9f * scale, 1.0f * scale,
                     0.9f * scale,
                     0.17f, 0.32f, 0.14f);
    }

    void drawBush(float x, float z, float scale)
    {
        sunsetSphere(x, 0.35f * scale, z,
                     0.9f * scale, 0.55f * scale,
                     0.7f * scale,
                     0.16f, 0.31f, 0.13f);

        sunsetSphere(x + 0.65f * scale, 0.35f * scale, z,
                     0.65f * scale, 0.5f * scale,
                     0.65f * scale,
                     0.20f, 0.36f, 0.15f);
    }

    void drawFarmFence()
    {
        for (int i = 0; i < 8; i++)
        {
            float x = -14.0f + i * 4.0f;

            sunsetBox(x, 0.55f, -10.0f,
                      0.16f, 1.1f, 0.16f,
                      0.34f, 0.22f, 0.12f);

            sunsetBox(x, 0.9f, -10.0f,
                      4.0f, 0.12f, 0.12f,
                      0.43f, 0.29f, 0.16f);

            sunsetBox(x, 0.4f, -10.0f,
                      4.0f, 0.12f, 0.12f,
                      0.43f, 0.29f, 0.16f);
        }
    }

    void drawOutdoorLamp()
    {
        sunsetCylinder(5.5f, 0.0f, 3.8f,
                       0.10f, 3.4f,
                       0.20f, 0.17f, 0.13f);

        sunsetBox(5.5f, 3.5f, 3.8f,
                  0.65f, 0.25f, 0.45f,
                  0.28f, 0.22f, 0.15f);

        sunsetSphere(5.5f, 3.35f, 3.8f,
                     0.22f, 0.18f, 0.22f,
                     1.0f, 0.72f, 0.34f);
    }

    void drawGarden()
    {
        // Small flower beds near the house
        for (int i = 0; i < 5; i++)
        {
            float x = -7.0f + i * 3.5f;

            sunsetBox(x, 0.02f, 5.3f,
                      1.0f, 0.12f, 0.65f,
                      0.28f, 0.22f, 0.13f);

            sunsetSphere(x, 0.35f, 5.3f,
                         0.18f, 0.25f, 0.18f,
                         0.85f, 0.32f, 0.30f);
        }

        // Bushes around the compound
        drawBush(-9.0f, -3.0f, 1.0f);
        drawBush(9.0f, -4.0f, 1.1f);
        drawBush(-8.0f, 5.0f, 0.8f);
        drawBush(8.0f, 6.0f, 0.9f);
    }

    void drawCloud(float x, float y, float z, float scale)
    {
        sunsetSphere(x, y, z,
                     1.7f * scale, 0.45f * scale,
                     0.45f * scale,
                     0.72f, 0.39f, 0.36f);

        sunsetSphere(x + 1.0f * scale, y + 0.2f * scale, z,
                     1.1f * scale, 0.55f * scale,
                     0.45f * scale,
                     0.78f, 0.46f, 0.38f);

        sunsetSphere(x - 0.9f * scale, y + 0.1f * scale, z,
                     1.0f * scale, 0.4f * scale,
                     0.4f * scale,
                     0.78f, 0.43f, 0.37f);
    }
}

void drawSunset()
{
    drawSunsetSky();
    drawDistantHills();
    drawSun();

    drawCloud(-13.0f, 10.0f, -25.0f, 1.2f);
    drawCloud(9.0f, 12.0f, -27.0f, 0.9f);

    drawGround();
    drawFarmFence();

    drawTree(-11.0f, -1.0f, 1.2f);
    drawTree(11.0f, -3.0f, 1.1f);
    drawTree(-13.0f, -9.0f, 0.9f);
    drawTree(14.0f, -10.0f, 1.0f);

    drawHouseWalls();
    drawHouseRoof();
    drawGarden();
    drawOutdoorLamp();
}
