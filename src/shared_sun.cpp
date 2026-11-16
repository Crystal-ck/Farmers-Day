#include <GL/freeglut.h>
#include "environment_utils.h"
#include "shared_sun.h"

void drawSharedSun(float x, float y, float z, float scale)
{
    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);

    // Outer golden sun
    drawEllipsoid(
        0.0f, 0.0f, 0.0f,
        1.1f, 1.1f, 1.1f,
        1.0f, 0.78f, 0.28f
    );

    // Bright inner sun
    drawEllipsoid(
        0.0f, 0.0f, 0.1f,
        0.85f, 0.85f, 0.85f,
        1.0f, 0.88f, 0.48f
    );

    glPopMatrix();
}