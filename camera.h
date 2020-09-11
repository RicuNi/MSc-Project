#pragma once

#include <GL\glut.h>

#include <cmath>
#include <cstdio>


void lockCameraDir(void);
void CameraXZ(float Velo, float dir);
void CameraY(float Velo, float dir);
void CameraControllor(float moveVelo, float mouseVelo, unsigned char key, int mX, int mY);
void updateCamera(void);

