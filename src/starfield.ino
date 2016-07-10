#include <Arduboy.h>
#include <avr/pgmspace.h>

#include "tank.h"
#include "bat.h"
#include "pew.h"
#include "boom.h"
#include "banner.h"

Arduboy arduboy;

/*
 * X and Y positions on the display are from the top left corner, thus a Y of 64 is the bottom of the screen and an X of 128 is the right side of the screen.
 * "Color" or "value" means choosing whether a pixel is lit or not - if color is 0, the pixel is off (black), if color is 1, the pixel is on (white).
 */

const uint8_t frameRate = 60;
const uint8_t screenWidth = 128;
const uint8_t screenHeight = 64;

uint8_t spriteSizePx = 8;

boolean gameStarted = false;
uint16_t score = 0;

struct t_tank {
  uint8_t X;
  uint8_t Y;
  uint8_t idleAnimationFrame;
};
t_tank player = {16, 48, 0};

const uint8_t shootCooldown = 30;
uint8_t currentShotCooldown = 0;

const uint8_t maxEnemies = 20;
const uint8_t numBats = 3;

const uint16_t spawnRate = 5 * frameRate;
const uint8_t pointsPerWave = 15;
struct t_spaceBat {
  uint8_t X;
  uint8_t Y;
  boolean isActive;
  uint8_t idleAnimationFrame;
  uint8_t hitAnimationFrame;
};

t_spaceBat spaceBats[maxEnemies];

t_spaceBat *currentHitSpaceBat;

// The year is 20XX
// War is beginning
// Dracula takes to the stars
// Man your tank for great honor
// ... (boop boop boop)
// ...and survival
void setup() {
  // put your setup code here, to run once:
  arduboy.beginNoLogo();
  arduboy.setFrameRate(frameRate);
}

void loop() {
  if (!arduboy.nextFrame()) { return; }
  arduboy.clear();

  if (!gameStarted) {
    arduboy.drawBitmap(0, 0, banner[0], screenWidth, screenHeight, WHITE);
    arduboy.display();

    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
      arduboy.initRandomSeed();
      initEnemies();
      gameStarted = true;
    }
    return;
  }

  handleInput();
  drawStarField();
  drawShootyShootyBoom();
  drawBats();
  drawTank();
  drawScoreAndSevenYearsAgo();
  advanceEnemies();
  sweepAndSpawn();
  arduboy.display();
}

void initEnemies() {
  for (int i = 0; i < maxEnemies; i++) {
    spaceBats[i] = {0, 0, false, i % 3, 0};
  }
  for (int i = 0; i < numBats; i++) {
    spawnBat(&spaceBats[i]);
  }
}

void handleInput() {
  if (arduboy.pressed(UP_BUTTON)) {
      arduboy.setCursor(62, 4);

      if (player.Y > 0) {
        player.Y--;
      }
  }

  if (arduboy.pressed(DOWN_BUTTON)) {
      arduboy.setCursor(62, 52);

      if (player.Y < screenHeight - spriteSizePx) {
        player.Y++;
      }
  }

  if (arduboy.pressed(LEFT_BUTTON)) {
      arduboy.setCursor(30, 30);

      if (player.X > 0) {
        player.X--;
      }
  }

  if (arduboy.pressed(RIGHT_BUTTON)) {
      arduboy.setCursor(92, 30);

      if (player.X < screenWidth - spriteSizePx) {
        player.X++;
      }
  }

  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
      arduboy.setCursor(1, 1);
      arduboy.print(F("LASER!"));
      if (currentShotCooldown == 0 ) {
        currentShotCooldown = shootCooldown;
      }
  }
}

void drawScoreAndSevenYearsAgo() {
  arduboy.setCursor(116, 1);
  char scoreBuffer[16];
  sprintf(scoreBuffer, "%d", score);
  arduboy.print(scoreBuffer);
}

void drawTank() {
  arduboy.drawBitmap(player.X, player.Y, tank[player.idleAnimationFrame], spriteSizePx, spriteSizePx, WHITE);

  if (arduboy.everyXFrames(16)) {
    player.idleAnimationFrame++;
    player.idleAnimationFrame = player.idleAnimationFrame % 3;
  }
}

void spawnBat(t_spaceBat *spaceBat) {
  spaceBat->X = rand() % 48 + 64;
  spaceBat->Y = rand() % (64 - spriteSizePx);
  spaceBat->isActive = true;
}

