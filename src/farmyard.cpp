
#include <GL/freeglut.h>
#include <cmath>
#include "shared_sun.h"
#include "farmyard.h"
#include "environment_utils.h"
#include "../characters/farmer.h"
#include "../characters/cow.h"

namespace
{
    const float PI = 3.14159265f;

    // --------------------------------------------------
    // ANIMATION SETTINGS
    // --------------------------------------------------

    float farmyardStartTime = -1.0f;

    const float WALK_DURATION = 10.0f;

    // --------------------------------------------------
    // BASIC 3D OBJECTS
    // --------------------------------------------------

    void farmBox(float x, float y, float z,
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

    void farmCylinder(float x, float y, float z,
                      float radius, float height,
                      float r, float g, float b)
    {
        glColor3f(r, g, b);

        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90.0f, 1, 0, 0);

        GLUquadric* q = gluNewQuadric();

        gluCylinder(q, radius, radius, height, 16, 4);
        gluDisk(q, 0, radius, 16, 1);

        glTranslatef(0, 0, height);
        gluDisk(q, 0, radius, 16, 1);

        gluDeleteQuadric(q);
        glPopMatrix();
    }

    void farmSphere(float x, float y, float z,
                    float sx, float sy, float sz,
                    float r, float g, float b)
    {
        glColor3f(r, g, b);

        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glutSolidSphere(1.0, 16, 12);
        glPopMatrix();
    }

    // --------------------------------------------------
    // FARMHOUSE
    // --------------------------------------------------

    void drawFarmhouse()
    {
        // Main farmhouse walls
        farmBox(-7.0f, 0.0f, -7.0f,
                6.0f, 4.0f, 3.0f,
                0.78f, 0.65f, 0.43f);

        // Door
        farmBox(-7.0f, -0.85f, -5.43f,
                1.0f, 2.3f, 0.12f,
                0.30f, 0.15f, 0.07f);

        // Door handle
        farmBox(-6.65f, -0.85f, -5.34f,
                0.08f, 0.08f, 0.06f,
                0.85f, 0.65f, 0.20f);

        // Windows
        farmBox(-9.0f, 0.45f, -5.42f,
                1.1f, 1.0f, 0.12f,
                0.25f, 0.48f, 0.65f);

        farmBox(-5.0f, 0.45f, -5.42f,
                1.1f, 1.0f, 0.12f,
                0.25f, 0.48f, 0.65f);

        // Window frames
        farmBox(-9.0f, 0.45f, -5.33f,
                1.2f, 0.09f, 0.08f,
                0.30f, 0.16f, 0.08f);

        farmBox(-5.0f, 0.45f, -5.33f,
                1.2f, 0.09f, 0.08f,
                0.30f, 0.16f, 0.08f);

        // --------------------------------------------------
        // ROOF: TWO SLOPING PANELS
        // --------------------------------------------------

        glColor3f(0.38f, 0.16f, 0.10f);

        glBegin(GL_QUADS);

        // Left roof slope
        glVertex3f(-10.2f, 2.0f, -8.7f);
        glVertex3f(-7.0f, 4.3f, -8.7f);
        glVertex3f(-7.0f, 4.3f, -5.2f);
        glVertex3f(-10.2f, 2.0f, -5.2f);

        // Right roof slope
        glVertex3f(-7.0f, 4.3f, -8.7f);
        glVertex3f(-3.8f, 2.0f, -8.7f);
        glVertex3f(-3.8f, 2.0f, -5.2f);
        glVertex3f(-7.0f, 4.3f, -5.2f);

        glEnd();

        // --------------------------------------------------
        // ROOF: FRONT TRIANGULAR GABLE
        // --------------------------------------------------

        glColor3f(0.58f, 0.34f, 0.20f);

        glBegin(GL_TRIANGLES);

        glVertex3f(-10.0f, 2.0f, -5.2f);
        glVertex3f(-7.0f, 4.3f, -5.2f);
        glVertex3f(-7.0f, 2.0f, -5.2f);

        glVertex3f(-7.0f, 4.3f, -5.2f);
        glVertex3f(-4.0f, 2.0f, -5.2f);
        glVertex3f(-7.0f, 2.0f, -5.2f);

        glEnd();

        // --------------------------------------------------
        // ROOF: BACK TRIANGULAR GABLE
        // --------------------------------------------------

        glColor3f(0.58f, 0.34f, 0.20f);

        glBegin(GL_TRIANGLES);

        glVertex3f(-10.0f, 2.0f, -8.7f);
        glVertex3f(-7.0f, 4.3f, -8.7f);
        glVertex3f(-7.0f, 2.0f, -8.7f);

        glVertex3f(-7.0f, 4.3f, -8.7f);
        glVertex3f(-4.0f, 2.0f, -8.7f);
        glVertex3f(-7.0f, 2.0f, -8.7f);

        glEnd();
    }

