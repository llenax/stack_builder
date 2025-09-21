#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "raylib.h"
#include "entity.h"

typedef struct GameState {
  Camera2D camera;
  EntityStack entities;
  Entity movingEntity;
  Entity anchorEntity;
  Entity fallingEntity;
  Entity groundEntity;
  EntityConnection connectionEntity;
  Vector2 direction;
  bool entityFalling;
  int score;
  float angle;
  float angular_velocity;
} GameState;

void GameState_Init(GameState* gs);
void GameState_Reset(GameState* gs);
void GameState_IncrementScore(GameState* gs);
void GameState_SetGround(GameState* gs);

#endif
