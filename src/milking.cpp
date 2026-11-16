
#include <GL/freeglut.h>
#include "milking.h"
#include "environment_utils.h"
#include "../characters/cow.h"
#include "../characters/farmer.h"
#include "../Objects/MilkingObjects.h"

#include <cmath>
namespace
{
    void milkBox(float x, float y, float z,
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

    void milkCylinder(float x, float y, float z,
                      float radius, float height,
                      float r, float g, float b)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        glColor3f(r, g, b);

        GLUquadric* quad = gluNewQuadric();
        gluCylinder(quad, radius, radius * 0.9f,
                    height, 24, 4);
        gluDeleteQuadric(quad);

        glPopMatrix();
    }

    void drawMetalBucket(float x, float y, float z)
    {
        // Bucket body
        milkCylinder(x, y, z, 0.42f, 0.75f,
                     0.60f, 0.64f, 0.67f);

        // Bottom
        glPushMatrix();
        glTranslatef(x, y, z);
        glColor3f(0.48f, 0.52f, 0.55f);
        glScalef(1.0f, 0.12f, 1.0f);
        glutSolidTorus(0.035f, 0.37f, 12, 24);
        glPopMatrix();

        // Top rim
        glPushMatrix();
        glTranslatef(x, y + 0.75f, z);
        glColor3f(0.75f, 0.78f, 0.80f);
        glutSolidTorus(0.045f, 0.42f, 12, 28);
        glPopMatrix();

        // Handle supports
        drawCylinder(x - 0.40f, y + 0.60f, z,
                     x - 0.48f, y + 0.88f, z,
                     0.035f, 0.35f, 0.37f, 0.39f);

        drawCylinder(x + 0.40f, y + 0.60f, z,
                     x + 0.48f, y + 0.88f, z,
                     0.035f, 0.35f, 0.37f, 0.39f);

        drawCylinder(x - 0.48f, y + 0.88f, z,
                     x + 0.48f, y + 0.88f, z,
                     0.035f, 0.35f, 0.37f, 0.39f);
    }

    void drawShedStructure()
    {
        // Floor
        milkBox(0.0f, -1.95f, -2.0f,
                20.0f, 0.2f, 20.0f,
                0.42f, 0.32f, 0.22f);

        // Back wall
        milkBox(0.0f, 0.5f, -11.0f,
                20.0f, 5.0f, 0.35f,
                0.48f, 0.33f, 0.21f);

        // Side walls
        milkBox(-10.0f, 0.5f, -2.0f,
                0.35f, 5.0f, 18.0f,
                0.50f, 0.35f, 0.22f);

        milkBox(10.0f, 0.5f, -2.0f,
                0.35f, 5.0f, 18.0f,
                0.50f, 0.35f, 0.22f);

        // Roof supports
        milkBox(-8.5f, 2.5f, -2.0f,
                0.25f, 5.0f, 0.25f,
                0.25f, 0.13f, 0.07f);

        milkBox(8.5f, 2.5f, -2.0f,
                0.25f, 5.0f, 0.25f,
                0.25f, 0.13f, 0.07f);

        milkBox(0.0f, 4.6f, -2.0f,
                0.25f, 0.25f, 18.0f,
                0.25f, 0.13f, 0.07f);

        // Roof slopes
        glColor3f(0.29f, 0.15f, 0.10f);

        glBegin(GL_QUADS);
            glVertex3f(-10.0f, 2.8f, 7.0f);
            glVertex3f(0.0f, 4.8f, 7.0f);
            glVertex3f(0.0f, 4.8f, -11.0f);
            glVertex3f(-10.0f, 2.8f, -11.0f);

            glVertex3f(0.0f, 4.8f, 7.0f);
            glVertex3f(10.0f, 2.8f, 7.0f);
            glVertex3f(10.0f, 2.8f, -11.0f);
            glVertex3f(0.0f, 4.8f, -11.0f);
        glEnd();
    }

    void drawStall()
    {
        // Wooden stall posts
        float postX[] = {-5.5f, -2.0f, 2.0f, 5.5f};

        for (int i = 0; i < 4; i++)
        {
            milkBox(postX[i], -0.1f, -4.5f,
                    0.22f, 3.7f, 0.22f,
                    0.30f, 0.16f, 0.08f);
        }

        // Horizontal wooden rails
        milkBox(0.0f, 0.6f, -4.5f,
                11.0f, 0.20f, 0.20f,
                0.40f, 0.24f, 0.12f);

        milkBox(0.0f, -0.6f, -4.5f,
                11.0f, 0.20f, 0.20f,
                0.40f, 0.24f, 0.12f);

        // Side rails
        milkBox(-5.5f, 0.1f, -1.5f,
                0.20f, 0.20f, 6.0f,
                0.40f, 0.24f, 0.12f);

        milkBox(5.5f, 0.1f, -1.5f,
                0.20f, 0.20f, 6.0f,
                0.40f, 0.24f, 0.12f);

        // Stall floor platform
        milkBox(0.0f, -1.72f, -3.0f,
                11.5f, 0.28f, 6.5f,
                0.55f, 0.42f, 0.28f);

        // Divider boards
        milkBox(-3.8f, -0.1f, -3.0f,
                0.16f, 2.8f, 0.18f,
                0.38f, 0.23f, 0.12f);

        milkBox(3.8f, -0.1f, -3.0f,
                0.16f, 2.8f, 0.18f,
                0.38f, 0.23f, 0.12f);
    }

