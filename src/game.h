#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "gamestate.h"
#include "camera.h"

void update(GameState* gs);
void render(GameState* gs);
void init();
void run();

#endif
