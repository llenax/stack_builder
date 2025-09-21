#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "entity.h"

void run()
{
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  InitWindow(screenWidth, screenHeight, "stack builder");
  SetTargetFPS(60);
  ToggleFullscreen();

  Camera2D camera = { 0 };
  Camera_Init(&camera);

  GameState gameState;
  GameState_Init(&gameState, &camera);

  loop(&gameState, &camera);

  CloseWindow();
}

void draw(GameState* gs, Camera2D* camera)
{
  BeginDrawing();
  ClearBackground(LIGHTGRAY);
  BeginMode2D(*camera);

  DrawRectangleRec((Rectangle){
    gs->anchorEntity.position.x,
    gs->anchorEntity.position.y,
    gs->anchorEntity.width,
    gs->anchorEntity.height
  }, GREEN);

  DrawRectangleRec((Rectangle){
    gs->movingEntity.position.x,
    gs->movingEntity.position.y,
    gs->movingEntity.width,
    gs->movingEntity.height
  }, BLUE);

  DrawRectanglePro(
    (Rectangle) {
      Entity_AnchorCenter(gs).x,
      Entity_AnchorCenter(gs).y,
      gs->connectionEntity.rect.width,
      gs->connectionEntity.rect.height
    },
    gs->connectionEntity.origin,
    gs->connectionEntity.angle,
    RED
  );

  Entity_DrawEntities(gs);
  Entity_DrawFallingEntity(gs);

  EndMode2D();

  char buf[1024];
  sprintf(buf, "Score: %d", gs->score);
  DrawText(buf, 0, 0, 20, BLACK);

  EndDrawing();
}

void loop(GameState* gs, Camera2D* camera)
{
  while (!WindowShouldClose())
  {
    gs->anchorEntity.position.x = gs->groundEntity.position.x;
    Camera_SetTarget(camera, (Vector2) {
      .x = 0,
      .y = gs->anchorEntity.position.y
    });

    gs->connectionEntity = Entity_Connection(gs);

    Entity_UpdateMoving(gs, camera);
    Entity_UpdateFalling(gs);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !gs->entityFalling)
    {
      Entity_SetFalling(gs);
    }

    draw(gs, camera);
  }
}