    void drawFeedingArea()
    {
        // Feed trough
        milkBox(-7.0f, -1.30f, -5.0f,
                2.5f, 0.65f, 5.0f,
                0.34f, 0.20f, 0.10f);

        // Feed inside trough
        milkBox(-7.0f, -0.94f, -5.0f,
                2.25f, 0.08f, 4.7f,
                0.45f, 0.48f, 0.18f);

        // Hay pile
        drawEllipsoid(-7.0f, -0.65f, -5.0f,
                      0.85f, 0.45f, 1.5f,
                      0.72f, 0.57f, 0.22f);
    }

    void drawMilkingEquipment()
    {
        // Milking stool
        milkBox(-1.5f, -1.0f, 2.0f,
                1.3f, 0.22f, 1.0f,
                0.48f, 0.29f, 0.14f);

        milkBox(-2.0f, -1.55f, 1.65f,
                0.12f, 1.0f, 0.12f,
                0.31f, 0.17f, 0.08f);

        milkBox(-1.0f, -1.55f, 1.65f,
                0.12f, 1.0f, 0.12f,
                0.31f, 0.17f, 0.08f);

        milkBox(-2.0f, -1.55f, 2.35f,
                0.12f, 1.0f, 0.12f,
                0.31f, 0.17f, 0.08f);

        milkBox(-1.0f, -1.55f, 2.35f,
                0.12f, 1.0f, 0.12f,
                0.31f, 0.17f, 0.08f);

        // Milk buckets
        drawMetalBucket(1.0f, -1.85f, 2.0f);
        drawMetalBucket(3.0f, -1.85f, 2.0f);

        // Washing basin
        glPushMatrix();
        glTranslatef(-6.5f, -1.45f, 3.0f);
        glColor3f(0.55f, 0.59f, 0.62f);
        glScalef(1.0f, 0.3f, 0.8f);
        glutSolidSphere(1.0f, 28, 20);
        glPopMatrix();

        // Water surface
        milkBox(-6.5f, -1.34f, 3.0f,
                1.35f, 0.025f, 0.85f,
                0.25f, 0.52f, 0.66f);

        // Folded cleaning cloth
        milkBox(-6.0f, -1.0f, 4.0f,
                0.65f, 0.08f, 0.45f,
                0.80f, 0.78f, 0.64f);

        // Storage shelf
        milkBox(7.5f, 0.0f, -5.0f,
                0.25f, 3.0f, 3.0f,
                0.36f, 0.21f, 0.11f);

        milkBox(8.0f, 1.2f, -5.0f,
                1.0f, 0.15f, 3.0f,
                0.38f, 0.23f, 0.12f);

        milkBox(8.0f, -0.2f, -5.0f,
                1.0f, 0.15f, 3.0f,
                0.38f, 0.23f, 0.12f);

        // Extra storage containers
        drawMetalBucket(7.5f, -1.85f, -4.5f);
    }

    void drawHooksAndRopes()
    {
        // Wall hooks
        for (int i = 0; i < 3; i++)
        {
            float z = -8.0f + i * 2.0f;

            drawCylinder(-9.5f, 1.0f, z,
                         -9.0f, 1.0f, z,
                         0.06f, 0.25f, 0.25f, 0.25f);
        }

        // Hanging rope coils represented by rings
        for (int i = 0; i < 2; i++)
        {
            glPushMatrix();
            glTranslatef(-9.0f, 0.5f, -7.0f + i * 2.0f);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glColor3f(0.65f, 0.48f, 0.25f);
            glutSolidTorus(0.045f, 0.22f, 10, 20);
            glPopMatrix();
        }
    }

    void drawShedDetails()
    {
        // Small high windows for daylight
        milkBox(-9.78f, 2.0f, -2.0f,
                0.08f, 0.8f, 2.0f,
                0.30f, 0.48f, 0.55f);

        milkBox(9.78f, 2.0f, -2.0f,
                0.08f, 0.8f, 2.0f,
                0.30f, 0.48f, 0.55f);

        // Hay bales in the corner
        drawEllipsoid(7.0f, -1.0f, -8.0f,
                      0.9f, 0.8f, 0.8f,
                      0.72f, 0.57f, 0.22f);

        drawEllipsoid(8.0f, -1.1f, -8.0f,
                      0.8f, 0.7f, 0.75f,
                      0.76f, 0.60f, 0.24f);
    }
}


void drawMilkingArea(float elapsedSeconds)
{
    drawShedStructure();
    drawStall();
    drawFeedingArea();
    drawMilkingObjects(elapsedSeconds);
    drawHooksAndRopes();
    drawShedDetails();

  
    // --------------------------------------------------
    // COW
    // --------------------------------------------------

    drawCow(-3.0f, -2.0f, 1.0f, 1.5f, elapsedSeconds);

    // --------------------------------------------------
    // FARMER: WASHING THEN MILKING
    // --------------------------------------------------

    glPushMatrix();

    // Position farmer beside the cow
    glTranslatef(-2.0f, -1.95f, 1.8f);

    // Turn farmer towards the cow
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

    if (elapsedSeconds < 9.0f)
    {
        // WASHING PHASE
        float washMotion = 25.0f * sin(elapsedSeconds * 5.0f);

        drawFarmerPosed(
            0, 0, 0,
            1.0f,
            12.0f,
            -90.0f, -90.0f,
            35.0f + washMotion,
            35.0f - washMotion,
            elapsedSeconds
        );
    }
    else
    {
        // MILKING PHASE
        float squeeze = 12.0f * sin(elapsedSeconds * 10.0f);

        float leftArm = 45.0f + squeeze;
        float rightArm = 45.0f - squeeze;

        drawFarmerPosed(
            0, 0, 0,
            1.0f,
            5.0f,
            -90.0f, -90.0f,
            leftArm,
            rightArm,
            elapsedSeconds
        );
    }

    glPopMatrix();
}
