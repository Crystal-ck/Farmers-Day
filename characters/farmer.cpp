#include "farmer.h"
#include "primitives.h"

#include <GL/freeglut.h>
#include <algorithm>
#include <cmath>

// Same conventions as the original code:
//   drawCube  (cx, cy, cz,  width, height, depth,  r, g, b)   - full sizes
//   drawSphere(cx, cy, cz,  rx, ry, rz,            r, g, b)   - radii
// Both draw around the given centre and leave the matrix stack as they found it.

namespace {

constexpr float kPi = 3.14159265f;

struct RGB { float r, g, b; };
inline RGB shade(RGB c, float f) { return {std::min(1.0f, c.r * f), std::min(1.0f, c.g * f), std::min(1.0f, c.b * f)}; }
inline void cube(float x, float y, float z, float w, float h, float d, RGB c) { drawCube(x, y, z, w, h, d, c.r, c.g, c.b); }
inline void ball(float x, float y, float z, float rx, float ry, float rz, RGB c) { drawSphere(x, y, z, rx, ry, rz, c.r, c.g, c.b); }

// Sphere rotated about its own centre (degrees, applied z then y then x like the original drawSphereRot).
void ballRot(float x, float y, float z, float rx, float ry, float rz, float ax, float ay, float az, RGB c) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(ax, 1, 0, 0); glRotatef(ay, 0, 1, 0); glRotatef(az, 0, 0, 1);
    ball(0, 0, 0, rx, ry, rz, c);
    glPopMatrix();
}
void cubeRot(float x, float y, float z, float w, float h, float d, float ax, float ay, float az, RGB c) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(ax, 1, 0, 0); glRotatef(ay, 0, 1, 0); glRotatef(az, 0, 0, 1);
    cube(0, 0, 0, w, h, d, c);
    glPopMatrix();
}
// A box stretched between two points (straps, the straw, laces).
void bar(float x1, float y1, float z1, float x2, float y2, float z2, float w, float d, RGB c) {
    float dx = x2 - x1, dy = y2 - y1, dz = z2 - z1, len = std::sqrt(dx * dx + dy * dy + dz * dz);
    if (len < 1e-5f) return;
    glPushMatrix();
    glTranslatef((x1 + x2) * 0.5f, (y1 + y2) * 0.5f, (z1 + z2) * 0.5f);
    float ang = std::acos(std::max(-1.0f, std::min(1.0f, dy / len))) * 180.0f / kPi;
    if (std::fabs(dx) + std::fabs(dz) > 1e-6f) glRotatef(ang, dz, 0.0f, -dx);
    else if (dy < 0) glRotatef(180.0f, 1, 0, 0);
    cube(0, 0, 0, w, len, d, c);
    glPopMatrix();
}
float clampf(float v, float a, float b) { return std::max(a, std::min(b, v)); }

// Palette (original colours kept, plus shades)
const RGB kSkin     {0.55f, 0.32f, 0.18f};
const RGB kSkinDark {0.44f, 0.24f, 0.13f};
const RGB kSkinLight{0.66f, 0.38f, 0.23f};
const RGB kRosy     {0.70f, 0.34f, 0.22f};
const RGB kDenim    {0.12f, 0.20f, 0.55f};
const RGB kDenimLt  {0.18f, 0.29f, 0.68f};
const RGB kDenimDk  {0.08f, 0.16f, 0.43f};
const RGB kGreen    {0.12f, 0.42f, 0.16f};
const RGB kGreenLt  {0.19f, 0.54f, 0.24f};
const RGB kBrass    {0.95f, 0.72f, 0.20f};
const RGB kBoot     {0.20f, 0.10f, 0.04f};
const RGB kSole     {0.08f, 0.045f, 0.02f};
const RGB kHair     {0.12f, 0.07f, 0.03f};
const RGB kStraw    {0.85f, 0.65f, 0.22f};
const RGB kBand     {0.40f, 0.22f, 0.07f};
const RGB kRed      {0.74f, 0.12f, 0.10f};
const RGB kThread   {0.80f, 0.68f, 0.35f};
const RGB kMud      {0.30f, 0.20f, 0.10f};

