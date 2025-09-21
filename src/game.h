#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "gamestate.h"
#include "camera.h"

void draw(GameState* gs);
void loop(GameState* gs);
void init();
void close();
void run();

#endif
