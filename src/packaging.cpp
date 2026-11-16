
#include <GL/freeglut.h>
#include <cmath>
#include <algorithm>

#include "../characters/farmer.h"
#include "packaging.h"
#include "environment_utils.h"

namespace
{
    void packBox(float x, float y, float z,
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

    void packCylinder(float x, float y, float z,
                      float radius, float height,
                      float r, float g, float b)
    {
        GLUquadric* quad = gluNewQuadric();

        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(r, g, b);

        gluCylinder(quad, radius, radius, height, 28, 4);
        gluDisk(quad, 0.0, radius, 28, 1);

        glTranslatef(0.0f, 0.0f, height);
        gluDisk(quad, 0.0, radius, 28, 1);

        glPopMatrix();
        gluDeleteQuadric(quad);
    }

    void packBottle(float x, float y, float z,
                    float scale, float r, float g, float b)
    {
        // Main bottle body
        packCylinder(x, y, z,
                     0.20f * scale, 0.65f * scale,
                     r, g, b);

        // Rounded shoulder
        drawEllipsoid(x, y + 0.65f * scale, z,
                      0.20f * scale, 0.13f * scale,
                      0.20f * scale,
                      r, g, b);

        // Neck
        packCylinder(x, y + 0.70f * scale, z,
                     0.09f * scale, 0.20f * scale,
                     r, g, b);

        // Cap
        packBox(x, y + 0.93f * scale, z,
                0.22f * scale, 0.08f * scale,
                0.22f * scale,
                0.82f, 0.82f, 0.76f);

        // Label
        packBox(x, y + 0.34f * scale, z + 0.19f * scale,
                0.23f * scale, 0.22f * scale,
                0.015f * scale,
                0.88f, 0.85f, 0.67f);
    }

    void drawPackagingBuilding()
    {
        // Floor
        packBox(0.0f, -1.95f, 0.0f,
                17.0f, 0.25f, 15.0f,
                0.68f, 0.61f, 0.48f);

        // Back wall
        packBox(0.0f, 1.0f, -7.0f,
                16.0f, 6.0f, 0.35f,
                0.79f, 0.72f, 0.58f);

        // Side walls
        packBox(-8.0f, 1.0f, 0.0f,
                0.35f, 6.0f, 14.0f,
                0.76f, 0.69f, 0.55f);

        packBox(8.0f, 1.0f, 0.0f,
                0.35f, 6.0f, 14.0f,
                0.76f, 0.69f, 0.55f);

        // Roof
        packBox(0.0f, 4.1f, 0.0f,
                16.5f, 0.35f, 15.0f,
                0.35f, 0.19f, 0.12f);

        // Roof support beams
        for (int i = -3; i <= 3; i += 2)
        {
            packBox(static_cast<float>(i), 3.8f, 0.0f,
                    0.16f, 0.3f, 14.0f,
                    0.36f, 0.22f, 0.13f);
        }

        // Front entrance support posts
        packBox(-7.7f, 0.9f, 6.5f,
                0.35f, 5.8f, 0.35f,
                0.40f, 0.24f, 0.14f);

        packBox(7.7f, 0.9f, 6.5f,
                0.35f, 5.8f, 0.35f,
                0.40f, 0.24f, 0.14f);

        // Rear ventilation windows
        packBox(-4.5f, 2.2f, -6.78f,
                2.4f, 1.3f, 0.08f,
                0.40f, 0.63f, 0.68f);

        packBox(4.5f, 2.2f, -6.78f,
                2.4f, 1.3f, 0.08f,
                0.40f, 0.63f, 0.68f);

        // Window dividers
        packBox(-4.5f, 2.2f, -6.68f,
                0.08f, 1.3f, 0.08f,
                0.35f, 0.22f, 0.13f);

        packBox(4.5f, 2.2f, -6.68f,
                0.08f, 1.3f, 0.08f,
                0.35f, 0.22f, 0.13f);
    }

    void drawProcessingTable()
    {
        // Stainless-steel worktop
        packBox(-3.5f, -0.35f, 1.0f,
                5.5f, 0.22f, 2.0f,
                0.66f, 0.69f, 0.70f);

        // Table frame
        packBox(-5.9f, -1.1f, 1.0f,
                0.12f, 1.4f, 0.12f,
                0.34f, 0.36f, 0.37f);

        packBox(-1.1f, -1.1f, 1.0f,
                0.12f, 1.4f, 0.12f,
                0.34f, 0.36f, 0.37f);

        packBox(-5.9f, -1.1f, 0.0f,
                0.12f, 1.4f, 0.12f,
                0.34f, 0.36f, 0.37f);

        packBox(-1.1f, -1.1f, 0.0f,
                0.12f, 1.4f, 0.12f,
                0.34f, 0.36f, 0.37f);

        // Processing containers
        packCylinder(-4.8f, -0.22f, 1.0f,
                     0.38f, 0.55f,
                     0.72f, 0.75f, 0.76f);

        packCylinder(-3.5f, -0.22f, 1.0f,
                     0.38f, 0.55f,
                     0.72f, 0.75f, 0.76f);

        packCylinder(-2.2f, -0.22f, 1.0f,
                     0.38f, 0.55f,
                     0.72f, 0.75f, 0.76f);
    }

    void drawMilkStorageTanks()
    {
        // Storage tanks
        packCylinder(3.7f, -1.8f, -3.0f,
                     1.05f, 2.8f,
                     0.66f, 0.70f, 0.72f);

        packCylinder(6.0f, -1.8f, -3.0f,
                     1.05f, 2.8f,
                     0.66f, 0.70f, 0.72f);

        // Rounded tops
        drawEllipsoid(3.7f, 1.0f, -3.0f,
                      1.05f, 0.22f, 1.05f,
                      0.72f, 0.75f, 0.76f);

        drawEllipsoid(6.0f, 1.0f, -3.0f,
                      1.05f, 0.22f, 1.05f,
                      0.72f, 0.75f, 0.76f);

        // Access lids
        packCylinder(3.7f, 1.15f, -3.0f,
                     0.28f, 0.20f,
                     0.45f, 0.49f, 0.51f);

        packCylinder(6.0f, 1.15f, -3.0f,
                     0.28f, 0.20f,
                     0.45f, 0.49f, 0.51f);

        // Connecting pipe
        drawCylinder(3.7f, 0.4f, -1.9f,
                     6.0f, 0.4f, -1.9f,
                     0.09f, 0.63f, 0.66f, 0.68f);

        // Outlet pipes
        drawCylinder(3.7f, -0.7f, -1.9f,
                     3.7f, -0.7f, -0.8f,
                     0.07f, 0.58f, 0.61f, 0.63f);

        drawCylinder(6.0f, -0.7f, -1.9f,
                     6.0f, -0.7f, -0.8f,
                     0.07f, 0.58f, 0.61f, 0.63f);
    }

    void drawFillingStation()
    {
        // Raised filling counter
        packBox(1.0f, -0.8f, 3.7f,
                5.0f, 0.25f, 1.3f,
                0.47f, 0.49f, 0.48f);

        // Filling machine support
        packBox(1.0f, 0.0f, 3.7f,
                1.4f, 1.4f, 0.9f,
                0.58f, 0.62f, 0.63f);

        // Filling nozzle
        packCylinder(1.0f, 0.7f, 3.7f,
                     0.12f, 0.7f,
                     0.42f, 0.45f, 0.47f);

        // Funnel
        glPushMatrix();
        glTranslatef(1.0f, -0.15f, 3.7f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.72f, 0.75f, 0.75f);

        GLUquadric* funnel = gluNewQuadric();
        gluCylinder(funnel, 0.45f, 0.12f, 0.35f, 24, 3);
        gluDeleteQuadric(funnel);

        glPopMatrix();

        // Emergency stop button
        drawEllipsoid(1.55f, 0.25f, 4.18f,
                      0.12f, 0.12f, 0.12f,
                      0.75f, 0.12f, 0.08f);
    }

    void drawBottleShelves()
    {
        // Shelving unit
        packBox(-5.7f, 0.0f, -4.8f,
                3.8f, 0.15f, 1.1f,
                0.39f, 0.25f, 0.15f);

        packBox(-5.7f, 1.2f, -4.8f,
                3.8f, 0.15f, 1.1f,
                0.39f, 0.25f, 0.15f);

        packBox(-7.4f, 0.6f, -4.8f,
                0.15f, 2.5f, 0.15f,
                0.31f, 0.19f, 0.11f);

        packBox(-4.0f, 0.6f, -4.8f,
                0.15f, 2.5f, 0.15f,
                0.31f, 0.19f, 0.11f);

        // Lower shelf bottles
        packBottle(-6.7f, -0.65f, -4.8f, 0.75f,
                   0.76f, 0.83f, 0.85f);

        packBottle(-5.7f, -0.65f, -4.8f, 0.75f,
                   0.76f, 0.83f, 0.85f);

        packBottle(-4.7f, -0.65f, -4.8f, 0.75f,
                   0.76f, 0.83f, 0.85f);

        // Upper shelf bottles
        packBottle(-6.7f, 0.55f, -4.8f, 0.75f,
                   0.76f, 0.83f, 0.85f);

        packBottle(-5.7f, 0.55f, -4.8f, 0.75f,
                   0.76f, 0.83f, 0.85f);

        packBottle(-4.7f, 0.55f, -4.8f, 0.75f,
                   0.76f, 0.83f, 0.85f);
    }

    void drawWashingSink()
    {
        // Sink counter
        packBox(-6.0f, -0.55f, 2.3f,
                2.8f, 0.25f, 1.5f,
                0.48f, 0.50f, 0.49f);

        // Sink basin
        drawEllipsoid(-6.0f, -0.37f, 2.3f,
                      0.85f, 0.18f, 0.55f,
                      0.30f, 0.43f, 0.49f);

        // Tap
        drawCylinder(-6.0f, -0.3f, 1.75f,
                     -6.0f, 0.4f, 1.75f,
                     0.06f, 0.60f, 0.65f, 0.66f);

        drawCylinder(-6.0f, 0.4f, 1.75f,
                     -6.0f, 0.4f, 2.2f,
                     0.06f, 0.60f, 0.65f, 0.66f);

        // Sink legs
        packBox(-7.1f, -1.3f, 1.8f,
                0.12f, 1.2f, 0.12f,
                0.35f, 0.36f, 0.36f);

        packBox(-4.9f, -1.3f, 1.8f,
                0.12f, 1.2f, 0.12f,
                0.35f, 0.36f, 0.36f);
    }

    void drawRoomSign()
    {
        packBox(0.0f, 3.0f, 6.75f,
                4.5f, 0.8f, 0.12f,
                0.30f, 0.22f, 0.14f);

        packBox(-1.0f, 3.0f, 6.66f,
                0.12f, 0.32f, 0.04f,
                0.91f, 0.86f, 0.70f);

        packBox(0.0f, 3.0f, 6.66f,
                0.12f, 0.32f, 0.04f,
                0.91f, 0.86f, 0.70f);

        packBox(1.0f, 3.0f, 6.66f,
                0.12f, 0.32f, 0.04f,
                0.91f, 0.86f, 0.70f);
    }

    // Draw the bottle at the station before collection,
    // then on the processing table after delivery.
    
void drawPackagingBottleProcess(float elapsedSeconds)
{
    // Bottle waits at the filling station.
    if (elapsedSeconds < 6.0f)
    {
        packBottle(
            1.0f, -0.67f, 3.7f,
            0.75f,
            0.76f, 0.83f, 0.85f
        );
    }
    // Bottle rests on the processing table from 11 to 14 seconds.
    else if (elapsedSeconds >= 11.0f && elapsedSeconds < 14.0f)
    {
        packBottle(
            -2.5f, -0.22f, 1.0f,
            0.75f,
            0.76f, 0.83f, 0.85f
        );
    }
}

// Farmer animation
}
void drawPackagingFarmer(float elapsedSeconds)
{
    float farmerX = 0.0f;
    float farmerZ = 0.0f;
    float rotation = 0.0f;

    float legL = 0.0f;
    float legR = 0.0f;
    float armL = 10.0f;
    float armR = 10.0f;
    float hip = 5.0f;

    float walkProgress = 0.0f;
    bool carryingBottle = false;

    // STAGE 1: Walk to the filling station.
    if (elapsedSeconds < 4.0f)
    {
        walkProgress = elapsedSeconds / 4.0f;

        farmerX = -2.5f + 3.3f * walkProgress;
        farmerZ = 3.3f;
        rotation = 90.0f;

        float step = sinf(elapsedSeconds * 7.0f);
        legL = 22.0f * step;
        legR = -22.0f * step;
        armL = -20.0f * step;
        armR = 20.0f * step;
    }

    // STAGE 2: Pick up the bottle.
    else if (elapsedSeconds < 6.0f)
    {
        farmerX = 0.8f;
        farmerZ = 3.3f;
        rotation = 90.0f;

        hip = 30.0f;
        armL = 65.0f;
        armR = 65.0f;
    }

    // STAGE 3: Carry bottle to the processing table.
    else if (elapsedSeconds < 11.0f)
    {
        walkProgress = (elapsedSeconds - 6.0f) / 5.0f;

        farmerX = 0.8f - 3.0f * walkProgress;
        farmerZ = 3.3f - 0.8f * walkProgress;
        rotation = -105.0f;

        float step = sinf(elapsedSeconds * 7.0f);
        legL = 20.0f * step;
        legR = -20.0f * step;

        armL = 55.0f;
        armR = 10.0f;
    }

    // STAGE 4: Place the bottle on the table.
    else if (elapsedSeconds < 14.0f)
    {
        farmerX = -2.2f;
        farmerZ = 2.5f;
        rotation = -105.0f;

        hip = 20.0f;
        armL = 55.0f;
        armR = 15.0f;
    }

    // STAGE 5: Pick the bottle up again.
    else if (elapsedSeconds < 16.0f)
    {
        farmerX = -2.2f;
        farmerZ = 2.5f;
        rotation = -105.0f;

        hip = 18.0f;
        armL = 60.0f;
        armR = 15.0f;
        carryingBottle = true;
    }

    // STAGE 6: Turn and walk out through the entrance.
    else
    {
        walkProgress = std::min((elapsedSeconds - 16.0f) / 7.0f, 1.0f);

        farmerX = -2.2f + 4.0f * walkProgress;
        farmerZ = 2.5f + 6.0f * walkProgress;

        rotation = 180.0f;

        float step = sinf(elapsedSeconds * 7.0f);
        legL = 22.0f * step;
        legR = -22.0f * step;

        armL = 45.0f;
        armR = 10.0f;

        carryingBottle = true;
    }

    glPushMatrix();

    glTranslatef(farmerX, -1.0f, farmerZ);
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);

    drawFarmerPosed(
        0.0f, 0.0f, 0.0f,
        1.0f,
        hip,
        legL,
        legR,
        armL,
        armR,
        elapsedSeconds
    );

    if (carryingBottle)
    {
        packBottle(
            -0.42f, 0.45f, 0.12f,
            0.65f,
            0.76f, 0.83f, 0.85f
        );
    }

    glPopMatrix();
}

// Complete packaging room
void drawPackagingRoom(float elapsedSeconds)
{
    drawPackagingBuilding();
    drawProcessingTable();
    drawMilkStorageTanks();
    drawFillingStation();
    drawBottleShelves();
    drawWashingSink();
    drawRoomSign();

    drawPackagingBottleProcess(elapsedSeconds);
    drawPackagingFarmer(elapsedSeconds);
}