// Front surface of the head ellipsoid (centre (0,1.78,0), radii .24/.27/.22) so features sit on it.
float faceZ(float x, float y) {
    float u = (y - 1.78f) / 0.27f, v = x / 0.24f, q = 1.0f - u * u - v * v;
    return q > 0 ? 0.22f * std::sqrt(q) : 0.0f;
}

/* ---------------- legs ---------------- */

// side: -1 = the leg at -X, +1 = the leg at +X. The origin is the hip joint.
void drawLeg(float side, float angle) {
    float knee = clampf(angle < 0 ? -angle : angle * 0.6f, 0.0f, 125.0f);   // shin folds back as the thigh swings
    glPushMatrix();
    glTranslatef(side * 0.13f, 0.75f, 0.0f);
    glRotatef(angle, 1, 0, 0);

    ball(0, -0.03f, 0, 0.115f, 0.12f, 0.115f, kDenim);                         // hip
    cube(0, -0.17f, 0, 0.21f, 0.31f, 0.21f, kDenim);                           // thigh
    cube(side * 0.106f, -0.17f, 0.0f, 0.006f, 0.30f, 0.17f, kDenimDk);         // outer seam
    cube(0, -0.17f, 0.1055f, 0.012f, 0.28f, 0.004f, kDenimDk);                 // front crease

    glTranslatef(0.0f, -0.34f, 0.0f);                                          // knee
    glRotatef(knee, 1, 0, 0);
    ball(0, 0, 0, 0.10f, 0.09f, 0.10f, kDenim);
    cube(0, -0.14f, 0, 0.185f, 0.28f, 0.185f, kDenim);                         // shin
    if (side < 0) {                                                            // a patch on the left knee
        cube(0, 0.0f, 0.104f, 0.095f, 0.095f, 0.008f, kRed);
        for (float s : {-1.0f, 1.0f}) cube(s * 0.047f, 0.0f, 0.109f, 0.004f, 0.09f, 0.003f, kThread);
        cube(0, 0.047f, 0.109f, 0.09f, 0.004f, 0.003f, kThread);
        cube(0, -0.047f, 0.109f, 0.09f, 0.004f, 0.003f, kThread);
    }
    cube(0, -0.255f, 0, 0.215f, 0.055f, 0.215f, kDenimLt);                     // rolled cuff
    cube(0, -0.2835f, 0, 0.217f, 0.006f, 0.217f, kDenimDk);

    // Work boot (positions are the original boot coordinates, relative to the knee at y = 0.41).
    cube(0, -0.31f, 0.08f, 0.235f, 0.16f, 0.35f, kBoot);
    cube(0, -0.385f, 0.10f, 0.245f, 0.035f, 0.37f, kSole);
    cube(0, -0.37f, -0.075f, 0.20f, 0.05f, 0.09f, shade(kSole, 1.3f));         // raised heel
    ball(0, -0.335f, 0.225f, 0.115f, 0.065f, 0.10f, shade(kBoot, 1.15f));      // toe cap
    cube(0, -0.29f, 0.258f, 0.12f, 0.025f, 0.012f, {0.35f, 0.20f, 0.08f});     // highlight (original)
    cube(0, -0.225f, 0.0f, 0.24f, 0.02f, 0.25f, shade(kBoot, 0.7f));           // collar of the boot
    for (int i = 0; i < 3; i++) cube(0, -0.25f + i * 0.0f, 0.1f + i * 0.04f, 0.1f, 0.01f, 0.012f, {0.85f, 0.78f, 0.6f}); // laces
    ball(0.06f, -0.345f, 0.27f, 0.02f, 0.014f, 0.014f, kMud);                  // mud
    ball(-0.07f, -0.36f, 0.2f, 0.016f, 0.012f, 0.012f, kMud);
    ball(0.02f, -0.37f, 0.32f, 0.014f, 0.01f, 0.01f, kMud);
    glPopMatrix();
}

/* ---------------- arms ---------------- */

void drawHand(float side, RGB skin) {
    ball(0, -0.04f, 0, 0.075f, 0.085f, 0.045f, skin);                           // palm
    for (int i = 0; i < 4; i++) {
        float len = (i == 1 || i == 2) ? 0.045f : 0.038f;
        ball((i - 1.5f) * 0.03f, -0.105f - len * 0.4f, 0.012f, 0.016f, len, 0.019f, shade(skin, 0.92f)); // fingers, slightly curled
    }
    ball(-side * 0.072f, -0.05f, 0.022f, 0.022f, 0.042f, 0.022f, skin);         // thumb
}

