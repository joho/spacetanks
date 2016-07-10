#ifndef INTRO_H
#define INTRO_H

#include "globals.h"

#define INTRO_MESSAGE_COUNT = 6
#define INTRO_MESSAGE_DURATION = 120

char introMessages[INTRO_MESSAGE_COUNT][] = {
  "The year is 20XX",
  "War is beginning"
  "Dracula takes to the stars"
  "Man your tank for great honor"
  "..."
  "...and survival!"
};

uint8_t introMessage = 0;
boolean introFinished = false;

void initIntro() {
  introMessage = 0;
  introFinished = false;
  arduboy.setTextSize(1);
  arduboy.setTextWrap(true);
}

void drawIntro() {
  if(arduboy.everyXFrames(INTRO_MESSAGE_DURATION)) introMessage++;
  if(introMessage > INTRO_MESSAGE_COUNT) introFinished = true;

  if(!introFinished) {
    arduboy.setCursor(20, 20);
    arduboy.print(introMessages[introMessage]);
  }
}

#endif
