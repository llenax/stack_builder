#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

void Camera_Init(Camera2D* camera);
void Camera_SetTarget(Camera2D* camera, Vector2 target);

#endif
