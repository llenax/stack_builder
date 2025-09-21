#include <stdlib.h>
#include "entity.h"
#include "gamestate.h"

void Entity_UpdateFalling(GameState* gs)
{
  if (!gs->entityFalling) return;

  Entity* falling = &gs->fallingEntity;
  falling->velocity.y = Lerp(falling->velocity.y, 200, GetFrameTime() * 14.0f);

  Entity_Fall(gs, falling);
}

Vector2 Entity_GroundPosition(Entity* ground, int offset)
{
  return (Vector2) {
    .x = 0,
    .y = ground->position.y - offset
  };
}


void Entity_AddNew(GameState* gs, Entity entity)
{
  gs->entities = realloc(
    gs->entities,
    (gs->entityCount + 1) * sizeof(Entity)
  );
  gs->entities[gs->entityCount] = entity;
  gs->entityCount++;
}

void Entity_MoveAnchor(GameState* gs, Entity* entity)
{
  gs->anchorEntity.position.y -= entity->height;
}

bool Entity_Overlaps(Entity* entityA, Entity* entityB)
{
  return (entityB->position.x + entityB->width > entityA->position.x &&
  entityB->position.x < entityA->position.x + entityA->width);
}

void Entity_Land(GameState* gs, Entity* box, Vector2 landingPos)
{
  box->position.y = landingPos.y;
  box->isGround = 1;
  gs->entityFalling = 0;

  if (!Entity_Overlaps(&gs->groundEntity, box)) {
    GameState_Reset(gs);
    return;
  }

  gs->groundEntity = *box;

  Entity_AddNew(gs, *box);
  Entity_MoveAnchor(gs, box);
  GameState_IncrementScore(gs);
}

void Entity_Fall(GameState* gs, Entity* box)
{
  Vector2 pos = Entity_GroundPosition(&gs->groundEntity, box->height);
  float next = box->position.y + box->velocity.y * GetFrameTime();

  if (next >= pos.y) {
    Entity_Land(gs, box, pos);
    return;
  }

  box->position.y = next;
}

Vector2 Entity_AnchorCenter(GameState* gs)
{
  return (Vector2) {
    .x = gs->anchorEntity.position.x + gs->anchorEntity.width / 2.0f,
    .y = gs->anchorEntity.position.y + gs->anchorEntity.height / 2.0f
  };
}

Vector2 Entity_MovingCenter(GameState* gs)
{
  return (Vector2) {
    .x = gs->movingEntity.position.x + gs->movingEntity.width / 2.0f,
    .y = gs->movingEntity.position.y + gs->movingEntity.height / 2.0f
  };
}

EntityConnection Entity_Connection(GameState* gs)
{

  Vector2 movingCenter = Entity_MovingCenter(gs);
  Vector2 anchorCenter = Entity_AnchorCenter(gs);

  Vector2 cv = Vector2Subtract(anchorCenter, movingCenter);
  float angle = atan2f(cv.y, cv.x) * (180.0f / PI) + 90.0f;
  float height = Vector2Length(cv);

  return (EntityConnection) {
    .vec = cv,
    .height = height,
    .angle = angle,
    .rect = (Rectangle) { 0, 0, 10.0f, height },
    .origin = (Vector2) { 5.0f, 0.0f }
  };
}

void Entity_UpdateMoving(GameState* gs, Camera2D* camera)
{
  const float radius_x = 140.0f;
  const float radius_y = 90.0f;

  Vector2 center = {
    gs->anchorEntity.position.x,
    gs->anchorEntity.position.y + radius_y
  };

  float angle = (PI / 2.0f) + (PI / 2.0f) * sinf(GetTime() * 1.2f);

  Vector2 movingPos = (Vector2) {
    .x = center.x + cos(angle) * radius_x,
    .y = center.y + sin(angle) * radius_y
  };

  gs->movingEntity.position.x = movingPos.x;
  gs->movingEntity.position.y = movingPos.y;
}

void Entity_DrawEntityRec(Entity* entity, Color color)
{
  DrawRectangleRec((Rectangle) {
    entity->position.x,
    entity->position.y,
    entity->width,
    entity->height
  }, color);
}

void Entity_DrawEntities(GameState* gs)
{
  for(size_t i = 0; i < gs->entityCount; i++)
  {
    Entity entity = gs->entities[i];
    if(entity.isGround){
      Entity_DrawEntityRec(&entity, RED);
    } else {
      Entity_DrawEntityRec(&entity, GREEN);
    }
  }
}

void Entity_DrawFallingEntity(GameState* gs)
{
  if(gs->entityFalling)
  {
    Entity entity = gs->fallingEntity;
    Entity_DrawEntityRec(&entity, GRAY);
  }
}

void Entity_SetFalling(GameState* gs)
{
  gs->entityFalling = 1;
  gs->fallingEntity = (Entity){
    .width = gs->movingEntity.width,
    .height = gs->movingEntity.height,
    .velocity = {0, 0},
    .position = {
      gs->movingEntity.position.x,
      gs->movingEntity.position.y
    },
    .isGround = 0
  };
}
