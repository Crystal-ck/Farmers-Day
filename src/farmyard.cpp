
#include <GL/freeglut.h>
#include <cmath>
#include "farmyard.h"
#include "environment_utils.h"

namespace
{
    // Draw a rectangular object.
    void farmBox(float x, float y, float z,
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

    // Draw a tree.
    void farmTree(float x, float z, float scale)
    {
        farmBox(x, -0.2f * scale, z,
                0.45f * scale, 3.6f * scale, 0.45f * scale,
                0.30f, 0.16f, 0.08f);

        drawEllipsoid(x, 1.7f * scale, z,
                      1.25f * scale, 1.35f * scale, 1.1f * scale,
                      0.17f, 0.38f, 0.15f);

        drawEllipsoid(x - 0.65f * scale, 1.35f * scale, z + 0.1f,
                      0.8f * scale, 0.9f * scale, 0.8f * scale,
                      0.21f, 0.43f, 0.17f);

        drawEllipsoid(x + 0.65f * scale, 1.4f * scale, z - 0.1f,
                      0.8f * scale, 0.9f * scale, 0.8f * scale,
                      0.19f, 0.40f, 0.15f);
    }

    void drawFarmhouseBackground()
    {
        // Main farmhouse walls
        farmBox(-7.0f, 0.0f, -7.0f,
                6.0f, 4.0f, 3.0f,
                0.76f, 0.62f, 0.43f);

        // Roof
        glColor3f(0.30f, 0.13f, 0.09f);

        glBegin(GL_TRIANGLES);
            glVertex3f(-10.0f, 2.0f, -5.45f);
            glVertex3f(-4.0f, 2.0f, -5.45f);
            glVertex3f(-7.0f, 4.0f, -5.45f);

            glVertex3f(-10.0f, 2.0f, -8.55f);
            glVertex3f(-4.0f, 2.0f, -8.55f);
            glVertex3f(-7.0f, 4.0f, -8.55f);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-10.0f, 2.0f, -5.45f);
            glVertex3f(-7.0f, 4.0f, -5.45f);
            glVertex3f(-7.0f, 4.0f, -8.55f);
            glVertex3f(-10.0f, 2.0f, -8.55f);

            glVertex3f(-7.0f, 4.0f, -5.45f);
            glVertex3f(-4.0f, 2.0f, -5.45f);
            glVertex3f(-4.0f, 2.0f, -8.55f);
            glVertex3f(-7.0f, 4.0f, -8.55f);
        glEnd();

        // Door and windows
        farmBox(-7.0f, -0.85f, -5.46f,
                1.2f, 2.3f, 0.12f,
                0.25f, 0.12f, 0.07f);

        farmBox(-8.8f, 0.45f, -5.44f,
                1.0f, 0.9f, 0.12f,
                0.32f, 0.55f, 0.65f);

        farmBox(-5.2f, 0.45f, -5.44f,
                1.0f, 0.9f, 0.12f,
                0.32f, 0.55f, 0.65f);

        // Window frames
        farmBox(-8.8f, 0.45f, -5.35f,
                1.1f, 0.09f, 0.08f,
                0.25f, 0.14f, 0.08f);

        farmBox(-5.2f, 0.45f, -5.35f,
                1.1f, 0.09f, 0.08f,
                0.25f, 0.14f, 0.08f);
    }

    void drawCowshed()
    {
        // Cowshed position: towards the right side of the farmyard.

        // Back wall
        farmBox(5.0f, 0.0f, -7.0f,
                8.0f, 4.2f, 0.35f,
                0.48f, 0.31f, 0.19f);

        // Left and right walls
        farmBox(1.0f, 0.0f, -3.0f,
                0.35f, 4.2f, 8.0f,
                0.55f, 0.37f, 0.23f);

        farmBox(9.0f, 0.0f, -3.0f,
                0.35f, 4.2f, 8.0f,
                0.55f, 0.37f, 0.23f);

        // Wooden support posts at the front
        farmBox(1.2f, 0.0f, 1.0f,
                0.35f, 4.4f, 0.35f,
                0.27f, 0.13f, 0.07f);

        farmBox(8.8f, 0.0f, 1.0f,
                0.35f, 4.4f, 0.35f,
                0.27f, 0.13f, 0.07f);

        farmBox(5.0f, 1.9f, 1.0f,
                8.0f, 0.35f, 0.35f,
                0.27f, 0.13f, 0.07f);

        // Triangular front and back gables
        glColor3f(0.55f, 0.37f, 0.23f);

        glBegin(GL_TRIANGLES);
            glVertex3f(1.0f, 2.1f, 1.0f);
            glVertex3f(9.0f, 2.1f, 1.0f);
            glVertex3f(5.0f, 4.4f, 1.0f);

            glVertex3f(1.0f, 2.1f, -7.0f);
            glVertex3f(9.0f, 2.1f, -7.0f);
            glVertex3f(5.0f, 4.4f, -7.0f);
        glEnd();

        // Pitched roof
        glColor3f(0.28f, 0.13f, 0.09f);

        glBegin(GL_QUADS);
            // Left roof slope
            glVertex3f(0.6f, 2.2f, 1.3f);
            glVertex3f(5.0f, 4.5f, 1.3f);
            glVertex3f(5.0f, 4.5f, -7.3f);
            glVertex3f(0.6f, 2.2f, -7.3f);

            // Right roof slope
            glVertex3f(5.0f, 4.5f, 1.3f);
            glVertex3f(9.4f, 2.2f, 1.3f);
            glVertex3f(9.4f, 2.2f, -7.3f);
            glVertex3f(5.0f, 4.5f, -7.3f);
        glEnd();

        // Roof ridge
        farmBox(5.0f, 4.48f, -3.0f,
                0.18f, 0.18f, 8.8f,
                0.20f, 0.09f, 0.06f);

        // Interior wooden divider
        farmBox(5.0f, -0.3f, -4.0f,
                0.15f, 2.8f, 4.0f,
                0.36f, 0.22f, 0.12f);

        // Feed trough
        farmBox(3.0f, -1.35f, -2.5f,
                2.8f, 0.65f, 0.8f,
                0.34f, 0.20f, 0.10f);

        farmBox(3.0f, -1.0f, -2.5f,
                2.5f, 0.08f, 0.65f,
                0.20f, 0.27f, 0.10f);

        // Hay storage
        drawEllipsoid(7.0f, -1.2f, -5.3f,
                      1.0f, 0.7f, 0.8f,
                      0.72f, 0.56f, 0.20f);

        drawEllipsoid(7.8f, -1.3f, -5.2f,
                      0.8f, 0.6f, 0.7f,
                      0.77f, 0.61f, 0.23f);
    }

