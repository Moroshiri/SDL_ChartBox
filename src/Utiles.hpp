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

/**
 * Average of values
 * \param value Array of values
 * \param count Count of element in array
 * \returns Average of values in array
*/
float mean(float* values, unsigned int count);

/**
 * Average of points coordinates.
 * WARNING
 * Averaging x and y values!
 * \param pts Array of points
 * \param count Count of element in array
 * \returns Average of points coordinates in array
*/
FPoint mean(FPoint* pts, unsigned int count);

/**
 * Minimum of values
 * \param values Array of values
 * \param count Count of elements in array
 * \returns Minimum od values
*/
float min(float* values, unsigned int count);

/**
 * Maximum of values
 * \param values Array of values
 * \param count Count of elements in array
 * \returns Maximum od values
*/
float max(float* values, unsigned int count);

/**
 * Minimum of y values of points in array
 * \param pts Array of points
 * \param count Count of element in array
 * \returns Minimum y value
*/
FPoint min(FPoint* pts, unsigned int count);

/**
 * Maximum of y values of points in array
 * \param pts Array of points
 * \param count Count of element in array
 * \returns Maximum y value
*/
FPoint max(FPoint* pts, unsigned int count);

#endif