// side: -1 = arm at -X, +1 = arm at +X. The origin is the shoulder joint.
void drawArm(float side, float angle, float time) {
    float elbow = -(14.0f + 0.4f * std::fabs(angle));                           // elbows flex forward
    glPushMatrix();
    glTranslatef(side * 0.38f, 1.30f, 0.0f);
    glRotatef(angle, 1, 0, 0);
    glRotatef(side * 8.0f, 0, 0, 1);                                           // slight outward lean

    ball(0, 0, 0, 0.125f, 0.125f, 0.125f, kGreen);                             // shoulder
    ball(side * 0.01f, -0.11f, 0, 0.115f, 0.165f, 0.115f, kGreen);              // upper arm in a green sleeve

    glTranslatef(0.0f, -0.24f, 0.0f);                                          // elbow
    glRotatef(elbow, 1, 0, 0);
    ball(0, -0.01f, 0, 0.115f, 0.042f, 0.115f, kGreenLt);                       // rolled-up sleeve
    ball(0, -0.10f, 0, 0.095f, 0.14f, 0.095f, kSkin);                           // forearm
    ball(side * 0.03f, -0.1f, 0.06f, 0.03f, 0.1f, 0.03f, kSkinLight);           // forearm muscle highlight
    if (side < 0) ball(0, -0.185f, 0, 0.085f, 0.018f, 0.085f, kBand);           // leather wrist band
    glTranslatef(0.0f, -0.21f, 0.0f);                                          // wrist
    drawHand(side, kSkin);
    (void)time;
    glPopMatrix();
}

/* ---------------- head ---------------- */

void drawEye(float x, float open) {
    float y = 1.83f, z = faceZ(x, y);
    ball(x, y, z, 0.05f, 0.055f, 0.025f, {1, 1, 1});                            // white (original size)
    ball(x, y - 0.003f, z + 0.021f, 0.031f, 0.037f, 0.017f, {0.35f, 0.20f, 0.08f}); // brown iris
    ball(x, y - 0.003f, z + 0.03f, 0.018f, 0.022f, 0.012f, {0.02f, 0.02f, 0.02f});  // pupil (original)
    ball(x + (x < 0 ? -0.008f : -0.008f), y + 0.015f, z + 0.037f, 0.008f, 0.009f, 0.005f, {1, 1, 1}); // glint
    if (open < 0.97f) ball(x, y, z + 0.012f, 0.054f, 0.059f * (1.0f - open), 0.03f, kSkin); // eyelid
    ball(x, y + 0.048f, z - 0.002f, 0.056f, 0.012f, 0.026f, kSkinDark);        // upper lid fold
}

void drawStubbleAndMoustache() {
    for (int i = 0; i < 19; i++) {                                              // stubble along the jaw
        float u = (i - 9) / 9.0f;
        float x = u * 0.17f, y = 1.60f + 0.075f * std::pow(std::fabs(u), 1.3f);
        float q = 1.0f - std::pow((y - 1.78f) / 0.27f, 2.0f) - std::pow(x / 0.24f, 2.0f);
        if (q <= 0) continue;
        ball(x, y, 0.22f * std::sqrt(q) - 0.002f, 0.015f, 0.013f, 0.008f, {0.30f, 0.20f, 0.13f});
    }
    for (int i = 0; i < 7; i++) {                                               // chin and cheek patches
        float x = (i - 3) * 0.045f, y = 1.585f + 0.01f * std::fabs(i - 3.0f);
        float q = 1.0f - std::pow((y - 1.78f) / 0.27f, 2.0f) - std::pow(x / 0.24f, 2.0f);
        if (q > 0) ball(x, y, 0.22f * std::sqrt(q) - 0.002f, 0.02f, 0.014f, 0.008f, {0.30f, 0.20f, 0.13f});
    }
    float mz = faceZ(0, 1.70f);                                                 // big friendly moustache
    ball(0, 1.703f, mz + 0.008f, 0.07f, 0.024f, 0.03f, kHair);
    for (float s : {-1.0f, 1.0f}) {
        ball(s * 0.075f, 1.698f, faceZ(s * 0.075f, 1.698f) + 0.008f, 0.06f, 0.022f, 0.026f, kHair);
        ball(s * 0.135f, 1.705f, faceZ(s * 0.135f, 1.705f) + 0.006f, 0.03f, 0.02f, 0.02f, kHair);
    }
}