void drawBats() {
  for (int i = 0; i < numBats; i++) {
    t_spaceBat *spaceBat = &spaceBats[i];
    if (arduboy.everyXFrames(24)) {
      spaceBat->idleAnimationFrame++;
      spaceBat->idleAnimationFrame = spaceBat->idleAnimationFrame % 2;
    }

    if (spaceBat->isActive) {
      arduboy.drawBitmap(spaceBat->X, spaceBat->Y, bat[spaceBat->idleAnimationFrame], spriteSizePx, spriteSizePx, WHITE);
    }

    // draw explosion over hit bat
    if (currentHitSpaceBat && currentHitSpaceBat->hitAnimationFrame > 0) {
      arduboy.drawBitmap(
          currentHitSpaceBat->X - 4,
          currentHitSpaceBat->Y - 4,
          boom[5 - currentHitSpaceBat->hitAnimationFrame],
          16, 16, WHITE
        );

      currentHitSpaceBat->hitAnimationFrame--;

      if (currentHitSpaceBat->hitAnimationFrame == 0) {
        currentHitSpaceBat->isActive = false;
      }
    }
  }
}

void drawShootyShootyBoom() {
  if (currentShotCooldown > 0) {
    if (currentShotCooldown == shootCooldown) {
      currentHitSpaceBat = NULL;
    }

    if (currentShotCooldown > 20) {
      int laserY = player.Y + 3;
      int laserWidth = screenWidth - (player.X + spriteSizePx);

      if (!currentHitSpaceBat) {
        for (int i = 0; i < numBats; i++) {
          t_spaceBat *spaceBat = &spaceBats[i];
          if (!spaceBat->isActive) { continue; }
          if (laserY >= spaceBat->Y + 2 && laserY <= spaceBat->Y + 6) {
            laserWidth = spaceBat->X - (player.X + spriteSizePx) + 2;
            spaceBat->hitAnimationFrame = 5;
            currentHitSpaceBat = spaceBat;
            score++;
          }
        }
      } else {
        laserWidth = currentHitSpaceBat->X - (player.X + spriteSizePx) + 2;
      }

      arduboy.drawFastHLine(player.X + spriteSizePx, laserY, laserWidth, WHITE);
      if (currentShotCooldown > 21) {
        arduboy.drawBitmap(player.X + spriteSizePx, player.Y, pew[(30 - currentShotCooldown) / 3], spriteSizePx, spriteSizePx, WHITE);
      }
    }

    currentShotCooldown--;
  }
}

void advanceEnemies() {
  for (int i = 0; i < numBats; i++) {
    t_spaceBat *spaceBat = &spaceBats[i];
    if (arduboy.everyXFrames(10)) {
      if (spaceBat->isActive) {
        spaceBat->X--;
        if (spaceBat->X <= 0) { spaceBat->X = screenWidth; }
      }
    }

    if (arduboy.everyXFrames(30)) {
      if (spaceBat->isActive) {
        spaceBat->Y++;
        if (spaceBat->Y > screenHeight) { spaceBat->Y = 0; }
      }
    }
  }
}

void sweepAndSpawn() {
  if (arduboy.everyXFrames(spawnRate)) {
      uint8_t spawnedThisWave = 0;
      uint8_t maxToSpawn = score - 3 * (score / pointsPerWave);
      for (int i = 0; i < maxEnemies; i++) {
        t_spaceBat *spaceBat = &spaceBats[i];
        if (!spaceBat->isActive && spawnedThisWave <= maxToSpawn) {
          spawnBat(spaceBat);
          spawnedThisWave++;
        }
      }
  }
}

byte movingStar[11][2] = {{84, 9}, {67, 14}, {109, 19}, {27, 24}, {9, 29}, {96, 34}, {31, 39}, {45, 44}, {82, 49}, {19, 54}, {57, 59}};
byte fastMovingStar[11][2] = {{16, 10}, {125, 15}, {62, 20}, {79, 25}, {115, 30}, {104, 35}, {16, 40}, {117, 45}, {65, 50}, {98, 55}, {23, 60}};
byte stillStar[11][2] = {{84, 7}, {67, 12}, {109, 17}, {27, 22}, {9, 27}, {96, 32}, {31, 37}, {45, 42}, {82, 47}, {19, 52}, {57, 57}};

void drawStarField()
{
  for (byte i = 0; i < 11; i++)
  {
    if (arduboy.everyXFrames(1))
    {
      fastMovingStar[i][0]--;
      if (fastMovingStar[i][0] < 1) fastMovingStar[i][0] = 127;
      arduboy.drawPixel(fastMovingStar[i][0], fastMovingStar[i][1], WHITE);
    }

    if (arduboy.everyXFrames(2))
    {
      movingStar[i][0]--;
      if (movingStar[i][0] < 1) movingStar[i][0] = 127;
      arduboy.drawPixel(movingStar[i][0], movingStar[i][1], WHITE);
    }

    if (arduboy.everyXFrames(3))
    {
      stillStar[i][0]--;
      if (stillStar[i][0] < 1) stillStar[i][0] = 127;
      arduboy.drawPixel(stillStar[i][0], stillStar[i][1], WHITE);
    }

  }
}

