#include "gamestate.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void GameState_Init(GameState* gs, Camera2D* camera)
{
  memset(gs, 0, sizeof(*gs));

  gs->score = 0;
  gs->entities = nullptr;
  gs->entityCount = 0;
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

  GameState_SetGround(gs, camera);
}

void GameState_Reset(GameState* gs)
{
  free(gs->entities);
  gs->entities = NULL;
  gs->entityCount = 0;
  gs->fallingEntity = (Entity){0};
  gs->entityFalling = 0;
  gs->score = 0;
  gs->anchorEntity.position.y = 0;
}

void GameState_IncrementScore(GameState* gs)
{
  gs->score++;
}

void GameState_SetGround(GameState* gs, Camera2D* camera)
{
  Entity ground = (Entity) {
    .width = 100,
    .height = 100,
    .isGround = 1
  };

  ground.position = GetScreenToWorld2D((Vector2){
    .x = GetScreenWidth() / 2 - (ground.width / 2),
    .y = GetScreenHeight() - ground.height
  }, *camera);

  gs->groundEntity = ground;

  Entity_AddNew(gs, ground);
}