void drawHat() {
    glPushMatrix();
    glTranslatef(0.0f, 2.02f, 0.0f);
    glRotatef(4.0f, 1, 0, 0);                                                   // jaunty tilt
    glRotatef(-4.0f, 0, 0, 1);
    ball(0, -0.012f, 0, 0.35f, 0.02f, 0.29f, shade(kStraw, 0.6f));              // underside
    ball(0, 0.0f, 0, 0.36f, 0.05f, 0.30f, kStraw);                              // wide brim (original)
    ball(0, 0.08f, 0, 0.21f, 0.12f, 0.20f, kStraw);                             // crown (original)
    ball(0, 0.055f, 0, 0.215f, 0.025f, 0.205f, kBand);                          // band (original)
    for (int i = 0; i < 3; i++) ball(0, 0.105f + i * 0.03f, 0, 0.205f - i * 0.02f, 0.005f, 0.195f - i * 0.02f, shade(kStraw, 0.78f)); // weave
    ball(-0.12f, 0.065f, 0.17f, 0.025f, 0.025f, 0.015f, {0.25f, 0.45f, 0.12f}); // flower (original)
    ball(-0.12f, 0.065f, 0.185f, 0.01f, 0.01f, 0.006f, {0.98f, 0.9f, 0.4f});
    for (int i = 0; i < 9; i++) {                                               // frayed straws round the brim
        float a = i * 2 * kPi / 9.0f + 0.3f;
        bar(std::cos(a) * 0.34f, -0.005f, std::sin(a) * 0.28f, std::cos(a) * 0.385f, -0.02f, std::sin(a) * 0.32f, 0.006f, 0.006f, shade(kStraw, 0.9f));
    }
    glPopMatrix();
}

void drawHead(float t) {
    float yaw = 6.0f * std::sin(t * 0.5f), pitch = 2.0f * std::sin(t * 0.8f);
    float ph = std::fmod(t, 4.6f);
    float open = ph > 4.4f ? 1.0f - std::sin((ph - 4.4f) / 0.2f * kPi) : 1.0f;

    glPushMatrix();
    glTranslatef(0.0f, 1.56f, 0.0f);
    glRotatef(yaw, 0, 1, 0);
    glRotatef(pitch, 1, 0, 0);
    glTranslatef(0.0f, -1.56f, 0.0f);

    ball(0, 1.78f, 0, 0.24f, 0.27f, 0.22f, kSkin);                              // head
    ball(0, 1.64f, 0.02f, 0.17f, 0.12f, 0.16f, kSkin);                          // strong jaw
    ball(0, 1.585f, 0.1f, 0.075f, 0.05f, 0.07f, kSkin);                         // chin
    for (float s : {-1.0f, 1.0f}) {
        ball(s * 0.24f, 1.78f, 0, 0.06f, 0.08f, 0.06f, kSkin);                  // ears (original)
        ball(s * 0.25f, 1.78f, 0.015f, 0.03f, 0.05f, 0.03f, kSkinDark);
        ball(s * 0.15f, 1.74f, faceZ(s * 0.15f, 1.74f) + 0.004f, 0.045f, 0.032f, 0.02f, kRosy); // sun-warmed cheeks
        ball(s * 0.07f, 1.985f, 0.0f, 0.02f, 0.02f, 0.02f, kSkin);
    }
    drawEye(-0.09f, open);
    drawEye(0.09f, open);
    for (float s : {-1.0f, 1.0f})                                               // thick brows
        ballRot(s * 0.09f, 1.915f, faceZ(s * 0.09f, 1.915f) + 0.002f, 0.06f, 0.014f, 0.016f, 0, 0, s * 8.0f, kHair);

    ball(0, 1.78f, faceZ(0, 1.78f) + 0.01f, 0.026f, 0.06f, 0.026f, kSkin);       // nose bridge
    ball(0, 1.75f, 0.22f, 0.052f, 0.045f, 0.03f, kRosy);                        // red, round nose (original spot)
    for (float s : {-1.0f, 1.0f}) ball(s * 0.02f, 1.738f, 0.245f, 0.012f, 0.008f, 0.006f, kSkinDark);

    drawStubbleAndMoustache();
    // Smile with a few teeth, and a stalk of straw in the corner of the mouth.
    ball(0, 1.665f, faceZ(0, 1.665f) + 0.003f, 0.042f, 0.014f, 0.01f, {0.2f, 0.05f, 0.04f});
    ball(0, 1.668f, faceZ(0, 1.668f) + 0.007f, 0.034f, 0.008f, 0.008f, {0.95f, 0.93f, 0.85f});
    for (int i = -3; i <= 3; i++) {
        float x = i * 0.022f, u = x / 0.07f, y = 1.678f - 0.016f * (1.0f - u * u);
        ball(x, y, faceZ(x, y) + 0.004f, 0.013f, 0.009f, 0.009f, {0.5f, 0.2f, 0.16f});
    }
    bar(0.045f, 1.668f, 0.215f, 0.17f, 1.70f, 0.33f, 0.012f, 0.012f, {0.9f, 0.78f, 0.35f});
    bar(0.17f, 1.70f, 0.33f, 0.195f, 1.71f, 0.35f, 0.02f, 0.006f, {0.8f, 0.65f, 0.25f});

    // Hair under the hat, with sideburns.
    ball(0, 1.98f, 0, 0.23f, 0.09f, 0.21f, kHair);                              // (original)
    ball(0, 1.86f, -0.1f, 0.22f, 0.2f, 0.17f, kHair);
    for (float s : {-1.0f, 1.0f}) {
        ball(s * 0.215f, 1.84f, 0.02f, 0.045f, 0.1f, 0.1f, kHair);
        ball(s * 0.2f, 1.72f, 0.04f, 0.018f, 0.06f, 0.03f, kHair);
    }
    drawHat();
    glPopMatrix();
}

