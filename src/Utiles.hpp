#ifndef _Utiles_hpp_
#define _Utiles_hpp_

#include "Types.hpp"
#include "Error.hpp"

/**
* Loads data from CSV file to FPoint array
* 
* Data in file should be organised in proper way:
* column 1 - X axis
* column 2 - Y axis
* 
* \param file Path to *.csv file
* \param count Count of elements in array
* \returns nullptr if fails, pointer to FPoint array if successful
*/
FPoint* loadDataCSV(const char* file, unsigned int* count);

int SDL_SetRenderDrawColor(SDL_Renderer* rend, Color color);


#endif