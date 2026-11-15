
#include <GL/freeglut.h>
#include <string>
#include "shop.h"

namespace
{
    void shopBox(float x, float y, float z,
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

    void shopCylinder(float x, float y, float z,
                      float radius, float height,
                      float r, float g, float b)
    {
        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(r, g, b);

        GLUquadric* quad = gluNewQuadric();
        gluCylinder(quad, radius, radius, height, 20, 4);
        gluDisk(quad, 0.0, radius, 20, 1);
        glTranslatef(0.0f, 0.0f, height);
        gluDisk(quad, 0.0, radius, 20, 1);
        gluDeleteQuadric(quad);

        glPopMatrix();
    }

    void shopText(float x, float y, float z,
                  const std::string& value,
                  float r, float g, float b)
    {
        glColor3f(r, g, b);
        glRasterPos3f(x, y, z);

        for (char character : value)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, character);
    }

    void drawShopGround()
    {
        shopBox(0.0f, -0.25f, 0.0f,
                30.0f, 0.3f, 24.0f,
                0.48f, 0.39f, 0.27f);

        // Dirt path leading to the entrance
        shopBox(0.0f, -0.075f, 8.0f,
                5.0f, 0.08f, 10.0f,
                0.58f, 0.46f, 0.32f);

        // Stones along the path
        for (int i = 0; i < 7; i++)
        {
            float x = (i % 2 == 0) ? -2.0f : 2.0f;
            float z = 4.0f + i * 1.25f;

            shopBox(x, 0.0f, z,
                    0.55f, 0.08f, 0.4f,
                    0.48f, 0.47f, 0.42f);
        }

        // Small grass patches
        for (int i = 0; i < 12; i++)
        {
            float x = -12.0f + (i % 6) * 4.5f;
            float z = -8.0f + (i / 6) * 17.0f;

            shopBox(x, 0.02f, z,
                    1.4f, 0.05f, 1.0f,
                    0.25f, 0.38f, 0.18f);
        }
    }

    void drawShopBuilding()
    {
        // Main shop floor
        shopBox(0.0f, 0.05f, 0.0f,
                12.0f, 0.25f, 9.0f,
                0.62f, 0.48f, 0.32f);

        // Rear wall
        shopBox(0.0f, 2.8f, -4.25f,
                12.0f, 5.5f, 0.35f,
                0.76f, 0.65f, 0.48f);

        // Left and right walls
        shopBox(-5.8f, 2.8f, 0.0f,
                0.4f, 5.5f, 8.5f,
                0.72f, 0.59f, 0.42f);

        shopBox(5.8f, 2.8f, 0.0f,
                0.4f, 5.5f, 8.5f,
                0.72f, 0.59f, 0.42f);

        // Front wall sections, leaving a wide entrance
        shopBox(-4.65f, 2.8f, 4.25f,
                2.3f, 5.5f, 0.35f,
                0.72f, 0.59f, 0.42f);

        shopBox(4.65f, 2.8f, 4.25f,
                2.3f, 5.5f, 0.35f,
                0.72f, 0.59f, 0.42f);

        // Front support posts
        shopBox(-3.5f, 2.8f, 4.0f,
                0.22f, 5.6f, 0.25f,
                0.35f, 0.22f, 0.13f);

        shopBox(3.5f, 2.8f, 4.0f,
                0.22f, 5.6f, 0.25f,
                0.35f, 0.22f, 0.13f);

        // Front roof beam
        shopBox(0.0f, 5.55f, 4.0f,
                12.0f, 0.35f, 0.5f,
                0.35f, 0.22f, 0.13f);

        // Roof
        shopBox(0.0f, 5.8f, 0.0f,
                13.0f, 0.3f, 10.0f,
                0.28f, 0.17f, 0.12f);

        // Roof front fascia
        shopBox(0.0f, 5.65f, 4.7f,
                13.0f, 0.5f, 0.25f,
                0.42f, 0.24f, 0.14f);

        // Roof support beams
        for (int i = -2; i <= 2; i++)
        {
            shopBox(i * 2.3f, 5.35f, 0.0f,
                    0.12f, 0.18f, 8.5f,
                    0.35f, 0.22f, 0.13f);
        }

        // Exterior window frames
        shopBox(-4.0f, 3.2f, 4.48f,
                1.4f, 1.3f, 0.12f,
                0.25f, 0.15f, 0.09f);

        shopBox(4.0f, 3.2f, 4.48f,
                1.4f, 1.3f, 0.12f,
                0.25f, 0.15f, 0.09f);

        // Window glass
        shopBox(-4.0f, 3.2f, 4.56f,
                1.15f, 1.05f, 0.04f,
                0.45f, 0.68f, 0.72f);

        shopBox(4.0f, 3.2f, 4.56f,
                1.15f, 1.05f, 0.04f,
                0.45f, 0.68f, 0.72f);

        // Window crossbars
        shopBox(-4.0f, 3.2f, 4.60f,
                0.07f, 1.1f, 0.04f,
                0.25f, 0.15f, 0.09f);

        shopBox(4.0f, 3.2f, 4.60f,
                0.07f, 1.1f, 0.04f,
                0.25f, 0.15f, 0.09f);

        // Shop signboard
        shopBox(0.0f, 5.0f, 4.55f,
                4.8f, 0.8f, 0.18f,
                0.28f, 0.18f, 0.10f);

        shopBox(0.0f, 5.0f, 4.67f,
                4.5f, 0.58f, 0.05f,
                0.84f, 0.72f, 0.46f);

        shopText(-1.45f, 4.94f, 4.72f,
                 "FRESH MILK SHOP",
                 0.22f, 0.13f, 0.07f);
    }

