#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "gamestate.h"
#include "camera.h"

void draw(GameState* gs, Camera2D* camera);
void loop(GameState* gs, Camera2D* camera);
void init();
void close();
void run();

#endif
