#include <Arduboy.h>
#include <avr/pgmspace.h>

#include "globals.h"
#include "state.h"

void setup() {
  arduboy.beginNoLogo();
  arduboy.setFrameRate(FRAMERATE);
}

void loop() {
  if (!(arduboy.nextFrame())) return;

  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}
