#ifndef STATE_H
#define STATE_H

#include "banner.h"
#include "game.h"
#include "globals.h"
#include "intro.h"
#include "utils.h"

#define GAME_STATE_BANNER  0
#define GAME_STATE_INTRO   1
#define GAME_STATE_START   2
#define GAME_STATE_PLAYING 3
#define GAME_STATE_DEAD    4

uint8_t gameState = GAME_STATE_BANNER;

void drawBanner() {
  // TODO drawbitmap
}

void stateBanner() {
  if (arduboy.pressed(A_BUTTON | B_BUTTON)) {
    initIntro();
    gameState = GAME_STATE_INTRO;
  }

  drawBanner();
}

void stateIntro() {
  if (arduboy.pressed(A_BUTTON | B_BUTTON) || introFinished) {
    gameState = GAME_STATE_START;
  }

  drawIntro();
}

void stateStart() {
  arduboy.initRandomSeed();
  initEnemies();
  // TODO
  // initScore();
  // initPlayer();
  gameState = GAME_STATE_PLAYING;
}

void statePlaying() {
  handleInput();
  drawStarField();
  calculatePlayerCollision();
  drawShootyShootyBoom();
  drawBats();
  drawTank();
  drawScoreAndSevenYearsAgo();
  advanceEnemies();
  sweepAndSpawn();
  arduboy.display();
}

void stateDead() {
  // TODO
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM mainGameLoop[] = {
  stateBanner,
  stateIntro,
  stateStart,
  statePlaying,
  stateDead,
};

#endif