    void drawShopCounter()
    {
        // Main sales counter
        shopBox(0.0f, 1.05f, 1.6f,
                6.0f, 1.8f, 1.0f,
                0.42f, 0.25f, 0.13f);

        shopBox(0.0f, 2.0f, 1.6f,
                6.3f, 0.18f, 1.2f,
                0.25f, 0.15f, 0.09f);

        // Front counter panels
        for (int i = -2; i <= 2; i++)
        {
            shopBox(i * 1.15f, 1.05f, 2.12f,
                    0.9f, 1.35f, 0.05f,
                    0.58f, 0.38f, 0.22f);
        }

        // Payment terminal
        shopBox(2.1f, 2.18f, 1.55f,
                0.55f, 0.28f, 0.4f,
                0.12f, 0.14f, 0.15f);

        shopBox(2.1f, 2.35f, 1.55f,
                0.42f, 0.04f, 0.28f,
                0.20f, 0.55f, 0.38f);

        // Small cash box
        shopBox(-2.0f, 2.18f, 1.55f,
                0.7f, 0.3f, 0.5f,
                0.22f, 0.22f, 0.22f);

        // Small counter display
        shopBox(0.0f, 2.25f, 1.55f,
                1.1f, 0.25f, 0.45f,
                0.78f, 0.78f, 0.72f);
    }

    void drawMilkProducts()
    {
        // Milk bottles displayed on the counter
        for (int i = 0; i < 5; i++)
        {
            float x = -2.0f + i * 1.0f;

            shopCylinder(x, 2.15f, 1.45f,
                         0.16f, 0.55f,
                         0.88f, 0.91f, 0.85f);

            shopCylinder(x, 2.70f, 1.45f,
                         0.07f, 0.12f,
                         0.85f, 0.85f, 0.78f);

            shopBox(x, 2.42f, 1.62f,
                    0.19f, 0.15f, 0.025f,
                    0.25f, 0.55f, 0.38f);
        }

        // Small milk crates beneath the counter
        shopBox(-4.0f, 0.48f, 0.8f,
                1.0f, 0.8f, 0.8f,
                0.25f, 0.38f, 0.28f);

        shopBox(4.0f, 0.48f, 0.8f,
                1.0f, 0.8f, 0.8f,
                0.25f, 0.38f, 0.28f);
    }

