#include <GL/freeglut.h>
#include <algorithm>
#include <cmath>
#include "environment_utils.h"

namespace
{
    constexpr float PI = 3.14159265f;
}

void drawEllipsoid(float x, float y, float z,
                   float sx, float sy, float sz,
                   float r, float g, float b)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidSphere(1.0, 28, 24);

    glPopMatrix();
}

void drawCylinder(float x1, float y1, float z1,
                  float x2, float y2, float z2,
                  float radius, float r, float g, float b)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;

    float length = std::sqrt(dx * dx + dy * dy + dz * dz);

    if (length < 0.001f)
        return;

    glPushMatrix();

    glTranslatef(x1, y1, z1);

    float cosine = std::max(-1.0f, std::min(1.0f, dy / length));
    float angle = std::acos(cosine) * 180.0f / PI;

    if (std::fabs(dx) > 0.0001f || std::fabs(dz) > 0.0001f)
        glRotatef(angle, -dz, 0.0f, dx);
    else if (dy < 0.0f)
        glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

    glColor3f(r, g, b);

    GLUquadric* quad = gluNewQuadric();

    gluCylinder(quad, radius, radius * 0.85f, length, 16, 4);

    gluDeleteQuadric(quad);

    glPopMatrix();
}