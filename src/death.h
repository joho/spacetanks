#ifndef DEATH_H
#define DEATH_H

#include "globals.h"
#include "utils.h"

uint8_t deathFrameCount = 0;
char deathMessage[] = "YOU LOSER";

bool isShowingDeathMessage() {
  if (deathFrameCount == 0) {
    startFlashingMessage(deathMessage, 2 * FRAMERATE);
  }

  drawFlashingMessage();

  deathFrameCount++;

  if (deathFrameCount > 3 * FRAMERATE) {
    return false;
  }

  return true;
}

#endif