    // --------------------------------------------------
    // COWSHED
    // --------------------------------------------------

    void drawCowshed()
    {
        farmBox(5.0f, -0.1f, -5.0f,
                6.0f, 3.6f, 0.25f,
                0.52f, 0.32f, 0.17f);

        farmBox(2.0f, -0.1f, -3.0f,
                0.25f, 3.6f, 4.0f,
                0.48f, 0.29f, 0.15f);

        farmBox(8.0f, -0.1f, -3.0f,
                0.25f, 3.6f, 4.0f,
                0.48f, 0.29f, 0.15f);

        farmBox(5.0f, 1.9f, -3.0f,
                6.7f, 0.25f, 4.6f,
                0.34f, 0.16f, 0.09f);

        farmBox(2.0f, 0.5f, -1.0f,
                0.18f, 3.0f, 0.18f,
                0.30f, 0.17f, 0.08f);

        farmBox(8.0f, 0.5f, -1.0f,
                0.18f, 3.0f, 0.18f,
                0.30f, 0.17f, 0.08f);

        farmBox(3.0f, 0.4f, -0.9f,
                0.18f, 2.8f, 0.18f,
                0.30f, 0.17f, 0.08f);

        farmBox(7.0f, 0.4f, -0.9f,
                0.18f, 2.8f, 0.18f,
                0.30f, 0.17f, 0.08f);

        // Feed trough
        farmBox(5.0f, -1.25f, -3.8f,
                3.0f, 0.45f, 0.65f,
                0.36f, 0.20f, 0.09f);

        drawEllipsoid(4.0f, -0.8f, -4.0f,
                      0.7f, 0.4f, 0.55f,
                      0.78f, 0.57f, 0.22f);

        drawEllipsoid(5.0f, -0.8f, -4.0f,
                      0.7f, 0.4f, 0.55f,
                      0.82f, 0.61f, 0.25f);
    }

    // --------------------------------------------------
    // COW INSIDE THE COWSHED
    // --------------------------------------------------

    void drawFarmyardCow()
    {
        float currentTime =
            glutGet(GLUT_ELAPSED_TIME) * 0.001f;

        drawCow(
            5.0f, -1.95f, -3.0f,
            0.85f, currentTime
        );
    }

    // --------------------------------------------------
    // FARMER WALKING TOWARDS THE COWSHED
    // --------------------------------------------------

    void drawWalkingFarmer()
    {
        float currentTime =
            glutGet(GLUT_ELAPSED_TIME) * 0.001f;

        if (farmyardStartTime < 0.0f)
        {
            farmyardStartTime = currentTime;
        }

        float elapsed = currentTime - farmyardStartTime;

        const float startX = -7.0f;
        const float startZ = -4.65f;

        const float endX = 4.2f;
        const float endZ = 0.2f;

        float progress = elapsed / WALK_DURATION;

        if (progress > 1.0f)
            progress = 1.0f;

        if (progress < 0.0f)
            progress = 0.0f;

        float smoothProgress =
            progress * progress * (3.0f - 2.0f * progress);

        float x = startX + (endX - startX) * smoothProgress;
        float z = startZ + (endZ - startZ) * smoothProgress;

        // Walking animation
        float walkCycle = sinf(elapsed * 7.0f);

        float leftLeg = 0.0f;
        float rightLeg = 0.0f;
        float leftArm = 0.0f;
        float rightArm = 0.0f;

        if (progress < 1.0f)
        {
            leftLeg = walkCycle * 25.0f;
            rightLeg = -walkCycle * 25.0f;

            leftArm = -walkCycle * 18.0f;
            rightArm = walkCycle * 18.0f;
        }

        // Face towards cowshed
        float dx = endX - startX;
        float dz = endZ - startZ;

        float facingAngle =
            atan2f(dx, dz) * 180.0f / PI;

        glPushMatrix();

        glTranslatef(x, -1.95f, z);
        glRotatef(facingAngle, 0.0f, 1.0f, 0.0f);

        drawFarmerPosed(
            0.0f, 0.0f, 0.0f,
            1.0f,
            0.0f,
            leftLeg,
            rightLeg,
            leftArm,
            rightArm,
            elapsed
        );

        glPopMatrix();
    }