    void drawFence()
    {
        // Fence along the left side
        for (int i = 0; i < 8; i++)
        {
            float x = -11.0f + i * 1.6f;

            farmBox(x, -0.9f, 3.5f,
                    0.18f, 2.0f, 0.18f,
                    0.35f, 0.19f, 0.09f);
        }

        // Horizontal fence rails
        farmBox(-5.4f, -0.35f, 3.5f,
                11.4f, 0.16f, 0.16f,
                0.39f, 0.23f, 0.12f);

        farmBox(-5.4f, -1.0f, 3.5f,
                11.4f, 0.16f, 0.16f,
                0.39f, 0.23f, 0.12f);

        // Fence near the cowshed
        for (int i = 0; i < 5; i++)
        {
            float z = -5.0f + i * 1.4f;

            farmBox(10.5f, -0.9f, z,
                    0.18f, 2.0f, 0.18f,
                    0.35f, 0.19f, 0.09f);
        }

        farmBox(10.5f, -0.35f, -2.2f,
                0.16f, 0.16f, 6.0f,
                0.39f, 0.23f, 0.12f);

        farmBox(10.5f, -1.0f, -2.2f,
                0.16f, 0.16f, 6.0f,
                0.39f, 0.23f, 0.12f);
    }

    void drawPath()
    {
        // Dirt path leading from farmhouse to cowshed
        glColor3f(0.48f, 0.32f, 0.18f);

        glBegin(GL_QUADS);
            glVertex3f(-5.0f, -1.97f, 5.0f);
            glVertex3f(3.5f, -1.97f, 5.0f);
            glVertex3f(6.0f, -1.97f, -1.0f);
            glVertex3f(2.0f, -1.97f, -1.0f);
        glEnd();

        // Small stones along the path
        drawEllipsoid(-2.5f, -1.88f, 2.0f,
                      0.18f, 0.06f, 0.14f,
                      0.40f, 0.37f, 0.31f);

        drawEllipsoid(0.2f, -1.88f, 0.0f,
                      0.14f, 0.05f, 0.12f,
                      0.44f, 0.40f, 0.34f);

        drawEllipsoid(3.5f, -1.88f, 1.5f,
                      0.20f, 0.06f, 0.15f,
                      0.38f, 0.34f, 0.28f);
    }

    void drawWaterTrough()
    {
        farmBox(8.5f, -1.45f, 2.5f,
                2.2f, 0.65f, 1.0f,
                0.36f, 0.23f, 0.13f);

        farmBox(8.5f, -1.1f, 2.5f,
                2.0f, 0.06f, 0.85f,
                0.25f, 0.43f, 0.53f);
    }

    void drawGrassDetails()
    {
        for (int i = 0; i < 45; i++)
        {
            float x = -12.0f + (i % 15) * 1.7f;
            float z = -1.0f + (i / 15) * 2.0f;

            drawEllipsoid(x, -1.85f, z,
                          0.12f, 0.12f, 0.12f,
                          0.24f, 0.43f, 0.17f);
        }
    }
}

void drawFarmyard()
{
    // Ground
    glColor3f(0.28f, 0.43f, 0.19f);

    glBegin(GL_QUADS);
        glVertex3f(-30.0f, -2.0f, -20.0f);
        glVertex3f(30.0f, -2.0f, -20.0f);
        glVertex3f(30.0f, -2.0f, 20.0f);
        glVertex3f(-30.0f, -2.0f, 20.0f);
    glEnd();

    drawPath();
    drawGrassDetails();

    drawFarmhouseBackground();
    drawCowshed();
    drawFence();
    drawWaterTrough();

    // Trees around the compound
    farmTree(-12.0f, -5.0f, 1.0f);
    farmTree(-12.0f, 4.0f, 0.85f);
    farmTree(12.0f, -8.0f, 1.1f);

    // Bushes
    drawEllipsoid(-10.0f, -1.4f, 1.0f,
                  1.0f, 0.6f, 0.8f,
                  0.19f, 0.36f, 0.13f);

    drawEllipsoid(11.0f, -1.4f, 5.0f,
                  1.1f, 0.6f, 0.8f,
                  0.17f, 0.33f, 0.12f);
}