    void drawShopShelves()
    {
        // Left-side shelving unit
        shopBox(-5.0f, 2.3f, -1.5f,
                0.18f, 4.4f, 5.0f,
                0.34f, 0.22f, 0.12f);

        shopBox(-4.1f, 2.3f, -1.5f,
                0.18f, 4.4f, 5.0f,
                0.34f, 0.22f, 0.12f);

        for (int i = 0; i < 4; i++)
        {
            float y = 0.65f + i * 1.1f;

            shopBox(-4.55f, y, -1.5f,
                    1.0f, 0.12f, 5.0f,
                    0.47f, 0.30f, 0.16f);
        }

        // Products on shelves
        for (int level = 0; level < 3; level++)
        {
            for (int item = 0; item < 4; item++)
            {
                float y = 0.85f + level * 1.1f;
                float z = -3.2f + item * 1.1f;

                shopBox(-4.55f, y, z,
                        0.55f, 0.55f, 0.45f,
                        0.72f - level * 0.08f,
                        0.42f + item * 0.05f,
                        0.20f + level * 0.08f);
            }
        }

        // Right-side shelves
        shopBox(4.1f, 2.3f, -1.5f,
                0.18f, 4.4f, 5.0f,
                0.34f, 0.22f, 0.12f);

        shopBox(5.0f, 2.3f, -1.5f,
                0.18f, 4.4f, 5.0f,
                0.34f, 0.22f, 0.12f);

        for (int i = 0; i < 4; i++)
        {
            float y = 0.65f + i * 1.1f;

            shopBox(4.55f, y, -1.5f,
                    1.0f, 0.12f, 5.0f,
                    0.47f, 0.30f, 0.16f);
        }

        // Small packages on right shelves
        for (int level = 0; level < 3; level++)
        {
            for (int item = 0; item < 4; item++)
            {
                float y = 0.85f + level * 1.1f;
                float z = -3.2f + item * 1.1f;

                shopBox(4.55f, y, z,
                        0.55f, 0.55f, 0.45f,
                        0.30f + item * 0.08f,
                        0.55f,
                        0.35f + level * 0.1f);
            }
        }
    }

    void drawDisplayFridge()
    {
        // Refrigerator body
        shopBox(0.0f, 1.8f, -3.25f,
                2.3f, 3.5f, 1.1f,
                0.72f, 0.75f, 0.76f);

        // Glass front
        shopBox(0.0f, 1.85f, -2.66f,
                2.0f, 3.0f, 0.05f,
                0.35f, 0.62f, 0.68f);

        // Door frame
        shopBox(-1.05f, 1.85f, -2.61f,
                0.08f, 3.1f, 0.08f,
                0.82f, 0.84f, 0.84f);

        shopBox(1.05f, 1.85f, -2.61f,
                0.08f, 3.1f, 0.08f,
                0.82f, 0.84f, 0.84f);

        // Interior shelves visible through the glass
        for (int i = 0; i < 3; i++)
        {
            shopBox(0.0f, 0.9f + i * 0.85f, -2.55f,
                    1.8f, 0.07f, 0.08f,
                    0.80f, 0.82f, 0.82f);
        }

        // Products inside the fridge
        for (int level = 0; level < 3; level++)
        {
            for (int item = 0; item < 4; item++)
            {
                float x = -0.7f + item * 0.45f;
                float y = 1.1f + level * 0.85f;

                shopCylinder(x, y, -2.48f,
                             0.10f, 0.35f,
                             0.90f, 0.92f, 0.86f);
            }
        }

        // Fridge base
        shopBox(0.0f, 0.1f, -3.25f,
                2.4f, 0.2f, 1.2f,
                0.35f, 0.37f, 0.38f);
    }

    void drawShopDetails()
    {
        // Wall clock
        shopCylinder(-2.6f, 4.3f, -4.0f,
                     0.38f, 0.08f,
                     0.88f, 0.84f, 0.72f);

        shopBox(-2.6f, 4.3f, -3.94f,
                0.04f, 0.3f, 0.04f,
                0.15f, 0.15f, 0.15f);

        // Price board above the counter
        shopBox(0.0f, 3.8f, -4.0f,
                2.6f, 0.85f, 0.12f,
                0.20f, 0.28f, 0.20f);

        shopText(-0.75f, 3.75f, -3.92f,
                 "MILK PRICES",
                 0.95f, 0.90f, 0.70f);

        // Wall light
        shopBox(2.7f, 4.6f, -4.0f,
                0.65f, 0.35f, 0.2f,
                0.95f, 0.78f, 0.40f);

        // Entrance step
        shopBox(0.0f, 0.0f, 4.8f,
                4.0f, 0.25f, 0.8f,
                0.48f, 0.43f, 0.36f);

        // Small bench outside
        shopBox(-7.0f, 0.55f, 2.0f,
                2.2f, 0.18f, 0.65f,
                0.35f, 0.22f, 0.12f);

        shopBox(-7.0f, 0.25f, 1.8f,
                0.15f, 0.5f, 0.15f,
                0.30f, 0.19f, 0.10f);

        shopBox(-7.0f, 0.25f, 2.2f,
                0.15f, 0.5f, 0.15f,
                0.30f, 0.19f, 0.10f);
    }
}

void drawVillageShop()
{
    drawShopGround();
    drawShopBuilding();
    drawShopShelves();
    drawDisplayFridge();
    drawShopCounter();
    drawMilkProducts();
    drawShopDetails();
}