    // --------------------------------------------------
    // SUN
    // --------------------------------------------------

    void drawFarmSun()
    {
        // Save current lighting state
        GLboolean lightingWasEnabled =
            glIsEnabled(GL_LIGHTING);

        // Disable lighting so the sun keeps its bright colour
        glDisable(GL_LIGHTING);

        // Sun body
        glColor3f(1.0f, 0.82f, 0.12f);

        glPushMatrix();

        glTranslatef(-10.0f, 7.0f, -10.0f);

        glutSolidSphere(1.0f, 32, 32);

        glPopMatrix();

        // Sun rays
        glColor3f(1.0f, 0.72f, 0.05f);

        glLineWidth(4.0f);

        glBegin(GL_LINES);

        for (int i = 0; i < 12; i++)
        {
            float angle =
                i * 2.0f * PI / 12.0f;

            float x1 =
                -10.0f + cosf(angle) * 1.3f;

            float y1 =
                7.0f + sinf(angle) * 1.3f;

            float x2 =
                -10.0f + cosf(angle) * 1.9f;

            float y2 =
                7.0f + sinf(angle) * 1.9f;

            glVertex3f(x1, y1, -10.0f);
            glVertex3f(x2, y2, -10.0f);
        }

        glEnd();

        glLineWidth(1.0f);

        // Restore lighting
        if (lightingWasEnabled)
        {
            glEnable(GL_LIGHTING);
        }
    }

    // --------------------------------------------------
    // TREES AND BUSHES
    // --------------------------------------------------

    void farmTree(float x, float z, float scale)
    {
        farmBox(x, -0.3f, z,
                0.35f * scale, 2.2f * scale,
                0.35f * scale,
                0.34f, 0.19f, 0.08f);

        drawEllipsoid(x, 1.1f * scale, z,
                      1.2f * scale, 1.5f * scale,
                      1.2f * scale,
                      0.12f, 0.39f, 0.13f);

        drawEllipsoid(x - 0.55f * scale,
                      0.8f * scale, z + 0.25f * scale,
                      0.8f * scale, 1.0f * scale,
                      0.8f * scale,
                      0.16f, 0.45f, 0.15f);

        drawEllipsoid(x + 0.55f * scale,
                      0.8f * scale, z - 0.2f * scale,
                      0.8f * scale, 1.0f * scale,
                      0.8f * scale,
                      0.13f, 0.35f, 0.12f);
    }

    void drawBush(float x, float z, float scale)
    {
        drawEllipsoid(x, -1.15f, z,
                      0.8f * scale, 0.55f * scale,
                      0.7f * scale,
                      0.13f, 0.34f, 0.10f);

        drawEllipsoid(x + 0.45f * scale, -1.05f,
                      z + 0.1f,
                      0.55f * scale, 0.45f * scale,
                      0.55f * scale,
                      0.18f, 0.42f, 0.12f);
    }

    // --------------------------------------------------
    // PATH AND GRASS
    // --------------------------------------------------

    void drawPath()
    {
        farmBox(0.0f, -1.94f, 1.5f,
                3.2f, 0.05f, 12.0f,
                0.48f, 0.34f, 0.20f);

        drawEllipsoid(-0.9f, -1.89f, -1.0f,
                      0.6f, 0.025f, 0.8f,
                      0.42f, 0.29f, 0.17f);

        drawEllipsoid(0.8f, -1.89f, 2.0f,
                      0.7f, 0.025f, 0.6f,
                      0.40f, 0.28f, 0.16f);
    }

    void drawGrassDetails()
    {
        for (int i = 0; i < 45; i++)
        {
            float x = -11.0f + i * 0.53f;
            float z = -1.0f + sinf(i * 2.3f) * 4.5f;

            if (fabsf(x) < 2.0f)
                continue;

            float green = 0.22f + 0.08f * sinf(i);

            drawEllipsoid(x, -1.88f, z,
                          0.18f, 0.035f, 0.14f,
                          0.10f, green, 0.08f);
        }
    }

