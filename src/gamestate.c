#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "gamestate.h"
#include "camera.h"

void GameState_Init(GameState* gs)
{
  memset(gs, 0, sizeof *gs);

  gs->score = 0;
  gs->entities = (EntityStack){0};
  gs->movingEntity = (Entity) {
    .width = 100,
    .height = 100,
    .position = (Vector2) { 0.0f, 0.0f },
    .velocity = (Vector2) { 0.0f, 0.0f }
  };
  gs->anchorEntity = (Entity) {
    .width = 20,
    .height = 50,
    .position = (Vector2) { 0.0f, 0.0f }
  };
  gs->direction = (Vector2) {
    .x = 1,
    .y = 1
  };
  gs->angle = 0.0f;
  gs->angular_velocity = 1.5f;
  gs->entityFalling = 0;

  EntityStack_Init(&gs->entities);

  Camera2D camera = { 0 };
  Camera_Init(&camera);

  gs->camera = camera;

  GameState_SetGround(gs);
}

void GameState_Reset(GameState* gs)
{
  EntityStack_Clear(&gs->entities);

  gs->fallingEntity = (Entity){0};
  gs->entityFalling = 0;
  gs->score = 0;
  gs->anchorEntity.position.y = 0;
  
  GameState_SetGround(gs);
}

void GameState_IncrementScore(GameState* gs)
{
  gs->score++;
}

void GameState_SetGround(GameState* gs)
{
  Entity ground = (Entity) {
    .width = 100,
    .height = 100,
    .isGround = 1
  };

  ground.position = GetScreenToWorld2D((Vector2){
    .x = GetScreenWidth() / 2 - (ground.width / 2),
    .y = GetScreenHeight() - ground.height
  }, gs->camera);

  gs->groundEntity = ground;

  EntityStack_Push(&gs->entities, ground);
}
