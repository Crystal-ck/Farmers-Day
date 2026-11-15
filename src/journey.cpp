
#include <GL/freeglut.h>
#include <cmath>
#include "journey.h"

namespace
{
    constexpr float PI = 3.14159265f;
    constexpr float ROAD_LENGTH = 48.0f;

    float skyR = 0.48f;
    float skyG = 0.70f;
    float skyB = 0.86f;

    void journeyBox(float x, float y, float z,
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

    void journeySphere(float x, float y, float z,
                       float sx, float sy, float sz,
                       float r, float g, float b)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glColor3f(r, g, b);
        glutSolidSphere(1.0, 18, 16);
        glPopMatrix();
    }

    void journeyCylinder(float x, float y, float z,
                         float radius, float height,
                         float r, float g, float b)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(r, g, b);

        GLUquadric* quad = gluNewQuadric();
        gluCylinder(quad, radius, radius * 0.85f,
                    height, 14, 3);
        gluDeleteQuadric(quad);

        glPopMatrix();
    }

    float movingPosition(float originalZ,
                         float offset,
                         bool returningHome)
    {
        float distance = originalZ + 30.0f;

        if (returningHome)
            distance -= offset;
        else
            distance += offset;

        distance = std::fmod(distance, ROAD_LENGTH);

        if (distance < 0.0f)
            distance += ROAD_LENGTH;

        return distance - 30.0f;
    }

    void drawGround()
    {
        journeyBox(0.0f, -0.35f, -5.0f,
                   65.0f, 0.4f, 75.0f,
                   0.30f, 0.43f, 0.23f);
    }

    void drawRoad()
    {
        // Road surface
        glColor3f(0.42f, 0.34f, 0.25f);

        glBegin(GL_QUADS);
            glVertex3f(-3.0f, -0.13f, 20.0f);
            glVertex3f(3.0f, -0.13f, 20.0f);
            glVertex3f(1.2f, -0.13f, -35.0f);
            glVertex3f(-1.2f, -0.13f, -35.0f);
        glEnd();

        // Slightly lighter worn edges
        glColor3f(0.52f, 0.42f, 0.30f);

        glBegin(GL_QUADS);
            glVertex3f(-3.5f, -0.12f, 20.0f);
            glVertex3f(-3.0f, -0.12f, 20.0f);
            glVertex3f(-1.2f, -0.12f, -35.0f);
            glVertex3f(-1.55f, -0.12f, -35.0f);

            glVertex3f(3.0f, -0.12f, 20.0f);
            glVertex3f(3.5f, -0.12f, 20.0f);
            glVertex3f(1.55f, -0.12f, -35.0f);
            glVertex3f(1.2f, -0.12f, -35.0f);
        glEnd();
    }

    void drawHills()
    {
        glColor3f(0.31f, 0.48f, 0.34f);

        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 3.0f, -34.0f);
            glVertex3f(-24.0f, -1.0f, -34.0f);
            glVertex3f(-19.0f, 4.0f, -34.0f);
            glVertex3f(-12.0f, 2.0f, -34.0f);
            glVertex3f(-5.0f, 6.0f, -34.0f);
            glVertex3f(4.0f, 3.0f, -34.0f);
            glVertex3f(13.0f, 6.0f, -34.0f);
            glVertex3f(20.0f, 2.0f, -34.0f);
            glVertex3f(24.0f, -1.0f, -34.0f);
        glEnd();

        glColor3f(0.38f, 0.53f, 0.36f);

        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 2.0f, -32.0f);
            glVertex3f(-25.0f, -1.0f, -32.0f);
            glVertex3f(-18.0f, 2.0f, -32.0f);
            glVertex3f(-10.0f, 1.0f, -32.0f);
            glVertex3f(-2.0f, 5.0f, -32.0f);
            glVertex3f(8.0f, 2.0f, -32.0f);
            glVertex3f(17.0f, 4.0f, -32.0f);
            glVertex3f(25.0f, -1.0f, -32.0f);
        glEnd();
    }

    void drawTree(float x, float z, float scale)
    {
        float trunkHeight = 2.8f * scale;

        // Main trunk
        journeyCylinder(x, -0.1f, z,
                        0.22f * scale, trunkHeight,
                        0.29f, 0.18f, 0.10f);

        // Branches
        journeyCylinder(x, trunkHeight * 0.55f, z,
                        0.11f * scale, 1.0f * scale,
                        0.29f, 0.18f, 0.10f);

        // Foliage
        journeySphere(x, trunkHeight + 0.7f * scale, z,
                      1.15f * scale, 1.15f * scale,
                      1.0f * scale,
                      0.16f, 0.37f, 0.16f);

        journeySphere(x - 0.65f * scale,
                      trunkHeight + 0.35f * scale, z,
                      0.75f * scale, 0.85f * scale,
                      0.8f * scale,
                      0.20f, 0.43f, 0.19f);

        journeySphere(x + 0.65f * scale,
                      trunkHeight + 0.35f * scale, z,
                      0.75f * scale, 0.85f * scale,
                      0.8f * scale,
                      0.18f, 0.40f, 0.17f);
    }

    void drawBush(float x, float z, float scale)
    {
        journeySphere(x, 0.35f * scale, z,
                      0.8f * scale, 0.55f * scale,
                      0.65f * scale,
                      0.20f, 0.38f, 0.15f);

        journeySphere(x + 0.45f * scale, 0.3f * scale, z,
                      0.55f * scale, 0.45f * scale,
                      0.55f * scale,
                      0.24f, 0.43f, 0.17f);
    }

    void drawFencePost(float x, float z)
    {
        journeyBox(x, 0.65f, z,
                   0.16f, 1.3f, 0.16f,
                   0.36f, 0.23f, 0.12f);

        journeyBox(x, 0.85f, z,
                   0.20f, 0.12f, 0.20f,
                   0.45f, 0.30f, 0.16f);
    }

    void drawFence(float side, float offset, bool returningHome)
    {
        for (int i = 0; i < 8; i++)
        {
            float originalZ = -28.0f + i * 6.0f;
            float z = movingPosition(originalZ, offset,
                                     returningHome);

            float x = side * (5.2f + (z + 30.0f) * 0.035f);

            drawFencePost(x, z);

            // Two wooden rails
            journeyBox(x, 0.95f, z,
                       0.12f, 0.10f, 5.8f,
                       0.43f, 0.29f, 0.16f);

            journeyBox(x, 0.48f, z,
                       0.12f, 0.10f, 5.8f,
                       0.43f, 0.29f, 0.16f);
        }
    }

    void drawRoadsideScenery(float offset, bool returningHome)
    {
        const float treePositions[] =
        {
            -27.0f, -19.0f, -11.0f, -3.0f,
             5.0f, 13.0f, 21.0f
        };

        for (int i = 0; i < 7; i++)
        {
            float z = movingPosition(treePositions[i],
                                     offset, returningHome);

            float scale = 0.85f + (i % 3) * 0.18f;

            drawTree(-7.0f, z, scale);
            drawTree(7.0f, z - 2.0f, scale * 0.95f);

            drawBush(-5.0f, z + 2.0f, 0.8f);
            drawBush(5.0f, z + 3.0f, 0.9f);
        }
    }

    void drawRoadMarkings(float offset, bool returningHome)
    {
        // Moving patches along the road help reinforce travel
        for (int i = 0; i < 8; i++)
        {
            float originalZ = -28.0f + i * 6.0f;
            float z = movingPosition(originalZ, offset,
                                     returningHome);

            float roadWidth = 1.2f + (z + 30.0f) * 0.032f;

            journeyBox(0.0f, -0.105f, z,
                       0.08f + roadWidth * 0.035f,
                       0.025f, 1.8f,
                       0.72f, 0.61f, 0.43f);
        }
    }

    void drawRoadsideStones(float offset, bool returningHome)
    {
        for (int i = 0; i < 10; i++)
        {
            float originalZ = -26.0f + i * 5.0f;
            float z = movingPosition(originalZ, offset,
                                     returningHome);

            float x = (i % 2 == 0) ? -3.8f : 3.8f;

            journeySphere(x, -0.02f, z,
                          0.35f, 0.12f, 0.28f,
                          0.48f, 0.45f, 0.39f);
        }
    }
}

void updateJourney(float elapsedSeconds, bool returningHome)
{
    if (!returningHome)
    {
        // Clear daytime sky
        skyR = 0.48f;
        skyG = 0.70f;
        skyB = 0.86f;
    }
    else
    {
        // Evening sky gradually darkens during the return
        float progress = elapsedSeconds / 20.0f;

        if (progress < 0.0f) progress = 0.0f;
        if (progress > 1.0f) progress = 1.0f;

        skyR = 0.75f - progress * 0.22f;
        skyG = 0.43f - progress * 0.18f;
        skyB = 0.30f - progress * 0.10f;
    }

    glClearColor(skyR, skyG, skyB, 1.0f);
}

void drawJourney(float elapsedSeconds, bool returningHome)
{
    float offset = std::fmod(elapsedSeconds * 4.0f,
                             ROAD_LENGTH);

    drawGround();
    drawHills();
    drawRoad();

    drawFence(-1.0f, offset, returningHome);
    drawFence(1.0f, offset, returningHome);

    drawRoadsideScenery(offset, returningHome);
    drawRoadsideStones(offset, returningHome);
    drawRoadMarkings(offset, returningHome);
}
