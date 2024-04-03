#ifndef _Types_hpp_
#define _Types_hpp_

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 672;
const int SCREEN_HEIGHT = 992;
const float SCREEN_RATIO = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
inline float SCREEN_SCALE;

// Structure that defines a point
struct Point
{
    Point() : x(0), y(0)
    { }
    Point(int x, int y) : x(x), y(y)
    { }
    int x, y;
};

// Structure that defines a point (floating point values)
struct FPoint
{
    FPoint() : x(0), y(0)
    { }
    FPoint(float x, float y) : x(x), y(y)
    { }
    float x, y;
};

// Structure that defines a size
struct Size
{
    Size() : w(0), h(0)
    { }
    Size(int w, int h) : w(w), h(h) 
    { }
    int w, h;
};

// Structure that defines a rectangle
struct Rect
{
    Rect() : w(0), h(0), x(0), y(0)
    { }
    Rect(int w, int h, int x, int y) : w(w), h(h), x(x), y(y)
    { }
    int w, h;
    int x, y;
};

struct Color
{
    Color() : r(0), g(0), b(0), a(0)
    { }
    Color(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b), a(255)
    { }
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a)
    { }
    Uint8 r, g, b, a;
};

const Color COLOR_WHITE = Color(255, 255, 255);
const Color COLOR_RED   = Color(255, 0, 0);
const Color COLOE_GREEN = Color(0, 255, 0);
const Color COLOR_BLUE  = Color(0, 0, 255);
const Color COLOR_CYAN  = Color(0, 255, 255);
const Color COLOR_MAGENTA = Color(255, 0, 255);
const Color COLOR_YELLOW = Color(255, 255, 0);
const Color COLOR_BLACK = Color(0, 0, 0);
const Color COLOR_GRAY  = Color(100, 100, 100);

#endif