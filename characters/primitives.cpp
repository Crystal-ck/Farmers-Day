
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <cmath>
#include "primitives.h"

namespace
{
    GLUquadric* quad()
    {
        static GLUquadric* q = nullptr;

        if (!q)
        {
            q = gluNewQuadric();
            gluQuadricNormals(q, GLU_SMOOTH);
        }

        return q;
    }

    const int SPHERE_SLICES = 32;
    const int SPHERE_STACKS = 24;
}

// Sphere
void drawSphere(float x, float y, float z,
                float sx, float sy, float sz,
                float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidSphere(1.0, SPHERE_SLICES, SPHERE_STACKS);

    glPopMatrix();
}

// Ellipsoid
void drawEllipsoid(float x, float y, float z,
                   float sx, float sy, float sz,
                   float r, float g, float b)
{
    drawSphere(x, y, z, sx, sy, sz, r, g, b);
}

// Cube
void drawCube(float x, float y, float z,
              float sx, float sy, float sz,
              float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidCube(1.0);

    glPopMatrix();
}

// Cone
void drawCone(float x, float y, float z,
              float radius, float height,
              float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);

    glColor3f(r, g, b);
    glutSolidCone(radius, height, 24, 12);

    glPopMatrix();
}

// Rotated sphere
void drawSphereRot(float x, float y, float z,
                   float sx, float sy, float sz,
                   float angX, float angY, float angZ,
                   float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(angZ, 0, 0, 1);
    glRotatef(angY, 0, 1, 0);
    glRotatef(angX, 1, 0, 0);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidSphere(1.0, SPHERE_SLICES, SPHERE_STACKS);

    glPopMatrix();
}

// Standard cylinder
void drawCylinder(float x, float y, float z,
                  float rBase, float rTop, float height,
                  float angX, float angY, float angZ,
                  float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(angZ, 0, 0, 1);
    glRotatef(angY, 0, 1, 0);
    glRotatef(angX, 1, 0, 0);

    glColor3f(r, g, b);

    gluCylinder(quad(), rBase, rTop, height, 24, 6);

    glPushMatrix();
    glRotatef(180.0f, 1, 0, 0);
    gluDisk(quad(), 0.0, rBase, 24, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, height);
    gluDisk(quad(), 0.0, rTop, 24, 1);
    glPopMatrix();

    glPopMatrix();
}

// Cylinder between two points (used by Sunrise)
void drawCylinder(float x1, float y1, float z1,
                  float x2, float y2, float z2,
                  float radius,
                  float r, float g, float b)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;

    float length = sqrt(dx * dx + dy * dy + dz * dz);

    if (length < 0.0001f)
        return;

    float axisX = -dy;
    float axisY = dx;
    float axisZ = 0.0f;

    float axisLength = sqrt(axisX * axisX + axisY * axisY);

    glPushMatrix();

    glTranslatef(x1, y1, z1);

    if (axisLength > 0.0001f)
    {
        float dot = dz / length;

        if (dot > 1.0f) dot = 1.0f;
        if (dot < -1.0f) dot = -1.0f;

        float angle = acos(dot) * 180.0f / 3.14159265f;

        glRotatef(angle, axisX, axisY, axisZ);
    }
    else if (dz < 0.0f)
    {
        glRotatef(180.0f, 1, 0, 0);
    }

    glColor3f(r, g, b);

    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);

    gluCylinder(q, radius, radius, length, 16, 1);

    gluDeleteQuadric(q);

    glPopMatrix();
}

// Torus
void drawTorus(float x, float y, float z,
               float tubeRadius, float ringRadius,
               float angX, float angY, float angZ,
               float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(angZ, 0, 0, 1);
    glRotatef(angY, 0, 1, 0);
    glRotatef(angX, 1, 0, 0);

    glColor3f(r, g, b);
    glutSolidTorus(tubeRadius, ringRadius, 16, 40);

    glPopMatrix();
}

// Lighting
void initCowLighting()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat spec[] = {0.22f, 0.22f, 0.22f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 28.0f);

    GLfloat globalAmb[] = {0.30f, 0.30f, 0.34f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

    glEnable(GL_LIGHTING);

    GLfloat keyPos[]  = {0.5f, 1.0f, 0.8f, 0.0f};
    GLfloat keyDiff[] = {0.95f, 0.92f, 0.84f, 1.0f};
    GLfloat keySpec[] = {0.60f, 0.60f, 0.55f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, keyPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, keyDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, keySpec);
    glEnable(GL_LIGHT0);

    GLfloat fillPos[]  = {-0.8f, 0.3f, -0.5f, 0.0f};
    GLfloat fillDiff[] = {0.25f, 0.30f, 0.40f, 1.0f};
    GLfloat fillSpec[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, fillPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, fillDiff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, fillSpec);
    glEnable(GL_LIGHT1);
}
