
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

void drawCube(float x, float y, float z,
              float sx, float sy, float sz,
              float r, float g, float b);

void drawSphere(float x, float y, float z,
                float sx, float sy, float sz,
                float r, float g, float b);

void drawEllipsoid(float x, float y, float z,
                   float sx, float sy, float sz,
                   float r, float g, float b);

void drawSphereRot(float x, float y, float z,
                   float sx, float sy, float sz,
                   float angX, float angY, float angZ,
                   float r, float g, float b);

void drawCylinder(float x, float y, float z,
                  float rBase, float rTop, float height,
                  float angX, float angY, float angZ,
                  float r, float g, float b);

void drawCylinder(float x1, float y1, float z1,
                  float x2, float y2, float z2,
                  float radius,
                  float r, float g, float b);

void drawCone(float x, float y, float z,
              float radius, float height,
              float r, float g, float b);

void drawTorus(float x, float y, float z,
               float tubeRadius, float ringRadius,
               float angX, float angY, float angZ,
               float r, float g, float b);

void initCowLighting();

#endif
