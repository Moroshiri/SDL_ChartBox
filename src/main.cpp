#include "Window.hpp"
#include "ChartBox.hpp"
#include <iostream>

void print(std::string);
void printError(Error);

int main(int argv, char** args)
{
    Window wnd = Window();
    Window::Print = print;
    Error::PrintError = printError;
    ChartBox chart = ChartBox();

    if(!wnd.Init(WND_INIT_DEFAULT))
    {
        printError(wnd.GetError());
        return -1;
    }

    wnd.AddToRenderList(&chart);

    wnd.Render();

    SDL_Delay(2000);

    return 0;
}

void print(std::string msg)
{
    std::cout << msg << std::endl;
}
void printError(Error err)
{
    std::cout << "An error occurred while the program was running!" << std::endl;
    std::cout << "Code: " << err.GetErrorCode() << std::endl;
    std::cout << "Message: " << err.GetErrorMsg() << std::endl;
}