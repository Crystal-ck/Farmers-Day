
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <cmath>
#include "MilkingObjects.h"

namespace
{
    const float PI = 3.14159265f;

    void box(float x, float y, float z,
             float sx, float sy, float sz,
             float r, float g, float b)
    {
        glColor3f(r, g, b);
        glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(sx, sy, sz);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    void cylinder(float x, float y, float z,
                  float bottomRadius, float topRadius,
                  float height,
                  float r, float g, float b)
    {
        GLUquadric* q = gluNewQuadric();

        glColor3f(r, g, b);
        glPushMatrix();
        glTranslatef(x, y, z);

        gluCylinder(q, bottomRadius, topRadius, height, 24, 4);

        gluDisk(q, 0.0, bottomRadius, 24, 1);

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, height);
        gluDisk(q, 0.0, topRadius, 24, 1);
        glPopMatrix();

        glPopMatrix();
        gluDeleteQuadric(q);
    }

    void metalBucket(float x, float y, float z, float time)
    {
        glPushMatrix();
        glTranslatef(x, y, z);

        // Bucket body
        glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        cylinder(0, 0, 0, 0.38f, 0.48f, 0.65f,
                 0.58f, 0.62f, 0.65f);
        glPopMatrix();

        // Thick rim
        glColor3f(0.78f, 0.80f, 0.82f);
        glPushMatrix();
        glTranslatef(0, 0.65f, 0);
        glutSolidTorus(0.045, 0.46, 12, 28);
        glPopMatrix();

        // Milk surface
        glColor3f(0.94f, 0.95f, 0.91f);
        glPushMatrix();
        glTranslatef(0, 0.52f, 0);
        glScalef(0.42f, 0.035f, 0.42f);
        glutSolidSphere(1.0, 20, 12);
        glPopMatrix();

        // Small animated milk ripples
        for (int i = 0; i < 3; i++)
        {
            float radius = 0.12f + 0.055f * i
                         + 0.015f * sin(time * 5.0f + i);

            glColor3f(0.78f, 0.82f, 0.80f);
            glPushMatrix();
            glTranslatef(0, 0.56f, 0);
            glScalef(radius, 0.008f, radius);
            glutWireTorus(0.012, 1.0, 6, 24);
            glPopMatrix();
        }

        // Handle supports
        glColor3f(0.35f, 0.37f, 0.39f);
        for (int side = -1; side <= 1; side += 2)
        {
            glPushMatrix();
            glTranslatef(side * 0.43f, 0.57f, 0);
            glutSolidSphere(0.055, 12, 10);
            glPopMatrix();
        }

        // Bail handle
        glColor3f(0.35f, 0.37f, 0.39f);
        glPushMatrix();
        glTranslatef(0, 0.61f, 0);
        glRotatef(90, 1, 0, 0);
        glutSolidTorus(0.025, 0.43, 10, 28);
        glPopMatrix();

        glPopMatrix();
    }

    void milkCan(float x, float y, float z)
    {
        // Main metal body
        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90, 1, 0, 0);

        cylinder(0, 0, 0, 0.42f, 0.34f, 0.85f,
                 0.58f, 0.61f, 0.64f);

        // Neck
        glTranslatef(0, 0, 0.85f);
        cylinder(0, 0, 0, 0.25f, 0.23f, 0.30f,
                 0.68f, 0.70f, 0.72f);

        // Lid
        glTranslatef(0, 0, 0.31f);
        glColor3f(0.38f, 0.40f, 0.42f);
        glutSolidTorus(0.035, 0.23, 10, 24);

        glPushMatrix();
        glScalef(0.23f, 0.23f, 0.035f);
        glutSolidSphere(1.0, 16, 10);
        glPopMatrix();

        glPopMatrix();

        // Side handles
        for (int side = -1; side <= 1; side += 2)
        {
            glColor3f(0.32f, 0.34f, 0.36f);
            glPushMatrix();
            glTranslatef(x + side * 0.39f, y + 0.67f, z);
            glRotatef(90, 0, 1, 0);
            glutSolidTorus(0.035, 0.17, 10, 20);
            glPopMatrix();
        }
    }

    void milkingStool(float x, float y, float z)
    {
        // Wooden seat
        box(x, y + 0.65f, z, 1.0f, 0.16f, 0.85f,
            0.48f, 0.27f, 0.12f);

        // Four legs
        for (int sx = -1; sx <= 1; sx += 2)
        {
            for (int sz = -1; sz <= 1; sz += 2)
            {
                box(x + sx * 0.37f, y + 0.30f,
                    z + sz * 0.29f,
                    0.12f, 0.65f, 0.12f,
                    0.35f, 0.19f, 0.08f);
            }
        }

        // Support rails
        box(x, y + 0.22f, z - 0.29f,
            0.78f, 0.09f, 0.09f,
            0.34f, 0.18f, 0.07f);

        box(x, y + 0.22f, z + 0.29f,
            0.78f, 0.09f, 0.09f,
            0.34f, 0.18f, 0.07f);
    }

    void washBasin(float x, float y, float z)
    {
        // Basin body
        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90, 1, 0, 0);
        cylinder(0, 0, 0, 0.55f, 0.65f, 0.32f,
                 0.48f, 0.52f, 0.55f);
        glPopMatrix();

        // Water surface
        glColor3f(0.42f, 0.66f, 0.72f);
        glPushMatrix();
        glTranslatef(x, y + 0.27f, z);
        glScalef(0.58f, 0.025f, 0.58f);
        glutSolidSphere(1.0, 20, 12);
        glPopMatrix();
    }

    void hangingRope(float time)
    {
        glColor3f(0.55f, 0.38f, 0.20f);
        glLineWidth(4.0f);

        glBegin(GL_LINE_STRIP);

        for (int i = 0; i <= 20; i++)
        {
            float t = i / 20.0f;
            float x = 5.5f + 0.12f * sin(time * 2.0f + t * 2.0f);
            float y = 3.0f - t * 2.0f;
            float z = 1.5f + 0.08f * sin(time * 2.0f + t);

            glVertex3f(x, y, z);
        }

        glEnd();
        glLineWidth(1.0f);
    }
}

void drawMilkingObjects(float elapsedSeconds)
{
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LINE_BIT);

    glDisable(GL_TEXTURE_2D);

    // Stool beside the milking position
    milkingStool(-1.5f, -1.95f, 2.0f);

    // Bucket positioned near the cow
   metalBucket(-3.0f, -1.95f, 2.3f, elapsedSeconds);

    // Milk storage can
    milkCan(3.5f, -1.95f, -2.0f);

    // Washing basin
    washBasin(-6.5f, -1.95f, 3.0f);

    // Hanging rope
    hangingRope(elapsedSeconds);

    glPopAttrib();
}
