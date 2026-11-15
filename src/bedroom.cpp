
#include <GL/freeglut.h>
#include <cmath>
#include "../characters/farmer.h"

namespace
{
    float bedroomTime = 0.0f;
}

void updateBedroom(float elapsedSeconds)
{
    bedroomTime = elapsedSeconds;
}


void drawBedroomFarmer()
{
    auto smoothStep = [](float t)
    {
        t = fmaxf(0.0f, fminf(1.0f, t));
        return t * t * (3.0f - 2.0f * t);
    };

    float sitProgress = smoothStep((bedroomTime - 5.0f) / 5.0f);
    float legProgress = smoothStep((bedroomTime - 10.0f) / 4.0f);

    float hipAngle = 90.0f * sitProgress;
    float legAngle = 90.0f * legProgress;

    glPushMatrix();

    glTranslatef(2.2f, -0.38f, -1.55f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    drawFarmer(0.0f, 0.0f, 0.0f,
               0.85f, hipAngle, legAngle);

    glPopMatrix();
}

// --------------------------------------------------
// BEDROOM ENVIRONMENT
// Open-front farmhouse bedroom
// --------------------------------------------------

void bedroomBox(float x, float y, float z,
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

void bedroomSphere(float x, float y, float z,
                   float sx, float sy, float sz,
                   float r, float g, float b)
{
    glColor3f(r, g, b);

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    glutSolidSphere(0.5, 24, 24);
    glPopMatrix();
}

void bedroomCylinder(float x, float y, float z,
                     float radius, float height,
                     float r, float g, float b)
{
    glColor3f(r, g, b);

    glPushMatrix();
    glTranslatef(x, y, z);

    GLUquadric* q = gluNewQuadric();
    gluCylinder(q, radius, radius, height, 20, 4);
    gluDisk(q, 0, radius, 20, 1);

    glTranslatef(0, 0, height);
    gluDisk(q, 0, radius, 20, 1);

    gluDeleteQuadric(q);
    glPopMatrix();
}

// --------------------------------------------------
// ROOM STRUCTURE
// --------------------------------------------------

void drawBedroomRoom()
{
    // Wooden floor
    bedroomBox(0, -1.9f, 0,
               14, 0.25f, 11,
               0.48f, 0.29f, 0.15f);

    // Floorboards
    for (int i = -6; i <= 6; i++)
    {
        bedroomBox(i, -1.765f, 0,
                   0.025f, 0.015f, 10.8f,
                   0.30f, 0.17f, 0.08f);
    }

    // Back wall
    bedroomBox(0, 1.5f, -5.4f,
               14, 7, 0.3f,
               0.78f, 0.66f, 0.48f);

    // Left wall
    bedroomBox(-6.85f, 1.5f, 0,
               0.3f, 7, 11,
               0.68f, 0.55f, 0.39f);

    // Right wall
    bedroomBox(6.85f, 1.5f, 0,
               0.3f, 7, 11,
               0.68f, 0.55f, 0.39f);

    // Wall skirting
    bedroomBox(0, -1.55f, -5.18f,
               13.7f, 0.25f, 0.12f,
               0.30f, 0.17f, 0.09f);

    bedroomBox(-6.65f, -1.55f, 0,
               0.12f, 0.25f, 10.5f,
               0.30f, 0.17f, 0.09f);

    bedroomBox(6.65f, -1.55f, 0,
               0.12f, 0.25f, 10.5f,
               0.30f, 0.17f, 0.09f);

    // Ceiling beams
    for (int i = -5; i <= 5; i += 5)
    {
        bedroomBox(i, 4.95f, 0,
                   0.18f, 0.22f, 10.5f,
                   0.30f, 0.18f, 0.09f);
    }

    // Ceiling cross beam
    bedroomBox(0, 4.95f, -5.1f,
               13.5f, 0.22f, 0.18f,
               0.30f, 0.18f, 0.09f);
}

// --------------------------------------------------
// WINDOW
// --------------------------------------------------

void drawBedroomWindow()
{
    // Window opening surround
    bedroomBox(-3.0f, 1.8f, -5.18f,
               3.5f, 2.6f, 0.12f,
               0.30f, 0.17f, 0.08f);

    // Window glass
    bedroomBox(-3.0f, 1.8f, -5.08f,
               3.15f, 2.25f, 0.06f,
               0.45f, 0.72f, 0.83f);

    // Window frame
    bedroomBox(-3.0f, 3.0f, -4.99f,
               3.4f, 0.12f, 0.12f,
               0.25f, 0.13f, 0.06f);

    bedroomBox(-3.0f, 0.6f, -4.99f,
               3.4f, 0.12f, 0.12f,
               0.25f, 0.13f, 0.06f);

    bedroomBox(-4.65f, 1.8f, -4.99f,
               0.12f, 2.5f, 0.12f,
               0.25f, 0.13f, 0.06f);

    bedroomBox(-1.35f, 1.8f, -4.99f,
               0.12f, 2.5f, 0.12f,
               0.25f, 0.13f, 0.06f);

    // Window crossbars
    bedroomBox(-3.0f, 1.8f, -4.94f,
               0.09f, 2.35f, 0.08f,
               0.25f, 0.13f, 0.06f);

    bedroomBox(-3.0f, 1.8f, -4.94f,
               3.25f, 0.09f, 0.08f,
               0.25f, 0.13f, 0.06f);

    // Curtains
    bedroomBox(-4.95f, 1.8f, -4.85f,
               0.65f, 2.9f, 0.18f,
               0.63f, 0.25f, 0.17f);

    bedroomBox(-1.05f, 1.8f, -4.85f,
               0.65f, 2.9f, 0.18f,
               0.63f, 0.25f, 0.17f);

    // Curtain folds
    for (int i = 0; i < 4; i++)
    {
        bedroomBox(-5.18f + i * 0.15f, 1.8f, -4.73f,
                   0.035f, 2.8f, 0.035f,
                   0.78f, 0.39f, 0.25f);

        bedroomBox(-1.28f + i * 0.15f, 1.8f, -4.73f,
                   0.035f, 2.8f, 0.035f,
                   0.78f, 0.39f, 0.25f);
    }

    // Curtain rod
    bedroomCylinder(-5.4f, 3.35f, -4.75f,
                    0.055f, 4.8f,
                    0.24f, 0.14f, 0.08f);

    // Rotate rod to horizontal
    // Decorative rod ends
    bedroomSphere(-5.4f, 3.35f, -4.75f,
                  0.16f, 0.16f, 0.16f,
                  0.24f, 0.14f, 0.08f);

    bedroomSphere(-0.6f, 3.35f, -4.75f,
                  0.16f, 0.16f, 0.16f,
                  0.24f, 0.14f, 0.08f);

    // Window sill
    bedroomBox(-3.0f, 0.38f, -4.78f,
               3.8f, 0.16f, 0.45f,
               0.38f, 0.23f, 0.12f);
}

// --------------------------------------------------
// BED
// --------------------------------------------------

void drawBedroomBed()
{
    // Bed position: right side of room

    // Legs
    bedroomBox(0.6f, -1.35f, -3.5f,
               0.22f, 0.8f, 0.22f,
               0.25f, 0.13f, 0.06f);

    bedroomBox(3.8f, -1.35f, -3.5f,
               0.22f, 0.8f, 0.22f,
               0.25f, 0.13f, 0.06f);

    bedroomBox(0.6f, -1.35f, 1.0f,
               0.22f, 0.8f, 0.22f,
               0.25f, 0.13f, 0.06f);

    bedroomBox(3.8f, -1.35f, 1.0f,
               0.22f, 0.8f, 0.22f,
               0.25f, 0.13f, 0.06f);

    // Bed frame
    bedroomBox(2.2f, -0.95f, -1.25f,
               3.5f, 0.35f, 4.8f,
               0.38f, 0.22f, 0.11f);

    // Mattress
    bedroomBox(2.2f, -0.67f, -1.25f,
               3.35f, 0.38f, 4.6f,
               0.88f, 0.82f, 0.69f);

    // Headboard
    bedroomBox(2.2f, -0.15f, -3.75f,
               3.65f, 1.25f, 0.22f,
               0.32f, 0.18f, 0.09f);

    // Headboard decorative panels
    for (int i = 0; i < 3; i++)
    {
        bedroomBox(1.15f + i * 1.05f, -0.15f, -3.61f,
                   0.85f, 0.85f, 0.06f,
                   0.43f, 0.27f, 0.14f);
    }

    // Pillows
    bedroomBox(1.35f, -0.40f, -3.05f,
               1.15f, 0.25f, 0.85f,
               0.95f, 0.91f, 0.80f);

    bedroomBox(3.05f, -0.40f, -3.05f,
               1.15f, 0.25f, 0.85f,
               0.95f, 0.91f, 0.80f);

    // Blanket
    bedroomBox(2.2f, -0.39f, -0.65f,
               3.28f, 0.16f, 2.65f,
               0.42f, 0.29f, 0.23f);

    // Blanket folded edge
    bedroomBox(2.2f, -0.28f, -1.55f,
               3.3f, 0.12f, 0.45f,
               0.62f, 0.43f, 0.29f);

    // Blanket decorative stripes
    for (int i = 0; i < 5; i++)
    {
        bedroomBox(0.85f + i * 0.65f, -0.295f, -0.65f,
                   0.035f, 0.02f, 2.45f,
                   0.79f, 0.65f, 0.43f);
    }
}

// --------------------------------------------------
// BEDSIDE TABLE AND LAMP
// --------------------------------------------------

void drawBedsideTable()
{
    // Table body
    bedroomBox(-0.3f, -1.0f, -3.0f,
               1.35f, 1.0f, 1.2f,
               0.39f, 0.23f, 0.12f);

    // Table top
    bedroomBox(-0.3f, -0.45f, -3.0f,
               1.5f, 0.12f, 1.35f,
               0.52f, 0.32f, 0.16f);

    // Drawer
    bedroomBox(-0.3f, -0.85f, -2.37f,
               1.05f, 0.35f, 0.06f,
               0.57f, 0.37f, 0.20f);

    // Drawer handle
    bedroomSphere(-0.3f, -0.85f, -2.30f,
                  0.09f, 0.09f, 0.09f,
                  0.85f, 0.68f, 0.30f);

    // Lamp base
    bedroomCylinder(-0.3f, -0.38f, -3.0f,
                    0.22f, 0.08f,
                    0.28f, 0.18f, 0.10f);

    // Lamp stem
    bedroomCylinder(-0.3f, -0.30f, -3.0f,
                    0.06f, 0.55f,
                    0.28f, 0.18f, 0.10f);

    // Lampshade
    bedroomSphere(-0.3f, 0.25f, -3.0f,
                  0.65f, 0.55f, 0.65f,
                  0.91f, 0.76f, 0.45f);
}

// --------------------------------------------------
// WARDROBE
// --------------------------------------------------

void drawBedroomWardrobe()
{
    // Wardrobe body
    bedroomBox(-5.2f, 0.8f, 1.7f,
               2.0f, 5.0f, 1.3f,
               0.38f, 0.22f, 0.11f);

    // Top trim
    bedroomBox(-5.2f, 3.35f, 1.7f,
               2.15f, 0.18f, 1.45f,
               0.26f, 0.14f, 0.07f);

    // Door panels
    bedroomBox(-5.72f, 0.85f, 1.02f,
               0.88f, 4.2f, 0.08f,
               0.52f, 0.32f, 0.17f);

    bedroomBox(-4.68f, 0.85f, 1.02f,
               0.88f, 4.2f, 0.08f,
               0.52f, 0.32f, 0.17f);

    // Vertical door details
    bedroomBox(-5.72f, 0.85f, 0.96f,
               0.05f, 3.8f, 0.04f,
               0.30f, 0.17f, 0.08f);

    bedroomBox(-4.68f, 0.85f, 0.96f,
               0.05f, 3.8f, 0.04f,
               0.30f, 0.17f, 0.08f);

    // Handles
    bedroomSphere(-5.32f, 0.9f, 0.88f,
                  0.09f, 0.09f, 0.09f,
                  0.85f, 0.68f, 0.28f);
}

// --------------------------------------------------
// BEDROOM DOOR
// --------------------------------------------------

void drawBedroomDoor()
{
    // Door frame on right wall
    bedroomBox(6.63f, 0.45f, 2.2f,
               0.15f, 4.3f, 2.2f,
               0.29f, 0.16f, 0.08f);

    // Door panel
    bedroomBox(6.48f, 0.45f, 2.2f,
               0.12f, 3.95f, 1.85f,
               0.48f, 0.28f, 0.13f);

    // Door panels
    bedroomBox(6.40f, 1.3f, 2.2f,
               0.05f, 1.0f, 1.45f,
               0.35f, 0.20f, 0.09f);

    bedroomBox(6.40f, -0.5f, 2.2f,
               0.05f, 1.1f, 1.45f,
               0.35f, 0.20f, 0.09f);

    // Door handle
    bedroomSphere(6.32f, 0.4f, 1.55f,
                  0.12f, 0.12f, 0.12f,
                  0.85f, 0.68f, 0.28f);
}

// --------------------------------------------------
// RUG
// --------------------------------------------------

void drawBedroomRug()
{
    bedroomBox(2.0f, -1.72f, 2.5f,
               4.0f, 0.035f, 2.0f,
               0.55f, 0.24f, 0.16f);

    bedroomBox(2.0f, -1.69f, 2.5f,
               3.7f, 0.025f, 1.7f,
               0.73f, 0.48f, 0.31f);

    // Rug border pattern
    bedroomBox(2.0f, -1.67f, 1.72f,
               3.6f, 0.02f, 0.06f,
               0.38f, 0.19f, 0.12f);

    bedroomBox(2.0f, -1.67f, 3.28f,
               3.6f, 0.02f, 0.06f,
               0.38f, 0.19f, 0.12f);
}

// --------------------------------------------------
// SMALL CHAIR
// --------------------------------------------------

void drawBedroomChair()
{
    // Seat
    bedroomBox(-3.2f, -0.85f, 3.1f,
               1.4f, 0.22f, 1.3f,
               0.39f, 0.23f, 0.12f);

    // Backrest
    bedroomBox(-3.2f, -0.05f, 3.65f,
               1.4f, 1.5f, 0.18f,
               0.39f, 0.23f, 0.12f);

    // Legs
    bedroomBox(-3.75f, -1.35f, 2.6f,
               0.13f, 0.85f, 0.13f,
               0.27f, 0.15f, 0.07f);

    bedroomBox(-2.65f, -1.35f, 2.6f,
               0.13f, 0.85f, 0.13f,
               0.27f, 0.15f, 0.07f);

    bedroomBox(-3.75f, -1.35f, 3.6f,
               0.13f, 0.85f, 0.13f,
               0.27f, 0.15f, 0.07f);

    bedroomBox(-2.65f, -1.35f, 3.6f,
               0.13f, 0.85f, 0.13f,
               0.27f, 0.15f, 0.07f);
}

// --------------------------------------------------
// WALL DECORATION
// --------------------------------------------------

void drawBedroomDecor()
{
    // Picture frame on back wall
    bedroomBox(4.7f, 2.7f, -5.15f,
               1.3f, 1.2f, 0.12f,
               0.25f, 0.14f, 0.07f);

    bedroomBox(4.7f, 2.7f, -5.06f,
               1.08f, 0.98f, 0.04f,
               0.78f, 0.68f, 0.47f);

    // Simple landscape inside picture
    bedroomBox(4.7f, 2.45f, -5.02f,
               0.95f, 0.35f, 0.02f,
               0.27f, 0.43f, 0.25f);

    bedroomSphere(4.7f, 2.95f, -5.0f,
                  0.35f, 0.35f, 0.04f,
                  0.84f, 0.65f, 0.29f);
}

// --------------------------------------------------
// MAIN BEDROOM DRAW FUNCTION
// --------------------------------------------------

void drawBedroom()
{
    glPushMatrix();

    drawBedroomRoom();
    drawBedroomWindow();
    drawBedroomBed();
    drawBedsideTable();
    drawBedroomWardrobe();
    drawBedroomDoor();
    drawBedroomRug();
    drawBedroomChair();
    drawBedroomDecor();
    drawBedroomFarmer();

    glPopMatrix();
}
