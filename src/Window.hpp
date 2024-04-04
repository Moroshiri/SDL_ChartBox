#ifndef _Window_hpp_
#define _Window_hpp_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Error.hpp"
#include "IRenderable.hpp"
#include "Utiles.hpp"

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

    // Value for windo screen scaling
    static float screenScale;

    // Inicjalizuje okno programu i renderer
    bool init(int initFlags);

    // Begins the event handling loop
    void run();

    // Stops the event handling loop
    void stop();

    // Render the window
    void render();

    // Add a reference to IRenderable objects for rendering
    void addToRenderList(IRenderable* element);

    // Get pointer to SDL_Renderer struct
    SDL_Renderer* getRenderer();

    // Get center of window
    Point getCenter();

    // Get size of window
    Size getSize();

    // Referende to print function
    static printHandle print;
private:
    void handleEvents();
    
    int _screen_width, _screen_height;
    std::string _window_title;

    IRenderable **_renderList;
    uint32_t _renderListPointer;

    SDL_Window *_window;
    SDL_Renderer *_renderer;

    bool _running;
};


#endif