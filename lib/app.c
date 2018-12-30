#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <emscripten.h>

#define NUM_CIRCLES 500

struct Circle
{
  int x;
  int y;
  int r;
  int cr;
  int cg;
  int cb;
};

struct CircleAnimationData
{
  int x;
  int y;
  int r;
  int vx;
  int vy;
  int dx;
  int dy;
};

struct Circle circles[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

int getRand(max)
{
  return (rand() % max);
}

int main()
{

  srand(time(NULL));

  for (int i = 0; i < NUM_CIRCLES; i++)
  {
    int radius = getRand(40);

    int x = getRand(40 + radius);
    int y = getRand(40 + radius);

    animationData[i].x = x;
    animationData[i].y = y;
    animationData[i].r = radius;
    animationData[i].vx = getRand(10);
    animationData[i].vy = getRand(10);
    animationData[i].dx = 1;
    animationData[i].dy = 1;

    circles[i].x = x;
    circles[i].y = y;
    circles[i].r = radius;
    circles[i].cr = getRand(255);
    circles[i].cg = getRand(255);
    circles[i].cb = getRand(255);
  }

  EM_ASM({ render($0, $1); }, NUM_CIRCLES * 6, 6);
}

struct Circle *getCircles(int canvasWidth, int canvasHeight)
{
  for (int i = 0; i < NUM_CIRCLES; i++)
  {
    if (animationData[i].x + animationData[i].r >= canvasWidth)
      animationData[i].dx = 0;
    if (animationData[i].x - animationData[i].r <= 0)
      animationData[i].dx = 1;
    if (animationData[i].y + animationData[i].r >= canvasWidth)
      animationData[i].dy = 0;
    if (animationData[i].y - animationData[i].r <= 0)
      animationData[i].dy = 1;

    if (animationData[i].dx == 1)
    {
      animationData[i].x += animationData[i].vx;
    }
    else
    {
      animationData[i].x -= animationData[i].vx;
    }

    if (animationData[i].dy == 1)
    {
      animationData[i].y += animationData[i].vy;
    }
    else
    {
      animationData[i].y -= animationData[i].vy;
    }

    circles[i].x = animationData[i].x;
    circles[i].y = animationData[i].y;
  }
  return circles;
}