/* ---------------- torso and overalls ---------------- */

void drawBandana() {
    ball(0, 1.49f, 0.0f, 0.17f, 0.045f, 0.15f, kRed);                          // knotted round the neck
    cubeRot(0, 1.405f, 0.205f, 0.13f, 0.13f, 0.02f, 0, 0, 45.0f, kRed);          // the triangle hanging on his chest
    for (int i = 0; i < 5; i++) {                                              // white dots
        float dx = ((i % 3) - 1) * 0.035f, dy = 1.42f - (i / 3) * 0.04f;
        ball(dx, dy, 0.218f, 0.008f, 0.008f, 0.004f, {0.96f, 0.94f, 0.9f});
    }
    ball(0, 1.49f, -0.15f, 0.04f, 0.035f, 0.035f, kRed);                        // knot at the back
}

void drawOveralls() {
    // Bib with a stitched pocket, patch and brass buttons.
    cube(0, 1.06f, 0.205f, 0.38f, 0.44f, 0.035f, kDenim);                        // bib (the original panel, taller)
    cube(0, 0.98f, 0.20f, 0.38f, 0.28f, 0.04f, kDenim);
    cube(0, 1.04f, 0.228f, 0.16f, 0.12f, 0.018f, kDenimDk);                     // chest pocket (original)
    for (float s : {-1.0f, 1.0f}) cube(s * 0.082f, 1.04f, 0.2375f, 0.004f, 0.12f, 0.003f, kThread);
    cube(0, 1.10f, 0.2375f, 0.16f, 0.004f, 0.003f, kThread);
    cube(0, 0.98f, 0.2375f, 0.16f, 0.004f, 0.003f, kThread);
    ball(0, 1.095f, 0.25f, 0.018f, 0.018f, 0.012f, kBrass);                     // pocket button (original)
    cube(-0.11f, 0.90f, 0.226f, 0.09f, 0.09f, 0.008f, kGreenLt);                // patch
    for (float s : {-1.0f, 1.0f}) cube(-0.11f + s * 0.045f, 0.90f, 0.23f, 0.004f, 0.085f, 0.003f, kThread);
    for (float s : {-1.0f, 1.0f}) cube(s * 0.13f, 0.98f, 0.225f, 0.012f, 0.20f, 0.008f, {0.35f, 0.48f, 0.75f}); // seams (original)
    cube(0, 0.84f, 0.2f, 0.4f, 0.014f, 0.045f, kDenimDk);                       // waist seam
    // Straps over the shoulders, and the back panel with a pocket and a red rag.
    for (float s : {-1.0f, 1.0f}) {
        bar(s * 0.15f, 1.27f, 0.205f, s * 0.17f, 1.52f, 0.12f, 0.07f, 0.035f, kDenim);
        bar(s * 0.17f, 1.52f, 0.12f, s * 0.16f, 1.52f, -0.1f, 0.07f, 0.035f, kDenim);
        bar(s * 0.16f, 1.52f, -0.1f, s * 0.13f, 1.28f, -0.19f, 0.07f, 0.035f, kDenim);
        ball(s * 0.15f, 1.29f, 0.225f, 0.036f, 0.036f, 0.02f, kBrass);          // buckles (original spots)
        ball(s * 0.15f, 1.27f, 0.235f, 0.012f, 0.012f, 0.008f, shade(kBrass, 0.7f));
        ball(s * 0.19f, 0.87f, 0.17f, 0.018f, 0.018f, 0.012f, kBrass);          // side buttons
    }
    cube(0, 1.0f, -0.2f, 0.36f, 0.34f, 0.03f, kDenim);                          // back panel
    cube(0.1f, 0.88f, -0.222f, 0.14f, 0.14f, 0.014f, kDenimDk);                 // back pocket
    cubeRot(0.11f, 0.97f, -0.23f, 0.06f, 0.1f, 0.01f, 0, 0, -12.0f, kRed);      // rag in the back pocket
}

