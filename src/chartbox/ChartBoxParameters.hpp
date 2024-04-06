#ifndef _ChartBoxParameters_hpp_
#define _ChartBoxParameters_hpp_

#include "../Utiles.hpp"

enum ChartType
{
    CBX_LINEAR,
    CBX_SEMILOG_X,
    CBX_SEMILOG_Y,
    CBX_LOGLOG
};

enum ChartDataReducingMethod
{
    CDR_REJECT,  // Rejection method
    CDR_AVERAGE, // Averaging method
    CDR_MINMAX   // Pulling minimum and maximum values
};

struct ChartParameters
{
    ChartParameters() : 
        box(),
        lineColor(COLOR_BLACK), 
        type(CBX_LINEAR), 
        xMin(0.0), xMax(0.0), 
        yMin(0.0), yMax(0.0), 
        grid(true),
        autoLimits(true),
        reducingMethod(CDR_MINMAX)
    { }
    Rect box;
    Color lineColor;
    ChartType type;
    float xMin, xMax;
    float yMin, yMax;
    bool grid;
    bool autoLimits;
    ChartDataReducingMethod reducingMethod;
};

#endif