    // --------------------------------------------------
    // 3D RUSTIC PERIMETER FENCE
    // --------------------------------------------------

    void fencePost(float x, float z)
    {
        glPushMatrix();

        glTranslatef(x, -1.15f, z);

        glRotatef(
            sinf(x * 2.0f + z) * 3.0f,
            0, 0, 1
        );

        farmBox(0, 0.85f, 0,
                0.22f, 1.7f, 0.24f,
                0.34f, 0.18f, 0.07f);

        farmBox(0, 1.70f, 0,
                0.27f, 0.12f, 0.28f,
                0.48f, 0.29f, 0.12f);

        glPopMatrix();
    }

    void fenceRail(float x1, float z1,
                   float x2, float z2, float y)
    {
        float dx = x2 - x1;
        float dz = z2 - z1;

        float length =
            sqrtf(dx * dx + dz * dz);

        float angle =
            atan2f(dz, dx) * 180.0f / PI;

        glPushMatrix();

        glTranslatef(
            (x1 + x2) * 0.5f,
            y,
            (z1 + z2) * 0.5f
        );

        glRotatef(-angle, 0, 1, 0);

        farmBox(0, 0, 0,
                length, 0.16f, 0.18f,
                0.43f, 0.25f, 0.11f);

        farmBox(0, 0.065f, 0,
                length * 0.96f, 0.025f, 0.19f,
                0.58f, 0.36f, 0.17f);

        glPopMatrix();
    }

    void drawFenceSection(float x1, float z1,
                          float x2, float z2, int posts)
    {
        for (int i = 0; i < posts; i++)
        {
            float t = i / (float)(posts - 1);

            fencePost(
                x1 + (x2 - x1) * t,
                z1 + (z2 - z1) * t
            );
        }

        for (int i = 0; i < posts - 1; i++)
        {
            float t1 = i / (float)(posts - 1);
            float t2 = (i + 1) / (float)(posts - 1);

            float ax = x1 + (x2 - x1) * t1;
            float az = z1 + (z2 - z1) * t1;

            float bx = x1 + (x2 - x1) * t2;
            float bz = z1 + (z2 - z1) * t2;

            fenceRail(ax, az, bx, bz, -0.60f);
            fenceRail(ax, az, bx, bz, 0.05f);
        }
    }

    void drawRusticFence()
    {
        drawFenceSection(-12, -10, 13, -10, 7);
        drawFenceSection(-12, -10, -12, 6, 5);
        drawFenceSection(13, -10, 13, 6, 5);

        drawFenceSection(-10, 7, -3, 7, 3);
        drawFenceSection(3, 7, 10, 7, 3);
    }

    // --------------------------------------------------
    // 3D HAY BALES
    // --------------------------------------------------

    void drawHayBale(float x, float y, float z,
                     float sx, float sy, float sz)
    {
        farmBox(x, y, z, sx, sy, sz,
                0.78f, 0.56f, 0.19f);

        for (int i = 0; i < 5; i++)
        {
            float offset =
                -sy * 0.35f + i * sy * 0.17f;

            farmBox(x, y + offset, z + sz * 0.51f,
                    sx * 0.85f, 0.025f, 0.025f,
                    0.58f, 0.39f, 0.10f);
        }

        for (int i = -1; i <= 1; i++)
        {
            farmBox(x + i * sx * 0.28f, y,
                    z + sz * 0.52f,
                    0.035f, sy * 0.95f, 0.025f,
                    0.43f, 0.30f, 0.10f);
        }
    }

    void drawScatteredHay()
    {
        drawHayBale(9.0f, -1.55f, -1.5f,
                    1.25f, 0.75f, 0.85f);

        drawHayBale(10.0f, -1.55f, -2.6f,
                    1.15f, 0.70f, 0.80f);

        drawHayBale(9.5f, -0.85f, -2.1f,
                    1.05f, 0.65f, 0.75f);

        drawHayBale(11.0f, -1.55f, -0.5f,
                    1.15f, 0.70f, 0.80f);
    }

    // --------------------------------------------------
    // 3D WOODEN WATER BARREL
    // --------------------------------------------------