void drawUpperBody(float armL, float armR, float breathe, float time) {
    glPushMatrix();
    glTranslatef(0.0f, 1.17f, 0.0f);
    glScalef(1.0f + 0.01f * breathe, 1.0f + 0.016f * breathe, 1.0f + 0.016f * breathe);
    ball(0, 0, 0, 0.34f, 0.40f, 0.22f, kGreen);                                 // shirt (original)
    glPopMatrix();
    ball(0, 1.42f, 0, 0.33f, 0.10f, 0.2f, kGreen);                              // shoulder line
    ball(0, 0.78f, 0, 0.27f, 0.14f, 0.19f, kDenim);                             // hips close the gap to the legs

    drawOveralls();
    drawBandana();
    ballRot(-0.09f, 1.50f, 0.14f, 0.09f, 0.045f, 0.025f, 0, 0, -25.0f, kGreenLt); // collar (original)
    ballRot(0.09f, 1.50f, 0.14f, 0.09f, 0.045f, 0.025f, 0, 0, 25.0f, kGreenLt);

    drawArm(-1.0f, armL, time);
    drawArm(1.0f, armR, time);
    ball(0, 1.53f, 0, 0.12f, 0.13f, 0.12f, kSkin);                              // neck (original)
    drawHead(time);
}

} // namespace

void drawFarmerPosed(float x, float y, float z, float scale, float hipAngle,
                     float legAngleL, float legAngleR, float armAngleL, float armAngleR, float time) {
    float breathe = 0.5f + 0.5f * std::sin(time * 1.7f);
    float sway = std::sin(time * 0.9f) * 1.2f;                                  // weight shift

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale);

    // lower body: each leg swings about the hip
    drawLeg(-1.0f, legAngleL);
    drawLeg(1.0f, legAngleR);

    // upper body bends at the hips
    glPushMatrix();
    glTranslatef(0.0f, 0.75f, 0.0f);
    glRotatef(hipAngle, 1, 0, 0);
    glRotatef(sway, 0, 0, 1);
    glTranslatef(0.0f, -0.75f, 0.0f);
    drawUpperBody(armAngleL + 1.5f * std::sin(time * 1.2f), armAngleR + 1.5f * std::sin(time * 1.2f + 1.7f), breathe, time);
    glPopMatrix();

    glPopMatrix();
}

void drawFarmer(float x, float y, float z, float scale, float hipAngle, float legAngle, float armAngle) {
    float t = glutGet(GLUT_ELAPSED_TIME) * 0.001f;
    drawFarmerPosed(x, y, z, scale, hipAngle, legAngle, legAngle, armAngle, armAngle, t);
}