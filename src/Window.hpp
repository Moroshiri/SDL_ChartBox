#ifndef _Window_hpp_
#define _Window_hpp_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Error.hpp"
#include "IRenderable.hpp"
#include "Types.hpp"

#define WND_INIT_DEFAULT (0) // Init without SLD_image
#define WND_INIT_IMAGE (1)  // Init with SDL_image

const int DEFAULT_SCREEN_WIDTH = 800;
const int DEFAULT_SCREEN_HEIGHT = 600;

typedef void (*printHandle)(std::string);

class Window : public Error
{
public:

    Window();
    Window(int width, int height, std::string title);
    Window(Size win_size, std::string title);
    
    ~Window();

    static float ScreenScale;

    // Inicjalizuje okno programu i renderer
    bool Init(int initFlags);

    //void Render(SDL_Texture* tex, SDL_Rect* rect);
    void Render();
    void AddToRenderList(IRenderable* element);

    SDL_Renderer* GetRenderer();
    Point GetCenter();
    Size GetSize();

    static printHandle Print;

private:
    int _screen_width, _screen_height;
    std::string _window_title;

    IRenderable **_renderList;
    uint32_t _renderListPointer;

    SDL_Window *_window;

    SDL_Renderer *_renderer;

};


#endif