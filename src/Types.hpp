#ifndef _Types_hpp_
#define _Types_hpp_

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 672;
const int SCREEN_HEIGHT = 992;
const float SCREEN_RATIO = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
inline float SCREEN_SCALE;

typedef SDL_Point Point;

struct Size
{
    Size() : w(0), h(0)
    { }
    Size(int w, int h) : w(w), h(h) 
    { }
    int w, h;
};

#endif