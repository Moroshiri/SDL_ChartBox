#include "Window.hpp"
#include "ChartBox.hpp"
#include <iostream>
#include <fstream>

void print(std::string);
void printError(Error);

// static FPoint testData[] {
//                     FPoint(0.0,0.0),
//                     FPoint(1.0,1.0),
//                     FPoint(2.0,10.0),
//                     FPoint(3.0,3.0),
//                     FPoint(4.0,1.0),
//                     FPoint(5.0,7.0),
//                     FPoint(6.0,5.0),
//                     FPoint(7.0,0.0),
//                     FPoint(8.0,1.0),
//                     FPoint(9.0,5.0) };
const char* dataPath = "assets/data/spectrum.csv";

int main(int argv, char** args)
{
    Window wnd = Window();
    Window::print = print;
    Error::PrintError = printError;
    ChartBox chart = ChartBox();
    
    unsigned int dataCount;
    FPoint* data = loadDataCSV(dataPath, &dataCount);
    if(data == nullptr)
    {
        printError(Error(ERROR_DATA_LOAD, "Unable to load data from file!"));
        return -1;
    }
    chart.setPoints(data, dataCount);

    if(!wnd.init(WND_INIT_DEFAULT))
    {
        printError(wnd.GetError());
        return -1;
    }

    wnd.addToRenderList(&chart);
    wnd.render();
    wnd.run();

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
