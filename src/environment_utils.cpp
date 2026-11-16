#include <GL/freeglut.h>
#include <algorithm>
#include <cmath>
#include "environment_utils.h"

namespace
{
    constexpr float PI = 3.14159265f;
}

void drawSharedSun(float x, float y, float z, float scale)
{
    // Outer golden glow
    drawEllipsoid(
        x, y, z,
        1.1f * scale,
        1.1f * scale,
        1.0f * scale,
        1.0f, 0.78f, 0.28f
    );

    // Brighter inner surface
    drawEllipsoid(
        x, y, z + 0.03f * scale,
        0.85f * scale,
        0.85f * scale,
        0.85f * scale,
        1.0f, 0.88f, 0.48f
    );
}
