#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "raymath.h"

typedef struct GameState GameState;

typedef struct {
  int height;
  int width;
  int isGround;
  Vector2 position;
  Vector2 direction;
  Vector2 velocity;
  Vector2 anchor;
} Entity;

typedef struct {
  Vector2 vec;
  float height;
  float angle;
  Rectangle rect;
  Vector2 origin;
} EntityConnection;

void Entity_UpdateFalling(GameState* gs);
Entity* Entity_Ground(GameState* gs);
Vector2 Entity_GroundPosition(Entity* ground, int offset);
void Entity_MoveAnchor(GameState* gs, Entity* entity);
void Entity_AddNew(GameState* gs, Entity entity);
bool Entity_Overlaps(Entity* entityA, Entity* entityB);
void Entity_Fall(GameState* gs, Entity* entity);
EntityConnection Entity_Connection(GameState* gs);
void Entity_UpdateMoving(GameState* gs, Camera2D* camera);
void Entity_UpdateGround(GameState* gs);
Vector2 Entity_AnchorCenter(GameState* gs);
Vector2 Entity_MovingCenter(GameState* gs);
void Entity_DrawEntityRec(Entity* entity, Color color);
void Entity_DrawEntities(GameState* gs);
void Entity_DrawFallingEntity(GameState* gs);
void Entity_SetFalling(GameState* gs);
void Entity_Land(GameState* gs, Entity* box, Vector2 landingPos);

#endif
