#include "Window.hpp"
#include "Types.hpp"

// ==================
// == Constructors ==
// ==================

Window::Window()
{
    _screen_width = DEFAULT_SCREEN_WIDTH;
    _screen_height = DEFAULT_SCREEN_HEIGHT;

    _window_title = "SDL";

    _renderListPointer = 0;

    _renderList = new IRenderable*();
}

Window::Window(int width, int height, std::string title) : Window()
{
    _screen_width = width;
    _screen_height = height;

    _window_title = title;
}

Window::Window(Size size, std::string title) : Window(size.w, size.h, title)
{ }

// ===================
// == Deconstructor ==
// ===================

Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    delete _renderList;
}

// ===================
// == Static Fields ==
// ===================

float Window::screenScale = 1;
printHandle Window::print = nullptr;

// =============
// == Methods ==
// =============

bool Window::init(int initFlags)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        _errorMsg = ErrorMsg("SDL library initialising error: ") + ErrorMsg(SDL_GetError());
        _errorCode = ERROR_WINDOW_SDLINIT;
        return false;
    }
    
    _window = SDL_CreateWindow(_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_width, _screen_height, SDL_WINDOW_SHOWN);
    if(_window == NULL)
    {
        _errorMsg = ErrorMsg("Window creation error: ") + ErrorMsg(SDL_GetError());
        _errorCode = ERROR_WINDOW_WINCREATION;
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if(_renderer == NULL)
    {
        _errorMsg = ErrorMsg("Renderer creation error: ") + ErrorMsg(SDL_GetError());
        _errorCode = ERROR_WINDOW_RENDCREATION;
        return false;
    }
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    if(initFlags & WND_INIT_IMAGE)
    {
        if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
        {
            _errorMsg = ErrorMsg("SDL_Image library initialising error: ") + ErrorMsg(SDL_GetError());
            _errorCode = ERROR_WINDOW_IMGINIT;
            return false;
        }
    }

    return true;
}

void Window::run()
{
    _running = true;
    while(_running)
    {
        handleEvents();
    }
}

void Window::stop()
{
    _running = false;
}

void Window::handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
            case SDL_QUIT:
                stop();
            break;

            case SDL_KEYDOWN:
                stop();
            break;

            default:
                if (e.type != SDL_MOUSEMOTION && e.type != SDL_MOUSEBUTTONDOWN && e.type != SDL_MOUSEBUTTONUP)
                {
                    // char *str = new char[32];
                    // sprintf(str, "Unhandled event: %d", e.type);
                    // print(std::string(str));
                }
            break;
        }
    }
}

void Window::addToRenderList(IRenderable* element)
{
    if (_renderListPointer == 0)
    {
        _renderList[0] = element;
        _renderListPointer++;
    }
    else
    {
        IRenderable **tmp = _renderList;
        _renderList = new IRenderable*[_renderListPointer + 1];
    
        for (uint32_t i = 0; i < _renderListPointer; i++)
            _renderList[i] = tmp[i];
        
        _renderList[_renderListPointer] = element;
        _renderListPointer++;
        delete tmp;
    }
}

//void Window::Render(SDL_Texture* tex, SDL_Rect* rect)
void Window::render()
{
    SDL_SetRenderDrawColor(_renderer, COLOR_WHITE);
    SDL_RenderClear(_renderer);

    // Render entities from the list
    if(_renderListPointer != 0)
    for(uint32_t i = 0; i < _renderListPointer; i++)
    {
        //Print(std::string("renderList ") + toString(i) + std::string(": ") + toString((int)_renderList[i]));
        _renderList[i]->render(_renderer);
    }
    // SDL_Rect rect = obj.GetRect();
    // SDL_RenderCopy(_renderer, obj.GetTexture()->GetSDLTexture(), NULL, &rect);

    SDL_RenderPresent(_renderer);
    //SDL_UpdateWindowSurface(_window);
}

// =================
// == Get Methods ==
// =================

SDL_Renderer* Window::getRenderer()
{
    return _renderer;
}

Point Window::getCenter()
{
    int w, h;
    SDL_GetWindowSizeInPixels(_window, &w, &h);
    Point res;
    res.x = w/2;
    res.y = h/2;
    return res;
}

Size Window::getSize()
{
    Size res;
    SDL_GetWindowSizeInPixels(_window, &res.w, &res.h);
    return res;
}