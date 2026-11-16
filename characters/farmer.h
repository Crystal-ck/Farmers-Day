#pragma once

// Draws the farmer standing at (x, y, z), feet on y, facing +Z. scale = uniform scale.
//
// drawFarmer() is a drop-in replacement for the old function (same arguments, same meaning):
//   hipAngle - bends the upper body forward (+) / back (-) around the hips, degrees
//   legAngle - swings BOTH legs around the hips (negative = forward); the knees now bend with it,
//              so -90 gives a proper seated pose with the shins hanging down
//   armAngle - swings BOTH arms around the shoulders; the elbows bend with it
// On top of that he breathes, blinks, sways his head and shifts his weight.
void drawFarmer(float x, float y, float z, float scale, float hipAngle, float legAngle, float armAngle);

// Same figure with independent left/right limbs (for walking: opposite angles) and your own clock.
//   left/right are from the farmer's own point of view of the screen: "L" is the limb on the -X side.
void drawFarmerPosed(float x, float y, float z, float scale, float hipAngle,
                     float legAngleL, float legAngleR, float armAngleL, float armAngleR, float time);