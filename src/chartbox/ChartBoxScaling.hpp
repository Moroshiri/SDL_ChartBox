#ifndef _ChartBoxScaling_hpp_
#define _ChartBoxScaling_hpp_

#include "ChartBoxParameters.hpp"
#include "../Utiles.hpp"

class ChartBoxScaling
{
public:
    ChartBoxScaling();
    ~ChartBoxScaling();

    static Point scaleLinear(FPoint, ChartParameters);
    static Point scaleSemilogX(FPoint, ChartParameters);
    static Point scaleSemilogY(FPoint, ChartParameters);
    static Point scaleLogLog(FPoint, ChartParameters);

private:
    

};

#endif