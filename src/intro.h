#ifndef INTRO_H
#define INTRO_H

#include "globals.h"

#define INTRO_MESSAGE_COUNT 6
#define INTRO_MESSAGE_DURATION 120

const char *introMessages[] = {
  "The year is 20XX",
  "War is beginning",
  "Dracula takes\n   to the stars",
  "Man your tank\n   for great honor",
  "...",
  "...and survival!"
};

const byte introMusic[] = {
  0x10, 0x12, 0x14, 0x15, 0x17
};

uint8_t introMessage = 0;
boolean introFinished = false;
uint8_t introFrameCount = 0;

void initIntro() {
  introMessage = 0;
  introFinished = false;
  arduboy.setTextSize(1);
  arduboy.setTextWrap(true);

  arduboy.audio.on();
  arduboy.tunes.playScore(introMusic);
}

void drawIntro() {
  introFrameCount++;
  if(arduboy.everyXFrames(INTRO_MESSAGE_DURATION)) { introMessage++; }
  if(introMessage >= INTRO_MESSAGE_COUNT) { introFinished = true; }
  if(introFrameCount > FRAMERATE &&
      (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON))) {
    introFinished = true;
    arduboy.audio.off();
  }

  if(!introFinished) {
    arduboy.setCursor(18, 20);
    arduboy.print(introMessages[introMessage]);
  }
}

#endif
