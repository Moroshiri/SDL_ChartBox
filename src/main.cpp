#include "Window.hpp"
#include "ChartBox.hpp"
#include <iostream>

void print(std::string);
void printError(Error);

static FPoint testData[] {
                    FPoint(0.0,0.0),
                    FPoint(1.0,1.0),
                    FPoint(2.0,10.0),
                    FPoint(3.0,3.0),
                    FPoint(4.0,1.0),
                    FPoint(5.0,7.0),
                    FPoint(6.0,5.0),
                    FPoint(7.0,0.0),
                    FPoint(8.0,1.0),
                    FPoint(9.0,5.0) };

int main(int argv, char** args)
{
    Window wnd = Window();
    Window::Print = print;
    Error::PrintError = printError;
    ChartBox chart = ChartBox();
    chart.setPoints(testData, 10);

    if(!wnd.Init(WND_INIT_DEFAULT))
    {
        printError(wnd.GetError());
        return -1;
    }

    wnd.AddToRenderList(&chart);

    wnd.Render();

    SDL_Delay(5000);

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