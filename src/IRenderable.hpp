#ifndef _Entity_hpp_
#define _Entity_hpp_

#include <SDL2/SDL.h>

class IRenderable
{
public:
    virtual void Render(SDL_Renderer*) = 0;
};

#endif