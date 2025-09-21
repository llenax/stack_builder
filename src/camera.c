#include "camera.h"
#include "math.h"

void Camera_SetTarget(Camera2D* camera, Vector2 target)
{
  camera->target = LerpVector2(camera->target, target, 20.0f * GetFrameTime());
}

void Camera_Init(Camera2D* camera)
{
  camera->rotation = 0.0f;
  camera->zoom = 1.0f;
}