    void drawFarmBarrel()
    {
        const float x = 8.8f;
        const float y = -2.0f;
        const float z = -4.0f;

        glPushMatrix();

        glTranslatef(x, y + 0.55f, z);

        glColor3f(0.40f, 0.22f, 0.09f);

        GLUquadric* q = gluNewQuadric();

        glRotatef(-90, 1, 0, 0);

        gluCylinder(q, 0.52, 0.52, 1.1, 24, 4);
        gluDisk(q, 0, 0.52, 24, 1);

        glTranslatef(0, 0, 1.1f);

        gluDisk(q, 0, 0.52, 24, 1);

        gluDeleteQuadric(q);

        glPopMatrix();

        for (int i = 0; i < 3; i++)
        {
            float bandY = y + 0.18f + i * 0.38f;

            farmCylinder(x, bandY, z,
                         0.54f, 0.07f,
                         0.25f, 0.25f, 0.26f);
        }

        farmCylinder(x, y + 1.65f, z,
                     0.53f, 0.07f,
                     0.31f, 0.16f, 0.06f);

        farmSphere(x, y + 1.70f, z,
                   0.43f, 0.025f, 0.43f,
                   0.15f, 0.46f, 0.68f);
    }

    // --------------------------------------------------
    // 3D RAKE
    // --------------------------------------------------

    void drawRake()
    {
        glPushMatrix();

        glTranslatef(7.8f, -1.95f, -5.65f);
        glRotatef(-13.0f, 0, 0, 1);

        farmBox(0, 1.0f, 0,
                0.09f, 2.0f, 0.09f,
                0.48f, 0.28f, 0.12f);

        farmBox(0, 2.0f, 0,
                0.95f, 0.13f, 0.14f,
                0.35f, 0.35f, 0.37f);

        for (int i = -3; i <= 3; i++)
        {
            farmBox(i * 0.13f, 1.82f, 0,
                    0.055f, 0.34f, 0.07f,
                    0.28f, 0.28f, 0.30f);
        }

        glPopMatrix();
    }

    // --------------------------------------------------
    // 3D PITCHFORK
    // --------------------------------------------------

    void drawPitchfork()
    {
        glPushMatrix();

        glTranslatef(8.7f, -1.95f, -5.65f);
        glRotatef(12.0f, 0, 0, 1);

        farmBox(0, 1.0f, 0,
                0.085f, 2.0f, 0.085f,
                0.48f, 0.28f, 0.12f);

        farmBox(0, 2.0f, 0,
                0.50f, 0.10f, 0.10f,
                0.30f, 0.30f, 0.33f);

        for (int i = -1; i <= 1; i++)
        {
            farmBox(i * 0.17f, 2.22f, 0,
                    0.065f, 0.42f, 0.065f,
                    0.40f, 0.40f, 0.43f);
        }

        glPopMatrix();
    }

    // --------------------------------------------------
    // COMPLETE FARMYARD EQUIPMENT
    // --------------------------------------------------

    void drawFarmEquipment()
    {
        drawRusticFence();
        drawScatteredHay();
        drawFarmBarrel();
        drawRake();
        drawPitchfork();
    }
}

// --------------------------------------------------
// PUBLIC SCENE FUNCTION
// --------------------------------------------------

void drawFarmyard()
{
    // Ground
    farmBox(0.0f, -2.05f, 0.0f,
            30.0f, 0.2f, 24.0f,
            0.25f, 0.43f, 0.16f);

    drawPath();
    drawGrassDetails();

    drawFarmhouse();
    drawCowshed();

    // Trees
    farmTree(-11.0f, -2.0f, 1.0f);
    farmTree(-11.0f, 3.0f, 0.85f);
    farmTree(11.0f, -7.0f, 1.0f);
    farmTree(10.5f, 4.0f, 0.9f);
    farmTree(-4.0f, 8.0f, 0.75f);

    // Bushes
    drawBush(-9.0f, -1.0f, 1.0f);
    drawBush(-8.0f, 2.0f, 0.8f);
    drawBush(10.0f, 1.0f, 0.9f);
    drawBush(3.0f, 5.0f, 0.8f);

    // Farm equipment and fence
    drawFarmEquipment();

    // Cow inside cowshed
    drawFarmyardCow();

    // Yellow sun
    drawFarmSun();

    // Farmer walks towards cowshed
    drawWalkingFarmer();

    glutPostRedisplay();
}
